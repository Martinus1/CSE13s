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
	char *ifile;
	bool out_print = false;
	char *ofile;

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
				ifile = optarg;				
                                break;
                        case 'o':
                		//specifies the output file to print the final state of the universe
                		out_print = true;
				ofile = optarg;
		   		break;
                        default:
                                return 1;
                }
        }

	FILE *file = fopen(ifile, "r");

	uint64_t row, col;
	fscanf(file, "%" SCNu64 "%" SCNu64 "\n", &row, &col);
        //Main universe
	Universe *u = uv_create(row, col, isToroidal);
	//Next screen universe
	Universe *b = uv_create(row, col ,isToroidal);

        uv_populate(u, file);
	uv_populate(b, file);
		
 	if (isNcurses == true) {
                initscr();
                curs_set(FALSE);
        }

	for(uint32_t i = 0; i < n; i+= 1) {
		if(isNcurses == true) {
			clear();
		}
		//create screen + play game
		for(uint32_t r = 0; r < row; r += 1) {
			
			for(uint32_t c = 0; c < col; c+=1 ) {
				int alive = uv_census(u, r, c);
				
				bool state = uv_get_cell(u,r,c);
				//Below I commened out the prints I used to test the program, 
				//as well as the ones that print out the cell state
				//fprintf(stdout, "POS = %d %d", r, c);
				//fprintf(stdout, " state: %d",state);
				//fprintf(stdout, " alive n = %d \n", alive);

				if (state == true) {
				//Cell is alive
					if ((alive == 2) || (alive == 3)) {
						//Cell survives
						uv_live_cell(b, r ,c);
						//fprintf(stdout, "Survives\n");
					} else {
						//Cell Dies
						uv_dead_cell(b, r, c);
						//fprintf(stdout, "Dies\n");
					}
				} else if (state == false) {
				//Cell is dead
					if (alive == 3) {
						//Bring to life
						uv_live_cell(b,r,c);
						//fprintf(stdout,"Becomes Alive\n");
					} else {
						//stays dead
						fprintf(stdout, "Stays Dead\n");
						//uv_dead_cell(b ,r ,c);
					}
				}	
			}
		}	
		
		uint32_t rowsc = uv_rows(u);
		uint32_t colsc = uv_cols(u);
		//Generate the output of the live cells on the screen
		for (uint32_t p = 0; p < rowsc; p+= 1) {
			for (uint32_t j = 0; j < colsc; j += 1) {
				bool state = uv_get_cell(u, p, j);
				if (state == true) {
					mvprintw(p, j, "o");
				}
			}
		}

		//Swap Universes		
      		Universe *temp = u;
                u = b;
                b = temp;

		if(isNcurses == true) {
			refresh();
			usleep(DELAY);
		}
		
	}

	endwin();
	if (out_print == true) {
		//print the last universe state in the 'output' file
		FILE *outfile = fopen(ofile, "w");
		uv_print(u,outfile);
		fclose(outfile);
	} else {
		//by default prints the last universe state in console
		uv_print(u, stdout);
	}
	uv_delete(u);
	uv_delete(b);
        fclose(file);

	return 0;
}
