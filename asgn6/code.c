#include "defines.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "code.h"

typedef struct {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
} Code;

Code code_init(void) {

    Code *c = (Code *) malloc(sizeof(Code));
    c->top = 0;
    //Zero out the array of bits
    c->bits[MAX_CODE_SIZE] = { 0 };

    return c;
}

uint32_t code_size(Code *c) {
    //Return the size of the Code -> number of bits pushed onto the code
    return c->top;
}

bool code_empty(Code *c) {
    //true if code is empty
    //false otherwise
    if (c->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool code_full(Code *c) {
    //true if code is full
    //false otherwise
    if (code_size(c) == MAX_CODE_SIZE) {
        return true;
    } else {
        return false;
    }
}

bool code_set_bit(Code *c, uint32_t i) {
    //set the bit at index i in the Code to 1
    //if i is out of range return false
    //otherwise return true

    //uint8_t mask = 1LL << (8 - i)

    if (i > ALPHABET) {
        return false;
    } else {
        c->bits[i / 8] |= (0x1 << i % 8);
        return true;
    }
}

bool code_clr_bit(Code *c, uint32_t i) {
    //clears the bit at index i, setting it to 0
    //If i is out of range return false
    //otherwise return true
    if (i > ALPHABET) {
        return false;
    } else {
        c->bits[i / 8] |= (0x0 << i % 8);
        return true;
    }
}

bool code_get_bit(Code *c, uint32_t i) {
    //Get the bit at index i in the Code
    //If i if Out of Range or if bit is 0 return false
    //true if bit i == 1
    uint32_t n = c->bits[i / 8];
    uint32_t bit = (n & (1 << i)) >> i;

    if (bit == 1) {
        return true;
    } else {
        return false;
    }
}

bool code_push_bit(Code *c, uint8_t bit) {
    //pushes a bit of value 'bit' onto Code
    //Return false is the Code is full prior to pushing the bit
    //oterwise return true

    if (code_full(c) == true) {
        return false;
    } else {
        //uint32_t n = c->bits[c->top/8];
        //bit = (n & (1 << i)) >> i;
        //Source DISCORD Prof. Long
        c->bits[c->top / 8] |= (bit << (c->top % 8));
        c->top = (c->top + 1);
        return true;
    }
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    //pop bit off the Code
    //value of popped bit is passed back with pointed bit
    //return false if the Code is empty prior to popping a bit and true otherwise
    if (code_empty(c) == true) {
        return false;
    } else {
        c->top = (c->top - 1);
        uint32_t n = c->bits[c->top / 8];
        *bit = (n >> (c->top % 8) & 0x1);
        //Source DISCORD Prof. Long
        c->bits[c->top / 8] &= ~(0x1 << (c->top % 8));
        ;
        return true;
    }
}

void code_print(Code *c) {
    //Debug Function
}
