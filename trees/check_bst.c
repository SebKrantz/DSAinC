/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
*/
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;

/* Pseudocode: 
isbst(tree t) {
 if(isEmpty(t)) 
    return true
 if(isEmpty(right(t)))
    return root(left(t)) < root(t) and isbst(left(t))
 if(isEmpty(left(t)))
    return root(right(t)) > root(t) and isbst(right(t))
 return root(left(t)) < root(t) < root(right(t)) and isbst(left(t)) and isbst(right(t))
}
*/

#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Problematic
bool checkBST(Node* root) {
    if(!root || (!root->left && !root->right)) return true;    
    if(!root->right) return root->left->data < root->data && checkBST(root->left);
    if(!root->left) return root->right->data > root->data && checkBST(root->right);
    return root->left->data < root->data && root->data < root->right->data && checkBST(root->left) && checkBST(root->right);
}

// Better: https://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/

// [Approach – 1] Using specified range of Min and Max Values – O(n) Time and O(h) Space
// Helper function to check if a tree is BST within a given range
bool isBSTUtil(Node* node, int min, int max) {
    if (node == NULL) return true;

    // If the current node's data 
    // is not in the valid range, return false
    if (node->data < min || node->data > max) return false;

    // Recursively check the left and 
    // right subtrees with updated ranges
    return isBSTUtil(node->left, min, node->data - 1) &&
           isBSTUtil(node->right, node->data + 1, max);
}

// Function to check if the entire binary tree is a BST
bool checkBST(Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

// OR: Also accommodates NULL children

bool validate(struct TreeNode* root, struct TreeNode* low, struct TreeNode* high) {
    // Empty trees are valid BSTs.
    if (root == NULL) return true;
    
    // The current node's value must be between low and high.
    if ((low != NULL && root->val <= low->val) ||
        (high != NULL && root->val >= high->val)) {
        return false;
    }
    // The left and right subtree must also be valid.
    return validate(root->right, root, high) && validate(root->left, low, root);
}
bool isValidBST(struct TreeNode* root) { return validate(root, NULL, NULL); }

// [Approach – 2] Using Inorder Traversal – O(n) Time and O(h) Space


// Recursive Function for inorder traversal
int isValidBST(Node* root, int* prev) {
    if (root == NULL) return 1;

    // Recursively check the left subtree
    if (!isValidBST(root->left, prev)) return 0;

    // Check the current node value against the previous value
    if (*prev >= root->data) return 0;

    // Update the previous value to the current node's value
    *prev = root->data;

    // Recursively check the right subtree
    return isValidBST(root->right, prev);
}

// Wrapper function to initialize previous value 
// and call the recursive function
int isBST(Node* root) {
    int prev = INT_MIN;
    return isValidBST(root, &prev);
}

// [Approach – 3] Using Morris Traversal – O(n) Time and O(1) Space

// Function to check if the binary tree is 
// a BST using Morris Traversal
int isBST(Node* root) {
    Node* curr = root;
    Node* pre;
    int prevValue = INT_MIN; 

    while (curr != NULL) {
        if (curr->left == NULL) {
          
            // Process curr node
            if (curr->data <= prevValue) {
              
                // Not in ascending order
                return 0; 
            }
            prevValue = curr->data;
            curr = curr->right;
        } else {
          
            // Find the inorder predecessor of curr
            pre = curr->left;
            while (pre->right != NULL && pre->right != curr) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
              
                // Create a temporary thread to the curr node
                pre->right = curr;
                curr = curr->left;
            } else {
              
                // Remove the temporary thread
                pre->right = NULL;

                // Process the curr node
                if (curr->data <= prevValue) {
                  
                    // Not in ascending order
                    return 0; 
                }
                prevValue = curr->data;
                curr = curr->right;
            }
        }
    }

    return 1; 
}
