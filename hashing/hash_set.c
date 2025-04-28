#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// This is accepted as well!!
// TODO: Use linked list bucket?? !!!

typedef struct {
    int * keys;
    // Optional: used array to detect collisions
} MyHashSet;

int hssize = 25000;

MyHashSet* myHashSetCreate() {
    MyHashSet *hs = malloc(sizeof(MyHashSet));
    hs->keys = malloc(hssize * sizeof(int));
    memset(hs->keys, -1, hssize * sizeof(int)); // keys can be 0 so need to initialize to -1
    return hs; 
}

void myHashSetAdd(MyHashSet* obj, int key) {
    int h = key % hssize;
    while(obj->keys[h] >= 0) {
        if(obj->keys[h] == key) return;
        if(++h == hssize) h = 0;
    }
    obj->keys[h] = key;
}

void myHashSetRemove(MyHashSet* obj, int key) {
    int h = key % hssize;
    int *keys = obj->keys;
    while(keys[h] >= 0) {
        if(keys[h] == key) {
            keys[h] = INT_MAX; // Need placeholder to find other values
            break;
        }
        if(++h == hssize) h = 0;
    }
}

bool myHashSetContains(MyHashSet* obj, int key) {
    int h = key % hssize;
    while(obj->keys[h] >= 0) {
        if(obj->keys[h] == key) return true;
        if(++h == hssize) h = 0;
    }
    return false;
}

void myHashSetFree(MyHashSet* obj) {
    free(obj->keys);
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
