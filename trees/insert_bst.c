/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    if(!root) {
        struct TreeNode* n = malloc(sizeof *n);
        n->val = val;
        n->left = NULL,
        n->right = NULL;
        return n;
    }
    if (root->val < val) {           // insert to the right subtree if val > root->val
        root->right = insertIntoBST(root->right, val);
    } else {                        // insert to the left subtree if val <= root->val
        root->left = insertIntoBST(root->left, val);
    }
    return root;
}