#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Edge {
    int startVertex;
    int endVertex;
    int weightEdge;
}* Edge;

typedef struct TList {
    int startVertex;
    int endVertex;
    struct TList* nextVertex;
}* TList;

TList createList() {
    return NULL;
}

void Push(int start, int end, TList* list) {
    TList h = malloc(sizeof(struct TList));
    assert(h != NULL);
    h->endVertex = end;
    h->startVertex = start;
    h->nextVertex = (*list);
    *list = h;
}

void makeSets(int countVertices, int* parentArray, int* rank) {
    for (int i = 0; i < countVertices; i++) {
        parentArray[i] = i;
        rank[i] = 0;
    }
}

void createEdge(int startVertex, int endVertex, int weightEdge, Edge edge) {
    edge->endVertex = endVertex;
    edge->startVertex = startVertex;
    edge->weightEdge = weightEdge;
}

int Compare(const void* edge1, const void* edge2) {
    return ((Edge)edge1)->weightEdge - ((Edge)edge2)->weightEdge;
}

int findSet(int vertex, int* parent) {
    if (vertex == parent[vertex]) {
        return vertex;
    }
    parent[vertex] = findSet(parent[vertex], parent);
    return parent[vertex];
}

void unionSets(int root1, int root2, int* rank, int* parent) {
    if (rank[root1] < rank[root2]) {
        parent[root1] = root2;
    }
    else if (rank[root1] > rank[root2]) {
        parent[root2] = root1;
    }
    else {
        parent[root1] = root2;
        rank[root2]++;
    }
}

bool checkRange(size_t sup, size_t inf, size_t value) {
    return (value <= sup && value >= inf) ? true : false;
}

void Destroy(TList* h) {
    while (*h != NULL) {
        TList tmp = (*h)->nextVertex;
        free(*h);
        *h = tmp;
    }
}

void printList(TList h) {
    while (h != NULL) {
        printf("%d %d\n", h->startVertex, h->endVertex);
        h = h->nextVertex;
    }
}

bool fillEdgesArray(int countEdges, int countVertices, Edge edgesArray) {
    int startVertex;
    int endVertex;
    size_t weightEdge;
    for (int i = 0; i < countEdges; i++) {
        if (scanf("%d", &startVertex) != 1) {
            printf("bad number of lines");
            return false;
        }
        if (!checkRange(countVertices, 0, startVertex)) {
            printf("bad vertex");
            return false;
        }
        if (scanf("%d", &endVertex) != 1) {
            printf("bad number of lines");
            return false;
        }
        if (!checkRange(countVertices, 0, endVertex)) {
            printf("bad vertex");
            return false;
        }
        if (scanf("%zu", &weightEdge) != 1) {
            printf("bad number of lines");
            return false;
        }
        if (weightEdge > INT_MAX) {
            printf("bad length");
            return false;
        }
        createEdge(startVertex, endVertex, weightEdge, &edgesArray[i]);
    }
    return true;
}

bool Kruskal(int countVertices, int countEdges, Edge edgesArray, int* parentArray, int* rankArray, TList* result) {
    int countRoot = countVertices;
    for (int i = 0; i < countEdges; i++) {
        int root1 = findSet(edgesArray[i].startVertex - 1, parentArray);
        int root2 = findSet(edgesArray[i].endVertex - 1, parentArray);
        if (root1 != root2) {
            unionSets(root1, root2, rankArray, parentArray);
            countRoot--;
            Push(edgesArray[i].startVertex, edgesArray[i].endVertex, result);
        }
    }
    return countRoot == 1;
}

void cleanUp(TList result, int* parentArray, int* rankArray, Edge edgesArray) {
    Destroy(&result);
    free(parentArray);
    free(rankArray);
    free(edgesArray);
}

int main() {
    int countVertices;
    int countEdges;

    if (scanf("%d", &countVertices) != 1) {
        return 0;
    }

    if (!checkRange(5000, 0, countVertices)) {
        printf("bad number of vertices");
        return 0;
    }

    if (scanf("%d", &countEdges) != 1) {
        return 0;
    }

    if (!checkRange((size_t)countVertices * (countVertices + 1) / 2, 0, countEdges)) {
        printf("bad number of edges");
        return 0;
    }

    if ((countEdges == 0 && countVertices > 1) || (countEdges == 0 && countVertices == 0)) {
        printf("no spanning tree");
        return 0;
    }

    int* parentArray = malloc(sizeof(int) * countVertices);
    assert(parentArray != NULL);

    int* rankArray = malloc(sizeof(int) * countVertices);
    assert(rankArray != NULL);

    makeSets(countVertices, parentArray, rankArray);

    Edge edgesArray = malloc(sizeof(struct Edge) * countEdges);
    assert(edgesArray != NULL);

    if (!fillEdgesArray(countEdges, countVertices, edgesArray)) {
        free(parentArray);
        free(rankArray);
        free(edgesArray);
        return 0;
    }

    qsort(edgesArray, (size_t)countEdges, sizeof(struct Edge), &Compare);

    TList result = createList();

    if (!Kruskal(countVertices, countEdges, edgesArray, parentArray, rankArray, &result)) {
        printf("no spanning tree");
        cleanUp(result, parentArray, rankArray, edgesArray);
        return 0;
    }
    printList(result);
    cleanUp(result, parentArray, rankArray, edgesArray);
    return 0;
}