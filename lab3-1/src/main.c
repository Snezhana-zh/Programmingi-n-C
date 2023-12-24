#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int QuickSort(int* array, int first, int last);
void Swap(int* a, int* b);
int Partition(int* array, int first, int last);
int Median(int* array, int index_1, int index_2, int index_3);

int Median(int* array, int index_1, int index_2, int index_3) {
    if (array[index_1] >= array[index_2]) {
        if (array[index_3] >= array[index_2]) {
            return index_2;
        }
        else {
            return index_1;
        }
    }
    else if (array[index_3] >= array[index_2]) {
        if (array[index_1] >= array[index_3]) {
            return index_3;
        }
        else {
            return index_2;
        }
    }
    else if (array[index_1] >= array[index_3]) {
        if (array[index_2] >= array[index_1]) {
            return index_1;
        }
        else {
            return index_3;
        }
    }
    return 0;
}

void Swap(int* a, int* b) {
    int t = *b;
    *b = *a;
    *a = t;
}

int Partition(int* array, int first, int last) {
    int middle = array[(first + last) / 2];
    int i = first;
    int j = last;
    while (true) {
        while (array[i] < middle) {
            i++;
        }
        while (array[j] > middle) {
            j--;
        }
        if (i >= j) {
            break;
        }
        Swap(&array[i], &array[j]);      
        i++;
        j--;  
    }
    return j;
}

int QuickSort(int* array, int first, int last) {    
    if (first < last) {
        int med = Median(array, first, last, (first + last) / 2);
        Swap(&array[med], &array[(first + last) / 2]);
        int middle = Partition(array, first, last);
        QuickSort(array, first, middle);
        QuickSort(array, middle + 1, last);
    }  
    return 0;  
}

int main() {
    int num;
    if (scanf("%d", &num) != 1) {
        return 0;
    }
    int* array = (int*)malloc(sizeof(int) * num);
    assert(array != NULL);
    for (int i = 0; i < num; i++) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return 0;
        }        
    }
    int first = 0;
    int last = num - 1;
    QuickSort(array, first, last);
    for (int i = 0; i < num; i++) {
        printf("%d ", array[i]);
    }
    free(array);
    return 0;
}