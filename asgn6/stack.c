#include "node.h"
#include "stack.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct Stack Stack;

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->top = 0;
    s->capacity = capacity;
    s->items = (Node **) calloc(capacity, sizeof(Node *));
    return s;
}

void stack_delete(Stack **s) {
    if (*s) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    //stack empty = true
    //else false
    if ((s->top) == -1) {
        return true;
    } else {
        return false;
    }
}

bool stack_full(Stack *s) {
    //stack full = true
    //else false

    if (s->top == s->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t stack_size(Stack *s) {
    //return number of nodes in the stack
    return s->top;
}

bool stack_push(Stack *s, Node *n) {
    //pushes a node onto the stack
    //return false is stack is full prior to pushing the node
    //otherwise return true
    if (stack_full(s)) {
        return false;
    } else {
        //CITE: Geeks for Geeks
        s->items[s->top++] = n;
        return true;
    }
}

bool stack_pop(Stack *s, Node **n) {
    //pops a node off the stack passing it back through double pointer n
    //return false is stack is empty prior to poping the node
    //otherwise return true

    if (stack_empty(s)) {
        return false;
    } else {
        //CITE: Geeks for Geeks
        n = &s->items[s->top--];
        return true;
    }
}

void stack_print(Stack *s) {
    //Debug function for stack
}
