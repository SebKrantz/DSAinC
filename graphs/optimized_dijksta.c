/*
 *  dijkstra_heap.c ― O((E+V) log V) implementation
 *
 *  Input format (via stdin)
 *      V  E                     number of vertices, edges
 *      u v w      (repeated E times; directed edge u→v, weight w > 0)
 *      s                         source vertex (0 … V-1)
 *
 *  Vertices are numbered 0 … V-1.  All weights must be non–negative.
 *
 *  Compile:   cc -std=c17 -O2 dijkstra_heap.c -o dijkstra
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ */
/*  adjacency list                                                    */

typedef struct Edge {
    int                to;
    int                w;
    struct Edge       *next;
} Edge;

static Edge **make_graph(int V)
{
    Edge **g = calloc(V, sizeof *g);   /* every head NULL            */
    return g;
}

static void add_edge(Edge **g, int u, int v, int w)
/* add directed edge u → v with weight w */
{
    Edge *e  = malloc(sizeof *e);
    e->to    = v;
    e->w     = w;
    e->next  = g[u];
    g[u]     = e;
}

/* ------------------------------------------------------------------ */
/*  binary min-heap that stores vertices, keyed by dist[vertex]       */

typedef struct {
    int  *heap;     /* heap[i] = vertex at position i               */
    int  *pos;      /* pos[v]  = position of vertex v inside heap   */
    int   size;
} MinHeap;

static inline void swap_heap(MinHeap *h, int i, int j)
{
    int vi = h->heap[i];
    int vj = h->heap[j];
    h->heap[i] = vj;  h->heap[j] = vi;
    h->pos[vi] = j;   h->pos[vj] = i;
}

static void sift_down(MinHeap *h, int i, const int *dist)
{
    for (;;) {
        int l = 2*i + 1;
        int r = 2*i + 2;
        int smallest = i;

        if (l < h->size && dist[h->heap[l]] < dist[h->heap[smallest]])
            smallest = l;
        if (r < h->size && dist[h->heap[r]] < dist[h->heap[smallest]])
            smallest = r;

        if (smallest == i) break;
        swap_heap(h, i, smallest);
        i = smallest;
    }
}

static void sift_up(MinHeap *h, int i, const int *dist)
{
    while (i && dist[h->heap[i]] < dist[h->heap[(i-1)/2]]) {
        swap_heap(h, i, (i-1)/2);
        i = (i-1)/2;
    }
}

static MinHeap *heap_build(int V, const int *dist)
/* heap initially contains all vertices 0 … V-1 */
{
    MinHeap *h = malloc(sizeof *h);
    h->heap = malloc(V * sizeof *h->heap);
    h->pos  = malloc(V * sizeof *h->pos);
    h->size = V;

    for (int i = 0; i < V; ++i) {
        h->heap[i] = i;
        h->pos[i]  = i;
    }
    /* Floyd build O(V) */
    for (int i = V/2 - 1; i >= 0; --i)
        sift_down(h, i, dist);

    return h;
}

static bool heap_empty(const MinHeap *h) { return h->size == 0; }

static int heap_extract_min(MinHeap *h, const int *dist)
{
    int root = h->heap[0];
    h->heap[0] = h->heap[--h->size];
    h->pos[h->heap[0]] = 0;
    sift_down(h, 0, dist);
    return root;
}

static void heap_decrease_key(MinHeap *h, int vertex, const int *dist)
{
    sift_up(h, h->pos[vertex], dist);
}

static void heap_destroy(MinHeap *h)
{
    free(h->heap);
    free(h->pos);
    free(h);
}

/* ------------------------------------------------------------------ */
/*  Dijkstra with heap                                                */

#define INF (INT_MAX/2)

static void dijkstra(int V, Edge **G, int s, int *dist)
{
    for (int i = 0; i < V; ++i) dist[i] = INF;
    dist[s] = 0;

    MinHeap *pq = heap_build(V, dist);

    while (!heap_empty(pq)) {
        int u = heap_extract_min(pq, dist);

        /* relax outgoing edges */
        for (Edge *e = G[u]; e; e = e->next) {
            int v = e->to;
            int alt = dist[u] + e->w;
            if (alt < dist[v]) {
                dist[v] = alt;
                heap_decrease_key(pq, v, dist);
            }
        }
    }
    heap_destroy(pq);
}

/* ------------------------------------------------------------------ */
/*  driver                                                            */

int main(void)
{
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) return 1;

    Edge **G = make_graph(V);

    for (int i = 0; i < E; ++i) {
        int u,v,w;
        if (scanf("%d %d %d", &u, &v, &w) != 3) return 1;
        add_edge(G, u, v, w);
    }
    int s;
    if (scanf("%d", &s) != 1) return 1;

    int *dist = malloc(V * sizeof *dist);
    dijkstra(V, G, s, dist);

    /* output */
    for (int i = 0; i < V; ++i)
        printf("%d%c", dist[i], i == V-1 ? '\n' : ' ');

    /* free graph */
    for (int u = 0; u < V; ++u) {
        Edge *e = G[u];
        while (e) {
            Edge *next = e->next;
            free(e);
            e = next;
        }
    }
    free(G);
    free(dist);
    return 0;
}

/*

How it works

    dist[] holds the current over-estimates (∞ except s = 0).
    A binary min-heap stores every vertex; its priority is dist[v].
    pos[v] tracks where vertex v sits inside the heap, so
    heap_decrease_key runs in O(log V).
    Main loop:
    • extract the vertex u with smallest distance
    • relax each outgoing edge u → v
    • if a shorter path is found, update dist[v] and
    heap_decrease_key.

Complexities

Time : O((E + V) log V)
Space : O(E + V)

which matches the requested “Version 2” analysis.

*/