#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <getopt.h>
#include <ncurses.h>
#include <unistd.h>
#include "universe.h"

#define DELAY 50000


int main(int argc, char **argv) {

        uint32_t n = 100;
        bool isToroidal = false;
        bool isNcurses = true;
        int opt = 0;

        while((opt = getopt(argc, argv, "tsn:i:o:")) != -1 ) {
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
                                n = atoi(optarg);
                                break;
                        case 'i':
                                //specifies the read file in order to populate the universe

                                break;
                        case 'o':
                                //specifies the output file to print the final state of the universe
                                break;
                        default:
                                return 1;
                }
        }

        
	if (isNcurses == true) {
	initscr();
	curs_set(FALSE);
	}

	FILE *file = fopen("dat.dat", "r");

	uint64_t row, col;
	fscanf(file, "%" SCNu64 "%" SCNu64 "\n", &row, &col);
        Universe *u = uv_create(row, col, isToroidal);

        uv_populate(u, file);
        //printf("%d\n",uv_cols(u));
        //printf("%d\n",uv_rows(u));

	for(uint32_t i = 0; i < n; i+= 1) {
		if(isNcurses == true) {
			clear();
		}

		//create screen + play game
		for(uint32_t r = 0; r < rows; r += 1) {
			for(uint32_t c = 0; c < col; c+=1 ) {
				int alive = uv_censes(u, r, c);
				
				bool state = uv_get_cell(u,r,c);
				
				if (state == true) {
				//Cell is alive
					if (alive == 2) || (alive == 3) {
						//Cell survives
					} else {
						//Cell Dies
						uv_dead_cell(u, r, c);
					}
				} else if (state == false) {
					if (alive == 3) {
						uv_live_cell(u,r,c);
					}
				}	
			}
		}	

		uv_print(u, )
		
		if(isNcurses == true) {
			refresh();
			usleep(DELAY);
		}
	}
	uv_print(u, stdout);
	endwin();
	uv_delete(u);
        fclose(file);
	
	return 0;
}
