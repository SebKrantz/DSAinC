#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

bool isPalindrome(struct ListNode* head) {
    int l = 0;
    struct ListNode* current = head;
    while(current->next) { // accepted answer is current
       current = current->next; ++l;
    }
    int counter = 0, half = l/2, half2 = l/2;
    if(l % 2 == 1) half2 += 1;
    // Used Variable Length Arrays, a C99 feature
    int lhs[half]; // = malloc(half * sizeof(int));
    int rhs[half]; // = malloc(half * sizeof(int));
    current = head;
    while(current->next) { // accepted answer is current
        if(counter < half) {
            lhs[counter] = current->val;
        } else if(counter >= half2) {
            rhs[counter % half2] = current->val;
        }
        current = current->next;
        ++counter;
    }
    bool is_pal = true;
    for(int i = 0; i < half; i++) {
       if(lhs[i] != rhs[half-i-1]) {
           is_pal = false;
           break;
       }    
    }
    // free(lhs); free(rhs);
    return is_pal;
}

// TODO: should create new list (separate copy...) Revisit!
struct ListNode* reverseList(struct ListNode* head) {
    
    struct ListNode *prev, *cur, *next;

    prev = NULL;
    cur = malloc(sizeof(struct ListNode));
    cur->val = head->val;
    cur->next = head->next;
    next = NULL;

    while (cur != NULL) {
        next = cur->next;     // Save next node
        cur->next = prev;     // Reverse the link
        prev = cur;           // Move prev forward
        cur = next;           // Move current forward
    }
    free(cur);
    return prev;
}

bool isPalindrome2(struct ListNode* head) {

    if(head == NULL) return true;
    struct ListNode *revl = reverseList(head);

    bool is_pal = true;
    while(head) {
        if(head->val != revl->val) {
            is_pal = false;
            break;
        }
        head = head->next;
        revl = revl->next;
    }

    return is_pal;
}

int main() {

    int arr1[] = {1, 2, 2, 1};
    int arr2[] = {1, 2, 1};
    int arr3[] = {1, 2, 2, 1, 1};

    struct ListNode *temp = malloc(sizeof(struct ListNode));
    struct ListNode *head = temp;
    for (int i = 0; i < sizeof(arr1) / sizeof(int); i++) {
        temp->val = arr1[i];
        printf("%d ", arr1[i]);
        temp->next = malloc(sizeof(struct ListNode));
        temp = temp->next;
    }
    temp->next = NULL;
    printf("\n%d\n", isPalindrome2(head));
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    temp = malloc(sizeof(struct ListNode));
    head = temp;
    for (int i = 0; i < sizeof(arr2) / sizeof(int); i++) {
        temp->val = arr2[i];
        printf("%d ", arr2[i]);
        temp->next = malloc(sizeof(struct ListNode));
        temp = temp->next;
    }
    temp->next = NULL;
    printf("\n%d\n", isPalindrome2(head));
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    temp = malloc(sizeof(struct ListNode));
    head = temp;
    for (int i = 0; i < sizeof(arr3) / sizeof(int); i++) {
        temp->val = arr3[i];
        printf("%d ", arr3[i]);
        temp->next = malloc(sizeof(struct ListNode));
        temp = temp->next;
    }
    temp->next = NULL;
    printf("\n%d\n", isPalindrome2(head));
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
