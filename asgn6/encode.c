#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "header.h"
#include "code.h"
#include "io.h"
#include "pq.h"
#include "node.h"
#include "huffman.h"
#include "defines.h"
#include "header.h"
#include "defines.h"


Header create_header(int symbols, int infile, int outfile) {
    Header *header;
    struct stat *statbuf = (struct stat *) malloc(sizeof(stat));

    // Load infile stats into buffer.
    fstat(infile, statbuf);

    // Copy permissions from stat buffer to outfile header
    fchmod(outfile, statbuf->st_mode);

    // Set header values from buffer
    header->tree_size = (3 * symbols) - 1;
    header->permissions = statbuf->st_mode;
    header->magic = MAGIC;
    header->file_size = statbuf->st_size;

    // Deref and return header
    return *header;
}

int main(int argc, char **argv) {

    char *in_file = "stdin";
    char *out_file = "stdout";
    bool isHelp = false;
    bool isVerbose = false;
    char opt;

    while ((opt = getopt(argc, argv, "i:o:vh")) != -1) {
        switch (opt) {
        case 'i':
            //specifies the input file (default: stdin)
            in_file = optarg;
            break;
        case 'o':
            //specifies the input file (default: stdin)
            out_file = optarg;
            break;
        case 'v':
            //Prints compression statistics to stderr.
            isVerbose = true;
            break;
        case 'h':
            //Prints program synopsis/help
            isHelp = true;
            break;
        }
    }

    //print HELP
    if (isHelp) {
        printf("SYNOPSIS:\n");
        printf("---USAGE---\n");
        printf("./decode [options]\n");
        printf(" -i   Specifies the input file\n");
        printf(" -o   Specifies the output file\n");
        printf(" -v   prints compression statistics to stderr\n");
        printf(" -h   prints program synopsis\n");
    }

    //Print Verbose
    if (isVerbose) {
    }

    if (in_file && out_file) {
        printf("Encoding files\n");

        FILE *infile = fopen(in_file, "r");
        int in_file_fd = fileno(infile);
        FILE *outfile = fopen(out_file, "w");
        int out_file_fd = fileno(outfile);

        //1) Compute Histogram of the file - num of unique occurances of each unique symbol in the file
        //create an array of 0s - size 256
        uint64_t histogram[ALPHABET] = { 0 };
        int symbols = 2;

        histogram[0] += 1;
        histogram[255] += 1;

        {
            uint8_t buffer[BLOCK] = { 0 };
            bool done = false;

            while (!done) {
                printf("Reading file chunk.\n");
                int file_bytes_read = read_bytes(in_file_fd, buffer, BLOCK);

                for (int i = 0; i < file_bytes_read; i++) {
                    char symbol = buffer[i];

                    if (histogram[symbol] == 0) {
                        symbols += 1;
                    }

                    histogram[symbol] += 1;

                    printf("%c", buffer[i]);
                }

                if (file_bytes_read < BLOCK) {
                    done = true;
                }
            }
        }

        //2) Construct Huffman tree using computer histogram(requires pq)
        Node *root = build_tree(histogram);

        //3) Construct a code table. Each index of the table represents a symbol and the value at th    at index the symbol’s code. You will need to use a stack of bits and perform a traversal of the Huff    man tree.
        Code table[ALPHABET];
        build_codes(root, table);

        //3.5) Create header and write it to file
        Header header = create_header(symbols, in_file_fd, out_file_fd);
        write_bytes(out_file_fd, (uint8_t *) &header, sizeof(Header));

        //4) Emit an encoding of the Huffman tree to a file. This will be done through a post-order     traversal of the Huffman tree. The encoding of the Huffman tree will be referred to as a tree dump.
        dump_tree(out_file_fd, root);

        //5) Step through each symbol of the input file again. For each symbol, emit its code to the     output file
        {
            rewind(infile);
            uint8_t buffer[BLOCK] = { 0 };
            bool done = false;
            while (!done) {
                int file_bytes_read = read_bytes(in_file_fd, buffer, BLOCK);

                for (int i = 0; i < file_bytes_read; i++) {
                    printf("%c", buffer[i]);
                    write_code(out_file_fd, &table[buffer[i]]);
                }

                if (file_bytes_read < BLOCK) {
                    done = true;
                }
            }
        }

         flush_codes(out_file_fd);
        fclose(outfile);
    } else {
        printf("Invalid input. Please provide an input and output file.\n");
    }

    return 0;
}
