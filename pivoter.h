#ifndef PIVOTER_H
#define PIVOTER_H

#include <QVector>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <QDebug>

extern double combination_table[2000][2000];

struct Edge {
    int source, destination, weight, next_edge;
};

struct Graph {
public:
    int edge_count, vertex_count;
    int current_edge_index;
    int *first_edge;
    Edge *edges;

    int *in_degree, *out_degree;
    int max_in_degree, max_out_degree;
};

static void clear_graph(Graph *graph) {
    graph->current_edge_index = graph->max_in_degree = graph->max_out_degree = 0;
    std::memset(graph->first_edge, -1, sizeof(int) * (graph->vertex_count + 1));
    memset(graph->in_degree, 0, sizeof(int) * (graph->vertex_count + 1));
    memset(graph->out_degree, 0, sizeof(int) * (graph->vertex_count + 1));
}

static Graph* initialize_graph(int vertex_num, int edge_num) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->edge_count = edge_num;
    graph->vertex_count = vertex_num;
    graph->first_edge = (int *)malloc(sizeof(int) * (vertex_num + 1));
    graph->edges = (Edge *)malloc(sizeof(Edge) * (edge_num + 10));
    graph->in_degree = (int *)malloc(sizeof(int) * (vertex_num + 1));
    graph->out_degree = (int *)malloc(sizeof(int) * (vertex_num + 1));
    clear_graph(graph);
    return graph;
}

static void free_graph(Graph *graph) {
    free(graph->first_edge);
    free(graph->edges);
    free(graph->in_degree);
    free(graph->out_degree);
    free(graph);
}

static void add_edge(Graph *graph, int src, int dst, int w) {
    Edge e = {src, dst, w, graph->first_edge[src]};
    graph->edges[++graph->current_edge_index] = e;
    graph->first_edge[src] = graph->current_edge_index;
    graph->in_degree[dst]++;
    graph->out_degree[src]++;
    graph->max_in_degree = std::max(graph->in_degree[dst], graph->max_in_degree);
    graph->max_out_degree = std::max(graph->out_degree[src], graph->max_out_degree);
}

static void add_unweighted_edge(Graph *graph, int src, int dst) {
    add_edge(graph, src, dst, 0);
}

class Pivoter {
public:
    Pivoter() {};
    static void initialize_combination_table(int n);
    static Graph* core_decomposition(Graph *graph);
    static void initialize_set(int *current_set, int *position_in_set, int vertex_count);
    static void insert_into_set(int *current_set, int *position_in_set, int vertex);
    static void remove_from_set(int *current_set, int *position_in_set, int vertex);
    static void pivot_dfs(int *current_set, int *position_in_set, int **neighbors_in_set, double *clique_counts, int current_clique_size, int pivot_count);
    static void run_pivoter_algorithm(Graph *graph, double *clique_counts);
};

#endif // PIVOTER_H
