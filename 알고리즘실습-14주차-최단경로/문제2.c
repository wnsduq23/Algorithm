#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
	int is;
	int ie;
	int weight;
}E;
typedef struct Vertex
{
	int elem;
	int distance;
	int visited;
}V;
typedef struct graph
{
	V vertices[101];
	E edge[1000];
	int size;
	int eNum;
}Graph;

void BellmanFordShortestPaths(Graph* G, int sIndex);
void swap(Graph* G, int index1, int index2);

int main()
{
	int n, m, s;
	int i;
	int v1, v2, w;
	Graph G;

	scanf("%d %d %d", &n, &m, &s);
	G.size = n;
	G.eNum = m;
	for (i = 1;i <= n;i++)
	{
		G.vertices[i].elem = i;
		G.vertices[i].distance = 1000000;
		G.vertices[i].visited = 0;
	}
	for (i = 0;i < m;i++)
	{
		scanf("%d %d %d", &v1, &v2, &w);
		G.edge[i].is = v1;
		G.edge[i].ie = v2;
		G.edge[i].weight = w;
	}
	BellmanFordShortestPaths(&G, s);
	for (i = 1;i <= G.size;i++)
	{
		if (G.vertices[i].visited == 0) continue;
		printf("%d %d\n", G.vertices[i].elem, G.vertices[i].distance);
	}
	return 0;
}

void BellmanFordShortestPaths(Graph* G, int s)

{
	int start, end;
	G->vertices[s].distance = 0;
	for (int i = 1;i <= G->size - 1;i++)
	{
		for (int j = 0;j < G->eNum;j++)
		{
			start = G->edge[j].is;
			end = G->edge[j].ie;
			if (G->vertices[end].distance == 1000000 && G->vertices[start].distance == 1000000) continue;
			if (G->vertices[end].distance > G->vertices[start].distance + G->edge[j].weight)
			{
				G->vertices[end].distance = G->vertices[start].distance + G->edge[j].weight;
				G->vertices[end].visited = 1;
			}
		}
	}
}