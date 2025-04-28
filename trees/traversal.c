/**
 * Definition for a binary tree node.
 */
struct TreeNode {
         int val;
         struct TreeNode *left;
         struct TreeNode *right;
     };
/**
 * Note: The returned array must be malloced, assume caller calls free().
 * Recursive solution:
 */

 // https://leetcode.com/explore/learn/card/data-structure-tree/134/traverse-a-tree/929/

 /**************************
  * Preorder Traversal
  * Top->Bottom
  * Left->Right
  **************************/

 // Recursive solution
void preorderHelper(struct TreeNode* root, int *a, int *j) {
    if(root) {
        a[(*j)++] = root->val;
        preorderHelper(root->left, a, j);
        preorderHelper(root->right, a, j);
    }
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int *res = (int*)malloc(100 * sizeof(int));
    *returnSize = 0;
    preorderHelper(root, res, returnSize);
    return res;
}

// Non-recursive solution: 
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = malloc(100 * sizeof(int));
    *returnSize = 0;
    struct TreeNode* stack[100];
    int top = -1;
    if (root) stack[++top] = root;
    while (top >= 0) {
        root = stack[top--];
        result[(*returnSize)++] = root->val;
        // This is correct: why? -> because stack gets last first, which is left
        if (root->right) stack[++top] = root->right;
        if (root->left) stack[++top] = root->left;
    }
    return result;
}

 /**************************
  * Inorder Traversal
  * Left->Top->Right
  **************************/

void inorderHelper(struct TreeNode* root, int *a, int *j) {
    if(!root) return;
    inorderHelper(root->left, a, j);
    a[(*j)++] = root->val;
    inorderHelper(root->right, a, j);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int *res = (int*)malloc(100 * sizeof(int));
    *returnSize = 0;
    inorderHelper(root, res, returnSize);
    return res;
}
/* Non-recursive solution: 

A minimal but clean way to fix it is to use the classic iterative‐inorder pattern “(1) walk left while pushing, (2) visit, (3) go right)”:

*/

int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
    /* --- bookkeeping ---------------------------------------------------- */
    int  capacity = 100;                /* grow if you need to */
    int* result   = malloc(capacity * sizeof(int));
    *returnSize   = 0;

    /* --- explicit stack -------------------------------------------------- */
    struct TreeNode* stack[100];
    int top = -1;

    /* --- iterative inorder ---------------------------------------------- */
    while (root || top >= 0) {
        /* 1. walk as far left as possible, pushing each node */
        while (root) {
            stack[++top] = root;
            root = root->left;
        }

        /* 2. visit the node on the top of the stack */
        root = stack[top--];
        result[(*returnSize)++] = root->val;

        /* 3. now process its right subtree */
        root = root->right;
    }

    return result;
}

 /**************************
  * Postorder Traversal
  * Bottom->Top
  * Left->Right
  **************************/

 // Recursive solution
 void postorderHelper(struct TreeNode* root, int *a, int *j) {
    if(root) {
        postorderHelper(root->left, a, j);
        postorderHelper(root->right, a, j);
        a[(*j)++] = root->val;
    }
}

int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    int *res = (int*)malloc(100 * sizeof(int));
    *returnSize = 0;
    postorderHelper(root, res, returnSize);
    return res;
}

// Non-recursive solution: 
int* postorderTraversal(struct TreeNode* root, int* returnSize)
{
    int capacity   = 100;                   /* enlarge if necessary */
    int* result    = malloc(capacity * sizeof(int));
    *returnSize    = 0;

    struct TreeNode* stack[100];
    int  top  = -1;

    struct TreeNode* prev = NULL;           /* node processed one step ago */

    /* keep going while we have a current node OR something on the stack */
    while (root || top >= 0) {

        /* 1. walk as far left as possible, pushing every node */
        while (root) {
            stack[++top] = root;
            root = root->left;
        }

        /* 2. peek the node on the top of the stack */
        root = stack[top];

        /*
           3. Two cases:

           a) Right child is absent OR already processed  -> visit the node.
           b) Otherwise, traverse the right subtree next.
        */
        if (root->right == NULL || root->right == prev) {
            /* case (a) : visit */
            result[(*returnSize)++] = root->val;
            top--;                 /* pop */
            prev = root;           /* remember we've processed it          */
            root = NULL;           /* don’t re‑enter the left-subtree loop */
        } else {
            /* case (b) : traverse right subtree */
            root = root->right;
        }
    }
    return result;
}


 /**************************
  * Breadth-First Traversal
  * Left->Right
  * Top->Bottom
  **************************/


  /* Recursive solution */

  /* Recursive C++ solution

vector<vector<int>> levels;
void helper(TreeNode* node, int level) {
    if (levels.size() == level) levels.push_back(vector<int>());
    levels[level].push_back(node->val);
    if (node->left != nullptr) helper(node->left, level + 1);
    if (node->right != nullptr) helper(node->right, level + 1);
}
vector<vector<int>> levelOrder(TreeNode* root) {
    if (root == nullptr) return levels;
    helper(root, 0);
    return levels;
}

*/

// Solution in C:

  #include <stdlib.h>

  /* LeetCode's tree‑node definition */
  struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  };
  
  /* --------------------------------------------------------------- */
  /* Recursive worker (exact analogue of the C++ helper method)      */
  static void helper(struct TreeNode      *node,
                     int                   level,
                     int                ***levels,          /* -> rows      */
                     int                  *returnSize,      /* -> #levels   */
                     int               ***returnColSizes)   /* -> widths    */
  {
      if (!node) return;
  
      /* ---------- first time we reach this depth? ---------------- */
      if (*returnSize == level) {
          /* grow the outer vector by one row                      */
          *levels = realloc(*levels, (level + 1) * sizeof(int *));
          **returnColSizes = realloc(**returnColSizes, (level + 1) * sizeof(int));
  
          /* initialise that new row                               */
          (*levels)[level]          = NULL;
          (**returnColSizes)[level] = 0;
          (*returnSize)++;                          /* increment #levels */
      }
  
      /* ---------- append current value to its level ------------- */
      int idx = (**returnColSizes)[level];                  /* old length  */
      (*levels)[level] = realloc((*levels)[level], (idx + 1) * sizeof(int));
      (*levels)[level][idx] = node->val;
      (**returnColSizes)[level]++;                           /* new length */
  
      /* ---------- recurse on children --------------------------- */
      helper(node->left,  level + 1, levels, returnSize, returnColSizes);
      helper(node->right, level + 1, levels, returnSize, returnColSizes);
  }
  
  /* --------------------------------------------------------------- */
  /* Public API (LeetCode style)                                     */
  
  int** levelOrder(struct TreeNode* root,
                   int* returnSize,
                   int** returnColumnSizes)
  {
      int **levels = NULL;          /* vector<vector<int>> analogue */
      *returnSize        = 0;       /* initially no levels          */
      *returnColumnSizes = NULL;    /* widths array starts empty    */
  
      if (root) helper(root, 0, &levels, returnSize, &returnColumnSizes);
  
      /* When the tree is empty, both pointers remain NULL, which   */
      /* is acceptable in LeetCode's contract                       */
      return levels;
  }
  
  /* --------------------------------------------------------------- */
  /* Optional disposer                                               */
  void freeLevels(int **levels, int *colSizes, int numLevels)
  {
      for (int i = 0; i < numLevels; ++i)
          free(levels[i]);
      free(levels);
      free(colSizes);
  }



// Now an iterative (queue) solution
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    int** res = malloc(sizeof(int*));
    *returnColumnSizes = malloc(sizeof(int));
    *returnSize = 0;
    if (root == NULL) return res;

    struct TreeNode* queue[10000];
    int front = 0, rear = -1, lastLevelNode = 0, cnt = 1;
    queue[++rear] = root;

    while (cnt > 0) {
        int* level = malloc(sizeof(int) * cnt);
        *returnColumnSizes =
        realloc(*returnColumnSizes, sizeof(int) * (*returnSize + 1));
        (*returnColumnSizes)[*returnSize] = cnt;
        for (int i = 0; i < cnt; i++) {
            struct TreeNode* node = queue[front++];
            level[i] = node->val;
            if (node->left != NULL) queue[++rear] = node->left;
            if (node->right != NULL) queue[++rear] = node->right;
        }
        res = realloc(res, sizeof(int*) * (*returnSize + 1));
        res[(*returnSize)++] = level;
        cnt = rear - lastLevelNode;
        lastLevelNode = rear;
    }
    return res;
}





// Iterative solution: with linked list queue

#include <stdlib.h>

// Define the TreeNode structure
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Define a generic queue node
typedef struct QueueNode {
    void* data;
    struct QueueNode* next;
} QueueNode;

// Define a queue
typedef struct Queue {
    QueueNode* head;
    QueueNode* tail;
} Queue;

// Create a new queue
Queue* createQueue() {
    Queue* queue = malloc(sizeof(Queue));
    queue->head = queue->tail = NULL;
    return queue;
}

// Add an element to the queue
void enqueue(Queue* queue, void* data) {
    QueueNode* node = malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;
    if (queue->tail == NULL) {
        queue->head = queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
}

// Remove an element from the queue
void* dequeue(Queue* queue) {
    if (queue->head == NULL) return NULL;
    QueueNode* node = queue->head;
    void* data = node->data;
    queue->head = node->next;
    if (queue->head == NULL) queue->tail = NULL;
    free(node);
    return data;
}

// Check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->head == NULL;
}

// Get the size of the queue
size_t getQueueSize(Queue* queue) {
    size_t count = 0;
    for (QueueNode* node = queue->head; node != NULL; node = node->next) {
        count++;
    }
    return count;
}

// Perform a level order traversal of a binary tree
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (root == NULL) return NULL;

    Queue* queue = createQueue();
    enqueue(queue, root);

    int** levels = malloc(2000 * sizeof(int*));
    *returnColumnSizes = malloc(2000 * sizeof(int));

    while (!isQueueEmpty(queue)) {
        int levelSize = getQueueSize(queue);
        levels[*returnSize] = malloc(levelSize * sizeof(int));
        (*returnColumnSizes)[*returnSize] = levelSize;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = dequeue(queue);
            levels[*returnSize][i] = node->val;
            if (node->left) enqueue(queue, node->left);
            if (node->right) enqueue(queue, node->right);
        }
        (*returnSize)++;
    }
    return levels;
}
