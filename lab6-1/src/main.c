#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

typedef enum {
    Black = 0,
    Red = 1
} Color;

typedef struct Node {
    int value;
    Color color;
    struct Node* left;
    struct Node* right;
}* Node;

void CreateLeaf(int k, Node l) {
    l->color = Red;
    l->left = NULL;
    l->right = NULL;
    l->value = k;
}

bool IsRed(Node r) {
    if (r == NULL) {
        return false;
    }
    return r->color == Red;
}

Node LeftRotate(Node* t) {
    Node rtree = (*t)->right;
    rtree->color = (*t)->color;
    (*t)->color = Red;
    (*t)->right = rtree->left;
    rtree->left = (*t);
    return rtree;     
}

Node RightRotate(Node* t) {
    Node ltree = (*t)->left;
    ltree->color = (*t)->color;
    (*t)->color = Red;
    (*t)->left = ltree->right;
    ltree->right = (*t);
    return ltree;      
}

void Balance(Node* root) {
    if (IsRed((*root)->left) && IsRed((*root)->right)) {
        if (IsRed((*root)->left->right) || IsRed((*root)->left->left)) {
            (*root)->left->color = Black;
            (*root)->right->color = Black;
            (*root)->color = Red;
        }
    }
    else if (IsRed((*root)->left) && !IsRed((*root)->right)) {
        if (IsRed((*root)->left->right)) {
            (*root)->left = LeftRotate(&(*root)->left);
        }
        (*root) = RightRotate(root);
    }
    if (IsRed((*root)->left) && IsRed((*root)->right)) {
        if (IsRed((*root)->right->left) || IsRed((*root)->right->right)) {
            (*root)->left->color = Black;
            (*root)->right->color = Black;
            (*root)->color = Red;
        }
    }
    else if (IsRed((*root)->right) && !IsRed((*root)->left)) {
        if (IsRed((*root)->right->left)) {
            (*root)->right = RightRotate(&(*root)->right);
        }
        (*root) = LeftRotate(root);
    }
}

Node InsertNode(Node* cur_root, Node* root,  Node t) {
    if ((*cur_root) == NULL) {
        *cur_root = t;
    }
    else if ((*cur_root)->value > t->value) {
        (*cur_root)->left = InsertNode(&(*cur_root)->left, root, t);
    }
    else if ((*cur_root)->value < t->value) {
        (*cur_root)->right = InsertNode(&(*cur_root)->right, root, t);
    }
    else {
        (*cur_root)->value = t->value;
    }
    Balance(cur_root);
    if (cur_root == root) {
        (*cur_root)->color = Black;
    }
    return *cur_root;
}

int CalcHeight(Node t) {
    if (t == NULL) {
        return 1;
    }
    int height = CalcHeight(t->left);
    return height + (t->color == Black);
}

Node CreateTree() {
    return NULL;
}

Node FillTree(int count, Node array) {
    Node root = CreateTree();
    for (int i = 0 ; i < count; i++) {
        int element;
        if (scanf("%d", &element) != 1) {
            return NULL;
        }
        CreateLeaf(element, &array[i]);
        root = InsertNode(&root, &root, &array[i]);
    }
    return root;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    if (n == 0) {
        printf("%d", 0);
        return 0;
    }
    Node array = malloc(sizeof(struct Node) * n);
    assert(array != NULL);
    Node root = FillTree(n, array);
    if (!root) {
        free(array);
        return 0;
    }
    printf("%d", CalcHeight(root));
    free(array);
    return 0;
}