#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pivoter.h"

double combination_table[2000][2000];

//组合数表初始化
void Pivoter::initialize_combination_table(int n) {
    for (int i = 0; i <= n; ++i)
        combination_table[i][0] = 1.0;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            combination_table[i][j] = combination_table[i-1][j-1] + combination_table[i-1][j];
}

//核分解,将原图转化为有向无环图（DAG），减少无效搜索
Graph* Pivoter::core_decomposition(Graph *original_graph) {

    //初始化
    Graph *decomposed_graph = initialize_graph(original_graph->vertex_count, original_graph->edge_count >> 1);
    int *degree_bins = (int *)calloc(original_graph->max_in_degree + 2, sizeof(int));//度数数组
    int *vertex_rank = (int *)calloc(original_graph->vertex_count + 1, sizeof(int));//节点排名
    int *rank_to_vertex = (int *)calloc(original_graph->vertex_count + 1, sizeof(int));//每个排名对应的节点
    int *current_degree = (int *)calloc(original_graph->vertex_count + 1, sizeof(int));//节点的度数
    memcpy(current_degree, original_graph->in_degree, sizeof(int) * (original_graph->vertex_count + 1));

    //计算每一个度数出现的次数
    for (int i = 1; i <= original_graph->vertex_count; ++i)
        degree_bins[current_degree[i] + 1]++;

    //累加每一个度出现的次数
    for (int i = 1; i <= original_graph->max_in_degree; ++i)
        degree_bins[i] += degree_bins[i-1];

    //跟据排名重构图
    for (int i = 1; i <= original_graph->vertex_count; ++i) {
        vertex_rank[i] = ++degree_bins[current_degree[i]];
        rank_to_vertex[vertex_rank[i]] = i;
    }

    //基于度的排名重构图
    for (int i = 1; i <= original_graph->vertex_count; ++i) {
        int u = rank_to_vertex[i];
        for (int j = original_graph->first_edge[u]; ~j; j = original_graph->edges[j].next_edge) {
            int v = original_graph->edges[j].destination;
            if (current_degree[v] <= current_degree[u]) continue;
            int w = rank_to_vertex[++degree_bins[--current_degree[v]]];
            vertex_rank[w] = vertex_rank[v];
            vertex_rank[v] = degree_bins[current_degree[v]];
            rank_to_vertex[vertex_rank[v]] = v;
            rank_to_vertex[vertex_rank[w]] = w;
        }
    }

    //重构新图
    for (int u = 1; u <= original_graph->vertex_count; ++u)
        for (int j = original_graph->first_edge[u]; ~j; j = original_graph->edges[j].next_edge) {
            int v = original_graph->edges[j].destination;
            if (current_degree[u] < current_degree[v] || (current_degree[u] == current_degree[v] && u < v))
                add_unweighted_edge(decomposed_graph, u, v);
        }

    free(degree_bins);
    free(vertex_rank);
    free(rank_to_vertex);
    free(current_degree);

    return decomposed_graph;
}

void Pivoter::initialize_set(int *current_set, int *position_in_set, int vertex_count) {

    for (int i = 1; i <= vertex_count; ++i) {
        current_set[i] = i;//集合大小
        position_in_set[i] = i;//顶点位置
    }
}

//实现集合插入、删除
void Pivoter::insert_into_set(int *current_set, int *position_in_set, int vertex) {
    int pos = position_in_set[vertex];
    if (pos <= current_set[0]) return;
    current_set[pos] = current_set[++current_set[0]];
    current_set[current_set[0]] = vertex;
    position_in_set[vertex] = current_set[0];
    position_in_set[current_set[pos]] = pos;
}
void Pivoter::remove_from_set(int *current_set, int *position_in_set, int vertex) {
    int pos = position_in_set[vertex];
    if (pos > current_set[0]) return;
    current_set[pos] = current_set[current_set[0]];
    current_set[current_set[0]] = vertex;
    position_in_set[vertex] = current_set[0]--;
    position_in_set[current_set[pos]] = pos;
}

//递归搜索
void Pivoter::pivot_dfs(int *current_set, int *position_in_set, int **neighbors_in_set, double *clique_counts, int current_clique_size, int pivot_count) {
    if (!current_set[0]) {
        // 如果current_set为空，更新clique_counts值
        for (int i = 0; i <= pivot_count; ++i)
            clique_counts[i + (current_clique_size - pivot_count)] += combination_table[pivot_count][i];
        return;
    }

    // Step 1: 选取Pivot（当前集合中度最大的顶点）
    int pivot = 0, max_neighbors = -1;
    for (int i = 1; i <= current_set[0]; ++i) {
        int u = current_set[i], neighbors = 0;
        for (int j = 1; j <= neighbors_in_set[u][0]; ++j) {
            int v = neighbors_in_set[u][j];
            if (position_in_set[v] <= current_set[0]) ++neighbors;
            else break;
        }
        if (neighbors > max_neighbors) {
            max_neighbors = neighbors;
            pivot = u;
        }
    }

    // Step 2: 生成候选集 = set \ neighbors(pivot)
    int *candidates = (int *)calloc(current_set[0] + 1, sizeof(int));
    memcpy(candidates, current_set, sizeof(int) * (current_set[0] + 1));

    for (int i = 1; i <= neighbors_in_set[pivot][0]; ++i) {
        int u = neighbors_in_set[pivot][i];
        if (position_in_set[u] <= current_set[0]) candidates[position_in_set[u]] = -1;
        else break;
    }

    candidates[0] = 0;
    for (int i = 1; i <= current_set[0]; ++i) {
        if (candidates[i] == -1) continue;
        candidates[++candidates[0]] = candidates[i];
    }

    // Step 3: 递归遍历候选集
    int original_set_size = current_set[0];
    for (int i = 1; i <= candidates[0]; ++i) {
        int u = candidates[i], set_size = current_set[0];
        current_set[0] = 0;

        //更新集合
        for (int j = 1; j <= neighbors_in_set[u][0]; ++j) {
            int v = neighbors_in_set[u][j];
            if (position_in_set[v] <= set_size) insert_into_set(current_set, position_in_set, v);
            else if (position_in_set[v] > original_set_size) break;
        }

        //更新邻居节点
        for (int j = 1; j <= current_set[0]; ++j) {
            int v = current_set[j], cnt = 0;
            for (int k = 1; k <= neighbors_in_set[v][0]; ++k) {
                int neighbor = neighbors_in_set[v][k];
                if (position_in_set[neighbor] <= current_set[0]) {
                    neighbors_in_set[v][k] = neighbors_in_set[v][++cnt];
                    neighbors_in_set[v][cnt] = neighbor;
                }
                if (position_in_set[neighbor] > original_set_size) break;
            }
        }

        //递归
        pivot_dfs(current_set, position_in_set, neighbors_in_set, clique_counts, current_clique_size + 1, pivot_count + (u == pivot));
        current_set[0] = set_size;
        remove_from_set(current_set, position_in_set, u);
    }

    current_set[0] = original_set_size;
    free(candidates);
}

void Pivoter::run_pivoter_algorithm(Graph *graph, double *clique_counts) {

    // 1. 初始化
    initialize_combination_table(1500);
    std::memset(clique_counts, 0, sizeof(int) * (graph->vertex_count + 1));

    Graph *decomposed_graph = core_decomposition(graph);
    int *current_set = (int *)calloc(graph->vertex_count + 1, sizeof(int));
    int *position_in_set = (int *)calloc(graph->vertex_count + 1, sizeof(int));
    int **neighbors_in_set = (int **)calloc(graph->vertex_count + 1, sizeof(int *));

    initialize_set(current_set, position_in_set, graph->vertex_count);
    for (int u = 1; u <= graph->vertex_count; ++u)
        neighbors_in_set[u] = NULL;

    // 2. 按核序遍历顶点
    for (int u = 1; u <= graph->vertex_count; ++u) {
        current_set[0] = 0;
        for (int j = decomposed_graph->first_edge[u]; ~j; j = decomposed_graph->edges[j].next_edge) {
            int v = decomposed_graph->edges[j].destination;
            insert_into_set(current_set, position_in_set, v);
        }

        // 获取邻居集（在分解图中）
        for (int i = 1; i <= current_set[0]; ++i) {
            int u = current_set[i];
            neighbors_in_set[u] = (int *)realloc(neighbors_in_set[u], sizeof(int) * (std::min(current_set[0], graph->in_degree[u]) + 1));
            neighbors_in_set[u][0] = 0;
        }

        //构建邻接关系
        for (int i = 1; i <= current_set[0]; ++i) {
            int u = current_set[i];
            for (int j = decomposed_graph->first_edge[u]; ~j; j = decomposed_graph->edges[j].next_edge) {
                int v = decomposed_graph->edges[j].destination;
                if (position_in_set[v] <= current_set[0]) {
                    neighbors_in_set[u][++neighbors_in_set[u][0]] = v;
                    neighbors_in_set[v][++neighbors_in_set[v][0]] = u;
                }
            }
        }

        // 3. 启动dfs
        pivot_dfs(current_set, position_in_set, neighbors_in_set, clique_counts, 1, 0);
    }

    for (int v = 1; v <= graph->vertex_count; ++v)
        if (neighbors_in_set[v] != NULL) free(neighbors_in_set[v]);
    free(current_set);
    free(position_in_set);
    free(neighbors_in_set);
    free_graph(decomposed_graph);
}
