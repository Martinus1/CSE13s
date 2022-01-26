#include <math.h>
#include <stdio.h>
#include "insert.h"
#include "stats.h"


void insertion_sort(Stats *stats, uint32_t *A, uint32_t n){
	for (uint32_t i = 1; i < n;  ++i) {
		int j = i;
		uint32_t temp = A[i];
		while (j > 0 && temp < A[j-1]) {
			A[j] = A[j - 1];
			j -= 1;
			stats -> compares += 1;			
		}
		A[j] = temp;
	}

}
