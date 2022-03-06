#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <stdbool.h>

#include "code.h"
#include "io.h"
#include "pq.h"
#include "node.h"
#include "huffman.h"
#include "defines.h"
#include "header.h"

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
        fprintf(stderr, "SYNOPSIS:\n");
        fprintf(stderr, "---USAGE---\n");
        fprintf(stderr, "./decode [options]\n");
        fprintf(stderr, " -i   Specifies the input file\n");
        fprintf(stderr, " -o   Specifies the output file\n");
        fprintf(stderr, " -v   prints compression statistics to stderr\n");
        fprintf(stderr, " -h   prints program synopsis\n");
    }

    //Print Verbose
    if (isVerbose) {
    }

    if (in_file && out_file) {

        FILE *infile = fopen(in_file, "r");
        int in_file_fd = fileno(infile);
        FILE *outfile = fopen(out_file, "w");
        int out_file_fd = fileno(outfile);

        //1) Compute Histogram of the file - num of unique occurances of each unique symbol in the file
        //create an array of 0s - size 256
        uint64_t histogram[ALPHABET] = { 0 };

        histogram[0] += 1;
        histogram[255] += 1;

        {
            uint8_t buffer[BLOCK] = { 0 };
            bool done = false;

            while (!done) {
                int file_bytes_read = read_bytes(in_file_fd, buffer, BLOCK);

                for (int i = 0; i < file_bytes_read; i++) {
                    histogram[buffer[i]] += 1;
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

        //4) Emit an encoding of the Huffman tree to a file. This will be done through a post-order     traversal of the Huffman tree. The encoding of the Huffman tree will be referred to as a tree dump.
        dump_tree(out_file_fd, root);

        //5) Step through each symbol of the input file again. For each symbol, emit its code to the     output file
        {
            uint8_t buffer[BLOCK] = { 0 };
            bool done = false;
            while (!done) {
                int file_bytes_read = read_bytes(in_file_fd, buffer, BLOCK);

                for (int i = 0; i < file_bytes_read; i++) {
                    write_code(out_file_fd, &table[buffer[i]]);
                }

                if (file_bytes_read < BLOCK) {
                    done = true;
                }
            }
        }
    } else {
        fprintf(stderr, "Invalid input. Please provide an input and output file.\n");
    }
}
