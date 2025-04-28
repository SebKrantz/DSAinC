#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 1000

typedef struct {
    int* set[MAX_LEN];
    int sizes[MAX_LEN];
} MyHashSet;

MyHashSet* myHashSetCreate() {
    MyHashSet* obj = (MyHashSet*)malloc(sizeof(MyHashSet));
    for (int i = 0; i < MAX_LEN; i++) {
        obj->set[i] = NULL;
        obj->sizes[i] = 0;
    }
    return obj;
}

void myHashSetAdd(MyHashSet* obj, int key) {
    int index = key % MAX_LEN;
    for (int i = 0; i < obj->sizes[index]; i++) {
        if (obj->set[index][i] == key) return;
    }
    obj->set[index] = realloc(obj->set[index], (obj->sizes[index] + 1) * sizeof(int));
    obj->set[index][obj->sizes[index]] = key;
    obj->sizes[index]++;
}

void myHashSetRemove(MyHashSet* obj, int key) {
    int index = key % MAX_LEN;
    for (int i = 0; i < obj->sizes[index]; i++) {
        if (obj->set[index][i] == key) {
            for (int j = i; j < obj->sizes[index] - 1; j++) {
                obj->set[index][j] = obj->set[index][j + 1];
            }
            obj->set[index] = realloc(obj->set[index], (obj->sizes[index] - 1) * sizeof(int));
            obj->sizes[index]--;
            return;
        }
    }
}

bool myHashSetContains(MyHashSet* obj, int key) {
    int index = key % MAX_LEN;
    for (int i = 0; i < obj->sizes[index]; i++) {
        if (obj->set[index][i] == key) return true;
    }
    return false;
}

void myHashSetFree(MyHashSet* obj) {
    for (int i = 0; i < MAX_LEN; i++) {
        free(obj->set[i]);
    }
    free(obj->sizes);
    free(obj);
}

int main() {
    MyHashSet* obj = myHashSetCreate();
    int keys[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int n = sizeof(keys) / sizeof(int);
    for (int i = 0; i < n; i++) {
        myHashSetAdd(obj, keys[i]);
    }
    for (int i = 0; i < n; i++) {
        if (!myHashSetContains(obj, keys[i])) {
            printf("Error: Could not find %d\n", keys[i]);
            exit(1);
        }
    }
    for (int i = 0; i < n; i++) {
        myHashSetRemove(obj, keys[i]);
        if (myHashSetContains(obj, keys[i])) {
            printf("Error: Could not remove %d\n", keys[i]);
            exit(1);
        }
    }
    myHashSetFree(obj);
    return 0;
}