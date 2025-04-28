/*
    C translation of the C++ “MyCircularQueue” class.
    Each operation is implemented as a plain function that receives
    a pointer to the queue object.

    Compile with (for example):
        gcc -std=c11 -Wall -Wextra -pedantic circular_queue.c -o cq
*/

#include <stdlib.h>
#include <stdbool.h>

/* ------------ data structure ------------------------------------------- */
typedef struct {
    int  *data;   /* dynamically‑allocated array                         */
    int   head;   /* index of the current front element, ‑1 if empty     */
    int   tail;   /* index of the current rear element,  ‑1 if empty     */
    int   size;   /* capacity (number of slots in the array)             */
} MyCircularQueue;

/* ------------ constructor / destructor --------------------------------- */
MyCircularQueue *myCircularQueueCreate(int k)
{
    if (k <= 0) return NULL;

    MyCircularQueue *obj = malloc(sizeof *obj);
    if (!obj) return NULL;

    obj->data = malloc((size_t)k * sizeof *obj->data);
    if (!obj->data) { free(obj); return NULL; }

    obj->head = -1;
    obj->tail = -1;
    obj->size = k;
    return obj;
}

void myCircularQueueFree(MyCircularQueue *obj)
{
    if (!obj) return;
    free(obj->data);
    free(obj);
}

/* ------------ helpers -------------------------------------------------- */
static inline bool myCircularQueueIsEmpty(const MyCircularQueue *obj)
{
    return obj->head == -1;
}

static inline bool myCircularQueueIsFull(const MyCircularQueue *obj)
{
    return ((obj->tail + 1) % obj->size) == obj->head;
}

/* ------------ core operations ------------------------------------------ */
bool myCircularQueueEnQueue(MyCircularQueue *obj, int value)
{
    if (!obj || myCircularQueueIsFull(obj)) return false;

    if (myCircularQueueIsEmpty(obj))
        obj->head = 0;                       /* first element goes at 0   */

    obj->tail            = (obj->tail + 1) % obj->size;
    obj->data[obj->tail] = value;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue *obj)
{
    if (!obj || myCircularQueueIsEmpty(obj)) return false;

    if (obj->head == obj->tail) {            /* queue will become empty   */
        obj->head = -1;
        obj->tail = -1;
    } else {
        obj->head = (obj->head + 1) % obj->size;
    }
    return true;
}

int myCircularQueueFront(const MyCircularQueue *obj)
{
    return (obj && !myCircularQueueIsEmpty(obj)) ? obj->data[obj->head] : -1;
}

int myCircularQueueRear(const MyCircularQueue *obj)
{
    return (obj && !myCircularQueueIsEmpty(obj)) ? obj->data[obj->tail] : -1;
}

/* ----------------------------------------------------------------------- */
// Example usage:

#include <stdio.h>

int main(void)
{
    MyCircularQueue *q = myCircularQueueCreate(3);

    myCircularQueueEnQueue(q, 1);
    myCircularQueueEnQueue(q, 2);
    myCircularQueueEnQueue(q, 3);   // queue is now full

    printf("Front: %d\n", myCircularQueueFront(q)); // 1
    printf("Rear : %d\n", myCircularQueueRear(q));  // 3

    myCircularQueueDeQueue(q);      // remove 1
    myCircularQueueEnQueue(q, 4);   // queue: 2 3 4

    printf("Front: %d\n", myCircularQueueFront(q)); // 2
    printf("Rear : %d\n", myCircularQueueRear(q));  // 4

    myCircularQueueFree(q);
}
