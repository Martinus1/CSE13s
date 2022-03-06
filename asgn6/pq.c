#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Source: Discord Prof. Long
typedef struct PriorityQueue PriorityQueue;

struct PriorityQueue {
    uint32_t size;
    uint32_t head, tail;
    Node **Q;
};

PriorityQueue *pq_create(uint32_t capacity) {
    //Constructor for a priority queue
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    pq->size = 0;
    pq->head = 0;
    pq->tail = 0;
    pq->Q = (Node **) calloc(capacity, sizeof(Node *));

    return pq;
}

void pq_delete(PriorityQueue **q) {
    //destructor for priority queue
    //Set pointer to Null after freeing the memory
    if (*q) {
        free((*q)->Q);
        free(q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    // Return True if struct is empty if not return false
    if (q->size == 0) {
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    // Return true is struct is full false otherwise

    //TEST unsure(!!!)
    if (q->size == sizeof(q)) {
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    return (q->size);
}

bool enqueue(PriorityQueue *q, Node *n) {
    //Enqueues a node into pq
    //return false if pq = full
    //true otherwise
    if (pq_full(q) == true) {
        return false;
    } else {
        q->size += 1;
        uint32_t lowFrequency = UINT32_MAX;
        int index = 0;
        for (int i = 0; i <= q->size; i++) {
            if (q->Q[i]->frequency < lowFrequency) {

                lowFrequency = q->Q[i]->frequency;
                index = i;
            }
        }

        //Move everything forward after the index;
        q->Q[index] = n;

        return true;
    }
}

bool dequeue(PriorityQueue *q, Node **n) {
    //Dequeues a node from pq
    //returns false if pq = empty
    //true otherwise
    if (pq_empty(q) == true) {
        return false;
    } else {
        q->size -= 1;
        *n = q->Q[0];

        return true;
    }
}

void pq_print(PriorityQueue *q) {
    //Print priority queue info for debug

}
