#include <stdio.h>
#include <stdlib.h>

/* ------------------- circular-queue of coordinate pairs ---------- */
typedef struct {
    int (*data)[2];     /* array of “int[2]”  – stored by value   */
    int head;
    int tail;
    int size;           /* capacity                               */
} Queue;

Queue *initQueue(int size)
{
    Queue *q = malloc(sizeof *q);
    q->data  = malloc(size * sizeof *q->data);   /* one allocation */
    q->head  = 0;
    q->tail  = 0;
    q->size  = size;
    return q;
}

void freeQueue(Queue *q)
{
    free(q->data);
    free(q);
}

static inline int isEmpty(Queue *q)
{
    return q->head == q->tail;
}

static inline int isFull(Queue *q)
{
    return (q->tail + 1) % q->size == q->head;   /* one slot wasted */
}

void enqueue(Queue *q, int r, int c)
{
    if (isFull(q)) { fprintf(stderr, "queue full\n"); exit(EXIT_FAILURE); }
    q->data[q->tail][0] = r;
    q->data[q->tail][1] = c;
    q->tail = (q->tail + 1) % q->size;
}

void dequeue(Queue *q, int *r, int *c)
{
    if (isEmpty(q)) { fprintf(stderr, "queue empty\n"); exit(EXIT_FAILURE); }
    *r = q->data[q->head][0];
    *c = q->data[q->head][1];
    q->head = (q->head + 1) % q->size;
}