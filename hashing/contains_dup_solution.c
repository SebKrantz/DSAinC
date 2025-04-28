#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool containsDuplicate(int* nums, int numsSize) {

   int table_size = 2 * numsSize + 50;
   int *hash_table = (int *)malloc(table_size * sizeof(int));
   bool *used = (bool *)calloc(table_size , sizeof(bool));

   for(int i = 0 ; i < numsSize ; i++){

    int element = nums[i];
    int index = (element % numsSize + numsSize) % numsSize;

    while(used[index]) {

        if(hash_table[index] == element){
            free(hash_table);
            free(used);
            return true;
        } else{
            index = (index + 1) % table_size;
        }
    }

    hash_table[index] = element;
    used[index] = true;
   }

   free(hash_table);
   free(used);
   return false;
}

int main() {

    int nums[] = {1, 2, 3, 1};
    int numsSize = 4;
    printf("%d\n", containsDuplicate(nums, numsSize));

    int nums2[] = {1, 2, 3, 4};
    int numsSize2 = 4;
    printf("%d\n", containsDuplicate(nums2, numsSize2));

    return 0;
}