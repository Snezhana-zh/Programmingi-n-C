#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int* HeapSort(int* array,int num);
void Swap(int* a, int* b);
int* Sort_tree(int* array, int num, int i);

void Swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int* Sort_tree(int* array, int num, int i) {
    int peak_index = i;
    int r_index = 2 * i + 2;
    int l_index = 2 * i + 1;
    while ((r_index < num && array[peak_index] < array[r_index]) || (l_index < num && array[peak_index] < array[l_index])) {
        if ((r_index < num) && (array[r_index] > array[peak_index])) {
            peak_index = r_index;
        }
        if ((l_index < num) && (array[l_index] > array[peak_index])) {
            peak_index = l_index;
        }
        if (peak_index == r_index || peak_index == l_index) {
            Swap(&array[i], &array[peak_index]);
            r_index = 2 * peak_index + 2;
            l_index = 2 * peak_index + 1;
            i = peak_index;
        }      
    }
    return array;
}

int* HeapSort(int* array, int num) {
    for (int i = num / 2 - 1; i >= 0; i--) {
        Sort_tree(array, num, i);
    }
    for (int i = num - 1; i >= 0; i--) {        
        Swap(&array[0], &array[i]);
        Sort_tree(array, i, 0);
    }    
    return array;
}

int main() {
    int num;
    if (scanf("%d", &num) != 1 || num < 1) {
        return 0;
    }
    int* array = (int*)malloc(sizeof(int) * num);
    assert(array != NULL);
    for (int i = 0; i < num; i++) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return 0;
        };
    }
    HeapSort(array, num);
    for (int i = 0; i < num; i++) {
        printf("%d ", array[i]);
    }
    free(array);
    return 0;
}