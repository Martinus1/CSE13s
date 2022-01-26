#include "batcher.h"
#include <stdio.h>

void comparator(uint32_t *A, int x, int y) {
	if(A[x] > A[y]) {
		uint32_t temp = A[x];
		A[x] = A[y];
		A[y] = temp;
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

	while (p > 0) {
		uint32_t q = 1 << (t - 1);
		uint32_t r = 0;
		uint32_t d = p;

		while(d > 0) {
			for (uint32_t i = 0; i < (n - d); i += 1) {
				if (i == r && p == r) {
					comparator(A, i, (i + d));
				}
			}
			d = q - p;
			q >>= 1;
			r = p;
		}
		
		p >>= 1;
		stats -> compares += 1;
	}
}

