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

	if (isHelp == true) {

        }

        if (isVerbose == true) {

        }
}
