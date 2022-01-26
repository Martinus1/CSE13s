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

typedef enum {
	INSERT = 0,
	HEAP = 1,
	QUICK = 2,
	BATCH = 3
} Sort;



int main(int argc, char **argv) {
	
	uint32_t n = 100;
	int seed = 13371453;	
	Set s = empty_set();
	
	int opt = 0;
	while((opt = getopt(argc, argv, "ahbiqr:n:p:H")) != -1 ) {
		switch (opt) { 
			case 'a':
				s = complement_set(empty_set());
				break;
			case 'h':
				s = insert_set(HEAP, s);
				break;
			case 'b':
				s = insert_set(BATCH, s);
				break;
			case 'i':
				s = insert_set(INSERT, s);
				break;
			case 'q':
				s = insert_set(QUICK, s);
				break;
			case 'r':
				seed = rand();
				break;
			case 'n':
				n = atoi(optarg);
				break;
			case 'p':
				break;
			case 'H':
				break;
			default:
				fprintf(stderr, "error/n");
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
	record.moves = 0;
	record.compares = 0;

	for (Sort i = INSERT; i <= BATCH; i += 1) {
		if(member_set(i, s)) {
			switch(i) {
				case INSERT:
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

