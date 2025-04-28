#include <stdio.h>

void insertionSortNaive(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j-1]) {
                // This is stable because no item is swapped past another unless it has a smaller key. 
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        int t = arr[j];
        while (j > 0 && t < arr[j-1]) { // Scan backward over the sorted items
            arr[j] = arr[j-1]; --j; 
        }
        arr[j] = t;  // Insert      
    }
}

int main() {
    int arr1[] = { 5, 2, 8, 12, 3, 10, 1, 7, 4, 6, 9, 0, 11, 15, 14, 16, 13, 18, 17, 19};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[n];
    for (int i = 0; i < n; i++) arr2[i] = arr1[i];

    insertionSortNaive(arr1, n);
    insertionSort(arr2, n);

    for (int i = 0; i < n; i++) printf("%d ", arr1[i]);
    printf("\n");

    for (int i = 0; i < n; i++) printf("%d ", arr2[i]);
    printf("\n");

    return 0;
}
