#include "batch.h"


void comparator(uint32_t *A, int x, int y) {
	if A[x] > A[y] {
		A[x] = A[y];
		A[y] = A[x];
	}
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
	if (sizeof(A) == 0) {
		return;
	}

	int n = sizeof(A);
	int t = n.bit_length();
	int p = 1 << (t - 1);

	while (p > 0) {
		int q = q << (t - 1);
		int r = 0;
		int d = p;

		while(d > 0) {
			for (int i = 0; i < (n - d); i += 1 ) {
				if (i == r && p == r) {
					comparator(A, i, (i + d));
				}
			}
			d = q - p;
			q >>= 1;
			r = p;
		}
		
		p >>= 1;
	
	}
}
