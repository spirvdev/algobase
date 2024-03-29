/*
 *  Source code written by Gabriel Correia
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

/* A single linked list used inside the queue algorithm */
typedef int (*Q_callback) (void*, size_t);
typedef int (*Q_user_callback) (void*, void*, size_t);

typedef struct queue_node {
    /* The stored data */
    void *data;
    /* Next node element */
    struct queue_node *next;
} Q_node_t;

typedef struct _queue {
    Q_node_t *head, *tail;

    /* A callable function used on the destroy method */
    Q_callback on_destroy,
    
    /* The same as above, but at the create method */
        on_create;
} queue_t;


/* Create a new queue (Without head/tail) */
queue_t* queue_new ();

/* Enqueue a new node element */
void queue_enqueue (void *data, queue_t *queue);

/*  For each element callback based function, if the callback function returns 1, the operation will
 *  be immediately stopped
*/
void queue_foreach (Q_callback callback, queue_t *queue);
void queue_foreach_user (Q_user_callback callback, void *user, queue_t *queue);

/* Dequeue a node element and returns his stored data */
void* queue_dequeue (queue_t *queue);

/* Event register functions */
/* Call this method on each node object destruction action */
void queue_on_destroy (Q_callback callback, queue_t *queue);
void queue_on_create (Q_callback callback, queue_t *queue);

/* Returns the queue size */
size_t queue_size (queue_t *queue);

/* Checking functions */
bool queue_is_full (queue_t *queue);
bool queue_is_empty (queue_t *queue);

/* Select a queue data from a position */
void* queue_select (size_t pos, queue_t *queue);

/* Cleanup the queue but doesn't destroy him (only the nodes will be destroyed) */
size_t queue_clear (queue_t *queue);
/* Destroy the queue and all elements inside him */
size_t queue_delete (queue_t *queue);
