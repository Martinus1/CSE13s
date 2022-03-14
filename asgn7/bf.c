#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

struct BloomFilter BloomFilter {
	uint64_t primary[2];
	uint64_t secondary[2];
	uint64_t tertiary[2];
	BitVector *filter;	
};

BloomFilter *bf_create(uint32_t size) {
	BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
	bf->primary = [SALT_PRIMARY_LO, SALT_PRIMARY_HI];	
	bf->secondary = [SALT_SECONDARY_LO, SALT_SECONDARY_HI];
	bf->tertiary = [SALT_TERTIARY_LO, SALT_TERTIARY_HI];

	return bf;
}

void bf_delete(BloomFilter **bf) {
	if (*bf) {
		free(*bf->primary);
		free(*bf->secondary);
		free(*bf->tertiary);
		free(*bf);
		*bf = NULL;	
	}
	return;
}

uint32_t bf_size(BloomFilter *bf) {
	//Return the size of the bit vector
}

void bf_insert(BloomFilter *bf, char *word) {
	//
}

bool bf_probe(BloomFilter *bf, char *word) {
	
}

void bf_print(BloomFilter *bf) {

}
