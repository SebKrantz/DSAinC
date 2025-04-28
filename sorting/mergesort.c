#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// See: https://www.geeksforgeeks.org/merge-sort/

/**
 * Merges two sorted arrays into a single sorted array.
 * 
 * @param nums1 The first sorted array which has enough space to hold the elements of nums2.
 *              It contains 'm' elements followed by enough space for 'n' elements.
 * @param nums1Size The total size of the nums1 array.
 * @param m The number of initialized elements in nums1.
 * @param nums2 The second sorted array.
 * @param nums2Size The total size of the nums2 array.
 * @param n The number of initialized elements in nums2.
 */
void merge(int* a, int* b, int left, int mid, int right) {
    int i = 0, l = right-left+1, nl = left, nr = mid+1;
    while (nl <= mid && nr <= right) 
        b[i++] = a[nl] <= a[nr] ? a[nl++] : a[nr++];
    while (nl <= mid) b[i++] = a[nl++];
    while (nr <= right) b[i++] = a[nr++];
    memcpy(a + left, b, l * sizeof(int));
}

// Naive recurse down to the end
// void mergesort_core(int a[], int b[], int left, int right) {
//     if (left < right) { // We partition until indices are equal
//         int mid = (left + right) / 2;
//         mergesort_core(a, b, left, mid);
//         mergesort_core(a, b, mid+1, right);
//         // Could put a more efficient merge function here for small arrays
//         merge(a, b, left, mid, right);
//     }
// }

void mergesort_core(int a[], int b[], int left, int right) {
    if (right - left > 1) { // We partition until indices are equal
        int mid = (left + right) / 2;
        mergesort_core(a, b, left, mid);
        mergesort_core(a, b, mid+1, right);
        // Could put a more efficient merge function here for small arrays
        merge(a, b, left, mid, right);
    } else if (a[left] > a[right]) { // Efficient for array of size 2
        int tmp = a[left];
        a[left] = a[right];
        a[right] = tmp;
    }
}

void mergesort2(int a[], int left, int right) {
    int *b = malloc((right - left + 1) * sizeof(int)); // Defining here for memory efficiency
    mergesort_core(a, b, left, right);
    free(b);
}

int main() {
    int a[] = {8, 6, 4, 3, 8, 10, 23, 56, 3, 5, 6, 3, 1};
    int n = sizeof(a) / sizeof(a[0]);
    mergesort2(a, 0, n-1);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}