#pragma once

#include "defines.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
} Code;

Code code_init(void) {	
	
	Code *c = (Code *) malloc(sizeof(Code));
	c->top = 0;
	//Zero out the array of bits
	c->bits[MAX_CODE_SIZE] = {0};

	return c;
}

uint32_t code_size(Code *c) {
	//Return the size of the Code -> number of bits pushed onto the code
	return sizeof(c->bits);
}

bool code_empty(Code *c) {
	//true if code is empty
	//false otherwise
	if (c == NULL) {
		return true;
	} else {
		return false;
	}
}

bool code_full(Code *c) {
        //true if code is full
        //false otherwise
	
	if (c) {
		return true;
	} else {
		return false;
	}
}


bool code_set_bit(Code *c, uint32_t i) {
	//set the bit at index i in the Code to 1
	//if i is out of range return false
	//otherwise return true
	if() {
	
	} else {
	
	}

}

bool code_clr_bit(Code *c, uint32_t i) {
	//clears the bit at index i, setting it to 0
	//If i is out of range return false
	//otherwise return true
	
}

bool code_get_bit(Code *c, uint32_t i) {
	//Get the bit at index i in the Code
	//If i if Out of Range or if bit is 0 return false
	//true if bit i == 1
	//b[i/8] |= (0x1 << i % 8);
}

bool code_push_bit(Code *c, uint8_t bit) {
	//pushes a bit of value 'bit' onto Code
	//Return false is the Code is full prior to pushing the bit
	//oterwise return true
	
	if (code_full(c) == true) {
		return false;
	} else {

		return true;
	}
}

bool code_pop_bit(Code *c, uint8_t *bit) {
	//pop bit off the Code
	//value of popped bit is passed back with pointed bit
	//return false if the Code is empty prior to popping a bit and true otherwise
	
}

void code_print(Code *c) {
	//Debug Function
}
