/*

A linked list is a set of dynamically allocated nodes, arranged in such a way that each node contains one value and one pointer. 
The pointer always points to the next member of the list. If the pointer is NULL, then it is the last node in the list.

A linked list is held using a local pointer variable which points to the first item of the list. If that pointer is also NULL, then the list is considered to be empty.

*/

#include <stdio.h>
#include <stdlib.h>

// Define the node structure for the linked list
typedef struct node {
    int val;                // The value stored in the node
    struct node *next;      // Pointer to the next node in the list
} node_t;
// Notice that we are defining the struct in a recursive manner, which is possible in C

// Function to print all elements in the linked list
void print_list(node_t *head) {
    node_t *current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

// Function to add a new node at the end of the linked list
void append(node_t *head, int val) {
    node_t *current = head;
    // Traverse to the end of the list
    while (current->next != NULL) {
        current = current->next;
    }

    // Allocate memory for the new node
    current->next = malloc(sizeof(node_t));
    if (current->next == NULL) {
        exit(1); // Exit if memory allocation fails
    }
    current->next->val = val;
    current->next->next = NULL;
}

// Function to add a new node at the beginning of the linked list
node_t *prepend(node_t *head, int val) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        exit(1); // Exit if memory allocation fails
    }
    new_node->val = val;
    new_node->next = head;
    return new_node;
}

// Same by reference: Stack
void push(node_t **head, int val) { // Need a double pointer to modify the pointer itself
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        exit(1); // Exit if memory allocation fails
    }
    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

// Fetch first item and delete from list
int pop(node_t **head) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head); // Deallocating memory pointed to by the pointer (first element of the list), not pointe itself
    *head = next_node;

    return retval;
}

int remove_last(node_t * head) {
    int retval = 0;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        return retval;
    }

    /* get to the second to last node in the list */
    node_t * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;

}

int remove_by_index(node_t ** head, int n) {
    int i = 0;
    int retval = -1;
    node_t * current = *head;
    node_t * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    if (current->next == NULL) {
        return -1;
    }

    temp_node = current->next;
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return retval;

}



// // Function to remove the first node with a specific value
// void remove_by_value(node_t ** head, int val) {
//     node_t * current = *head;
//     if(current == NULL) {
//         return -1;
//     }
//     node_t * previous = NULL;
//     while (current->val != val && current->next != NULL) {
//         previous = current;
//         current = current->next;
//     }

//     if (current->val == val) {
//         previous->next = current->next;
//         free(current);
//     }
// }


int remove_by_value(node_t ** head, int val) {
    node_t *previous, *current;

    if (*head == NULL) {
        return -1;
    }

    if ((*head)->val == val) {
        return pop(head);
    }

    previous = *head;
    current = (*head)->next;
    while (current) {
        if (current->val == val) {
            previous->next = current->next;
            free(current);
            return val;
        }

        previous = current;
        current  = current->next;
    }
    return -1;
}


void delete_list(node_t *head) {
    node_t  *current = head, 
            *next = head;

    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
}


int main() {
    // Initialize the linked list with the first node
    node_t *head = malloc(sizeof(node_t));
    if (head == NULL) {
        return 1; // Exit if memory allocation fails
    }
    head->val = 1;
    head->next = NULL;

    // Append nodes with values 2 and 3
    append(head, 2);
    append(head, 3);

    // Prepend a node with value 0
    head = prepend(head, 0);

    // Print the current list
    printf("Initial list:\n");
    print_list(head);

    // Remove the node with value 2
    remove_by_value(&head, 2);

    // Print the modified list
    printf("\nList after removing value 2:\n");
    print_list(head);

    // Free the remaining nodes
    node_t *current = head;
    while (current != NULL) {
        node_t *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
