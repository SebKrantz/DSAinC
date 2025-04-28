#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
      int val;
      struct ListNode *next;
};

struct ListNode* removeElements(struct ListNode* head, int val) {
  if (head != NULL) {
      if(head->val == val) return removeElements(head->next, val);
      if(head->next != NULL) {
         head->next = removeElements(head->next, val);
      }
  }
  return head;
}

// More parsimonious:
struct ListNode* removeElements1(struct ListNode* head, int val) {
    if (head == NULL) return NULL;
    head->next = removeElements(head->next, val);
    return (head->val == val) ? head->next : head;
}



/**
 * Removes all elements from a linked list that have a specific value.
 *
 * This function iterates through the linked list and removes nodes
 * containing the specified value `val`. It handles the case where
 * the head of the list may need to be removed by updating the head
 * pointer to the first node that does not contain `val`. It then
 * traverses the list, maintaining a previous node pointer to adjust
 * the links when a node with the target value is found and removed.
 *
 * @param head The head of the linked list.
 * @param val The value to be removed from the list.
 * @return The head of the modified list with the target value removed.
 */

struct ListNode* removeElements2(struct ListNode* head, int val) {
    while (head != NULL && head->val == val) {
        head = head->next;
    }
    if (head == NULL) return head;
    struct ListNode *prev = head, *current = head->next;
    while (current != NULL) {
        if (current->val == val) {
            prev->next = current->next;
        } else prev = current;
        current = current->next;
    }
    return head;
  }

  int main() {
    struct ListNode *head = malloc(sizeof(struct ListNode));
    head->val = 1;
    head->next = malloc(sizeof(struct ListNode));
    head->next->val = 2;
    head->next->next = malloc(sizeof(struct ListNode));
    head->next->next->val = 2;
    head->next->next->next = NULL;
    
    struct ListNode *head2 = head;
    while (head2 != NULL) {
        printf("%d ", head2->val);
        head2 = head2->next;
    }
    printf("\n");

    removeElements1(head, 2);

    head2 = head;
    while (head2 != NULL) {
        printf("%d ", head2->val);
        head2 = head2->next;
    }
    printf("\n");

    return 0;
  }