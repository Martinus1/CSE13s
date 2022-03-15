#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <regex.h>
#include "text.h"
#include "parser.h"

extern uint32_t noiselimit; // Number of noise words to filter out.

struct Text Text {
	HashTable *ht;
	BloomFilter *bf;
	uint32_t word_count;
}

Text *text_create(FILE *infile, Text *noise) {
	//Filter our 'noise' words
	//If sufficient memory cannot be allocated return null
	
	//Pseudocode from Prof. Darrel Long
	regex_t re;
	if(regcomp(&re, WORD, REG_EXTENDED)) {
		printf("Failed to compile regex. \n");
		return NULL;
	}
	
	char *word = NULL;
	while ((word = next_word(*infile, &re)) != NULL) {
		printf("Word: %s \n", word);
	} 
	
	regfree(&re);
	
	uint32_t bf_size = pow(2, 21);
	uint32_t ht_size = pow(2, 19);	

	Text *text = (Text *) malloc(sizeof(Text));
	text->bf = bf_create(bf_size);
	text->ht = ht_create(ht_size);	

	return *Text;
}

void text_delete(Text **text) {
	//Text destructor
	if (*text) {
		free(*text->ht);
		free(*text->bf);
		free(*text);
		*text = NULL;
	}
}

double text_dist(Text *text1, Text *text2, Metric metric) {
//Distance between the two texts depending on the metric being used
	
}

double text_frequency(Text *text, char *word) {
//Returns the frequency of word in a text
//If word is not in text -> return 0
//Otherwise return the normalized frequency of the word
	if (text_contains(text, word)) {
		Node node = ht_lookup(text->ht, word);
		return node->frequency; 
	}

	return 0;
}

bool text_contains(Text *text, char *word) {
//if word in text -> return true
//else return false
	if (bf_probe(text->bf, word) == true) {
		return true;
	} else {
		return false;
	}

}

void text_print(Text *text) {
	printf("DEBUG TEXT");
}
