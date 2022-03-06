#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

int main(int argc, char **argv) {

    char *in_file = "stdin";
    char *out_file = "stdout";
    bool isHelp = false;
    bool isVerbose = false;

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

        //Print Help
        if (isHelp == true) {
            fprintf(stderr, "SYNOPSIS:\n");
            fprintf(stderr, "---USAGE---\n");
            fprintf(stderr, "./decode [options]\n");
            fprintf(stderr, " -i   Specifies the input file\n");
            fprintf(stderr, " -o   Specifies the output file\n");
            fprintf(stderr, " -v   prints compression statistics to stderr\n");
            fprintf(stderr, " -h   prints program synopsis\n");
        }

        //Print Verbose output
        if (isVerbose == true) {
            fprintf(stderr, "Compressed file is %d bytes\n", );
            fprintf(stderr, "Normal file is %d bytes\n", );
        }

        FILE *infile = fopen(in_file, "r");
        FILE *outfile = fopen(out_file, "w");

        //1) Compute Histogram of the file - num of unique occurances of each unique symbol in the file
        read_bytes(infile, (uint8_t *) h, (sizeof()));
        //2) Construct Huffman tree using computer histogram(requires pq)

        //3) Construct a code table. Each index of the table represents a symbol and the value at that index the symbol’s code. You will need to use a stack of bits and perform a traversal of the Huffman tree.

        //4) Emit an encoding of the Huffman tree to a file. This will be done through a post-order traversal of the Huffman tree. The encoding of the Huffman tree will be referred to as a tree dump.

        //5) Step through each symbol of the input file again. For each symbol, emit its code to the output file
    }
