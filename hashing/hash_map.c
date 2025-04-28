#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int * keys;
    int * values;
    // Optional: used array to detect collisions
} MyHashMap;

#define hssize 25000

MyHashMap* myHashMapCreate() {
    MyHashMap *m = malloc(sizeof(MyHashMap));
    m->keys = malloc(hssize * sizeof(int));
    m->values = malloc(hssize * sizeof(int));
    memset(m->keys, -1, hssize * sizeof(int)); // Optional: used array to detect collisions
    return m;
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
    int h = key % hssize;
    while(obj->keys[h] >= 0) {
        if(obj->keys[h] == key) break;
        if(++h >= hssize) h = 0;
    }
    obj->keys[h] = key;
    obj->values[h] = value;
}

int myHashMapGet(MyHashMap* obj, int key) {
    int h = key % hssize;
    while(obj->keys[h] >= 0) {
        if(obj->keys[h] == key) return obj->values[h];
        if(++h >= hssize) h = 0;
    }
    return -1;
}

void myHashMapRemove(MyHashMap* obj, int key) {
    int h = key % hssize;
    while(obj->keys[h] >= 0) {
        if(obj->keys[h] == key) {
            obj->keys[h] = INT_MAX; // Need placeholder to find other values
            break;
        }
        if(++h >= hssize) h = 0;
    }
}

void myHashMapFree(MyHashMap* obj) {
    free(obj->keys);
    free(obj->values);
    free(obj);
}

int main() {
    MyHashMap* obj = myHashMapCreate();
    
    // Put key-value pairs
    myHashMapPut(obj, 1, 10);
    myHashMapPut(obj, 2, 20);
    myHashMapPut(obj, 3, 30);

    // Get values
    printf("Get key 1: %d\n", myHashMapGet(obj, 1)); // Should print 10
    printf("Get key 2: %d\n", myHashMapGet(obj, 2)); // Should print 20
    printf("Get key 3: %d\n", myHashMapGet(obj, 3)); // Should print 30
    printf("Get key 4: %d\n", myHashMapGet(obj, 4)); // Should print -1 (not found)

    // Remove a key
    myHashMapRemove(obj, 2);
    printf("Get key 2 after removal: %d\n", myHashMapGet(obj, 2)); // Should print -1

    // Free the hash map
    myHashMapFree(obj);

    return 0;
}
