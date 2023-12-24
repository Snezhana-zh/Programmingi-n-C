#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct AVL {
    int Value;
    unsigned char height;
    struct AVL* left;
    struct AVL* right;
}* AVL;

unsigned char Height(AVL t) {
    if (t != NULL) {
        return t->height;
    }
    else {
        return 0;
    }
}

int Bfactor(AVL t) {
    return Height(t->right) - Height(t->left);
}

void Fixheight(AVL t) {
    unsigned char hl = Height(t->left);
    unsigned char hr = Height(t->right);
    if (hl > hr) {
        t->height = hl + 1;
    }
    else {
        t->height = hr + 1;
    }  
}

AVL RotateRight(AVL t) {
    AVL h = t->left;
    t->left = h->right;
    h->right = t;
    Fixheight(t);
    Fixheight(h);
    return h;
}

AVL RotateLeft(AVL t) {
    AVL h = t->right;
    t->right = h->left;
    h->left = t;
    Fixheight(t);
    Fixheight(h);
    return h;
}

AVL Balance(AVL t) {
    if (Bfactor(t) == 2) {
        if (Bfactor(t->right) < 0) {
            t->right = RotateRight(t->right);
        }
        return RotateLeft(t);
    }
    else if (Bfactor(t) == -2) {
        if (Bfactor(t->left) > 0) {
            t->left = RotateLeft(t->left);
        }
        return RotateRight(t);
    }
    else {
        Fixheight(t);
    }
    return t;
}

void CreateLeaf(int value, AVL tree) {
    tree->height = 1;
    tree->left = NULL;
    tree->right = NULL;
    tree->Value = value;
}

AVL Insert(AVL tree, AVL leaf) {
    if (tree == NULL) {
        return leaf;
    }
    else if (leaf->Value < tree->Value) {
        tree->left = Insert(tree->left, leaf);
    }
    else {
        tree->right = Insert(tree->right, leaf);
    }
    return Balance(tree);
}

int main() {
    int count;
    if (scanf("%d", &count) != 1) {
        return 0;
    }
    if (count == 0) {
        printf("%d", 0);
        return 0;
    }
    AVL root = NULL;
    AVL array = malloc(sizeof(struct AVL) * count);
    assert(array != NULL);
    int element;
    for (int i = 0 ; i < count; i++) {
        if (scanf("%d", &element) != 1) {
            free(array);
            return 0;
        }
        CreateLeaf(element, &array[i]);
        root = Insert(root, &array[i]);
        root = Balance(root);        
    }
    printf("%d", root->height);
    free(array);
    return 0;
}