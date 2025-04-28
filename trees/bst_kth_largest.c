/*  kth_largest_bst.c ─ C translation of the C++ “KthLargest” class
 *
 *  Build a size-augmented binary-search tree and return the k-th
 *  largest element after each insertion.
 *
 *  The public interface replicates LeetCode’s C binding:
 *
 *      struct KthLargest *kthLargestCreate(int k,
 *                                          int *nums,
 *                                          int numsSize);
 *      int  kthLargestAdd(struct KthLargest *obj, int val);
 *      void kthLargestFree(struct KthLargest *obj);
 *
 *  Compile / demo:
 *      cc -std=c17 -O2 kth_largest_bst.c -o kth
 *      ./kth
 */

 // https://leetcode.com/explore/learn/card/introduction-to-data-structure-binary-search-tree/142/conclusion/1018/

#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------ */
/*  Node definition                                                   */

typedef struct Node {
    int            val;      /* key                               */
    int            cnt;      /* size of the subtree rooted here   */
    struct Node   *left;
    struct Node   *right;
} Node;

/* allocate & initialise a new node */
static Node *node_new(int v)
{
    Node *n   = malloc(sizeof *n);
    n->val    = v;
    n->cnt    = 1;
    n->left   = n->right = NULL;
    return n;
}

/* ------------------------------------------------------------------ */
/*  BST helpers                                                       */

/* insert num into subtree rooted at root; return (possibly new) root */
static Node *insertNode(Node *root, int num)
{
    if (!root)
        return node_new(num);

    if (root->val < num)
        root->right = insertNode(root->right, num);
    else
        root->left  = insertNode(root->left,  num);

    root->cnt++;                    /* update subtree size */
    return root;
}

/* return k-th largest key (1-based) in subtree rooted at root */
static int searchKth(Node *root, int k)
{
    int m = root->right ? root->right->cnt : 0;   /* size right subtree */

    if (k == m + 1)
        return root->val;

    if (k <= m)
        return searchKth(root->right, k);         /* stay right  */
    else
        return searchKth(root->left, k - m - 1);  /* go left */
}

/* post-order deletion */
static void node_free(Node *root)
{
    if (!root) return;
    node_free(root->left);
    node_free(root->right);
    free(root);
}

/* ------------------------------------------------------------------ */
/*  Object that mimics the C++ class                                  */

typedef struct KthLargest {
    Node *root;
    int   k;
} KthLargest;

struct KthLargest *
kthLargestCreate(int k, int *nums, int numsSize)
{
    KthLargest *obj = malloc(sizeof *obj);
    obj->root = NULL;
    obj->k    = k;

    for (int i = 0; i < numsSize; ++i)
        obj->root = insertNode(obj->root, nums[i]);

    return obj;
}

int kthLargestAdd(struct KthLargest *obj, int val)
{
    obj->root = insertNode(obj->root, val);
    return searchKth(obj->root, obj->k);
}

void kthLargestFree(struct KthLargest *obj)
{
    node_free(obj->root);
    free(obj);
}

/* ------------------------------------------------------------------ */
/*  Small demo                                                        */

#define DEMO

#ifdef DEMO
int main(void)
{
    int init[] = {4, 5, 8, 2};
    KthLargest *kl = kthLargestCreate(3, init, 4);

    printf("%d\n", kthLargestAdd(kl, 3));  /* -> 4 */
    printf("%d\n", kthLargestAdd(kl, 5));  /* -> 5 */
    printf("%d\n", kthLargestAdd(kl, 10)); /* -> 5 */
    printf("%d\n", kthLargestAdd(kl, 9));  /* -> 8 */
    printf("%d\n", kthLargestAdd(kl, 4));  /* -> 8 */

    kthLargestFree(kl);
    return 0;
}
#endif