// Inspired by: https://www.youtube.com/watch?v=t0Cq6tVNRBA

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct heap {
    int *arr;
    int size;
    int cap;
} MinHeap;

// Definition

MinHeap *min_heap_create(int capacity) {
    MinHeap *h = malloc(sizeof *h);
    h->arr  = malloc(sizeof *h->arr * capacity);
    h->size = 0;
    h->cap  = capacity;
    return h;
}

void min_heap_free(MinHeap *h) {
    free(h->arr);
    free(h);
}

// Utilities

int left_child(int i) {
    return 2 * i + 1;
}

int right_child(int i) {
    return 2 * i + 2;
}

int parent(int i) {
    return (i - 1) / 2;
}

bool has_left_child(MinHeap *h, int i) {
    return left_child(i) < h->size;
}

bool has_right_child(MinHeap *h, int i) {
    return right_child(i) < h->size;
}

bool has_parent(MinHeap *h, int i) {
    return parent(i) >= 0;
}

int get_left_child(MinHeap *h, int i) {
    return h->arr[left_child(i)];
}

int get_right_child(MinHeap *h, int i) {
    return h->arr[right_child(i)];
}

int get_parent(MinHeap *h, int i) {
    return h->arr[parent(i)];
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Main Methods

int peek(MinHeap *h) {
    return h->arr[0];
}

void heapifyDown(MinHeap *h, int i) { // bubble down
    while (has_left_child(h, i)) { // Because heap is a complete binary tree
        int min_child = left_child(i);
        if (has_right_child(h, i) && get_right_child(h, i) < get_left_child(h, i)) { // If right child is smaller
            min_child = right_child(i);
        }
        if (h->arr[i] > h->arr[min_child]) {
            swap(&h->arr[i], &h->arr[min_child]);
            i = min_child;
        } else {
            break;
        }
    }
}

int poll(MinHeap *h) {
    int min = h->arr[0]; // get root
    h->arr[0] = h->arr[h->size - 1]; // move last to root
    h->size--; // reduce size
    heapifyDown(h, 0); // bubble down
    return min;
}

void heapifyUp(MinHeap *h, int i) {
    while (has_parent(h, i) && get_parent(h, i) > h->arr[i]) {
        swap(&h->arr[i], &h->arr[parent(i)]);
        i = parent(i);
    }
}

void add(MinHeap *h, int val) {
    h->arr[h->size] = val;
    heapifyUp(h, h->size++);
}

void remove2(MinHeap *h, int val) {
    for (int i = 0; i < h->size; i++) {
        if (h->arr[i] == val) {
            h->arr[i] = h->arr[h->size - 1];
            h->size--;
            heapifyDown(h, i);
            return;
        }
    }
}

void print(MinHeap *h) {
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}

/* Build a heap from an existing array in O(n) time (Floyd’s method) */
// https://www.geeksforgeeks.org/building-heap-from-array/
MinHeap *heapify(const int *src, int n)
{
    MinHeap *h = malloc(sizeof *h);
    h->arr  = malloc(sizeof *h->arr * n);
    memcpy(h->arr, src, sizeof *h->arr * n);
    h->size = h->cap = n;

    /* start at last parent and sift-down */
    // n / 2 - 1 is same as parent(n - 1) -> Complexity: O(n)
    for (int i = n / 2 - 1; i >= 0; --i)
        heapifyDown(h, i);

    return h;
}

void heapsort2(int *arr, int n) { // O(n log n)
    MinHeap *h = heapify(arr, n); // O(n)
    for (int i = 0; i < n; i++) {
        arr[i] = poll(h); // O(log n)
    }
}

int* top_k(int* nums, int numsSize, int k) { // Could poll in order to get sorted
    MinHeap *h = heapify(nums, k);
    for (int i = k; i < numsSize; i++) {
        if (nums[i] > peek(h)) {
            poll(h);
            add(h, nums[i]);
        }
    }
    return h->arr;
}

// Kth Largest Element in an Array
int findKthLargest(int* nums, int numsSize, int k) {
    return top_k(nums, numsSize, k)[0];
}

// Testing 

int main() {
    int arr[] = {4, 2, 9, 6, 5, 1, 8, 3, 7, 0};

    MinHeap *h = heapify(arr, 10);

    printf("MinHeap: ");
    print(h);

    remove2(h, 5);

    printf("After removing 5: ");
    print(h);

    add(h, 4);

    printf("After adding 4: ");
    print(h);

    // Top 3 elements
    int *top = top_k(arr, 10, 3);
    printf("Top 3 elements: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", top[i]);
    }
    printf("\n");

    int n  = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", n);
    heapsort2(arr, n);
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
