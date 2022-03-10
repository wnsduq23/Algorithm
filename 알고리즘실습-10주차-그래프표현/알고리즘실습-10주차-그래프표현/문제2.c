#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IncidenceList {
    struct IncidenceList* next;
    int edgeIndex;
}IL;
typedef struct Vertex {
    int data;
    IL* link;
}V;
typedef struct Edge {
    int start;
    int end;
    int weight;
}E;
typedef struct graph {
    V vertices[6];
    E edges[21];
}G;

void insertVertex(G* graph, int data);
void insertEdge(G* graph, int start, int end, int weight);
void adjacent(G graph, int data);
void modify(G* graph, int start, int end, int weight);
IL* getIL(int edgeIndex);

int main() {
    G graph;
    IL* p, * q;
    char ch;
    int data, i, start, end, weight;
    for (i = 0;i < 6;i++) {
        graph.vertices[i].link = getIL(-1); //헤더는 data를 -1로 설정
    }
    insertVertex(&graph, 1);
    insertVertex(&graph, 2);
    insertVertex(&graph, 3);
    insertVertex(&graph, 4);
    insertVertex(&graph, 5);
    insertVertex(&graph, 6);
    insertEdge(&graph, 1, 2, 1);
    insertEdge(&graph, 1, 3, 1);
    insertEdge(&graph, 1, 4, 1);
    insertEdge(&graph, 1, 6, 2);
    insertEdge(&graph, 2, 3, 1);
    insertEdge(&graph, 3, 5, 4);
    insertEdge(&graph, 5, 5, 4);
    insertEdge(&graph, 5, 6, 3);
    while (1) {
        scanf("%c", &ch);
        if (ch == 'a') {
            scanf("%d", &data);
            getchar();
            adjacent(graph, data);
        }
        else if (ch == 'm') {
            scanf("%d %d %d", &start, &end, &weight);
            getchar();
            modify(&graph, start, end, weight);
        }
        else if (ch == 'q') {
            break;
        }
        else {
            printf("입력이 잘못됨\n");
        }
    }
    //free
    for (i = 0;i < 6;i++) {
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

void insertVertex(G* graph, int data) {
    graph->vertices[data - 1].data = data;
}

void insertEdge(G* graph, int start, int end, int weight) {
    IL* p, * new;
    int i, k = 6, sum = 0, edgeIndex;
    for (i = 0;i < start - 1;i++) {
        sum += k - i;
    }
    edgeIndex = end - start + sum;
    graph->edges[edgeIndex].start = start - 1; //index 생각
    graph->edges[edgeIndex].end = end - 1;
    graph->edges[edgeIndex].weight = weight;

    p = graph->vertices[start - 1].link; //헤더로 이동
    while (p->next != NULL && p->next->edgeIndex < edgeIndex) {
        p = p->next;
    }
    new = getIL(edgeIndex);
    new->next = p->next;
    p->next = new;
    if (start != end) {
        p = graph->vertices[end - 1].link;
        while (p->next != NULL && p->next->edgeIndex < edgeIndex) {
            p = p->next;
        }
        new = getIL(edgeIndex);
        new->next = p->next;
        p->next = new;
    }
}

void adjacent(G graph, int data) {
    IL* p;
    int index = data - 1;
    int edgeIndex;
    if (data > 6 || data < 0) {
        printf("-1\n");
        return;
    }
    p = graph.vertices[index].link->next;
    if (p == NULL) {
        return;
    }
    while (p != NULL) {
        edgeIndex = p->edgeIndex;
        if (graph.edges[edgeIndex].start != index) { //start가 연결된 정점이면
            printf(" %d", graph.vertices[graph.edges[edgeIndex].start].data);
            printf(" %d", graph.edges[edgeIndex].weight);
        }
        else if (graph.edges[edgeIndex].end != index) { //end가 연결된 정점이면
            printf(" %d", graph.vertices[graph.edges[edgeIndex].end].data);
            printf(" %d", graph.edges[edgeIndex].weight);
        }
        else if (graph.edges[edgeIndex].start == graph.edges[edgeIndex].end) {//자신이면
            printf(" %d", graph.vertices[graph.edges[edgeIndex].end].data);
            printf(" %d", graph.edges[edgeIndex].weight);
        }
        p = p->next;
    }
    printf("\n");
    return;
}

IL* getIL(int edgeIndex) {
    IL* new;
    new = (IL*)malloc(sizeof(IL));
    new->edgeIndex = edgeIndex;
    new->next = NULL;
    return new;
}

void modify(G* graph, int start, int end, int weight) {
    IL* p, * new, * q1, * q2;
    int index1 = start - 1, index2 = end - 1;
    int edgeIndex, mEdgeIndex;
    int i, k = 6, sum = 0, b, s;
    if (start > 6 || start < 0 || end>6 || end < 0) {
        printf("-1\n");
        return;
    }
    if (start > end) {
        b = start;
        s = end;
    }
    else {
        b = end;
        s = start;
    }
    //수정할 간선의 edgeIndex
    for (i = 0;i < s - 1;i++) {
        sum += k - i;
    }
    mEdgeIndex = b - s + sum;
    q1 = (*graph).vertices[index1].link; //삭제용
    q2 = (*graph).vertices[index2].link; //삭제용
    p = q1->next;
    if (weight != 0) { //삽입 or 수정
        while (p != NULL) {
            edgeIndex = p->edgeIndex;
            if (edgeIndex == mEdgeIndex) {
                (*graph).edges[edgeIndex].weight = weight;
                return;
            }
            p = p->next;
        }
        insertEdge(graph, s, b, weight);
    }
    else { //삭제
        p = q1->next;
        while (p != NULL) {
            edgeIndex = p->edgeIndex;
            if (edgeIndex == mEdgeIndex) {
                q1->next = p->next;
                p->next = NULL;
                free(p);
                break;
            }
            q1 = p;
            p = p->next;
        }
        if (start != end) {
            p = q2->next;
            while (p != NULL) {
                edgeIndex = p->edgeIndex;
                if (edgeIndex == mEdgeIndex) {
                    q2->next = p->next;
                    p->next = NULL;
                    free(p);
                    return;
                }
                q2 = p;
                p = p->next;
            }
            printf("-1\n");
        }
    }
}