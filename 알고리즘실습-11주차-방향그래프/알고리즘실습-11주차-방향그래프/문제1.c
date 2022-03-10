#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IncidenceList {
    int vIndex;
    struct IncidenceList* next;
}IL;
typedef struct Vertex {
    char name;
    int inDegree;
    IL* uHeader;
    IL* wHeader;
}V;
typedef struct Graph {
    V vertices[100];
    int n;
    int m;
    int* topOrder;
    int* queue;
    int front, rear;
}G;

G buildGraph(G* graph);
G insertVertex(char vName, int ind, G* graph);
G insertDirectedEdge(char uName, char wName, int ind, G* graph);
int Index(char vName, G graph);
void addFirst(IL* header, int ind);
int* topologicalSort(G graph);
int isEmpty(G graph);
void enqueue(G* graph, V* vertice);
int dequeue(G* graph);

int main() {
    G graph;
    IL* p, * q;
    int i;
    int* topOrder;
    graph = buildGraph(&graph);
    topOrder = topologicalSort(graph);
    if (topOrder[0] == 0) {
        printf("0\n");
    }
    else {
        for (i = 1;i < graph.n + 1;i++) {
            printf("%c ", graph.vertices[topOrder[i]].name);
        }
    }

    //free
    free(graph.queue);
    free(graph.topOrder);
    for (i = 0;i < graph.n;i++) {
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

G buildGraph(G* graph) {
    int i;
    char s, e;
    char ch;
    scanf("%d", &graph->n);
    getchar();
    for (i = 0;i < graph->n;i++) {
        scanf("%c", &ch);
        getchar();
        insertVertex(ch, i, graph);
    }
    scanf("%d", &graph->m);
    getchar();
    for (i = 0;i < graph->m;i++) {
        scanf("%c %c", &s, &e);
        getchar();
        insertDirectedEdge(s, e, i, graph);
    }
    graph->front = graph->rear = 0;
    graph->queue = (int*)malloc(sizeof(int) * graph->n);
    graph->topOrder = (int*)malloc(sizeof(int) * (graph->n + 1));
    return *graph;
}

G insertVertex(char vName, int ind, G* graph) {
    graph->vertices[ind].inDegree = 0;
    graph->vertices[ind].name = vName;
    graph->vertices[ind].uHeader = (IL*)malloc(sizeof(IL));
    graph->vertices[ind].wHeader = (IL*)malloc(sizeof(IL));
    graph->vertices[ind].uHeader->next = NULL;
    graph->vertices[ind].wHeader->next = NULL;
    graph->vertices[ind].uHeader->vIndex = -1;
    graph->vertices[ind].wHeader->vIndex = -1;
    return *graph;
}

G insertDirectedEdge(char uName, char wName, int ind, G* graph) {
    int iu, iw;
    iu = Index(uName, *graph);
    iw = Index(wName, *graph);
    addFirst(graph->vertices[iu].wHeader, iw);
    addFirst(graph->vertices[iw].uHeader, iu);
    graph->vertices[iw].inDegree++; //w의 inDegree 증가
    return *graph;
}

int Index(char vName, G graph) {
    int i;
    for (i = 0;i < graph.n;i++) {
        if (graph.vertices[i].name == vName) return i;
    }
    return -1;
}

void addFirst(IL* header, int ind) {
    IL* new;
    new = (IL*)malloc(sizeof(IL));
    new->vIndex = ind;
    new->next = header->next;
    header->next = new;
}

int* topologicalSort(G graph) {
    int i, * in, t = 1, index;
    IL* p;
    in = (int*)malloc(sizeof(int) * graph.n);
    for (i = 0;i < graph.n;i++) { //정점 개수만큼 돌면서 in 저장
        in[i] = graph.vertices[i].inDegree;
        if (in[i] == 0) {
            enqueue(&graph, &graph.vertices[i]);
        }
    }
    while (!isEmpty(graph)) {
        index = dequeue(&graph);
        graph.topOrder[t] = index;
        t++;
        p = graph.vertices[index].wHeader->next; //끝나는 정점들
        while (p != NULL) {
            in[p->vIndex]--;
            if (in[p->vIndex] == 0) {
                enqueue(&graph, &graph.vertices[p->vIndex]);
            }
            p = p->next;
        }
    }
    if (t <= graph.n) {
        graph.topOrder[0] = 0;
    }
    else {
        graph.topOrder[0] = 1;
    }
    free(in);
    return graph.topOrder;
}

int isEmpty(G graph) {
    if (graph.front == graph.rear) return 1;
    return 0;
}

void enqueue(G* graph, V* vertice) {
    int index;
    int i;
    index = Index(vertice->name, *graph);
    graph->queue[graph->rear] = index;
    graph->rear++;
}

int dequeue(G* graph) {
    int index;
    index = graph->queue[graph->front];
    graph->front++;
    return index;
}