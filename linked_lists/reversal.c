#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} LL;

/**
 * Reverses a linked list. The function uses three pointers to traverse the linked list. 
 * It saves the next node (next), reverses the link of the current node (current->next = prev),
 * and moves the prev pointer forward (prev = current). 
 * The function then moves the current pointer forward (current = next) and repeats the process until 
 * the end of the linked list is reached. The new head of the reversed linked list is returned.
 */
LL* reverseList(LL* head) {
    LL *prev = NULL;
    LL *current = head;
    LL *next = NULL;

    while (current != NULL) {
        next = current->next;     // Save next node
        current->next = prev;     // Reverse the link
        prev = current;           // Move prev forward
        current = next;           // Move current forward
    }
    return prev;  // New head
}


LL* myReverseList(LL* head) {
    if (head == NULL) {
        return head;
    }
    LL *current = head;
    LL *next = NULL;

    while (current->next != NULL) {
        next = current->next;       // Save next node
        current->next = next->next; // Point to the one after current
        next->next = head;          // Point current to head
        head = next;                // Move head
    }
    return head;  // New head
}


/**
 * Recursively reverses a linked list.
 *
 * @param head The head of the linked list
 * @return The new head of the reversed linked list
 */
LL* reverseList2(LL* head) {
    if(head == NULL || head->next == NULL) {
        return head;
    }
    LL *newHead = reverseList2(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}

int main() {
    LL *head = malloc(sizeof(LL));
    head->val = 1;
    head->next = malloc(sizeof(LL));
    head->next->val = 2;
    head->next->next = malloc(sizeof(LL));
    head->next->next->val = 3;
    head->next->next->next = NULL;

    LL *reversed = reverseList(head);

    while (reversed != NULL) {
        printf("%d ", reversed->val);
        reversed = reversed->next;
    }
    return 0;
}