#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n, m, s;//정점 수, 간선 수, 출발 번호 전역변수 선언
int* visitedvertices;
int* visitededges;

typedef struct Edge {
	int start_vertex;
	int end_vertex;
}edge;//간선 구조체

typedef struct Incident {
	edge* E;
	struct Incident* next;
}incident;//인접리스트 구현 구조체

typedef struct Vnode {
	int vertex;
	incident* Head;
}vnode;//정점 구조체

typedef struct Graph {
	vnode V[101];
	edge E[1000];
	int edgesize;
}graph;//그래프 구조체

graph* G;

incident* getinode() {
	incident* newnode = (incident*)malloc(sizeof(incident));
	newnode->next = NULL;
	return newnode;
}

edge* getenode(int u, int v) {
	edge* newnode = (edge*)malloc(sizeof(edge));
	newnode->start_vertex = u;
	newnode->end_vertex = v;
	return newnode;
}

void Init_Graph() {
	G = (graph*)malloc(sizeof(graph));
	G->edgesize = 0;
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i <= n; i++) {
		G->V[i].vertex = i;
		G->V[i].Head = getinode();
	}
}

void addEdge(int u, int v) {
	G->E[G->edgesize].start_vertex = u;
	G->E[G->edgesize].end_vertex = v;
	incident* newnode = getinode();
	newnode->E = G->E + G->edgesize;
	incident* tmp = G->V[u].Head;
	while (tmp->next != NULL) {
		if (tmp->next->E->start_vertex == u) {
			if (tmp->next->E->end_vertex < newnode->E->end_vertex) {
				tmp = tmp->next;
			}
			else {
				newnode->next = tmp->next;
				tmp->next = newnode;
				break;
			}
		}//그대로 비교
		else if (tmp->next->E->end_vertex == u) {
			if (tmp->next->E->start_vertex < newnode->E->end_vertex) {
				tmp = tmp->next;
			}
			else {
				newnode->next = tmp->next;
				tmp->next = newnode;
				break;
			}
		}//반대로 비교
	}
	if (tmp->next == NULL) {
		tmp->next = newnode;
	}
	if (u != v) {
		incident* newnode = getinode();
		newnode->E = G->E + G->edgesize;
		incident* tmp = G->V[v].Head;
		while (tmp->next != NULL) {
			if (tmp->next->E->start_vertex == v) {
				if (tmp->next->E->end_vertex < newnode->E->start_vertex) {
					tmp = tmp->next;
				}
				else {
					newnode->next = tmp->next;
					tmp->next = newnode;
					break;
				}
			}//그대로 비교
			else if (tmp->next->E->end_vertex == v) {
				if (tmp->next->E->start_vertex < newnode->E->start_vertex) {
					tmp = tmp->next;
				}
				else {
					newnode->next = tmp->next;
					tmp->next = newnode;
					break;
				}
			}//반대로 비교
		}
		if (tmp->next == NULL) {
			tmp->next = newnode;
		}
	}
	G->edgesize++;
}

void Make_Graph() {
	int u, v;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}
}

int opposite(int v, edge* E) {
	if (E->start_vertex == v) {
		return E->end_vertex;
	}
	else {
		return E->start_vertex;
	}
}

int findedgeidx(edge* E) {
	for (int i = 0; i < m; i++) {
		if (G->E[i].start_vertex == E->start_vertex && G->E[i].end_vertex == E->end_vertex) {
			return i;
		}
		else if (G->E[i].start_vertex == G->E[i].end_vertex && G->E[i].end_vertex == G->E[i].start_vertex) {
			return i;
		}
	}
	return -1;
}

void rDFS(int a) {
	visitedvertices[a] = 1;
	printf("%d\n", a);
	incident* traverse = G->V[a].Head->next;
	while (traverse != NULL) {
		int w = opposite(a, traverse->E);
		if (visitedvertices[w] == 0) {
			visitededges[findedgeidx(traverse->E)] = 1;
			rDFS(w);
		}
		else {
			visitededges[findedgeidx(traverse->E)] = 0;
		}
		traverse = traverse->next;
	}
}

void DFS() {
	visitedvertices = (int*)calloc(n + 1, sizeof(int));
	visitededges = (int*)calloc(m, sizeof(int));
	for (int i = 1; i <= n; i++) {
		if (visitedvertices[i] == 0) {
			rDFS(i);
		}
	}
}

int main(void) {
	Init_Graph();
	Make_Graph();
	DFS();
	return 0;
}