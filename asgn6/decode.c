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

    // 1) Read Header from infile and verify the magic number
    // If magic number does not match 0xBEEFBBAD, the invalid file was passed
    // Display error message and quit

    if (in_file && out_file) {
          printf("Decoding files\n");
 
          FILE *infile = fopen(in_file, "r");
          int in_file_fd = fileno(infile);
          FILE *outfile = fopen(out_file, "w");
          int out_file_fd = fileno(outfile);	
	 
	  Header h;
	  read_bytes(in_file_fd, (uint8_t *) h, sizeof(Header));
	  
	  if (h->magic != MAGIC) {
		fprintf(stderr, "Magic number is not the same as in header file\n");	
	  } 	
//2) permissions filed in the header indicated the permissions that outfile should be set to. Set it with fchmod(int filedes, mode_t mode)
	fchmod(out_file_fd, h->permissions);
	
	//3) the size of the dumped tree is given by tree_size field in header
	// Read Dumped tree from infile into an array tree_size bytes long
	// reconstruct Huffman tree using rebuild_tree()
	//rebuild_tree(h->tree_size, );
	

	//4) Read infile one bit at a time using read_bit(). You will be traversing down the tree one link ata time for each bit that is read.
	
	
	// 5) close infile and outfile
	fclose(infile);
	fclose(outfile);
	
     } else {
        printf("Invalid input. Please provide an input and output file.\n");
     }

 return 0;	


}
