int search(int* nums, int numsSize, int target) {
    // Set the left and right boundaries
    int left = 0, right = numsSize - 1;
    
    // Under this condition
    while (left <= right) {
        // Get the middle index and the middle value.
        int mid = (left + right) / 2; // left + (right - left) / 2;
        
        // Case 1, return the middle index.
        if (nums[mid] == target) {
            return mid;
        } 
        // Case 2, discard the smaller half.
        else if (nums[mid] < target) {
            left = mid + 1;   
        } 
        // Case 3, discard the larger half.
        else {
            right = mid - 1;
        }
    }
    
    // If we finish the search without finding target, return -1.
    return -1;
}

// Same, more compact
int search2(int* a, int n, int x) {
    int left = 0, right = n-1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if(x == a[mid]) return mid; // Optional (gives speedup)
        if (x > a[mid]) left = mid+1;
        else right = mid-1;
    }
    return -1;        
}

// Slightly simpler but less efficient
int search3(int* a, int n, int x) {
    int left = 0, right = n-1, mid;
    while (left < right) {
        mid = (left + right) / 2;
        if (x > a[mid]) left = mid+1;
        else right = mid;
    }
    if (a[left] == x) return left;
    return -1;        
}



/* Recursive Function: problem: index adjustment
int search(int* nums, int numsSize, int target) {
    int half = numsSize / 2; 
    if (nums[half] == target) return half;
    if(target < nums[half]) return search(nums, half, target);
    if(target > nums[half]) return search(nums+half, half, target);
    return -1;
}
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define TEST_ARRAY_SIZE (1 << 24)

int main() {
    int* test_array = (int*)malloc(sizeof(int) * TEST_ARRAY_SIZE);
    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
        test_array[i] = i*2;
    }

    clock_t start = clock();
    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
        if(search(test_array, TEST_ARRAY_SIZE, i*2) == -1) {
            printf("search failed\n");
        }
    }
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("search took %f seconds\n", time_taken);

    start = clock();
    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
        if(search2(test_array, TEST_ARRAY_SIZE, i*2) == -1) {
            printf("search2 failed\n");
        };
    }
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("search2 took %f seconds\n", time_taken);

    free(test_array);
    return 0;
}
