#include "quick.h"


int partition(uint32_t *A, int lo, int hi) {
	int i = lo - i;
	for(int j = lo; j < hi; j += 1) {
		if A[j - 1] < A[hi -1] {
			i += 1;
			A[i - 1] = A[j -1];
			A[j - 1] = A[i - 1];
		}
	}

	A[i] = A[hi - 1];
	A[hi - 1] = A[i];
	return i + 1;
}

void quick_sorter(uint32_t *A, int lo, int hi) {
	if lo < hi {
		int p = partition(A, lo, hi);
		quick_sorter(A, lo, pi - 1);
		quick_sorter(A, p + 1 , hi);
	}
}


void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
	quick_sorter(A, 1, sizeof(A));
	
}
