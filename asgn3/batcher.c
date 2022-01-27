#include "batcher.h"
#include <stdio.h>
#include "stats.h"

//Below is the batcher algorithm
//This algorithm is linear and always follows a specifici patern of comparing and swapping particular elements in the given array
//It is however linear - no matter how many elements are passed the execution time stays the same

void comparator(Stats *stats, uint32_t *A, int x, int y) {
	if(cmp(stats, A[x], A[y]) > 0) {
		//uint32_t temp = A[x];
		//A[x] = A[y];
		//A[y] = temp;
		move(stats, A[x]);
		move(stats, A[y]);
		swap(stats, &A[x], &A[y]);
	}
}

//The function below was provided by Darrell Long
uint32_t bl(uint32_t n) {
     uint32_t count = 0;
     while (n > 0) {
             count += 1;
             n = n/2;
     }

  return count;
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
	if (n == 0) {
		return;
	}

	uint32_t t = bl(n);
	uint32_t p = 1 << (t - 1);
	move(stats, p);

	while (p > 0) {
		uint32_t q = 1 << (t - 1);
		uint32_t r = 0;
		uint32_t d = p;
		
		move(stats, q);

		while(d > 0) {
			for (uint32_t i = 0; i < (n - d); i += 1) {
				if ( i == r && cmp(stats, p , r) == 0) {
					comparator(stats, A, i, (i + d));
				}
			}
			d = q - p;
			q >>= 1;
			r = p;
			move(stats, q);
			move(stats, r);
			move(stats, d);
		}
		move(stats, p);
		p >>= 1;
	}
}

