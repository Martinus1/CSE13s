#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "salts.h"
#include "speck.h"
#include "bf.h"
#include "bv.h"

struct BloomFilter {
	uint64_t primary[2];
	uint64_t secondary[2];
	uint64_t tertiary[2];
	BitVector *filter;	
};

BloomFilter *bf_create(uint32_t size) {
	BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
	bf->primary[2] = (uint64_t) {SALT_PRIMARY_LO, SALT_PRIMARY_HI};	
	bf->secondary[2] = (uint64_t) {SALT_SECONDARY_LO, SALT_SECONDARY_HI};
	bf->tertiary[2] = (uint64_t) {SALT_TERTIARY_LO, SALT_TERTIARY_HI};
	bf->filter = (BitVector *) calloc(size, sizeof(BitVector *));

	return bf;
}

void bf_delete(BloomFilter **bf) {
	if (*bf) {
		free((*bf)->primary);
		free((*bf)->secondary);
		free((*bf)->tertiary);
		free(*bf);
		*bf = NULL;	
	}
	return;
}

uint32_t bf_size(BloomFilter *bf) {
	//Return the size of the bit vector
	return sizeof(bf->filter);
}

void bf_insert(BloomFilter *bf, char *word) {
	//insert 'word' into bloom filter, this entails hashing word with each of the three indices stting the bigs at those indices i nthe underlying bit vector
	uint32_t hash_one = hash(bf->primary, word);
	uint32_t hash_two = hash(bf->secondary, word);	
	uint32_t hash_three = hash(bf->tertiary, word);	
	
	bv_set_bit(bf->filter, hash_one);
	bv_set_bit(bf->filter, hash_two);
	bv_set_bit(bf->filter, hash_three);

	return;
}

bool bf_probe(BloomFilter *bf, char *word) {
	//checks if word esists at every hashed location

	uint32_t hash_one = hash(bf->primary, word);
	uint32_t hash_two = hash(bf->secondary, word);	
	uint32_t hash_three = hash(bf-> tertiary, word);	
	
	bool isLocationOne = bv_get_bit(bf->filter, hash_one);
	bool isLocationTwo = bv_get_bit(bf->filter, hash_two);
	bool isLocationThree = bv_get_bit(bf->filter, hash_three);

	if (isLocationOne && isLocationTwo && isLocationThree) {
		return true;
	} 

	return false;
	
}


//void bf_print(BloomFilter *bf) {
//	prinf("Debug Bloom Filter, %");
//}
