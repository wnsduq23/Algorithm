#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 
#pragma warning(disable:4996)

typedef struct edge
{
	int v1, v2;
	int w;
}E;

typedef struct Incid
{
	int Vs;
	struct Incid* next;
}I;

typedef struct vertex
{
	int elem;
}V;

typedef struct sack
{
	int size;//배낭 안에 몇개의 정점이 들어가 있는지
	I* head;
}S;

typedef struct graph
{
	V* vertices;
	E* edges;
	int Vsize, Esize;
	int num;
}Graph;

typedef struct heap
{
	int key; //인덱스?
	int w;
}H;

void initG(Graph* G, int n, int m);
void insertEdge(Graph* G, int v1, int v2, int w, int idx);
void KruskalMST(Graph* G);
S* buildSet(Graph* G);
H* buildHeap(Graph* G);
int findSet(Graph* G, S* set, int v);
void unionSet(Graph* G, S* set, int v1, int v2);
void downHeap(H* heap, int idx, int size);
int removeMin(H* heap, int idx);
void swap(H* x, H* y);
void addFirst(I** head, int idx);
int deleteFirst(I** head);
void freeSet(Graph* G, S* set);
void freeGraph(Graph* G);

int main(void)
{
	Graph G;
	I* head;
	int n, m;
	int v1, v2, w;

	scanf("%d %d", &n, &m);
	initG(&G, n, m);
	for (int i = 0; i < G.Esize; i++)
	{
		scanf("%d %d %d", &v1, &v2, &w);
		insertEdge(&G, v1, v2, w, i);
	}
	KruskalMST(&G);
	freeGraph(&G);
	return 0;
}

void initG(Graph* G, int n, int m)
{
	G->Vsize = n;
	G->Esize = m;
	G->num = 0;
	G->vertices = (V*)malloc(sizeof(V) * (n + 1)); //1부터 시작
	G->edges = (E*)malloc(sizeof(E) * m);
	for (int i = 1; i <= n; i++)
	{
		G->vertices[i].elem = i;
	}
}

void insertEdge(Graph* G, int v1, int v2, int w, int idx)
{
	G->edges[idx].v1 = v1;
	G->edges[idx].v2 = v2;
	G->edges[idx].w = w;
}

void KruskalMST(Graph* G)
{
	S* set = buildSet(G);
	H* H = buildHeap(G);
	int size = G->Esize;
	int sum = 0;
	int u, v1, v2;

	while (size > 0)
	{
		u = removeMin(H, size);// 같은 배낭안에 있냐 없냐를 체크하는 구간
		v1 = findSet(G, set, G->edges[u - 1].v1);
		v2 = findSet(G, set, G->edges[u - 1].v2);
		if (v1 != v2)
		{
			printf(" %d", G->edges[u - 1].w);
			sum += G->edges[u - 1].w;
			unionSet(G, set, v1, v2);
		}
		size--;
	}
	printf("\n%d", sum);
	freeSet(G, set);
	free(H);
}

S* buildSet(Graph* G)
{
	S* set = (S*)malloc(sizeof(S) * G->Vsize);

	for (int i = 0; i < G->Vsize; i++)
	{
		set[i].size = 0;
		set[i].head = (I*)malloc(sizeof(I));
		set[i].head->Vs = G->vertices[i + 1].elem;
		set[i].head->next = NULL;
	}
	return set;
}

H* buildHeap(Graph* G)
{
	H* heap = (H*)malloc(sizeof(H) * (G->Esize + 1));
	int i;

	for (i = 1; i <= G->Esize; i++)
	{ //초기화
		heap[i].w = G->edges[i - 1].w;
		heap[i].key = i;
	}
	for (i = G->Esize / 2; i >= 1; i--)
	{ //상향식 힙생성
		downHeap(heap, i, G->Esize);
	}
	return heap;
}

int findSet(Graph* G, S* set, int v)
{
	I* p;

	for (int i = 0; i < G->Vsize; i++)
	{
		p = set[i].head;
		while (p != NULL)
		{
			if (G->vertices[p->Vs].elem == v) return i;
			p = p->next;
		}
	}
	return -1;
}

void unionSet(Graph* G, S* set, int v1, int v2)
{
	int temp, i;

	if (set[v1].size < set[v2].size)
	{
		temp = v1;
		v1 = v2;
		v2 = temp;
	}
	while (1)
	{
		i = deleteFirst(&(set[v2].head));
		if (i == -1) break;
		addFirst(&(set[v1].head), i);
	}
	set[v2].head = NULL;
	set[v2].size = 0;
}

void downHeap(H* H, int idx, int size)
{
	int left = 2 * idx;
	int right = 2 * idx + 1;
	int min;

	if (left > size) return;
	min = left;
	if (right <= size)
	{
		if (H[right].w < H[left].w)
		{
			min = right;
		}
	}
	if (H[idx].w <= H[min].w) return;
	swap(H + idx, H + min);
	downHeap(H, min, size);
}

void swap(H * x, H * y)
{
	H temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
}

int removeMin(H* Heap, int idx)
{
	H remove;

	if (idx == 0) return -1;
	remove = Heap[1];
	swap(Heap + 1, Heap + idx);
	downHeap(Heap, 1, --idx);
	return remove.key;
}

void addFirst(I** H, int idx)
{
	I* node = (I*)malloc(sizeof(I));
	
	node->Vs = idx;
	node->next = *H;
	*H = node;
}

int deleteFirst(I** head)
{
	int remove;

	if (*head == NULL) return -1;
	remove = (*head)->Vs;
	*head = (*head)->next;
	return remove;
}

void freeSet(Graph* G, S* set)
{
	I* p, * next;

	for (int i = 0; i < G->Vsize; i++)
	{
		p = set[i].head;
		while (p != NULL)
		{
			next = p->next;
			free(p);
			p = next;
		}
	}
	free(set);
}

void freeGraph(Graph* G)
{
	free(G->vertices);
	free(G->edges);
}