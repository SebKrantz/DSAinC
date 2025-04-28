#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 1000

typedef struct {
    int* keys[MAX_LEN];
    int* values[MAX_LEN];
    int sizes[MAX_LEN];
} MyHashMap;

MyHashMap* myHashMapCreate() {
    MyHashMap* obj = (MyHashMap*)malloc(sizeof(MyHashMap));
    for (int i = 0; i < MAX_LEN; i++) {
        obj->keys[i] = NULL;
        obj->values[i] = NULL;
        obj->sizes[i] = 0;
    }
    return obj;
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
    int index = key % MAX_LEN;
    for (int i = 0; i < obj->sizes[index]; i++) {
        if (obj->keys[index][i] == key) {
            obj->values[index][i] = value;
            return;
        }
    }
    obj->keys[index] = realloc(obj->keys[index], (obj->sizes[index] + 1) * sizeof(int));
    obj->values[index] = realloc(obj->values[index], (obj->sizes[index] + 1) * sizeof(int));
    obj->keys[index][obj->sizes[index]] = key;
    obj->values[index][obj->sizes[index]] = value;
    obj->sizes[index]++;
}

int myHashMapGet(MyHashMap* obj, int key) {
    int index = key % MAX_LEN;
    for (int i = 0; i < obj->sizes[index]; i++) {
        if (obj->keys[index][i] == key) {
            return obj->values[index][i];
        }
    }
    return -1;
}

void myHashMapRemove(MyHashMap* obj, int key) {
    int index = key % MAX_LEN;
    for (int i = 0; i < obj->sizes[index]; i++) {
        if (obj->keys[index][i] == key) {
            for (int j = i; j < obj->sizes[index] - 1; j++) {
                obj->keys[index][j] = obj->keys[index][j + 1];
                obj->values[index][j] = obj->values[index][j + 1];
            }
            obj->sizes[index]--;
            obj->keys[index] = realloc(obj->keys[index], obj->sizes[index] * sizeof(int));
            obj->values[index] = realloc(obj->values[index], obj->sizes[index] * sizeof(int));
            return;
        }
    }
}

void myHashMapFree(MyHashMap* obj) {
    for (int i = 0; i < MAX_LEN; i++) {
        free(obj->keys[i]);
        free(obj->values[i]);
    }
    // Don't need to free arrays themselves because allocated on stack (not dynamically allocated)
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

// /*
// C++:

// #define MAX_LEN 100000            // the amount of buckets

// class MyHashMap {
// private:
//     vector<pair<int, int>> map[MAX_LEN];       // hash map implemented by array
    
//     /** Returns the corresponding bucket index. */
//     int getIndex(int key) {
//         return key % MAX_LEN;
//     }
    
//     /** Search the key in a specific bucket. Returns -1 if the key does not existed. */
//     int getPos(int key, int index) {
//         // Each bucket contains a vector. Iterate all the elements in the bucket to find the target key.
//         for (int i = 0; i < map[index].size(); ++i) {
//             if (map[index][i].first == key) {
//                 return i;
//             }
//         }
//         return -1;
//     }
    
// public:
//     /** Initialize your data structure here. */
//     MyHashMap() {
        
//     }
    
//     /** value will always be positive. */
//     void put(int key, int value) {
//         int index = getIndex(key);
//         int pos = getPos(key, index);
//         if (pos < 0) {
//             map[index].push_back(make_pair(key, value));
//         } else {
//             map[index][pos].second = value;
//         }
//     }
    
//     /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
//     int get(int key) {
//         int index = getIndex(key);
//         int pos = getPos(key, index);
//         if (pos < 0) {
//             return -1;
//         } else {
//             return map[index][pos].second;
//         }
//     }
    
//     /** Removes the mapping of the specified value key if this map contains a mapping for the key */
//     void remove(int key) {
//         int index = getIndex(key);
//         int pos = getPos(key, index);
//         if (pos >= 0) {
//             map[index].erase(map[index].begin() + pos);
//         }
//     }
// };

// /**
//  * Your MyHashMap object will be instantiated and called as such:
//  * MyHashMap obj = new MyHashMap();
//  * obj.put(key,value);
//  * int param_2 = obj.get(key);
//  * obj.remove(key);
//  */

// */