#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

typedef struct TList {
    unsigned int weight;
    int cost;
    struct TList* Next;
}* TList;

void Push(TList* l, unsigned int weight, int cost) {
    TList t = malloc(sizeof(struct TList));
    assert(t != NULL);
    t->weight = weight;
    t->cost = cost;
    t->Next = (*l);
    (*l) = t;
}

int Max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

void DestroyList(TList* h) {
    while (*h != NULL) {
        TList t = (*h) -> Next;
        free(*h);
        *h = t;       
    }
}

void PrintList(TList l) {
    while (l != NULL) {
        printf ("%u %d\n", l->weight, l->cost);
        l = l->Next;
    }
}

void FillTable(unsigned int count_elements, unsigned int capacity, unsigned int* table, unsigned int* weight_array, int* cost_array) {
    int cost;
    unsigned int weight;
    
    for (unsigned int k = 1; k <= count_elements; k++) {
        if (scanf("%u %d", &weight, &cost) != 2) {
            return;
        }
        weight_array[k - 1] = weight;
        cost_array[k - 1] = cost;
        for (unsigned int s = 1; s <= capacity; s++) {
            if (s >= weight) {
                table[k * (capacity + 1) + s] = Max(table[(k - 1) * (capacity + 1) + s], table[(k - 1) * (capacity + 1) + (s - weight)] + cost);
            }
            else {
                table[k * (capacity + 1) + s] = table[(k - 1) * (capacity + 1) + s];
            }
        }
    }
}

void PrintWeightAndCost(unsigned int capacity, unsigned int count_elements, unsigned int* table, unsigned int* weight_array, int* cost_array) {
    TList l = NULL;
    unsigned int row = capacity;
    for (unsigned int k = count_elements; k >= 1; k--) {
        if (capacity == 0) {
            break;
        }
        if (table[k * (row + 1) + capacity] != table[(k - 1) * (row + 1) + capacity]) {
            Push(&l, weight_array[k - 1], cost_array[k - 1]);
            capacity -= weight_array[k - 1];
        }
    }
    PrintList(l);
    DestroyList(&l);
}

int main() {
    unsigned int count_elements, capacity;
    if (scanf("%u %u", &count_elements, &capacity) != 2) {
        return 0;
    }    
    unsigned int* table = calloc((count_elements + 1) * (capacity + 1), sizeof(unsigned int));
    unsigned int weight_array[count_elements];
    int cost_array[count_elements];
    FillTable(count_elements, capacity, table, weight_array, cost_array);    
    printf("%u\n", table[count_elements * (capacity + 1) + capacity]);
    PrintWeightAndCost(capacity, count_elements, table, weight_array, cost_array);
    free(table);
    return 0;
}