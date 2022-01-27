#include <stdio.h>
#include <stdbool.h>
#include "heap.h"
#include "stats.h"
 
//This is the implementation of the HEAP sorting algorithm
//This algorithm algoritm sorts the values in the array in accordace to heaps, therefore steps, which are intended to check the n-adjacency of a value

int max_child(uint32_t *A, int first, int last){
	int left = 2 * first;
	int right = left + 1;
	if (right <= last && (A[right - 1] > A[left - 1])) {
		return right;
	}
	return left;
}

void fix_heap(uint32_t *A, int first, int last) {
	bool found = false;
	int mother = first;
	int great = max_child(A, mother, last);

	while ((mother <= (last / 2)) && (found == false)) {
		if (A[mother - 1] < A[great - 1]) {
			uint32_t temp = A[mother - 1];
			A[mother - 1] = A[great - 1];
			A[great - 1] = temp;
			mother = great;
			great = max_child(A, mother, last);
		} else {
			found = true;
		}
	}
}

void build_heap(uint32_t *A, int first, int last) {
	for (int father = (last / 2); father < (first - 1); father -= 1)  {
		fix_heap(A, father, last);
	}
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
	int first = 1;
	int last = n;
	build_heap(A, first, last);
	for (int leaf = last; cmp(stats, first, leaf) > 0; leaf -= 1 ) {
		//uint32_t temp = A[first - 1];
		swap(stats, &A[leaf - 1], &A[first - 1]);
		//A[first - 1] = A[leaf - 1];
		//A[leaf - 1] = temp;
		fix_heap(A, first, leaf - 1);
	}
}

