/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if(root==NULL||root->val==val)
    {
        return root;
    }
    else if(val>root->val)
    {
        return searchBST(root->right,val);
    }
    else if(val<root->val)
    {
        return searchBST(root->left,val);
    }
    else
    {
        return root;
    }
    
}

// This algorithm searches a general binary tree for a specific value.

struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if(!root) return NULL; 
    if(root->val == val) return root;
    struct TreeNode* n = searchBST(root->left, val);
    if(n) return n; 
    n = searchBST(root->right, val);
    if(n) return n;
    return NULL;
}
