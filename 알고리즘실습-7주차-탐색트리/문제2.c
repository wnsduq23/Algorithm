#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node* lChild;
    struct Node* rChild;
    struct Node* parent;
    int key;
    int height;
}ND;
typedef struct BST {
    ND* Root;
}B;

void searchAndFixAfterInsertion(B* bst, ND* node);
int updateHeight(ND* node);
int isBalanced(ND* node);
ND* restructure(ND** x, ND** y, ND** z);
void expandExternal(ND* node);
ND* getExternalNode(ND* r);
int findElement(B* bst, int k);
void insertItem(B* bst, int k);
ND* treeSearch(B* bst, int k);
int isExternal(ND* node);
int isInternal(ND* node);
void printTree(ND* root);
void freeTree(ND* root);

int main() {
    char ch;
    int data;
    B bst;
    ND* root;
    bst.Root = getExternalNode(bst.Root);
    bst.Root->parent = NULL;
    while (1) {
        scanf("%c", &ch);
        if (ch == 'i') {
            scanf("%d", &data);
            insertItem(&bst, data);
        }
        else if (ch == 's') {
            scanf("%d", &data);
            data = findElement(&bst, data);
        }
        else if (ch == 'p') {
            root = bst.Root;
            printTree(root);
            printf("\n");
        }
        else if (ch == 'q') {
            break;
        }
        else {
            printf("입력이 잘못됐음\n");
        }
        getchar();
    }
    root = bst.Root;
    freeTree(root); //남은 트리 원소들 free
    return 0;
}
ND* getExternalNode(ND* r) {
    ND* newnode;
    newnode = (ND*)malloc(sizeof(ND));
    newnode->lChild = newnode->rChild = NULL;
    newnode->parent = r;
    return newnode;
}
int findElement(B* bst, int k) {
    ND* r = bst->Root;
    while (1) {
        if (isExternal(r)) {
            printf("X\n");
            return 0;
        }
        if (r->key == k) {
            printf("%d\n", r->key);
            return r->key;
        }
        if (k > r->key) {//더 큰 값이면 오른쪽으로 이동
            r = r->rChild;
        }
        else {//더 작은 값이면 왼쪽으로 이동
            r = r->lChild;
        }
    }
}
void expandExternal(ND* node) {
    node->lChild = getExternalNode(node);
    node->rChild = getExternalNode(node);
    node->lChild->height = 0;
    node->rChild->height = 0;
    node->height = 1;
}
void insertItem(B* bst, int k) {
    ND* w;
    w = treeSearch(bst, k);
    if (isInternal(w)) {
        return;
    }
    else {
        w->key = k;
        expandExternal(w);
        searchAndFixAfterInsertion(bst, w);
    }
}
ND* treeSearch(B* bst, int k) {
    ND* r = bst->Root;
    while (1) {
        if (isExternal(r)) return r;
        if (r->key == k) {
            return r;
        }
        else if (k > r->key) {
            r = r->rChild;
        }
        else {
            r = r->lChild;
        }
    }

}
int isExternal(ND* node) {
    if (node->lChild == NULL && node->rChild == NULL) return 1;
    else return 0;
}
int isInternal(ND* node) {
    if (node->lChild != NULL || node->rChild != NULL) return 1;
    else return 0;
}
void printTree(ND* root) {
    if (isExternal(root)) return;
    printf(" %d", root->key);
    printTree(root->lChild);
    printTree(root->rChild);
}
void freeTree(ND* root) {
    if (isExternal(root)) {
        free(root);
        return;
    }
    freeTree(root->lChild);
    freeTree(root->rChild);
}
void searchAndFixAfterInsertion(B* bst, ND* node) {
    ND* w = node;
    ND* x, * y, * z;
    updateHeight(bst->Root);
    while (1) {
        if (w == NULL) return;
        if (isBalanced(w)) w = w->parent;
        else break;
    }

    z = w;
    if (z->lChild->height > z->rChild->height) y = z->lChild;
    else y = z->rChild;
    if (y->lChild->height > y->rChild->height) x = y->lChild;
    else x = y->rChild;
    w = restructure(&x, &y, &z);
    if (w->parent == NULL) bst->Root = w;
}
int updateHeight(ND* node) {
    if (isExternal(node)) {
        return 0;
    }
    else {
        updateHeight(node->lChild);
        updateHeight(node->rChild);
        if (node->lChild->height > node->rChild->height) {
            node->height = node->lChild->height + 1;
        }
        else {
            node->height = node->rChild->height + 1;
        }
        return 1;
    }
}
int isBalanced(ND* node) {
    if (node->lChild->height > node->rChild->height) {
        if ((node->lChild->height - node->rChild->height) <= 1) {
            return 1;
        }
        else return 0;
    }
    else {
        if (node->rChild->height - node->lChild->height <= 1) {
            return 1;
        }
        else return 0;
    }
}
ND* restructure(ND** x, ND** y, ND** z) {
    ND* p = (*z)->parent;
    if ((*z)->rChild == *y && (*y)->rChild == *x) { //case 1
        if (p != NULL) {
            if (p->rChild == *z) p->rChild = *y;
            else p->lChild = *y;
            (*y)->parent = p;
        }
        else {
            (*y)->parent = NULL;
        }
        (*z)->rChild = (*y)->lChild;
        (*y)->lChild->parent = *z;
        (*y)->lChild = *z;
        (*z)->parent = *y;
        return *y;
    }
    else if ((*z)->lChild == *y && (*y)->lChild == *x) { //case 2
        if (p != NULL) {
            if (p->rChild == *z) p->rChild = *y;
            else p->lChild = *y;
            (*y)->parent = p;
        }
        else {
            (*y)->parent = NULL;
        }
        (*z)->lChild = (*y)->rChild;
        (*y)->rChild->parent = *z;
        (*y)->rChild = *z;
        (*z)->parent = *y;
        return *y;
    }
    else if ((*z)->rChild == *y && (*y)->lChild == *x) { //case 3
        if (p != NULL) {
            if (p->rChild == *z) p->rChild = *x;
            else p->lChild = *x;
            (*x)->parent = p;
        }
        else {
            (*x)->parent = NULL;
        }
        (*z)->rChild = (*x)->lChild;
        (*x)->lChild->parent = *z;
        (*y)->lChild = (*x)->rChild;
        (*x)->rChild->parent = *y;
        (*z)->parent = *x;
        (*y)->parent = *x;
        (*x)->lChild = *z;
        (*x)->rChild = *y;
        return *x;
    }
    else { // case 4
        if (p != NULL) {
            if (p->rChild == *z) p->rChild = *x;
            else p->lChild = *x;
            (*x)->parent = p;
        }
        else {
            (*x)->parent = NULL;
        }
        (*z)->lChild = (*x)->rChild;
        (*x)->rChild->parent = *z;
        (*y)->rChild = (*x)->lChild;
        (*x)->lChild->parent = *y;
        (*z)->parent = *x;
        (*y)->parent = *x;
        (*x)->rChild = *z;
        (*x)->lChild = *y;
        return *x;
    }
}