#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "universe.h"

//Not Typedef
struct Universe {
	uint32_t rows;
	uint32_t cols;
	bool **grid;
	bool toroidal;
};


Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
	//Create a universe
	bool **matrix = (bool **) calloc(rows, sizeof(bool *));
	for (uint32_t r = 0; r < rows; r += 1) {
		matrix[r] = (bool *) calloc(cols, sizeof(bool));
	}

	Universe *u = (Universe *)malloc(sizeof(Universe));
	u->rows = rows;
	u->cols = cols;
	u->grid = matrix;
	u->toroidal = toroidal;
	return u;
}

void uv_delete(Universe *u) {
	//free up memory
	free(u->grid);
	free(u);
}

uint32_t uv_rows(Universe *u) {
	// return rows
	return u->rows; 
}

uint32_t uv_cols(Universe *u) {
	//return columns
	return u->cols;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
	//Marks cell at row -‘r’ , and column - ‘c’ as live
	if ((r < (u->rows)) && (c < (u->cols))) {
		u->grid[r][c] = 1;
	}
}


void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
	//This function marks the cell of row -‘r’ , and column - ‘c’ as dead
	if ((r < uv_rows(u)) && (c < uv_cols(u))) {
		u->grid[r][c] = 0;
	} else {
		printf("Invalid Cell");
	}
}

bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
	// Returns the state of a cell of row -‘r’ , and column - ‘c’ 
	if ((r < (u->rows)) && (c < (u->cols))) {
		return u->grid[r][c]; 
	}

	return -1;
}

bool uv_populate(Universe *u, FILE *infile) {
	//This is the caller function and will populate the Universe with row-column pairs 
	uint32_t rowsc, colsc;	
	//fscanf(infile, "%d %d\n", &rowsc, &colsc);
        rowsc = uv_rows(u);
	colsc = uv_cols(u);

	//assigns false to all values in the array
        for (int i = 0; (uint32_t)i < rowsc; i+= 1) {
                for (int j = 0; (uint32_t)j < colsc; j += 1) {
                       uv_dead_cell(u, i, j);
                }
        }
	//assigns true to the values specified in the file

	int r, c;
	while (fscanf(infile, "%d %d\n", &r, &c) != EOF) {
		//fscanf(infile, "%d %d\n", &r, &c);
		uv_live_cell(u, r, c);
	}

	return true;
}

uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
	//This function returns the number of live neighbors adjacent to the cell as row ‘r’ and column ‘c’.
	
	uint32_t alive = 0;
	int rowsc = (int)uv_rows(u);
	int colsc = (int)uv_cols(u);
	bool **grd = u->grid;
	
	int row = (int) r;
	int col = (int) c;

	if (u->toroidal == false) {
	 //Normal
		for(int i=row-1; i<=row + 1; i+= 1) {
       			 for(int j=col-1;j<=col + 1;j+= 1) {
				if ((i==row && j==col) || (i>=rowsc) ||(j>=colsc) || ((j < 0) || (i < 0))) {
           		     		continue;
            			}	

            			if(grd[i][j]==1) {
                			alive += 1;
            			}
				
        		}
    		}
	} else {

	//Toroidal
	
		for(int i=row-1; i<=row + 1; i+=1 ) {
			for(int j=col-1; j<=col + 1; j += 1) {
				//if top right
				//if top left
				//if bottom right
				//if bottom right
				//if top
				//if bottom
				//if left
				//if right
				
				if (i==row && j==col) {
					continue;
				}
				
				if(grd[(i + rowsc) % rowsc][(j + colsc) % colsc] == 1) {
					alive += 1;
				}
			}
		}	
	
	}
	return alive;
}

void uv_print(Universe *u, FILE *outfile) {
	//Prints the universe in an ‘outfile’
	uint32_t rowsc = uv_rows(u);
	uint32_t colsc = uv_cols(u);
	bool **grd = u->grid;
	for (uint32_t i = 0; i < rowsc; i+= 1) {
		for (uint32_t j = 0; j < colsc; j += 1) {
			if (grd[i][j] == true) {
				fprintf(outfile, "%s", "o");
			} else if (grd[i][j] == false) {
				fprintf(outfile, "%s", ".");
			}
		}
		fprintf(outfile, "\n");
	}
}

