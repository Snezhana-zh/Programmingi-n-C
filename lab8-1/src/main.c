#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Edge {
    int start_vertex;
    int end_vertex;
    int weight;
}* Edge;

typedef struct TList {
    int start_vertex;
    int end_vertex;
    struct TList* Next;
}* TList;

TList CreateList() {
    return NULL;
}

void Push(int start, int end, TList* list) {
    TList h = malloc(sizeof(struct TList));
    assert(h != NULL);
    h->end_vertex = end;
    h->start_vertex = start;
    h->Next = (*list);
    *list = h;
}

void Fill_arrays(int count_vertices, int* dist, int* prev) {
    for (int i = 0; i < count_vertices; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[0] = 0;
}

void CreateEdge(int start_vertex, int end_vertex, size_t weight_edge, Edge edge) {
    edge->end_vertex = end_vertex - 1;
    edge->start_vertex = start_vertex - 1;
    edge->weight = weight_edge;
}

bool CheckRange(size_t sup, size_t inf, size_t value) {
    return (value <= sup && value >= inf) ? true : false;
}

void Destroy(TList* h) {
    while(*h != NULL) {
        TList tmp = (*h)->Next;
        free(*h);
        *h = tmp;
    }
}

void PrintList(TList h) {
    while (h != NULL) {
        printf("%d %d\n", h->start_vertex, h->end_vertex);
        h = h->Next;
    }
}

bool FillEdgesArray(int count_edges, int count_vertices, Edge edges_array) {
    int start_vertex;
    int end_vertex;
    size_t weight_edge;
    for (int i = 0; i < count_edges; i++) {
        if (scanf("%d", &start_vertex) != 1) {
            printf("bad number of lines");
            return false;
        }
        if (!CheckRange(count_vertices, 0, start_vertex)) {
            printf("bad vertex");
            return false;
        }
        if (scanf("%d", &end_vertex) != 1) {
            printf("bad number of lines");
            return false;
        }
        if (!CheckRange(count_vertices, 0, end_vertex)) {
            printf("bad vertex");
            return false;
        }
        if (scanf("%zu", &weight_edge) != 1) {
            printf("bad number of lines");
            return false;
        }
        if (weight_edge > INT_MAX) {
            printf("bad length");
            return false;
        }
        CreateEdge(start_vertex, end_vertex, weight_edge, &edges_array[i]);
    }
    return true;
}

int ExtractMin(int* dist, int* used, int count_vertices) {
    size_t min = UINT_MAX;
    int index = 0;
    for (int i = 0; i < count_vertices; i++) {
        if ((size_t)dist[i] < min && used[i] != -1) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

bool MSTPrima(int count_vertices, int count_edges, Edge edges_array, int* dist, int* prev, int* used, TList* result) {
    for (int j = 0; j < count_vertices; j++) {
        int min_vertex = ExtractMin(dist, used, count_vertices);
        int check_edges = 0;
        used[min_vertex] = -1;
        if (prev[min_vertex] != -1) {
            Push(prev[min_vertex] + 1, min_vertex + 1, result);
        }
        for (int i = 0; i < count_edges; i++) {
            int prev_vertex;
            if (edges_array[i].start_vertex == min_vertex) {
                prev_vertex = edges_array[i].end_vertex;
            }
            else if (edges_array[i].end_vertex == min_vertex) {
                prev_vertex = edges_array[i].start_vertex;
            }
            else {
                continue;
            }
            check_edges++;
            if ((used[prev_vertex] != -1 && edges_array[i].weight < dist[prev_vertex]) || (edges_array[i].weight == INT_MAX)) {
                prev[prev_vertex] = min_vertex;
                dist[prev_vertex] = edges_array[i].weight;
            }
        }
        if (check_edges == 0 && count_edges != 0) {
            return false;
        }
    }
    return true;
}

void CleanUp(TList list, int* a, int* b, Edge c, int* d) {
    Destroy(&list);
    free(a);
    free(b);
    free(c);
    free(d);
}

int main() {
    int count_vertices;
    int count_edges;

    if (scanf("%d", &count_vertices) != 1) {
        return 0;
    }

    if (!CheckRange(5000, 0, count_vertices)) {
        printf("bad number of vertices");
        return 0;
    }

    if (scanf("%d", &count_edges) != 1) {
        return 0;
    }

    if (!CheckRange((size_t)count_vertices * (count_vertices + 1) / 2, 0, count_edges)) {
        printf("bad number of edges");
        return 0;
    }

    if ((count_edges == 0 && count_vertices > 1) || (count_edges == 0 && count_vertices == 0)) {
        printf("no spanning tree");
        return 0;
    }

    int* dist_arr = malloc(sizeof(int) * count_vertices);
    assert(dist_arr != NULL);

    int* prev_arr = malloc(sizeof(int) * count_vertices);
    assert(prev_arr != NULL);

    int* used = calloc(count_vertices, sizeof(int));
    assert(used != NULL); 

    Fill_arrays(count_vertices, dist_arr, prev_arr);

    Edge edges_array = malloc(sizeof(struct Edge) * count_edges);
    assert(edges_array != NULL);

    if (!FillEdgesArray(count_edges, count_vertices, edges_array)) {
        free(dist_arr);
        free(prev_arr);
        free(edges_array);
        free(used);
        return 0;
    }

    TList result = CreateList();

    if (!MSTPrima(count_vertices, count_edges, edges_array, dist_arr, prev_arr, used, &result)) {
        printf("no spanning tree");
        CleanUp(result, dist_arr, prev_arr, edges_array, used);
        return 0;
    }
    PrintList(result);
    CleanUp(result, dist_arr, prev_arr, edges_array, used);
    return 0;
}