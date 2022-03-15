#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "bv.h"

typedef struct BitVector BitVector;

struct  BitVector {
	uint32_t length;
	uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
	BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
	bv->length = length;
	bv->vector = (uint8_t *) calloc(length, sizeof(uint8_t));

	return bv;
}

void bv_delete(BitVector **bv) {
	if (*bv) {
		free(*bv);
		*bv = NULL;
	}
	return;	
}

uint32_t bv_length(BitVector *bv) {
	return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
	
    if (i > bv->length) {
        return false;
    } else {
        bv->vector[i / 8] |= (0x1 << i % 8);
        return true;
    }

}

bool bv_clr_bit(BitVector *bv, uint32_t i) {

    if (i > bv->length) {
        return false;
    } else {
        bv->vector[i / 8] |= (0x0 << i % 8);
        return true;
    }

}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    
    uint32_t n = bv->vector[i / 8];
    uint32_t bit = (n & (1 << i)) >> i;

    if (bit == 1) {
        return true;
    } else {
        return false;
    }
}
/*
void bv_print(BitVector *bv) {
	printf("BIT VECTOR DEBUG");
	return;
}
*/
