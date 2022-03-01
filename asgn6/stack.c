#pragma once

#include "node.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct Stack Stack;

Stack *stack_create(uint32_t capacity) {
	Stack *s = (Stack *) malloc(sizeof(Stack)); 
	s->capacity = capacity;

	return s;
}

void stack_delete(Stack **s) {
	if(*s) {
                free(*s);
                *s = NULL;
        }
        return;
}

bool stack_empty(Stack *s) {
	//stack empty = true
        //else false
	if (s == NULL) {
		return true;
	} else {
		return false;
	}
}

bool stack_full(Stack *s) {
	//stack full = true
	//else false
	
	if (s) {
		return true;
	} else {
		return false;
	}

}

uint32_t stack_size(Stack *s) {
	//return number of nodes in the stack
	return ;
}

bool stack_push(Stack *s, Node *n) {
	//pushes a node onto the stack
	//return false is stack is full prior to pushing the node
	//otherwise return true
	
}

bool stack_pop(Stack *s, Node **n) {
	//pops a node off the stack passing it back through double pointer n
	//return false is stack is full prior to pushing the nde
        //otherwise return true
}

void stack_print(Stack *s) {
	//Debug function for stack
}
