#pragma once

#include <stdint.h>

typedef struct Node Node;

struct Node {
    Node *left;
    Node *right;
    uint8_t symbol;
    uint64_t frequency;
};

Node *node_create(uint8_t symbol, uint64_t frequency) {
        //Constructor for a node
        Node *n = (Node *) malloc(sizeof(Node));
        n->frequency = frequency;
        n->symbol = symbol;

        return n;
}

void node_delete(Node **n) {
        //Node Destructor
        free(n->symbol);
        free(n->);
        free(n);
}

Node *node_join(Node *left, Node *right) {
	//Join Left and Right children and return parent node
	Node *n = (Node *) malloc(sizeof(Node));
	n->left = left;
	n->right = right;
	n->symbol = '$';
	n->frequency = ((left->frequency) + (right->frequency));

	return *n;
}

void node_print(Node *n) {
	//Debug Function
	printf("Debug Node \n");
	printf("Node symbol: %u\n ", symbol);
	printf("Node frequency: %u\n ", frequency);
}
