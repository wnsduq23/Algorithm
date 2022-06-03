#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node 
{
    int ID;
    char name[21];
}ND;

int binarySearch(ND* st, int l, int r, int id);

int main(void) 
{
    int i, N, id, index;
    char name[21];
    ND* st;
    scanf("%d", &N);
    st = (ND*)malloc(sizeof(ND) * N);
    for (i = 0;i < N;i++) {
        scanf("%d", &id);
        getchar();
        scanf("%s", &name);
        st[i].ID = id;
        strcpy(st[i].name, name);
    }
    scanf("%d", &id);
    index = binarySearch(st, 0, N - 1, id);
    if (index == -1) printf("-1");
    else {
        printf("%d %s", st[index].ID, st[index].name);
    }
    //free
    free(st);
    return 0;
}
int binarySearch(ND* st, int l, int r, int id) 
{
    int mid;
    if (l > r) return -1;
    mid = (l + r) / 2;
    if (st[mid].ID == id) { //mid�� ã������ id�̸�
        return mid;
    }
    else if (id > st[mid].ID) { //ã������ id�� �� ũ��
        binarySearch(st, mid + 1, r, id); //mid+1~r�� Ž��
    }
    else { //ã������ id�� �� ������
        binarySearch(st, l, mid - 1, id); //l~mid-1�� Ž��
    }
}