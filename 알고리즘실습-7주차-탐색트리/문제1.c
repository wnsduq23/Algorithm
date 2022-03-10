#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node* lChild;
    struct Node* rChild;
    struct Node* parent;
    int key;
}ND;

typedef struct BST {
    ND* Root;
}B;

ND* getExternalNode(ND** r);
int findElement(B* bst, int k);
void insertItem(B* bst, int k);
ND* treeSearch(B* bst, int k);
int removeElement(B* bst, int k);
int isExternal(ND* node);
int isInternal(ND* node);
ND* inOrderSucc(ND* node);
void printTree(ND* root);
ND* reduceExternal(B* bst, ND* z);
ND* sibling(ND* w);
void freeTree(ND* root);

int main() {
    char ch;
    int data;
    B bst;
    ND* root;
    bst.Root = (ND*)malloc(sizeof(ND));
    bst.Root->lChild = bst.Root->rChild = bst.Root->parent = NULL;
    while (1) {
        scanf("%c", &ch);
        if (ch == 'i') {
            scanf("%d", &data);
            insertItem(&bst, data);
        }
        else if (ch == 'd') {
            scanf("%d", &data);
            data = removeElement(&bst, data);
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
            printf("�Է��� �߸�����\n");
        }
        getchar();
    }
    root = bst.Root;
    freeTree(root); //���� Ʈ�� ���ҵ� free
    return 0;
}

ND* getExternalNode(ND** r) {
    ND* newnode;
    newnode = (ND*)malloc(sizeof(ND));
    newnode->lChild = newnode->rChild = NULL;
    newnode->parent = *r;
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
        if (k > r->key) {//�� ū ���̸� ���������� �̵�
            r = r->rChild;
        }
        else {//�� ���� ���̸� �������� �̵�
            r = r->lChild;
        }
    }
}
void insertItem(B* bst, int k) {
    ND* r = bst->Root;
    while (1) {
        if (isExternal(r)) { //r�� �ܺγ���
            r->key = k;
            r->lChild = getExternalNode(&r);
            r->rChild = getExternalNode(&r);
            return;
        }
        if (k > r->key) {//�� ū ���̸� ���������� �̵�
            r = r->rChild;
        }
        else {
            r = r->lChild;
        }
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

int removeElement(B* bst, int k) {
    ND* w; //ã������ Ű���� �ִ��� Ȯ��
    ND* wp, * z, * zs, * ios;
    int key;
    w = treeSearch(bst, k);
    if (isExternal(w)) {
        printf("X\n");
        return 0;
    }
    key = w->key;
    if (isExternal(w->lChild) || isExternal(w->rChild)) {//�� �ڽ� �� �ϳ��� �ܺ� ����
        if (isExternal(w->lChild)) { //���� �ڽ��� �ܺ� ����̸�
            z = w->lChild;
        }
        else { //������ �ڽ��� �ܺ� ����̸�
            z = w->rChild;
        }
        reduceExternal(bst, z);
    }
    else { //�� �ڽ� ��� ���� ����̸�
        ios = inOrderSucc(w);
        w->key = ios->key;
        if (isExternal(ios->lChild)) {
            z = ios->lChild;
        }
        else {
            z = ios->rChild;
        }
        reduceExternal(bst, z);
    }
    printf("%d\n", key);
    return key;
}

int isExternal(ND* node) {
    if (node->lChild == NULL && node->rChild == NULL) return 1;
    else return 0;
}

int isInternal(ND* node) {
    if (node->lChild != NULL || node->rChild != NULL) return 1;
    else return 0;
}

ND* inOrderSucc(ND* node) {
    ND* f = node;
    f = f->rChild;
    if (isExternal(f)) {
        printf("������ȸ �İ��ڰ� �����ϴ�\n");
        return f; //External ��ȯ
    }
    while (1) {
        if (isExternal(f->lChild)) {
            return f;
        }
        f = f->lChild;
    }

}

void printTree(ND* root) {
    if (isExternal(root)) return;
    printf(" %d", root->key);
    printTree(root->lChild);
    printTree(root->rChild);
}

ND* reduceExternal(B* bst, ND* z) {
    ND* w, * zs, * wp;
    w = z->parent;
    zs = sibling(z);
    wp = w->parent;
    if (w->parent == NULL) { //w�� ��Ʈ��
        bst->Root = zs;
        zs->parent = NULL;
    }
    else {
        zs->parent = wp;
        if (wp->rChild == w) {
            wp->rChild = zs;
        }
        else {
            wp->lChild = zs;
        }
    }
    free(z);
    free(w);
    return zs;
}

ND* sibling(ND* z) {
    if (z->parent == NULL) { //z�� ��Ʈ��
        printf("��Ʈ�Դϴ�\n");
        return z;
    }
    if (z->parent->lChild == z) {
        return z->parent->rChild;
    }
    else {
        return z->parent->lChild;
    }
}

void freeTree(ND* root) {
    if (isExternal(root)) {
        free(root);
        return;
    }
    freeTree(root->lChild);
    freeTree(root->rChild);
}