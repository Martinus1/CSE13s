#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <ncurses.h>
#include "universe.h"

/*
int main(int argc, char **argv) {

        uint32_t n = 100;
        bool isToroidal = false;
        bool isNcurses = true;

        int opt = 0;
        while((opt = getopt(argc, argv, "ts:n:i:o:")) != -1 ) {
                switch (opt) {
                        case 't':
                                //toggle toriodal on
                                isToroidal = true;
                                break;
                        case 's':
                                //Toggle Silence ncurses off
                                isNcurses = false;
                                break;
                        case 'n':
                                //specifies the number of generations
                                n = atoi(optarg)
                                break;
                        case 'i':
                                //specifies the read file in order to populate the universe

                                break;
                        case 'o':
                                //specifies the output file to print the final state of the universe
                                break;
                        default:
                                usage();
                                return 1;
                }
        }
}

*/

int main(void) {
	FILE *file = fopen("dat.dat", "r");
	
	Universe *u = uv_create(30, 30, false);

	uv_populate(u, file);
	//printf("%d\n",uv_cols(u));
	//printf("%d\n",uv_rows(u));
	fclose(file);
	//uv_delete(u);
	
	return 0;

}

