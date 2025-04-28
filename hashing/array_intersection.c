#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int *returnSize) {
    int table_size = 2 * nums1Size + 50;
    int *hash_table = malloc(table_size * sizeof(int));
    bool *used = calloc(table_size, sizeof(bool));

    // fill hash table
    for (int i = 0; i < nums1Size; ++i) {
        int h = (nums1[i] % table_size + nums1Size) % table_size;
        while(used[h]) {
            if(hash_table[h] == nums1[i]) goto loopend;
            if(++h >= table_size) h = 0;
        }
        hash_table[h] = nums1[i];
        used[h] = true;
        loopend:;
    }

    // Now check for nums2
    int *res = NULL, count = 0;
    for (int i = 0; i < nums2Size; ++i) {
        int h = (nums2[i] % table_size + nums1Size) % table_size;
        while(used[h]) {
            if(hash_table[h] == nums2[i]) {
                int* temp = realloc(res, ++count * sizeof(int));
                if (temp == NULL) {
                    free(res);
                    free(hash_table);
                    free(used);
                    return NULL;
                }
                res = temp;
                res[count-1] = nums2[i];
                hash_table[h] = INT_MAX; // need to keep used active to find other elements
                break;
            }
            if(++h >= table_size) h = 0;
        }
    }
    free(hash_table);
    free(used);
    *returnSize = count;
    return res;
}

int main() {
    int nums1[] = {1, 2, 2, 1};
    int nums2[] = {2, 2};
    int nums1Size = sizeof(nums1) / sizeof(nums1[0]);
    int nums2Size = sizeof(nums2) / sizeof(nums2[0]);

    int returnSize;
    int* res = intersection(nums1, nums1Size, nums2, nums2Size, &returnSize);
    if (res == NULL) {
        printf("Error: unable to allocate memory\n");
        return 1;
    }

    printf("Intersection: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(res);
    return 0;
}