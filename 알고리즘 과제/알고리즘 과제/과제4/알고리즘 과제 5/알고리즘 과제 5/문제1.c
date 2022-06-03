#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//������ ��ġ ������ ������ �ִ� ���� ����Ʈ�� �̿��� �׷��� ����

typedef struct IncidenceList 
{
    struct IncidenceList* next;
    int vIndex;
    int weight;
    int type;//0�̸� new, 1�̸� Tree, 2�� cross
    int print; //����� ���� ����
    //�Է��� 3 1 2�� �޾��� �� ������ ����� �� 3 1�� �ؾߵǱ� ������ ǥ�����ֱ� ����
}IL;

typedef struct Vertex 
{
    int name;
    IL* header;
    int visited;
}V;

typedef struct Graph 
{
    V vertices[100];
    int vNum;
}G;

void BFS(G* graph, int start);
IL* getIL(int vIndex, int weight);

int main(void) 
{
    int n, m, s;
    int v1, v2, w;
    int i;
    IL* p, * new, * q;
    G graph;

    scanf("%d %d %d", &n, &m, &s);
    graph.vNum = n;
    for (i = 0;i < n;i++) {
        graph.vertices[i].name = i + 1;
        graph.vertices[i].header = getIL(-1, -1);
        graph.vertices[i].visited = 0;
    }
    for (i = 0;i < m;i++) {
        scanf("%d %d %d", &v1, &v2, &w);
        p = graph.vertices[v1 - 1].header; //v1 ������ ���� ����Ʈ ����
        while (p->next != NULL) {
            if (p->next->vIndex > v2 - 1) {
                break;
            }
            p = p->next;
        }
        new = getIL(v2 - 1, w);
        new->next = p->next;
        p->next = new;
        new->print = 1;

        p = graph.vertices[v2 - 1].header; //v2 ������ ���� ����Ʈ ����
        while (p->next != NULL) {
            if (p->next->vIndex > v1 - 1) {
                break;
            }
            p = p->next;
        }
        new = getIL(v1 - 1, w);
        new->next = p->next;
        p->next = new;
        new->print = 0;
    }
    BFS(&graph, s);
    //free
    for (i = 0;i < n;i++) {
        p = graph.vertices[i].header;
        while (p->next != NULL) {
            q = p->next;
            p->next = q->next;
            free(q);
        }
        free(p);
    }
    return 0;
}

IL* getIL(int vIndex, int weight) {
    IL* new;
    new = (IL*)malloc(sizeof(IL));
    new->next = NULL;
    new->type = 0;
    new->vIndex = vIndex;
    new->weight = weight;
}

void BFS(G* graph, int start) {
    int queue[100];
    int sum = 0;
    int dData; //dequeue�� ��
    int f = 0, r = 0;
    IL* p, * q;
    queue[r] = start - 1;
    r++;
    while (f != r) {
        graph->vertices[queue[f]].visited = 1; //�湮
        p = graph->vertices[queue[f]].header->next;
        dData = queue[f];
        f++; //dequeue
        while (p != NULL) {
            if (graph->vertices[p->vIndex].visited == 1 && p->type == 0) { //�̹� �湮 + Tree�ƴϸ�
                p->type = 2; //cross
                q = graph->vertices[p->vIndex].header->next;
                while (q != NULL) {
                    if (dData + 1 == graph->vertices[q->vIndex].name) {
                        q->type = 2; //cross
                        break;
                    }
                    q = q->next;
                }
                if (p->print == 1) { //�Է� ���� ������ ���
                    printf("%d %d\n", dData + 1, graph->vertices[p->vIndex].name);
                }
                else {
                    printf("%d %d\n", graph->vertices[p->vIndex].name, dData + 1);
                }
            }
            else if (graph->vertices[p->vIndex].visited == 0) { //���� �湮 ��������
                p->type = 1; //Tree
                q = graph->vertices[p->vIndex].header->next;
                while (q != NULL) {
                    if (dData + 1 == graph->vertices[q->vIndex].name) { //�ݴ������� ���� Tree ǥ��
                        q->type = 1; //Tree
                        break;
                    }
                    q = q->next;
                }
                graph->vertices[p->vIndex].visited = 1; //�湮 ó��
                queue[r] = p->vIndex; //enqueue
                r++;
                sum += p->weight;
            }
            p = p->next;
        }
    }
    printf("%d\n", sum);
}