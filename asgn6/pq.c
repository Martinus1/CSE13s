#pragma once

#include "node.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct PriorityQueue PriorityQueue;

PriorityQueue *pq_create(uint32_t capacity) {
        //Constructor for a priority queue
        PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
        
        return pq;
}

void pq_delete(PriorityQueue **q) {
	//destructor for priority queue
	//Set pointer to Null after freeing the memory
	if(*q) {
		free(*q);
		*q = NULL;
	}
	return;
}

bool pq_empty(PriorityQueue *q) {
	// Return True if struct is empty if not return false
	if (pq == NULL) {
		return true;
	} else {
		return false;
	}
}

bool pq_full(PriorityQueue *q) {
	// Return true is struct is full false otherwise
	if () {
		return true;
	} else {
		return false;
	}
}

uint32_t pq_size(PriorityQueue *q) {
	return (sizeof(q));
}

bool enqueue(PriorityQueue *q, Node *n) {
	//Enqueues a node into pq
	//return false if pr = full
	//true otherwise
	if (pq_full(q) == true) {
		return false;	
	} else {
		q = n;	
		return true;
	}
}

bool dequeue(PriorityQueue *q, Node **n) {
	//Dequeues a node from pq
	//returns false if pq = empty
	//true otherwise
	if(pq_empty(q) == true) {
		return false;	
	} else {
		
		return true;
	}
}

void pq_print(PriorityQueue *q) {
	//Print priority queue info for debug
	for(PriorityQueue *qu = q; qu != NULL; qu = qu->next) {
		printf("%s\n", curr->key);
	}
}
