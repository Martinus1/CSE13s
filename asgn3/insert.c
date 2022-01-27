#include <math.h>
#include <stdio.h>
#include "insert.h"
#include "stats.h"


void insertion_sort(Stats *stats, uint32_t *A, uint32_t n){
	for (uint32_t i = 1; i < n;  ++i) {
		int j = i;
		uint32_t temp = A[i];
		move(stats, A[i]);
		//cmp(stats, j, 0);
		//cmp(stats, temp, A[j-1]);
		while ( j > 0 && cmp(stats, A[j - 1],temp) > 0) {
			//cmp(stats,temp, A[j - 1]);
			//23cmp(stats, j, 0);
			move(stats, A[j - 1]);
			A[j] = A[j - 1];
			j -= 1;
						
		}
		move(stats,A[j]);
		A[j] = temp;
	}

}
