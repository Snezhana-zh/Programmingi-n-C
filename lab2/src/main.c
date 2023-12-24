#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool It_is_bad_input(char* p, int len);
int Index_first_max_el(const char* p, int len);
int Index_bigger_el(const char* p, int len, char el);
void Swap(char* a, char* b);
char* Reverse_p(char* p, int len, int i);

bool It_is_bad_input(char* p, int len) {
    for (int i = 0; i < len - 1; i++) {
        if ((p[i] - '0' > 9) || (p[i] - '0' < 0)) {
            return true;
        }
        for (int j = i + 1; j < len - 1; j++) {
            if (p[i] == p[j]) {
                return true;
            }
        }
    }
    return false;
}

int Index_first_max_el(const char* p, int len) {
    for (int i = len - 2; i > 0; i--) {        
        if (p[i - 1] - '0' < p[i] - '0') {
            return i - 1;
        }
    }
    return -1;
}

int Index_bigger_el(const char* p, int len, char el) {
    for (int i = len - 2; i >= 0; i--) { 
        if (p[i] - '0' > el - '0') {
            return i;
        }
    }
    return 0;
}

void Swap(char* a, char* b) {
    char t = *b;
    *b = *a;
    *a = t;
}

char* Reverse_p(char* p, int len, int i) {
    int j = len - 2;
    while (j - (i + 1) > 0) {
        Swap(&p[i + 1], &p[j]);
        j--;
        i++;
    }
    return p;
}

int main() {
    char p[13] = {0};
    int num;
    if ((fgets(p, 13, stdin) && scanf("%d", &num))) {
        int len = strlen(p);
        printf("%d ", len);
        if (It_is_bad_input(p, len)) {
            printf("bad input");
            return 0;
        }
        while(num > 0) {
            int i = Index_first_max_el(p, len);
            if (i == -1) {
                return 0;
            }
            int j = Index_bigger_el(p, len, p[i]);
            Swap(&p[i], &p[j]);
            printf("%s", Reverse_p(p, len, i));
            num--;
        }        
    }
    else {
        printf("bad input");
    }    
    return 0;
}
