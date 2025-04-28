// Root to leaf path sum equal to target

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool hasPathSum(struct TreeNode* root, int sum) {
    if (!root) return false;
    sum -= root->val;
    if (!root->left && !root->right)  // if reach a leaf
        return sum == 0;
    return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
}