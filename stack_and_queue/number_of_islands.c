/*
Naive solution below doesn't handle this array:

 [["1","0","1","1","1"],
  ["1","0","1","0","1"],
  ["1","1","1","0","1"]]

*/

 int numIslands_naive(char** grid, int gridSize, int* gridColSize) {
    int num = 0;
    char top[gridSize * 100];
    memset(top, '0', gridSize * 100 * sizeof(char));
    // printf("nrow = %d", gridSize);
    
    int check;
    for (int r = 0; r < gridSize; r++) {
        char *row_r = grid[r];
        char prev = '0';
        for(int c = 0; c < gridColSize[r]; c++) {
            if(row_r[c] == '1' && prev != '1' && top[c] != '1') {
                ++num; check = c;
                while(++check < gridColSize[r] && row_r[check] == '1') {
                    if(top[check] == '1') {
                        --num; break; 
                    };
                }
            }
            top[c] = prev = row_r[c];
        }
    }
    return num;    
}

// https://leetcode.com/problems/number-of-islands/discuss/1006/Short-and-Simple-C%2B%2B-solution

// DFS Solution: Uses the call stack

int dirs[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// Recursion using the call stack (basically we keep pushing neighbours down the stack when we find a 1, implying we wonder off away from the neighbours)
 void dfs(char** grid, int r, int c, int m, int n) {
    for(int i = 0; i < 4; i++) {
        int nr = r + dirs[i][0];
        int nc = c + dirs[i][1];

        if(nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == '1') {
            grid[nr][nc] = '0';
            // Basically explore the neighbors in the 4 directions (go along the first direction and then again the first that matches)
            dfs(grid, nr, nc, m, n);
        }
    }
 }
 
 int numIslands(char** grid, int gridSize, int* gridColSize) {
    int num = 0;
    for (int r = 0; r < gridSize; r++) {
        for(int c = 0; c < gridColSize[r]; c++) {
            if(grid[r][c] == '1') {
                ++num; // DFS sets visited to 0
                dfs(grid, r, c, gridSize, gridColSize[r]);
            }
        }
    }
    return num;    
}

// Another nice solution from leetcode: 

void dfs(char** grid, int i, int j, int rows, int cols) {
    // Check bounds and stop if it's water or already visited
    if (i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] == '0')
        return;

    // Mark the land as visited
    grid[i][j] = '0';

    // Explore all 4 directions
    dfs(grid, i + 1, j, rows, cols);
    dfs(grid, i - 1, j, rows, cols);
    dfs(grid, i, j + 1, rows, cols);
    dfs(grid, i, j - 1, rows, cols);
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    if (grid == NULL || gridSize == 0 || gridColSize == NULL)
        return 0;

    int count = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == '1') {
                count++;
                dfs(grid, i, j, gridSize, gridColSize[i]);
            }
        }
    }
    return count;
}

// BFS Solution

// Idea: First explore all the neighbours! 
// We need a queue to do this (first in first out, implying we visit the neighbours first)

void bfs(char** grid, int r, int c, int m, int n) {

    int queue[1000][2];
    int front = -1, rear = 0; // OR head = 0, tail = 0

    queue[rear][0] = r;
    queue[rear][1] = c;

    while (front < rear) {
        int r = queue[++front][0];
        int c = queue[front][1];

        for(int i = 0; i < 4; i++) {
            int nr = r + dirs[i][0];
            int nc = c + dirs[i][1];
    
            if(nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == '1') {
                grid[nr][nc] = '0'; 
                queue[++rear][0] = nr;
                queue[rear][1] = nc;
            }
        }
    }
 }
 
 int numIslandsBFS(char** grid, int gridSize, int* gridColSize) {
    int num = 0;
    for (int r = 0; r < gridSize; r++) {
        for(int c = 0; c < gridColSize[r]; c++) {
            if(grid[r][c] == '1') {
                ++num; // BFS sets visited to 0
                bfs(grid, r, c, gridSize, gridColSize[r]);
            }
        }
    }
    return num;    
}

// Now immplementing a proper circular queue for BFS

#include <stdio.h>
#include <stdlib.h>

int dirs[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

/* ------------------- circular-queue of coordinate pairs ---------- */
typedef struct {
    int (*data)[2];     /* array of “int[2]”  – stored by value   */
    int head;
    int tail;
    int size;           /* capacity                               */
} Queue;

Queue *initQueue(int size)
{
    Queue *q = malloc(sizeof *q);
    q->data  = malloc(size * sizeof *q->data);   /* one allocation */
    q->head  = 0;
    q->tail  = 0;
    q->size  = size;
    return q;
}

void freeQueue(Queue *q)
{
    free(q->data);
    free(q);
}

static inline int isEmpty(Queue *q)
{
    return q->head == q->tail;
}

static inline int isFull(Queue *q)
{
    return (q->tail + 1) % q->size == q->head;   /* one slot wasted */
}

void enqueue(Queue *q, int r, int c)
{
    if (isFull(q)) { fprintf(stderr, "queue full\n"); exit(EXIT_FAILURE); }
    q->data[q->tail][0] = r;
    q->data[q->tail][1] = c;
    q->tail = (q->tail + 1) % q->size;
}

void dequeue(Queue *q, int *r, int *c)
{
    if (isEmpty(q)) { fprintf(stderr, "queue empty\n"); exit(EXIT_FAILURE); }
    *r = q->data[q->head][0];
    *c = q->data[q->head][1];
    q->head = (q->head + 1) % q->size;
}

/* ---------------------------- BFS -------------------------------- */
void bfs(char **grid, int r, int c, int m, int n)
{
    Queue *q = initQueue(1024);          /* choose a safe bound       */

    enqueue(q, r, c);
    grid[r][c] = '0';                    /* mark source visited  */   /* FIX */

    while (!isEmpty(q)) {
        dequeue(q, &r, &c);

        for (int i = 0; i < 4; ++i) {
            int nr = r + dirs[i][0];
            int nc = c + dirs[i][1];

            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == '1') {
                grid[nr][nc] = '0';      /* mark & enqueue once  */
                enqueue(q, nr, nc);
            }
        }
    }
    freeQueue(q);
}
