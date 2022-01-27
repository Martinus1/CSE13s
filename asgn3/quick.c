#include "quick.h"
#include "stats.h"


//Below is the Quick Sorting Algorithm
//The algorthm functions in a way of choosing a pointer and creating 2 groups regarding to values smaller and higher from that pointer. It does that until the array is sorter
//NOTE: works a bit like binary sort

int partition(Stats *stats, uint32_t *A, int lo, int hi) {
	int i = lo - 1;
	for(int j = lo; j < hi; j += 1) {
		if (cmp(stats, A[hi - 1], A[j - 1]) > 0) {
			i += 1;
			swap(stats, &A[i - 1],&A[j - 1]);
			//uint32_t temp = A[i-1];
			//A[i - 1] = A[j -1];
			//A[j - 1] = temp;
		}
	}
	
	//uint32_t tempa = A[i];
	//A[i] = A[hi - 1];
	//A[hi - 1] = tempa;
	swap(stats, &A[i], &A[hi - 1]);
	return (i + 1);
}

void quick_sorter(Stats *stats, uint32_t *A, int lo, int hi) {
	if  (lo < hi) {
		int p = partition(stats, A, lo, hi);
		//move(stats, p);
		quick_sorter(stats, A, lo, p - 1);
		quick_sorter(stats, A, p + 1 , hi);
	}
}


void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
	quick_sorter(stats, A, 1, n);
}

