#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static inline void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// First a simple brute force implementation
int partition_simple(int a[], int left, int right) {
    int pivot = a[left];
    int i = left, j = right;
    while (i < j) {
        while (a[i] <= pivot && i < right) i++;
        while (a[j] > pivot && j > left) j--;
        if (i < j) swap(a+i, a+j);
    }
    swap(a+left, a+j);
    return j;
}

void quicksort_simple(int a[], int left, int right) {
    if (left < right) {
        int pivotindex = partition_simple(a, left, right);
        quicksort_simple(a, left, pivotindex-1);
        quicksort_simple(a, pivotindex+1, right);
    }
}

// Now a smart implementation using a median of three
/* ------------------- Hoare–style partition --------------------- */
static int partition_fast(int a[], int left, int right)
{
    int mid = (left + right) >> 1, lp = left + 1;
    swap(a+mid, a+lp); /* move pivot to a[lp] */

    /* median-of-three for a decent pivot and sentinels */
    if (a[left]  > a[right]) swap(a+left,  a+right);
    if (a[lp]    > a[right]) swap(a+lp,   a+right);
    if (a[left]  > a[lp])    swap(a+left,  a+lp);

    const int pivot = a[lp];  /* pivot is a[lp] */
    
    // Now a[left] <= a[lp] <= a[right]
    // This means a[left] <= pivot <= a[right]
    // So a[left] serves as left sentinel and a[right] as right sentinel
    
    int i = lp, j = right;
    for (;;) {
        do i++; while (a[i] < pivot); // Safe because a[right] >= pivot acts as sentinel
        do j--; while (a[j] > pivot); // Safe because a[left] <= pivot acts as sentinel
        if (i > j) break; 
        swap(a+i, a+j);
    }
    a[lp] = a[j];                              
    a[j] = pivot;  
    return j;
}

// static int partition_fast(int a[], int left, int right)
// {
//     int mid = (left + right) >> 1;

//     /* median-of-three for a decent pivot and sentinels */
//     if (a[left] > a[right]) swap(a+left, a+right);
//     if (a[mid] > a[right]) swap(a+mid, a+right);
//     if (a[left] > a[mid]) swap(a+left, a+mid);

//     const int pivot = a[mid];  /* pivot is a[mid] */
    
//     // Swap pivot to the left side to get it out of the way
//     swap(a+mid, a+left+1);
    
//     int i = left+1, j = right;
//     for (;;) {
//         do i++; while (a[i] < pivot);
//         do j--; while (a[j] > pivot);
//         if (i >= j) break; 
//         swap(a+i, a+j);
//     }
    
//     // Put pivot at its final position
//     swap(a+left+1, a+j);
    
//     return j;  // Return pivot's final position
// }

void quicksort_fast(int a[], int left, int right) {
    if (right - left > 1) {  // Need at least 3 elements for median-of-three
        int pivotindex = partition_fast(a, left, right);
        quicksort_fast(a, left, pivotindex-1);
        quicksort_fast(a, pivotindex+1, right);
    } else if (a[left] > a[right]) {  // Handle case with only 2 elements
        swap(a+left, a+right);
    }
}

int main() {
    int a[] = {8, 6, 4, 3, 8, 10, 23, 56, 3, 5, 6, 3, 1};
    int n = sizeof(a) / sizeof(a[0]);
    quicksort_fast(a, 0, n-1);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    
    int N = 10000000;
    int *b = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        b[i] = rand();
    }
    clock_t start = clock();
    quicksort_fast(b, 0, N-1);
    clock_t end = clock();
    // Verification
    for (int i = 0; i < N-1; i++) {
        if (b[i] > b[i+1]) {
            printf("Not sorted: i = %d, b[i] = %d, b[i+1] = %d\n", i, b[i], b[i+1]);
            return 1;
        }
    }
    printf("Sorting %d elements took %f seconds\n", N, (double)(end-start)/CLOCKS_PER_SEC);
    free(b);
    return 0;
}