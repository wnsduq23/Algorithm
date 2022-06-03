#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//������ ��ġ ������ ������ �ִ� ���� ����Ʈ�� �̿��Ͽ� DFS�� �̿��� ���� ���� ����

typedef struct IncidenceList 
{
    int vIndex;
    struct IncidenceList* next;
}IL;

typedef struct Vertex 
{
    char name;
    int visited;
    int isTopOrder;
    IL* uHeader;
    IL* wHeader;
}V;

typedef struct Graph 
{
    V vertices[10];
    int* topOrder;
    int n;
    int m;
    int cycle;
}G;

void insertVertex(G* graph, char vName, int ind);
void insertDirectedEdge(char uName, char wName, G* graph);
int Index(char vName, G graph);
void add(IL* header, int ind);
void rToplogicalSortDFS(G* graph, int ind);

int main(void) 
{
    int n, m, i;
    char s, ch;
    char u, w;
    IL* p, * q;
    G graph;

    scanf("%d %d %c", &n, &m, &s);
    graph.n = n;
    graph.m = m;
    graph.cycle = 0;
    graph.topOrder = (int*)malloc(sizeof(int) * n);
    for (i = 0;i < n;i++) {
        getchar();
        scanf("%c", &ch);
        insertVertex(&graph, ch, i);
        graph.topOrder[i] = -1;
    }
    for (i = 0;i < m;i++) {
        getchar();
        scanf("%c %c", &u, &w);
        insertDirectedEdge(u, w, &graph);
    }
    rToplogicalSortDFS(&graph, Index(s, graph)); //���� ���ں��� ���� ���� ����
    for (i = 0;i < n;i++) {
        if (graph.vertices[i].visited == 0) { //fresh�� ����
            rToplogicalSortDFS(&graph, i);
        }
    }
    if (graph.cycle == 1) {
        printf("-1");
    }
    else {
        for (i = 0;i < n;i++) {
            printf("%c ", graph.vertices[graph.topOrder[i]].name);
        }
    }
    //free
    free(graph.topOrder);
    for (i = 0;i < n;i++) {
        p = graph.vertices[i].uHeader;
        while (p->next != NULL) {
            q = p->next;
            p->next = q->next;
            free(q);
        }
        free(p);
        p = graph.vertices[i].wHeader;
        while (p->next != NULL) {
            q = p->next;
            p->next = q->next;
            free(q);
        }
        free(p);
    }
    return 0;
}

void insertVertex(G* graph, char vName, int ind) { //���� �߰� �� �ʱ�ȭ
    graph->vertices[ind].name = vName;
    graph->vertices[ind].uHeader = (IL*)malloc(sizeof(IL));
    graph->vertices[ind].wHeader = (IL*)malloc(sizeof(IL));
    graph->vertices[ind].uHeader->next = NULL;
    graph->vertices[ind].wHeader->next = NULL;
    graph->vertices[ind].uHeader->vIndex = -1;
    graph->vertices[ind].wHeader->vIndex = -1;
    graph->vertices[ind].visited = 0;
    graph->vertices[ind].isTopOrder = 0;
}

void insertDirectedEdge(char uName, char wName, G* graph) { //���� ����Ʈ �߰�
    int iu, iw;
    iu = Index(uName, *graph);
    iw = Index(wName, *graph);
    add(graph->vertices[iu].wHeader, iw);
    add(graph->vertices[iw].uHeader, iu);
}

int Index(char vName, G graph) { //ã�� ������ �ε��� ���ϴ� �Լ�
    int i;
    for (i = 0;i < graph.n;i++) {
        if (graph.vertices[i].name == vName) return i;
    }
    return -1;
}

void add(IL* header, int ind) { //���� �������� ���� ����Ʈ �߰� �Լ�
    IL* new, * p;
    new = (IL*)malloc(sizeof(IL));
    new->vIndex = ind;
    p = header;
    while (p->next != NULL) {
        if (p->next->vIndex > ind) break;
        p = p->next;
    }
    new->next = p->next;
    p->next = new;
}

void rToplogicalSortDFS(G* graph, int ind) { //DFS�� �̿��� ���� ���� �Լ�
    IL* p;
    graph->vertices[ind].visited = 1; //�湮
    p = graph->vertices[ind].wHeader->next;
    while (p != NULL) {
        if (graph->vertices[p->vIndex].visited == 0) { //fresh�� 
            rToplogicalSortDFS(graph, p->vIndex);
        }
        else if (graph->vertices[p->vIndex].isTopOrder == 0) { //isTopOrder�� ������ ���� ������ �Ǿ����� Ȯ�ο�
            graph->cycle = 1;
            return;
        }
        p = p->next;
    }
    graph->vertices[ind].isTopOrder = 1;
    graph->topOrder[graph->n - 1] = ind;
    graph->n--;
}