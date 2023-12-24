#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct TList {
    int Value;
    struct TList* Next;
}* TList;

typedef enum {
    Green = 1,
    Blue = 0,
    Red = 2
} Color;

void PrintList(TList h) {
    while (h != NULL) {
        printf("%d ", 1 + h->Value);
        h = h->Next;
    }
}

void DestroyList(TList* h) {
    while (*h != NULL) {
        TList t = (*h) -> Next;
        free(*h);
        *h = t;       
    }
}

void PushNeighbour(TList* destination, int value) {
    TList vertex = malloc(sizeof(struct TList));
    assert(vertex != NULL);
    vertex->Value = value;
    vertex->Next = *destination;
    (*destination) = vertex;
}

bool CheckEdges(char const* graph, int count_of_vertices, int vertex, int cur_vertex) {
    int bit = vertex * count_of_vertices + cur_vertex;
    int index = bit/8;
    char mask = 1 << (bit % 8);
    char element_of_graph = graph[index];
    element_of_graph &= mask;
    return element_of_graph;
}

bool CycleCheck(int vertex, Color* color, int count_of_vertices, char const* graph) {
    if (color[vertex] == Green) {
        return true;
    }
    color[vertex] = Green;
    for (int i = 0; i < count_of_vertices; i++) {
        if (CheckEdges(graph, count_of_vertices, vertex, i)) {
            if (color[i] == Blue) {
                bool cycle_found = CycleCheck(i, color, count_of_vertices, graph);
                if (cycle_found == true) {
                    return true;
                }
            }
            else if (color[i] == Green) {
                return true;
            }
        }
    }
    color[vertex] = Red;
    return false;
}

void DFS(int count_of_vertices, char const* graph, bool* visited, TList* ans, int vertex) {
    visited[vertex] = true;
    for (int i = 0; i < count_of_vertices; i++) {
        if (CheckEdges(graph, count_of_vertices, vertex, i)) {
            if (!visited[i]) {
                DFS(count_of_vertices, graph, visited, ans, i);
            }
        }
    }
    PushNeighbour(ans, vertex);
}

void InsertInGraph(int cur_vertex_start, int cur_vertex_end, char* graph, int count_of_vertices) {
    int bit = (cur_vertex_start - 1) * count_of_vertices + (cur_vertex_end - 1);
    int index = bit/8;
    char mask = 1 << (bit % 8);
    graph[index] |= mask;
}

bool FillGraph(char* graph, int count_of_edges, int count_of_vertices) {
    int cur_vertex_start;
    int cur_vertex_end;
    for (int i = 0; i < count_of_edges; i++) {
        if (scanf("%d", &cur_vertex_start) != 1) {
            printf("bad number of lines");
            return false;        
        }
        if (scanf("%d", &cur_vertex_end) != 1) {
            return false;        
        }
        if (cur_vertex_start < 1 || cur_vertex_end < 1 || cur_vertex_start > count_of_vertices || cur_vertex_end > count_of_vertices) {
            printf("bad vertex");
            return false;
        }
        InsertInGraph(cur_vertex_start, cur_vertex_end, graph, count_of_vertices);
    }
    return true;
}

bool IsCycle(int count_of_vertices, char const* graph) {
    Color* color = calloc(count_of_vertices, sizeof(Color));
    assert(color != NULL);
    for (int i = 0; i < count_of_vertices; i++) {
        if (color[i] == Blue) {
            bool cycle_found = CycleCheck(i, color, count_of_vertices, graph);
            if (cycle_found == true) {
                free(color);
                return true;
            }
        }
    }
    free(color);
    return false;    
}

void TopSort(TList* ans, int count_of_vertices, char const* graph) {
    bool* visited = calloc(count_of_vertices, sizeof(bool));
    assert(visited != NULL);
    for (int i = 0; i < count_of_vertices; i++) {
        if (!visited[i]) {
            DFS(count_of_vertices, graph, visited, ans, i);
        }
    }
    free(visited);
}

int main() {
    int count_of_vertices;
    if (scanf("%d", &count_of_vertices) != 1) {
        printf("bad number of lines");
        return 0;        
    }
    if (count_of_vertices < 0 || count_of_vertices > 2000) {
        printf("bad number of vertices");
        return 0;
    }
    int count_of_edges;
    if (scanf("%d", &count_of_edges) != 1) {
        printf("bad number of lines");
        return 0;        
    }
    if (count_of_edges < 0 || count_of_edges > (count_of_vertices * (count_of_vertices + 1)/2)) {
        printf("bad number of edges");
        return 0;
    }

    char* graph = calloc(count_of_vertices*count_of_vertices/8 + 1, 1);
    assert(graph != NULL);
    if (!FillGraph(graph, count_of_edges, count_of_vertices)) {
        free(graph);
        return 0;
    }

    if (IsCycle(count_of_vertices, graph)) {
        printf("impossible to sort");
        free(graph);
        return 0;
    }

    TList ans = NULL;
    TopSort(&ans, count_of_vertices, graph);
    PrintList(ans);
    DestroyList(&ans);
    free(graph);
    return 0;    
}