

typedef struct TNode {
    int val;
    struct TNode *left;
    struct TNode *right;
} TreeNode;


// Top-down solution

void maximum_depth_td(struct TreeNode* root, int* answer, int depth) {
    if (!root) return;
    if (!root->left && !root->right) {
        *answer = fmax(*answer, depth);
    }
    maximum_depth_td(root->left, answer, depth + 1);
    maximum_depth_td(root->right, answer, depth + 1);
}

int maxDepthtd(struct TreeNode* root) {
    int answer = 0; 
    maximum_depth_td(root, &answer, 1);
    return answer;
}

// Bottom-up solution

int maxDepth(TreeNode* root) {
    if(!root) return 0;
    return 1 + fmax(maxDepth(root->left), maxDepth(root->right));
}

/*

It is not easy to understand recursion and find a recursive solution for the problem. It needs practice.

When you meet a tree problem, ask yourself two questions: Can you determine some parameters 
to help the node know its answer? Can you use these parameters and the value of the node itself to 
determine what should be the parameters passed to its children? If the answers are both yes, try to 
solve this problem using a "top-down" recursive solution.

Or, you can think of the problem in this way: for a node in a tree, if you know the answer of its children, 
can you calculate the answer of that node? If the answer is yes, solving the problem recursively using a bottom-up 
approach might be a good idea.

In the following sections, we provide several classic problems for you to help you understand tree structure and 
recursion better.

*/