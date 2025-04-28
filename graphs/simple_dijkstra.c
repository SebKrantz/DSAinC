/*
 *  dijkstra_v1.c ― the “simplest” O(V²) implementation that follows
 *  the textbook description you supplied:  
 *
 *      – keep an array D[ ] of overestimates (initially 0 / ∞)  
 *      – keep an array tight[ ] telling which estimates are already
 *        known to be tight (i.e. final)  
 *      – at each round pick the still-loose vertex with minimal D,
 *        make it tight, relax its outgoing edges
 *
 *  The program expects
 *      • number of vertices V  (vertices are numbered 0 … V-1)
 *      • number of directed edges E
 *      • then E triples:  u  v  w   (edge u→v with weight w > 0)
 *      • finally the start vertex s
 *
 *  Compile:   cc -std=c17 -O2 dijkstra_v1.c  -o dijkstra
 *  Run example:
 *      echo "5 7
 *            0 1 10
 *            0 3  5
 *            1 2  1
 *            1 3  2
 *            2 4  4
 *            3 1  3
 *            3 2  9
 *            0" | ./dijkstra
 *
 *  Output: 0 8 9 5 13
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF (INT_MAX / 2)      /* “infinite” distance (avoid overflow) */

/* ------------------------------------------------------------------ */
/* Build an adjacency-matrix filled with INF.                          */

static int **create_matrix(int n)
{
    int **m = malloc(n * sizeof *m);
    for (int i = 0; i < n; ++i) {
        m[i] = malloc(n * sizeof **m);
        for (int j = 0; j < n; ++j)
            m[i][j] = INF;              /* no edge by default         */
    }
    return m;
}

/* ------------------------------------------------------------------ */
/* The textbook (O(V²)) Dijkstra.  `weight` is the adjacency matrix.  */
/* On return, D[] holds the shortest-path lengths from source s.      */

static void dijkstra(int **weight, int V, int s, int *D)
{
    bool *tight = calloc(V, sizeof *tight);   /* all false            */

    /*  --- initial overestimates ---------------------------------- */
    for (int z = 0; z < V; ++z)
        D[z] = (z == s) ? 0 : INF;

    /*  --- main loop: V iterations -------------------------------- */
    for (int iter = 0; iter < V; ++iter) {

        /* find a still-loose vertex u with minimal D[u] */
        int u = -1, best = INF;
        for (int v = 0; v < V; ++v)
            if (!tight[v] && D[v] < best) {
                best = D[v];
                u = v;
            }

        if (u == -1) break;             /* remaining vertices unreachable */

        tight[u] = true;

        /* relax every edge u → z */
        for (int z = 0; z < V; ++z) {
            if (weight[u][z] != INF && !tight[z]) {
                if (D[u] + weight[u][z] < D[z])
                    D[z] = D[u] + weight[u][z];
            }
        }
    }

    free(tight);
}

/* ------------------------------------------------------------------ */
/* Small driver to show the algorithm in action.                      */

int main(void)
{
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) return 1;

    int **W = create_matrix(V);

    for (int k = 0; k < E; ++k) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3) return 1;
        W[u][v] = w;                     /* directed graph            */
    }

    int s;
    if (scanf("%d", &s) != 1) return 1;

    int *D = malloc(V * sizeof *D);
    dijkstra(W, V, s, D);

    /* print result */
    for (int i = 0; i < V; ++i)
        printf("%d%c", D[i], i == V - 1 ? '\n' : ' ');

    /* tidy up */
    for (int i = 0; i < V; ++i) free(W[i]);
    free(W);
    free(D);
    return 0;
}

/*

Explanation of the core steps

    Initialisation

    D[s] = 0, every other D[z] = ∞, all tight[z] = false.

    Iteration (V times)

    • Pick the still-loose vertex u with the smallest over-estimate
    • Declare it tight (tight[u] = true) – its distance is now final
    • For every outgoing edge u → z relax:
    if (D[u] + w(u,z) < D[z])  D[z] = D[u] + w(u,z);

    When every vertex is tight or unreachable, D[ ] contains the actual
    shortest-path lengths from s.

Complexities

Time: O(V²) (linear scan to choose u each round)
Space: O(V²) for the adjacency matrix plus O(V) for the arrays.

This matches the “Version 1” algorithm described in your instruction
set and is easy to verify or use as a baseline for a later O(E log V)
heap-based optimisation.

*/