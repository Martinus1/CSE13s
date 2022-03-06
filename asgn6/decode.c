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
        /* fprintf(stderr, "Compressed file is %d bytes\n", ); */
        /* fprintf(stderr, "Normal file is %d bytes\n", ); */
    }

    FILE *infile = fopen(in_file, "r");
    FILE *outfile = fopen(out_file, "w");
}
