#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <getopt.h>
#include <ncurses.h>
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

        FILE *infile = fopen(in_file, "r");
        FILE *outfile = fopen(out_file, "w");

        //1) Compute Histogram of the file - num of unique occurances of each unique symbol in the file
        //create an array of 0s - size 256
        uint64_t histogram[ALPHABET] = { 0 };

        histogram[0] += 1;
        histogram[255] += 1;
        //2) Construct Huffman tree using computer histogram(requires pq)
        Node *root = build_tree(histogram);
        PriorityQueue *pq = pq_create(ALPHABET);
        for (uint8_t i = 0; i <= ALPHABET; i++) {
            if (histogram[i] > 0) {
                Node *node = ("", histogram[i]);
            }
        }

        //3) Construct a code table. Each index of the table represents a symbol and the value at th    at index the symbol’s code. You will need to use a stack of bits and perform a traversal of the Huff    man tree.
        Code c = code_init();

        //Do tree traversal
        //DO I have to check both of them
        if (root->left == NULL && root->right == NULL) {
            //Leaf
            write_bytes(outfile, "L", 1);
            write_bytes(outfile, &room->symbol, 1);
        } else {
            //Not Leaf
            traverse(root->left, outfile);
            traverse(root->right, outfile);
            write_bytes(outfile, "I", 1);
        }

        //4) Emit an encoding of the Huffman tree to a file. This will be done through a post-order     traversal of the Huffman tree. The encoding of the Huffman tree will be referred to as a tree dump.

        //5) Step through each symbol of the input file again. For each symbol, emit its code to the     output file
    }
