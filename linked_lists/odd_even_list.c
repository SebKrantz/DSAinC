/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* oddEvenList(struct ListNode* head) {
    if(head == NULL) return head;
    struct ListNode *current = head->next, *prev = head;
    struct ListNode *evenlist = NULL, *evenhead = NULL;
    int index = 0;
    
    while (current != NULL) {
        if(index % 2 == 0) {
            if (evenhead == NULL) {
                evenlist = current;
                evenhead = evenlist;
            } else {
                evenlist->next = current;
                evenlist = evenlist->next;
            }
            prev->next = current->next;
        } else prev = current; 
        current = current->next;
        ++index;
    }
    if (evenlist != NULL) evenlist->next = NULL;
    prev->next = evenhead;
    return head;    
}