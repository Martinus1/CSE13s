#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include "quick.h"
#include "heap.h"
#include "insert.h"
#include "stats.h"
#include "batcher.h"
#include "set.h"
#include "stats.h"


//universal enum/set for sort types
typedef enum {
	INSERT = 0,
	HEAP = 1,
	QUICK = 2,
	BATCH = 3
} Sort;


void usage() {
    printf("SYNOPSIS \n"
	" Collection of comparison-based algortihms \n"
       "\n"
      " USAGE \n"
     " ./sorting [-Haibhqn:p:r:] [-n length] [-p element] [-r seed]  \n "
     "\n"
    " OPTIONS \n"
   " -a shows integration of all sorts \n"
   " -H display Help and usage \n "
   "-i Enable Insertion Sort \n" 
   "-b Enable Batcher Sort \n"
   " -h Enable Heap Sort \n"
   " -q Enable Quick Sort \n"
   "-r Enables random seed for random number generator \n"
  " -n [length] number of array element, default = 100 \n "
  "-p [elements] low low integral starting poin. \n");
}


int main(int argc, char **argv) {
	
	uint32_t n = 100;
	int seed = 13371453;	
	Set s = empty_set();
	
	int opt = 0;
	while((opt = getopt(argc, argv, "ahbiqr:n:p:H")) != -1 ) {
		switch (opt) { 
			case 'a':
				//all sets are selected
				s = complement_set(empty_set());
				break;
			case 'h':
				//Heap sort selected
				s = insert_set(HEAP, s);
				break;
			case 'b':
				//batch sort Selected
				s = insert_set(BATCH, s);
				break;
			case 'i':
				//insertion sort Selected
				s = insert_set(INSERT, s);
				break;
			case 'q':
				//quick sort Selected
				s = insert_set(QUICK, s);
				break;
			case 'r':
				// randomize seed
				seed = rand();
				break;
			case 'n':
				//number of elements in an array
				n = atoi(optarg);
				break;
			case 'p':
				//Specify Number of elements to print
				break;
			case 'H':
				//Show help
				usage();
				return EXIT_FAILURE;
			default:
				usage();
				return 1;
		}
	}


	uint32_t *A = (uint32_t *)malloc(n * sizeof(uint32_t));
	srandom(seed);
	for (uint32_t i = 0; i < n; i += 1) {
		uint32_t val = random();
		uint32_t mask = 0x3fffffff;
		A[i] = (val & mask);
	}

	Stats record;
	reset(&record);
	
	//Below is the directl implementation of the sorting algorithms into my program
	for (Sort i = INSERT; i <= BATCH; i += 1) {
		if(member_set(i, s)) {
			switch(i) {
				case INSERT:
					reset(&record);
					insertion_sort(&record, A, n);
					printf("Insertion Sort, ");
					printf("%u elements, ", n);
					printf("%lu moves, ", record.moves);
					printf("%lu compares, \n ", record.compares);
					for(uint32_t v = 0; v < n; v ++) {
						printf("%u     ", A[v]);
						if (((v + 1) % 5 == 0)) {
							printf("\n");
						}
					}

					printf("\n");
					
					break;
				case HEAP:
					reset(&record);
					heap_sort(&record, A, n);
					printf("Heap Sort, ");
                                        printf("%u elements, ", n);
                                        printf("%lu moves, ", record.moves);
                                        printf("%lu compares, \n ", record.compares);
                                       	for(uint32_t v = 0; v < n; v ++) {
                                                printf("%u     ", A[v]);
                                                if (((v + 1) % 5 == 0)) {
                                                        printf("\n");
                                                }
                                        }

                                        printf("\n");


					break;
				case QUICK:
					reset(&record);
	                                quick_sort(&record, A, n);
                                        printf("Quick Sort, ");
                                        printf("%u elements, ", n);
                                        printf("%lu moves, ", record.moves);
                                        printf("%lu compares, \n ", record.compares);
                                        for(uint32_t v = 0; v < n; v ++) {
                                                printf("%u     ", A[v]);
                                                if (((v + 1) % 5 == 0)) {
                                                        printf("\n");
                                                }
                                        }

                                        printf("\n"); 
					break;
				case BATCH:
					reset(&record);
                                        batcher_sort(&record, A, n);
                                        printf("Batcher Sort, ");
                                        printf("%u elements, ", n);
                                        printf("%lu moves, ", record.moves);
                                        printf("%lu compares, \n ", record.compares);
                                        for(uint32_t v = 0; v < n; v ++) {
                                        	printf("%u \t", A[v]);
                                        	if (((v + 1) % 5 == 0)) {
							printf("\n");
						}
					}


					printf("\n");
					break;
				default:
					break;
			}
		}
	
	}
	free(A);
}

