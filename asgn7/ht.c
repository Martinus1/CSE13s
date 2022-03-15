#include "node.h"
#include "ht.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct HashTable {
	uint64_t salt[2];
	uint64_t size;
	uint64_t top;
	Node **slots;	
};

struct HashTableIterator {
	HashTable *table;
	uint32_t slot;
};

HashTable *ht_create(uint32_t size) {
	//make hast table 1.5 bigger than size
	HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
	//ht->salt = ;
	ht->top = 0;
	ht->size = size;
	ht->slots = (Node **) calloc((size * 1.5), sizeof(Node *));

	return ht;
		
}


void ht_delete(HashTable **ht) {
	if (*ht) {
		free((*ht)->salt);
		free((*ht)->slots);
		free(*ht);
		*ht = NULL;
	}
	return;
}

uint32_t ht_size(HashTable *ht) {
	return ht->size;
}

Node* ht_lookup(HashTable *ht, char *word) {
	//Go over hash table -> if word is found, return pointer to the node
	for (int i = 1; i < (ht->size); i++) {
		if(ht->slots[i]->word == word) {
			return(*ht->slots[i]);
		}	
	}	
	
	return(NULL);
}


Node* ht_insert(HashTable *ht, char *word) {
	//Insert word into a hast table -> if word exist, increment count by 1
	//Otherwise insert a new node containing word with count = 1
	
	Node* node = ht_lookup(ht, *word);
	
	if (node != NULL) {
		//Existing Node, increment by 1
		node->count += 1;
 		return(node);		
	} else {
		//create new Node in ht
		Node newNode = node_create(word);
		ht->slots[ht->top] = newNode;
		ht->top += 1;
		return(node);
	}

	return(NULL);

}

void ht_print(HashTable *ht) {
	for (int i = 1; i < (ht->top); i++) {
		printf("%c | ", ht->slots[i]->word);
		printf("%d \n", ht->slots[i]->count);
	}
}

HashTableIterator *hti_create(HashTable *ht) {
 	HashTableIterator *hti = (HashTableIterator *) malloc(sizeof(HashTableIterator));
        hti->slot = 0;	
	hti->table = (HashTable *) malloc(sizeof(HashTable));
	return HashTableIterator;
}

void hti_delete(HashTableIterator **hti) {
	if (*hti) {
		free(*hti);
	}

	return;
}

Node *ht_iter(HashTableIterator *hti) {
	// Returns the pointer to the next valid entry in the hash table.
	// Should return NULL if iterator went over the whole hash table
	if ((hti->table[hti->slot])->count > 0) {
		hti->slot += 1;
		return *hti->table[hti->slot];
	}	

	return NULL;
}
