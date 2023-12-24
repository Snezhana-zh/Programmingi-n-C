#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef char simple_string[100];

bool check_b1_notation(int b1, const simple_string num);
void print_notation_b2(int b1, int b2, const simple_string num);

bool check_b1_notation(int b1, const simple_string num) {
    int count_dot = 0;
    if (strlen(num) == 0 || num[0] == '.' || num[strlen(num)-1] == '.') {
        return false;
    }
    for (unsigned int i = 0; i < strlen(num); i++) {
        if (num[i] == '.') {
            count_dot++;
            if(count_dot > 1) {
                return false;
            }
        }
        else if (num[i] >= '0' && num[i] <= '9') {
            if(num[i] - '0' >= b1) {
                return false;
            }  
        }   
        else if (num[i] >= 'A' && num[i] <= 'Z') {
            if(num[i] - 'A' >= (b1 - 10)) {
                return false;
            }  
        } 
        else {
            return false;
        }
    }
    return true;
} 

int give_value_of_number(char n, const char *symbol) {
    int cur_num = 0;
    for (int j = 0; j <= 15; j++) {
        if (n == symbol[j]) {
            cur_num = j; //чтобы А = 10, В = 11 и т.п., а также, чтобы все элементы стали int
        }
    }
    return cur_num;
}

void print_notation_b2(int b1, int b2, const simple_string num) {
    const char *symbol = "0123456789ABCDEF";
    long long int integer = 0; //целая часть дробного числа
    double fraction = 0; //дробная часть дробного числа
    int cur_num = 0;
    long long degree_b1 = b1;

    unsigned int i = 0;
    while (i < strlen(num) && num[i] != '.') {
        cur_num = give_value_of_number(num[i], symbol);
        integer = integer * b1 + cur_num; //переводим целую часть в 10 с.с.
        i++;
    }
    i++;
    while (i < strlen(num)) {
        cur_num = give_value_of_number(num[i], symbol);
        fraction += (double)cur_num / degree_b1; //если встретили точку, то переводим в 10 с.с. ещё и дробную часть
        degree_b1 *= b1; 
        i++;
    }

    simple_string res_int = {0};

    if (integer == 0) {
        printf("%d", 0);
    }
    unsigned int l = 0;
    while (integer != 0) {
        res_int[l] = symbol[integer % b2];
        integer /= b2;
        l++;
    }

    for (int j = (strlen(res_int) - 1); j >= 0; j--) {
        printf("%c", res_int[j]);
    }  

    if (fraction != 0) {
        printf("%c", '.');
        
        int int_fraction = fraction; //целая часть от деления
        while (fraction > 0) {
            fraction *= b2;
            int_fraction = fraction;
            printf("%c", symbol[int_fraction]);
            fraction -= int_fraction;                 
        }
    }
}

int main() {
    int b1, b2;
    simple_string num = {0};
    if (scanf("%d %d", &b1, &b2) != 2) {
        return 0;
    }
    if (b1 > 16 || b2 > 16 || b1 < 2 || b2 < 2) {
        printf("bad input");
        return 0;
    }
    if (scanf("%99s",num) != 1) {
        return 0;
    }
    for (unsigned int i = 0; i < strlen(num); i++) {
        num[i] = toupper(num[i]);
    }
    if (check_b1_notation(b1, num)) {
        print_notation_b2(b1, b2,  num);
    }
    else {
        printf("bad input");
    }
    return 0;
}