
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *val;
    int sum;
    int size;
    int count;
    int head;
} MovingAverage;


MovingAverage* movingAverageCreate(int size) {
    MovingAverage *ma = malloc(sizeof(MovingAverage));
    ma->val = (int*)calloc(size, sizeof(int));
    ma->sum = 0;
    ma->size = size;
    ma->count = 0;
    ma->head = 0;
    return ma;
}

double movingAverageNext(MovingAverage* obj, int val)
{
    /* put the new value in the circular buffer */
    int prev = obj->val[obj->head];
    obj->val[obj->head] = val;
    obj->head = (obj->head + 1) % obj->size;

    /* update the number of valid elements (no runaway growth) */
    if (obj->count < obj->size) ++(obj->count);

    /* compute the average of the current window */
    obj->sum += val - prev;
    // for (int i = 0; i < obj->count; ++i)
    //     sum += obj->val[i];

    return (double)obj->sum / obj->count;     /* real moving average */
}

void movingAverageFree(MovingAverage* obj) {
    free(obj->val);
    free(obj);
}
/**
 * Your MovingAverage struct will be instantiated and called as such:
 * MovingAverage* obj = movingAverageCreate(size);
 * double param_1 = movingAverageNext(obj, val);
 
 * movingAverageFree(obj);
*/
