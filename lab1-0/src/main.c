#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int* fill_shift(char* pattern, int* shift);

int* fill_shift(char* pattern, int* shift) {
    shift[(unsigned char)pattern[strlen(pattern) - 1]] = strlen(pattern);
    for (unsigned int j = 0; j < strlen(pattern) - 1; j++) {
        shift[(unsigned char)pattern[j]] = strlen(pattern) - 1 - j;
    }
    return shift;
}

int main() {
    char pattern[17] = {0}; 
    char c = getchar();
    int len_p = 0;
    int i = 0;
    while(c != '\n') {
        pattern[i] = c;
        i++;
        len_p++;
        c = getchar();
    }  

    int shift[256] = {0};
    fill_shift(pattern, shift);  

    int text_pos = 0;
    int pat_pos = len_p - 1;
    int cur_shift = len_p;
    char text[17] = {0};

    while (true) {
        int len_text = fread(&text[len_p - cur_shift], sizeof(unsigned char), cur_shift, stdin);
        if (len_text < cur_shift) {
            return 0;
        }
        while ((pat_pos >= 0) && (text[pat_pos] == pattern[pat_pos])) {
            printf("%d ", text_pos + pat_pos + 1);
            pat_pos--;
        }
        if (pat_pos == -1 || pat_pos == 0) {
            if (pat_pos == 0) {
                printf("%d ", text_pos + pat_pos + 1);
            }
            pat_pos++;
            cur_shift = len_p;
        }
        else {
            printf("%d ", text_pos + pat_pos + 1);
            cur_shift = shift[(unsigned char)text[pat_pos]];

            if (cur_shift == 0) {
                if (pat_pos != len_p - 1) {
                    cur_shift = len_p - 1;
                }
                else {
                    cur_shift = len_p;
                }
            }
        }
        
        text_pos += cur_shift;    
        pat_pos = len_p - 1;

        for (int i = 0; i < len_p - cur_shift; i++) {
            text[i] = text[i + cur_shift];
        }
    }
    return 0;
}