#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

long Hash(const unsigned char* text, int len_text);
bool Print_compared_char(const unsigned char* text, const unsigned char* pattern,int len_text, int text_pos);
long Roll_hash(long hash_text, char p_el, unsigned char* text, int len_p, int degree);

long Hash(const unsigned char* text, int len_text) {
    long hash = text[len_text - 1] % 3;
    for (int i = len_text - 1; i > 0; --i) {
        hash = (hash * 3) + ((text[i - 1] % 3));
    }
    return hash;
}

bool Print_compared_char(const unsigned char* text, const unsigned char* pattern,int len_text, int text_pos) {
    int position_text = text_pos - len_text + 1;
    for (int i = 0; i < len_text; ++i) {
        printf("%d ", position_text + 1);
        ++position_text;
        if (text[i] != pattern[i]) {
            return false;
        }
    }
    return true;
}

long Roll_hash(long hash_text, char p_el, unsigned char* text, int len_p, int degree) {
   long hash = (hash_text - (p_el % 3)) / 3;
   hash += (text[len_p - 1] % 3) * degree;
   return hash;
}

int main() {
    unsigned char pattern[17] = {0}; 
    char c = getchar();
    int len_p = 0;
    int i = 0;
    while(c != '\n') {
        pattern[i] = c;
        i++;
        len_p++;
        c = getchar();
    }  
     
    long hash_p = Hash(pattern, len_p);
    printf ("%ld ", hash_p);
    
    int text_pos = len_p - 1;
    int cur_shift = len_p;
    unsigned char text[17] = {0};
    long hash_text = 0;
    int degree = pow(3, len_p - 1);

    while(true) {
        char p_el = text[0];
        if (cur_shift == 1) {
            memmove(text, &text[cur_shift], len_p - 1);
        }
        int count_read = fread(&text[len_p - cur_shift], sizeof(unsigned char), cur_shift, stdin);
        if (count_read < cur_shift) {
            return 0;
        }
        if (cur_shift == len_p) {
            hash_text = Hash(text, len_p);
        }
        else { 
            hash_text = Roll_hash(hash_text, p_el, text, len_p, degree);          
        }
        if (hash_text == hash_p && Print_compared_char(text, pattern, len_p, text_pos)) {
            cur_shift = len_p;
        }
        else {
            cur_shift = 1;
        }
        text_pos += cur_shift;
    }
    return 0;
}
