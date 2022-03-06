#include "node.h"
#include "code.h"
#include "defines.h"
#include <stdint.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    //construct a huffman tree
    //return the root node of the constructed tree
    // --- INITIALIZE Vars
    Node *root;
    Node *left;
    Node *right;
    PriorityQueue *pq = pq_create(ALPHABET);

    while () {
    }

    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    //populates the code table, buliding the code for each symbol of the huffman tree
    Code c = code_init();
}

void dump_tree(int outfile, Node *root) {
    //Conducts a post-order traversal of the Huffman tree rooted at root, writing it to outfile.
    //This should write an ‘L’ followed by the byte of the symbol for each leaf, and an ‘I’ for interior nodes.
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    //Reconstructs a Huffman tree given its post-order tree dump stored in the array tree_dump.
    //The length in bytes of tree_dump is given by nbytes. Returns the root node of the reconstructed tree.
}

void delete_tree(Node **root) {
    //Destructor for huffman tree
    if (*root) {
        while
            free(*root->left);
        free(*root->right);
        free(*root);

        node_delete(root);
    }
    return;
}
