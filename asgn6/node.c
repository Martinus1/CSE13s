#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

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
    n->left = NULL;
    n->right = NULL;

    return n;
}

void node_delete(Node **n) {
    //Node Destructor
    if (*n) {
        free(n);
        *n = NULL;
    }
}

Node *node_join(Node *left, Node *right) {
    //Join Left and Right children and return parent node
    //Returns pointer to created parent node
    Node *n = (Node *) malloc(sizeof(Node));
    n->left = left;
    n->right = right;
    n->symbol = '$';
    n->frequency = ((left->frequency) + (right->frequency));

    return n;
}

void node_print(Node *n) {
    //Debug Function
    printf("Debug Node \n");
    printf("Node symbol: %u\n ", n->symbol);
    printf("Node frequency: %lu\n ", n->frequency);
}
