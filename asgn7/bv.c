
#include <stdbool.h>
#include <stdint.h>

struct BitVector BitVector {
	uint32_t length;
	uint8_t *vector;
}

BitVector *bv_create(uint32_t length) {
	BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
	bv->length = (uint8_t *) calloc(length, sizeof(uint8_t));
	memset(c->vector, 0, sizeof c->vector);
}

void bv_delete(BitVector **bv) {
	if (*bv) {
		free(*bv);
		*bv = NULL;
	}	
}

uint32_t bv_length(BitVector *bv) {
	return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
	
    if (i > bv->length) {
        return false;
    } else {
        c->vector[i / 8] |= (0x1 << i % 8);
        return true;
    }

}

bool bv_clr_bit(BitVector *bv, uint32_t i) {

    if (i > bv->length) {
        return false;
    } else {
        c->vector[i / 8] |= (0x0 << i % 8);
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

void bv_print(BitVector *bv) {
	print("BIT VECTOR DEBUG");
}
