#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct IncidenceList 
{
    struct IncidenceList* next;
    int vIndex;
    int weight;
}I;
typedef struct Vertex {
    int data;
    int visited;
    int distance;
    int locator;
    I* link;
}V;
typedef struct Graph {
    V vertices[100];
    V heap[100];
    int vNum;
    int num;
}G;

I* getIL(int end, int weight);
void insertEdge(G* graph, int start, int end, int weight);
void push(G* graph, V* vertex);
V pop(G* graph);
void upHeap(G* graph, int index);
void downHeap(G* graph, int index);
void swap(G* graph, int index1, int index2);
void PrimJarnikMST(G* graph, int start);
void replaceKey(G* graph);
void swapLocator(G* graph, int index1, int index2);

int main() {
    int n, m;
    int start, end, weight;
    int i;
    G graph;
    I* p, * q;
    scanf("%d %d", &n, &m);
    graph.vNum = n;
    for (i = 0;i < n;i++) {
        graph.vertices[i].data = i + 1; //index 0부터 1씩 들어감
        graph.vertices[i].visited = 0;
        graph.vertices[i].link = getIL(-1, -1);
        graph.vertices[i].distance = INT_MAX;
        graph.vertices[i].locator = -1;
    }
    for (i = 0;i < m;i++) {
        scanf("%d %d %d", &start, &end, &weight);
        insertEdge(&graph, start, end, weight);
    }
    graph.heap[0].distance = -1;
    graph.num = 0;
    PrimJarnikMST(&graph, 0);
    //free
    for (i = 0;i < n;i++) {
        q = graph.vertices[i].link;
        p = q->next;
        while (p != NULL) {
            q->next = p->next;
            free(p);
            p = q->next;
        }
        free(q);
    }
    return 0;
}

void insertEdge(G* graph, int start, int end, int weight) { //오름 차순으로 연결
    I* new, * new2, * p;
    new = getIL(end, weight);
    p = graph->vertices[start - 1].link;
    while (p->next != NULL && p->next->vIndex < end) {
        p = p->next;
    }
    new->next = p->next;
    p->next = new;

    if (start != end) {
        new2 = getIL(start, weight);
        p = graph->vertices[end - 1].link;
        while (p->next != NULL && p->next->vIndex < start) {
            p = p->next;
        }
        new2->next = p->next;
        p->next = new2;
    }

}

I* getIL(int end, int weight) {
    I* new;
    new = (I*)malloc(sizeof(I));
    new->weight = weight;
    new->vIndex = end - 1;
    new->next = NULL;
    return new;
}

void upHeap(G* graph, int index) {
    if (index == 1) return;
    if (graph->heap[index].distance < graph->heap[index / 2].distance) {
        swap(graph, index, index / 2);
        swapLocator(graph, index, index / 2);
        upHeap(graph, index / 2);
    }
    else return;
}

void downHeap(G* graph, int index) {
    int min;
    if (index * 2 > graph->num) return;
    if (index * 2 == graph->num) {
        if (graph->heap[index].distance > graph->heap[index * 2].distance) {
            swap(graph, index, index * 2);
            swapLocator(graph, index, index * 2);
            downHeap(graph, index * 2);
        }
    }
    else {
        if (graph->heap[index * 2].distance < graph->heap[index * 2 + 1].distance) {
            min = index * 2;
        }
        else min = index * 2 + 1;
        if (graph->heap[min].distance < graph->heap[index].distance) {
            swap(graph, min, index);
            swapLocator(graph, min, index);
            downHeap(graph, min);
        }
    }
}

void swap(G* graph, int index1, int index2) { //힙 원소들 교환
    V tmp;
    tmp = graph->heap[index1];
    graph->heap[index1] = graph->heap[index2];
    graph->heap[index2] = tmp;
}

void swapLocator(G* graph, int index1, int index2) { //힙의 교환에 따른 vertices의 locator를 교환
    int tmp;
    tmp = graph->vertices[(graph->heap[index1].data) - 1].locator;
    graph->vertices[(graph->heap[index1].data) - 1].locator = graph->vertices[(graph->heap[index2].data) - 1].locator;
    graph->vertices[(graph->heap[index2].data) - 1].locator = tmp;
}

void push(G* graph, V* vertex) {
    graph->vertices[graph->num].locator = graph->num + 1;
    graph->num++;
    graph->heap[graph->num] = *vertex;
    upHeap(graph, graph->num);
}

V pop(G* graph) {
    V data;
    data = graph->heap[1];
    graph->vertices[graph->heap[1].data - 1].locator = -1;
    graph->heap[1] = graph->heap[graph->num];
    graph->vertices[graph->heap[1].data - 1].locator = 1; //locator 변경!!
    graph->num--;
    downHeap(graph, 1);
    return data;
}

void PrimJarnikMST(G* graph, int start) {
    int i;
    int sum = 0;
    V u;
    I* p;
    graph->vertices[start].distance = 0; //distance 0으로 설정
    for (i = 0;i < graph->vNum;i++) { //큐에 차례대로 삽입
        push(graph, &graph->vertices[i]);
    }
    while (graph->num != 0) {
        u = pop(graph);
        sum += u.distance;
        printf(" %d", u.data);
        graph->vertices[u.data - 1].visited = 1;//방문 처리
        p = graph->vertices[u.data - 1].link->next;
        while (p != NULL) {
            if (graph->vertices[p->vIndex].visited == 0 && p->weight < graph->heap[graph->vertices[p->vIndex].locator].distance) { //아직 방문하지 않았고, 탐색중인 간선의 가중치가 더 작으면
                graph->heap[graph->vertices[p->vIndex].locator].distance = p->weight; //갱신
                upHeap(graph, graph->vertices[p->vIndex].locator);
            }
            p = p->next;
        }
    }
    printf("\n");
    printf("%d\n", sum);
}