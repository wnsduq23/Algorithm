#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#pragma warning(disable : 4996)

typedef struct IncidenceNode
{
	struct IncidenceNode* next;
	int vIndex;
	int weight;
}I;
typedef struct vertexnode
{
	struct IncidenceNode* Head;
	int locator;
	int distance;
	int elem;
	int visited;
}V;
typedef struct G
{
	int num;
	V* vertices;
	int size;
	V H[101];
}Graph;

void initG(Graph* G, int n);
void insertEdge(Graph* G, int v1, int v2, int w);
I* getLL(int vIndex, int weight);
void addList(I* Head, int OpV, int w);
void upHeap(Graph* G, int i);
void downHeap(Graph* G, int i);
void swap(Graph* G, int i1, int i2);
void swapLocator(Graph* G, int i1, int i2);
void push(Graph* G, V vertex);
V pop(Graph* G);
void DijikstraShortestPaths(Graph* G, int start);

int main(void)
{
	Graph G;
	int n, m, s;
	int v1, v2, w;

	scanf("%d %d %d", &n, &m, &s);
	initG(&G, n);
	for (int i = 0;i < m;i++)
	{
		scanf("%d %d %d", &v1, &v2, &w);
		insertEdge(&G, v1, v2, w);
	}
	DijikstraShortestPaths(&G, s);
	for (int i = 1;i <= G.size;i++)
	{
		if (G.vertices[i].visited == 0) continue;//O
		printf("%d %d\n", G.vertices[i].elem, G.vertices[i].distance);
	}
	return 0;
}

void initG(Graph* G, int n)
{
	G->vertices = (V*)malloc(sizeof(V) * (n + 1));
	G->num = 0;
	G->size = n;

	for (int i = 1;i <= n;i++)
	{
		G->vertices[i].distance = INT_MAX;
		G->vertices[i].elem = i;
		G->vertices[i].Head = getLL(-1, -1);
		G->vertices[i].locator = -1;
		G->vertices[i].visited = 0;
	}
}

I* getLL(int vIndex, int weight)
{
	I* new = (I*)malloc(sizeof(I));
	new->next = NULL;
	new->vIndex = vIndex;
	new->weight = weight;
	return new;
}

void insertEdge(Graph* G, int v1, int v2, int w)
{
	addList(G->vertices[v1].Head, v2, w);
	addList(G->vertices[v2].Head, v1, w);
}

void addList(I* Head, int OpV, int w)
{
	I* new = getLL(OpV, w);
	I* p = Head;

	while (p->next != NULL && p->next->vIndex < OpV)//오름차순 정렬
		p = p->next;
	new->next = p->next;
	p->next = new;
}

void upHeap(Graph* G, int i)
{
	if (i == 1) return;
	if (G->H[i].distance < G->H[i / 2].distance)
	{
		swap(G, i, i / 2);
		swapLocator(G, i, i / 2);
		upHeap(G, i / 2);
	}
	else return;
}

void downHeap(Graph* G, int i)
{
	int min;

	if (i * 2 > G->num) return;
	if (i * 2 == G->num)
	{
		if (G->H[i].distance > G->H[i * 2].distance)
		{
			swap(G, i, i * 2);
			swapLocator(G, i, i * 2);
			downHeap(G, i * 2);
		}
	}
	else
	{
		if (G->H[i * 2].distance < G->H[i * 2 + 1].distance)
			min = i * 2;
		else min = i * 2 + 1;
		if (G->H[min].distance < G->H[i].distance)
		{
			swap(G, min, i);
			swapLocator(G, min, i);
			downHeap(G, min);
		}
	}
}

void swap(Graph* G, int i1, int i2)
{
	V tmp;
	tmp = G->H[i1];
	G->H[i1] = G->H[i2];
	G->H[i2] = tmp;
}

void swapLocator(Graph* G, int i1, int i2)
{
	int tmp;

	tmp = G->vertices[(G->H[i1].elem)].locator;
	G->vertices[(G->H[i1].elem)].locator = G->vertices[(G->H[i2].elem)].locator;
	G->vertices[(G->H[i2].elem)].locator = tmp;
}

void push(Graph* G, V vertex)
{
	G->num++;
	G->vertices[G->num].locator = G->num;
	G->H[G->num] = vertex;
	upHeap(G, G->num);
}
V pop(Graph* G)
{
	V data;

	data = G->H[1];
	G->vertices[G->H[1].elem].locator = -1;
	G->H[1] = G->H[G->num];
	G->vertices[G->H[1].elem].locator = 1; //locator 변경!!
	G->num--;
	downHeap(G, 1);
	return data;
}

void DijikstraShortestPaths(Graph* G, int start)
{
	int i;
	V u;
	I* p;

	G->vertices[start].distance = 0; //distance 0으로 설정
	for (i = 1;i <= G->size;i++)//큐에 차례대로 삽입
		push(G, G->vertices[i]);
	while (G->num != 0)
	{
		u = pop(G);
		p = G->vertices[u.elem].Head->next;
		while (p != NULL)
		{
			if (G->vertices[p->vIndex].distance > p->weight + u.distance)
			{
				G->vertices[p->vIndex].distance = p->weight + u.distance;
				G->H[G->vertices[p->vIndex].locator].distance = p->weight + u.distance;
				G->vertices[p->vIndex].visited = 1;
				upHeap(G, G->vertices[p->vIndex].locator);
			}
			p = p->next;
		}
	}
}