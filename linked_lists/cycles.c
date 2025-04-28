// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
 };
 
typedef struct ListNode ListNode;

bool hasCycle(ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }

    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;           // move 1 step
        fast = fast->next->next;     // move 2 steps

        if (slow == fast) {
            return true;  // fast caught up with slow → cycle
        }
    }

    return false;  // fast reached NULL → no cycle
}


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    // Initialize tortoise and hare pointers
    struct ListNode *tortoise = head;
    struct ListNode *hare = head;
    if (head == NULL || head->next == NULL) {
        return NULL;
    }
    // Move tortoise one step and hare two steps
    do {
        tortoise = tortoise->next;
        hare = hare->next->next;
    } while (hare != NULL && hare->next != NULL && tortoise != hare);
    // Check if there is no cycle
    if (hare == NULL || hare->next == NULL) {
        return NULL;
    }
    // Reset the hare pointer to the head
    hare = head;
    // Move both pointers one step until they meet again
    while (tortoise != hare) {
        tortoise = tortoise->next;
        hare = hare->next;
    }
    // Return the node where the cycle begins
    return tortoise;
}