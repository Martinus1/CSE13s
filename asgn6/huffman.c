#include "node.h"
#include "code.h"
#include "defines.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void traverse(Node *root, Code table[ALPHABET], Code c) {
    if (root) {
        uint8_t popped;
        // check for children
        if (!root->left && !root->right) {
            table[root->symbol] = c;
        } else {
            code_push_bit(&c, 0);
            traverse(root->left, table, c);
            code_pop_bit(&c, &popped);

            code_push_bit(&c, 1);
            traverse(root->right, table, c);
            code_pop_bit(&c, &popped);
        }
    }
}

Node *build_tree(uint64_t hist[static ALPHABET]) {
    //construct a huffman tree
    //return the root node of the constructed tree
    // --- INITIALIZE Vars
    PriorityQueue *pq = pq_create(ALPHABET);

    for (int i = 0; i < ALPHABET; i++) {
        uint8_t frequency = hist[i];
        uint8_t symbol = i;

        if (frequency > 0) {
            Node *entry = node_create(symbol, frequency);
            enqueue(pq, entry);
        }
    }

    pq_print(pq);

    while (pq_size(pq) >= 2) {
        Node *left;
        Node *right;
        dequeue(pq, &left);
        pq_print(pq);
        dequeue(pq, &right);
        pq_print(pq);

        Node *joined = node_join(left, right);

        enqueue(pq, joined);
    }

    Node *root;
    dequeue(pq, &root);

    fprintf(stdout, "Printing Huffman Tree\n");
    node_print(root);
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    //populates the code table, buliding the code for each symbol of the huffman tree
    Code c = code_init();
    traverse(root, table, c);
}

void dump_tree(int outfile, Node *root) {
    //Conducts a post-order traversal of the Huffman tree rooted at root, writing it to outfile.
    //This should write an ‘L’ followed by the byte of the symbol for each leaf, and an ‘I’ for interior nodes.
    //Prof. Long Assignment document

    if (!root->left && !root->right) {
        char l = 'L';
        write_bytes(outfile, &l, 1);
        write_bytes(outfile, &root->symbol, 1);
    } else {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);
        char i = 'I';
        write_bytes(outfile, &i, 1);
    }
}
    

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    //Reconstructs a Huffman tree given its post-order tree dump stored in the array tree_dump.
    //The length in bytes of tree_dump is given by nbytes. Returns the root node of the reconstructed tree.
    Stack *s = stack_create(nbytes);

    int i = 0;
    while (i < nbytes) {
        char leaf = tree[i];

        if (leaf == 'L') {
            Node *n = node_create(tree[i + 1], 0);
            stack_push(s, n);

            i += 2;
        }
        else if (leaf == 'I'){
            Node *right;
            Node *left;

            stack_pop(s, &right);
            stack_pop(s, &left);
            Node *n = node_join(left, right);
            stack_push(s, n);

            i += 1;
        }
    }

    Node *root;
    stack_pop(s, &root);
    stack_delete(&s);

    return root;
}

void delete_tree(Node **root) {
    //Destructor for huffman tree
    if (*root) {

        if ((*root)->left != NULL) {
            delete_tree(&(*root)->left);
        }

        if ((*root)->right != NULL) {
            delete_tree(&(*root)->right);
        }

        node_delete(root);
    }
}
