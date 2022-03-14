#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "node.h"


typedef struct Node Node;

struct Node {
    char *word;
    uint32_t count;
};

Node *node_create(char *word) {
	Node *n = (Node *) malloc(sizeof(Node));
	//allocate memory and copy over cahracters for the 'word' with strdup()
	n->word = word;
	n->count = 1;

	return n;
}

void node_delete(Node **n) {
	if (*n) {
		free(*n);
		*n = NULL;
	}
}

void node_print(Node *n) {
    //Debug Function
    printf("Debug Node\n");
    printf("Node word: '%c'\n", n->word);
    printf("Node count: %d\n", n->count);
    printf("\n");

}
