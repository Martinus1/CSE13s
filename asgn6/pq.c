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
    uint32_t capacity;
    Node **Q;
};

PriorityQueue *pq_create(uint32_t capacity) {
    //Constructor for a priority queue
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    pq->size = 0;
    pq->head = 0;
    pq->tail = 0;
    pq->capacity = capacity;
    pq->Q = (Node **) calloc(capacity, sizeof(Node *));

    return pq;
}

void pq_delete(PriorityQueue **q) {
    //destructor for priority queue
    //Set pointer to Null after freeing the memory
    if (*q) {
        free((*q)->Q);
        free(*q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    // Return True if struct is empty if not return false
    return q->size == 0;
}

bool pq_full(PriorityQueue *q) {
    // Return true is struct is full false otherwise
    return q->size == q->capacity;
}

uint32_t pq_size(PriorityQueue *q) {
    return (q->size);
}

bool enqueue(PriorityQueue *q, Node *n) {
    //Enqueues a node into pq
    //return false if pq = full
    //true otherwise
    if (pq_full(q)) {
        return false;
    } else {
        q->Q[q->tail] = n;

        q->tail += 1;
        q->size += 1;

        /* uint32_t lowFrequency = UINT32_MAX; */
        /* int index = 0; */
        /* for (uint32_t i = 0; i <= q->size; i++) { */
        /*     if (q->Q[i] && q->Q[i]->frequency < lowFrequency) { */
        /*         lowFrequency = q->Q[i]->frequency; */
        /*         index = i; */
        /*     } */
        /* } */

        /* //Move everything forward after the index; */
        /* q->Q[index] = n; */

        return true;
    }
}

bool dequeue(PriorityQueue *q, Node **n) {
    //Dequeues a node from pq
    //returns false if pq = empty
    //true otherwise
    if (pq_empty(q)) {
        return false;
    } else {
        *n = q->Q[q->head];

        q->head += 1;
        q->size -= 1;

        return true;
    }
}

void pq_print(PriorityQueue *q) {
    //Print priority queue info for debug
    printf("Debug PQ \n");
    printf("PriorityQueue size: %u\n ", q->size);
    printf("PriorityQueue head: %u\n ", q->head);
    printf("PriorityQueue tail: %u\n ", q->tail);

    for (uint32_t i = 0; i < q->size; i++) {
        if (q->Q[i]) {
            node_print(q->Q[i]);
        }
    }

}
