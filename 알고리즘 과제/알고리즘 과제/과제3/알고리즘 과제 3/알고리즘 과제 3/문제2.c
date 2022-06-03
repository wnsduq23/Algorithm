#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int ID;
    char name[21];
}ND;

void divideAndConquer(ND* st, int l, int r, int id, int ans[]);

int main(void) 
{
    int i, N, id, ans[1];
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
    ans[0] = -1;
    divideAndConquer(st, 0, N - 1, id, ans);
    if (ans[0] == -1) printf("-1");
    else {
        printf("%d %s", st[ans[0]].ID, st[ans[0]].name);
    }
    //free
    free(st);
    return 0;
}

void divideAndConquer(ND* st, int l, int r, int id, int ans[]) {
    int mid;
    if (l > r) return;
    mid = (l + r) / 2;
    if (st[mid].ID == id) { //mid가 찾으려는 id이면
        ans[0] = mid; //답 배열에 index 넣어주
        return;
    }
    divideAndConquer(st, l, mid - 1, id, ans); //l~mid-1까지 다시 분할 후 탐색
    divideAndConquer(st, mid + 1, r, id, ans); //mid+1 ~ r까지 다시 분할 후 탐색
}