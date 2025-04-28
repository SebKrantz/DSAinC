typedef struct node {
    int value;
    struct node * next;
} MyLinkedList;

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* newLL = malloc(sizeof(MyLinkedList));
    if (newLL == NULL) {
        exit(1); // Exit if memory allocation fails
    }
    newLL->next = NULL;
    return newLL;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    int i = 0;
    while(obj != NULL && i < index) {
        obj = obj->next; ++i; 
    }
    return obj ? obj->value : -1;
}

void myLinkedListAddAtHead(MyLinkedList** obj, int val) {
    MyLinkedList* newNode = malloc(sizeof(MyLinkedList));
    if (newNode == NULL) {
        exit(1); // Exit if memory allocation fails
    }
    newNode->value = val;
    newNode->next = *obj;
    *obj = newNode;
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList* newNode = malloc(sizeof(MyLinkedList));
    if (newNode == NULL) {
        exit(1); // Exit if memory allocation fails
    }
    newNode->value = val;
    newNode->next = NULL;
    while(obj->next != NULL) {
        obj = obj->next; 
    }
    obj->next = newNode;
}

void myLinkedListAddAtIndex(MyLinkedList** obj, int index, int val) {
    if (index == 0) {
        myLinkedListAddAtHead(obj, val);
        return;
    }
    MyLinkedList* newNode = malloc(sizeof(MyLinkedList));
    if (newNode == NULL) {
        exit(1); // Exit if memory allocation fails
    }
    int i = 0;
    MyLinkedList* current = *obj;
    while(current != NULL && i < index-1) {
        current = current->next; ++i;
    }
    if(i != index-1) return;
    newNode->value = val;
    newNode->next = current->next;
    current->next = newNode;
}

void myLinkedListDeleteAtIndex(MyLinkedList** obj, int index) {
    if (index == 0 && *obj != NULL) {
        MyLinkedList* temp = *obj;
        *obj = (*obj)->next;
        free(temp);
        return;
    }
    int i = 0;
    MyLinkedList* current = *obj;
    while(current != NULL && i < index-1) {
        current = current->next; ++i;
    }
    if(current == NULL || current->next == NULL) return;
    MyLinkedList* temp = current->next;
    current->next = temp->next;
    free(temp);
}

void myLinkedListFree(MyLinkedList* obj) {
    MyLinkedList* next;
    while(obj) {
        next = obj->next;
        free(obj);
        obj = next;
    }
}

void printList(MyLinkedList* obj) {
    while (obj != NULL) {
        printf("%d -> ", obj->value);
        obj = obj->next;
    }
    printf("NULL\n");
}
