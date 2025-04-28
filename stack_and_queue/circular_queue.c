#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data; 
    int size;
    int front;
    int count;
} MyCircularQueue;

MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue *q = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    q->data = (int*)malloc(k * sizeof(int));
    q->size = k;
    q->front = 0;
    q->count = 0;
    return q;
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return obj->count == 0;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return obj->count == obj->size;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (myCircularQueueIsFull(obj)) return false;
    int rear = (obj->front + obj->count) % obj->size;
    obj->data[rear] = value;
    ++(obj->count);
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) return false;
    ++(obj->front);
    obj->front %= obj->size;
    --(obj->count);
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) return -1;
    return obj->data[obj->front];
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) return -1;
    int rear = (obj->front + obj->count - 1) % obj->size;
    return obj->data[rear];
}

void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->data);
    free(obj);
}

int main() {
    MyCircularQueue* queue = myCircularQueueCreate(3);

    printf("Enqueue 1: %s\n", myCircularQueueEnQueue(queue, 1) ? "Success" : "Failed");
    printf("Enqueue 2: %s\n", myCircularQueueEnQueue(queue, 2) ? "Success" : "Failed");
    printf("Enqueue 3: %s\n", myCircularQueueEnQueue(queue, 3) ? "Success" : "Failed");
    printf("Enqueue 4 (should fail): %s\n", myCircularQueueEnQueue(queue, 4) ? "Success" : "Failed");

    printf("Front item: %d\n", myCircularQueueFront(queue));
    printf("Rear item: %d\n", myCircularQueueRear(queue));

    printf("Dequeue: %s\n", myCircularQueueDeQueue(queue) ? "Success" : "Failed");
    printf("Front item after dequeue: %d\n", myCircularQueueFront(queue));

    myCircularQueueFree(queue);
    return 0;
}

// C++ Solution: 
// class MyCircularQueue {
//     private:
//         vector<int> data;
//         int head;
//         int tail;
//         int size;
//     public:
//         /** Initialize your data structure here. Set the size of the queue to be k. */
//         MyCircularQueue(int k) {
//             data.resize(k);
//             head = -1;
//             tail = -1;
//             size = k;
//         }
        
//         /** Insert an element into the circular queue. Return true if the operation is successful. */
//         bool enQueue(int value) {
//             if (isFull()) {
//                 return false;
//             }
//             if (isEmpty()) {
//                 head = 0;
//             }
//             tail = (tail + 1) % size;
//             data[tail] = value;
//             return true;
//         }
        
//         /** Delete an element from the circular queue. Return true if the operation is successful. */
//         bool deQueue() {
//             if (isEmpty()) {
//                 return false;
//             }
//             if (head == tail) {
//                 head = -1;
//                 tail = -1;
//                 return true;
//             }
//             head = (head + 1) % size;
//             return true;
//         }
        
//         /** Get the front item from the queue. */
//         int Front() {
//             if (isEmpty()) {
//                 return -1;
//             }
//             return data[head];
//         }
        
//         /** Get the last item from the queue. */
//         int Rear() {
//             if (isEmpty()) {
//                 return -1;
//             }
//             return data[tail];
//         }
        
//         /** Checks whether the circular queue is empty or not. */
//         bool isEmpty() {
//             return head == -1;
//         }
        
//         /** Checks whether the circular queue is full or not. */
//         bool isFull() {
//             return ((tail + 1) % size) == head;
//         }
//     };
    
//     /**
//      * Your MyCircularQueue object will be instantiated and called as such:
//      * MyCircularQueue obj = new MyCircularQueue(k);
//      * bool param_1 = obj.enQueue(value);
//      * bool param_2 = obj.deQueue();
//      * int param_3 = obj.Front();
//      * int param_4 = obj.Rear();
//      * bool param_5 = obj.isEmpty();
//      * bool param_6 = obj.isFull();
//      */