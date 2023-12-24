#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

bool get_values(int length, int* array);
void print_sum_array(int length, const int* array);

int main(){
    int length;
    int array[10];
    if(scanf("%d", &length) != 1 || length < 1 || length > 10){
        printf("bad input");
    }
    else { 
        if(get_values(length, array)){
            print_sum_array(length, array);
        }
        else {
            printf("bad input");
        }
    }
    return 0;
}

bool get_values(int length, int* array){
    long long tmp;
    for(int i = 0; i < length; i++){
        if(scanf("%lld", &tmp) != 1 || tmp > INT_MAX || tmp < INT_MIN){
            return false;
        }
        array[i] = tmp;
    }
    return true;
}

void print_sum_array(int length, const int* array){
    long long sum = 0;
    for(int i = 0; i < length; i++){
        sum += array[i];
        if(sum > INT_MAX || sum < INT_MIN){
            printf("overflow");
            return;
        }
    }
    printf("%lld", sum);
}
