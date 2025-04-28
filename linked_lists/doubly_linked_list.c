/*
 *  Doubly-linked list – fixed version
 *
 *  Compile & run:
 *      cc -std=c17 -Wall -Wextra -pedantic dll.c -o dll
 *      ./dll
 */

 #include <stdio.h>
 #include <stdlib.h>
 
 typedef struct node {
     int             value;
     struct node    *next;
     struct node    *prev;
 } MyLinkedList;
 
 /* ------------------------------------------------------------------ */
 /*  Constructors / accessors                                           */
 
 MyLinkedList *myLinkedListCreate(void)
 /* Return an empty list (head == NULL) */
 {
     return NULL;
 }
 
 int myLinkedListGet(MyLinkedList *head, int index)
 /* Return element at position index, or –1 if out of bounds            */
 {
     int i = 0;
     while (head && i < index) {
         head = head->next;
         ++i;
     }
     return (head && i == index) ? head->value : -1;
 }
 
 /* ------------------------------------------------------------------ */
 /*  Insertion helpers                                                  */
 
 static MyLinkedList *newNode(int val)
 {
     MyLinkedList *n = malloc(sizeof *n);
     if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
     n->value = val;
     n->next  = n->prev = NULL;
     return n;
 }
 
 void myLinkedListAddAtHead(MyLinkedList **headRef, int val)
 {
     MyLinkedList *n = newNode(val);
 
     n->next = *headRef;
     if (*headRef)
         (*headRef)->prev = n;
 
     *headRef = n;
 }
 
 void myLinkedListAddAtTail(MyLinkedList **headRef, int val)
 {
     MyLinkedList *n = newNode(val);
 
     if (*headRef == NULL) {            /* empty list */
         *headRef = n;
         return;
     }
 
     MyLinkedList *cur = *headRef;
     while (cur->next)
         cur = cur->next;
 
     cur->next = n;
     n->prev   = cur;
 }
 
 void myLinkedListAddAtIndex(MyLinkedList **headRef, int index, int val)
 /* Insert before element currently at index (like vector::insert).     */
 {
     if (index < 0) return;
 
     if (index == 0) {                  /* prepend */
         myLinkedListAddAtHead(headRef, val);
         return;
     }
 
     MyLinkedList *cur = *headRef;
     int i = 0;
     while (cur && i < index - 1) {
         cur = cur->next;
         ++i;
     }
     if (!cur) return;                  /* index > length */
 
     MyLinkedList *n = newNode(val);
     n->next = cur->next;
     n->prev = cur;
 
     if (cur->next)
         cur->next->prev = n;
     cur->next = n;
 }
 
 /* ------------------------------------------------------------------ */
 /*  Deletion                                                           */
 
 void myLinkedListDeleteAtIndex(MyLinkedList **headRef, int index)
 {
     if (index < 0 || *headRef == NULL) return;
 
     MyLinkedList *cur = *headRef;
     int i = 0;
     while (cur && i < index) {
         cur = cur->next;
         ++i;
     }
     if (!cur) return;                  /* index out of bounds */
 
     if (cur->prev)
         cur->prev->next = cur->next;
     else                                /* deleting head */
         *headRef = cur->next;
 
     if (cur->next)
         cur->next->prev = cur->prev;
 
     free(cur);
 }
 
 /* ------------------------------------------------------------------ */
 /*  Destruction                                                        */
 
 void myLinkedListFree(MyLinkedList *head)
 {
     while (head) {
         MyLinkedList *next = head->next;
         free(head);
         head = next;
     }
 }
 
 /* ------------------------------------------------------------------ */
 /*  Debug helper                                                       */
 
 void printList(const MyLinkedList *head)
 {
     while (head) {
         printf("%d -> ", head->value);
         head = head->next;
     }
     puts("NULL");
 }
 
 /* ------------------------------------------------------------------ */
 /*  Demo                                                               */
 
 int main(void)
 {
     MyLinkedList *list = myLinkedListCreate();
 
     myLinkedListAddAtHead(&list, 1);
     myLinkedListAddAtTail(&list, 3);
     myLinkedListAddAtIndex(&list, 1, 2);   /* 1 -> 2 -> 3 */
     printList(list);
 
     printf("Get element at index 1: %d\n", myLinkedListGet(list, 1));
 
     myLinkedListDeleteAtIndex(&list, 1);   /* 1 -> 3      */
     printList(list);
 
     myLinkedListFree(list);
     return 0;
 }