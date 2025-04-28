/*
 *  fast_qsort.c  –  median–of–three quick-sort with the usual
 *                   performance tricks:
 *
 *    • half-open intervals  [lo, hi)  (easier bounds handling)
 *    • median-of-three pivot, copied to  hi-1
 *    • insertion-sort for tiny segments (<= INSERTION_LIMIT)
 *    • recurse on the *smaller* half first, tail-recursing on the
 *      larger → O(log n) stack in the worst case
 *
 *  public interface:
 *      void qsort_int(int *a, size_t n);
 *
 *  (C17; just remove the `static` if you want the helpers exported)
 */
#include <stddef.h>   /* size_t */
#include <stdint.h>   /* INT32_MIN / INT32_MAX */
#include <assert.h>

/* ------------------------------------------------------------------ */
/* small helpers                                                      */

static inline void swap_int(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/* ------------------------------------------------------------------ */
/* insertion sort – faster for tiny runs                              */

#define INSERTION_LIMIT 16

static void insertion_sort(int *a, size_t lo, size_t hi)   /* [lo, hi) */
{
    for (size_t i = lo + 1; i < hi; ++i) {
        int key = a[i];
        size_t j = i;
        while (j > lo && a[j - 1] > key) {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = key;
    }
}

/* ------------------------------------------------------------------ */
/* median-of-three partition; returns final pivot index               */

static size_t partition(int *a, size_t lo, size_t hi)      /* [lo, hi) */
{
    size_t mid = lo + ((hi - lo) >> 1);        /* floor((lo+hi)/2)   */

    /* median-of-three to choose a good pivot ---------------------- */
    if (a[lo]   > a[mid]) swap_int(&a[lo],  &a[mid]);
    if (a[lo]   > a[hi-1]) swap_int(&a[lo],  &a[hi-1]);
    if (a[mid]  > a[hi-1]) swap_int(&a[mid], &a[hi-1]);

    /* Move the median (pivot) to hi-1 so it is out of the way.      */
    swap_int(&a[mid], &a[hi-1]);
    const int pivot = a[hi-1];

    /* Hoare-style bidirectional scan ------------------------------ */
    size_t i = lo;
    size_t j = hi - 2;                  /* hi-1 is the pivot guard   */

    for (;;) {
        while (a[i] < pivot) ++i;
        while (a[j] > pivot) --j;
        if (i >= j) break;
        swap_int(&a[i], &a[j]);
        ++i; --j;
    }
    /* place pivot between the partitions                           */
    swap_int(&a[i], &a[hi-1]);
    return i;                           /* pivot’s final index       */
}

/* ------------------------------------------------------------------ */
/* main quicksort – non-recursive large half                          */

static void quicksort_core(int *a, size_t lo, size_t hi)   /* [lo, hi) */
{
    while (hi - lo > INSERTION_LIMIT) {
        size_t p = partition(a, lo, hi);

        /* Recurse on the smaller half first to keep stack O(log n) */
        if (p - lo < hi - (p + 1)) {
            quicksort_core(a, lo, p);
            lo = p + 1;                 /* tail-recurse on right  */
        } else {
            quicksort_core(a, p + 1, hi);
            hi = p;                     /* tail-recurse on left   */
        }
    }
}

/* ------------------------------------------------------------------ */
/* public API                                                         */

void qsort_int(int *a, size_t n)
{
    if (n < 2) return;
    quicksort_core(a, 0, n);
    insertion_sort(a, 0, n);    /* final polish for all tiny runs */
}

/* ------------------------------------------------------------------ */
/* (Optional) self-test – compile with  -DQSORT_TEST=1                */
// #if QSORT_TEST
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int is_sorted(const int *a, size_t n)
{
    for (size_t i = 1; i < n; ++i)
        if (a[i-1] > a[i]) return 0;
    return 1;
}

int main(void)
{
    const size_t N = 10000000;          /* 1 M elements */
    int *v = malloc(N * sizeof *v);
    if (!v) return 2;

    /* fill with some pattern */
    for (size_t i = 0; i < N; ++i)
        v[i] = (int)((i*2654435761u) & 0x7fffffff);

    clock_t start = clock();
    qsort_int(v, N);
    clock_t end = clock();
    printf("Sorting %zu elements took %f seconds\n", N, (double)(end-start)/CLOCKS_PER_SEC);
    printf("sorted: %s\n", is_sorted(v, N) ? "yes" : "NO!");
    free(v);
    return 0;
}
// #endif