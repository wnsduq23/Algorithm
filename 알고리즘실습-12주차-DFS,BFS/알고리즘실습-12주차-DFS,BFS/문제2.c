#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n, m, s;//정점 수, 간선 수, 시작 정점 전역변수 선언

typedef struct Queue {
	int queue[1001];
	int front;
	int rear;
}queue;//큐 구조체

typedef struct edge {
	int start_vertex;
	int end_vertex;
}edge;//간선 구조체

typedef struct vertex {
	int vertex;
}vertex;//정점 구조체

typedef struct Graph {
	vertex V[101];
	edge E[1000];
	int adj_matrix[101][101];
	int edgesize;
}graph;//그래프 구조체 : 인접행렬까지 포함

graph *G;
queue *Q;//전역변수 선언

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	G->edgesize = 0;
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			G->adj_matrix[i][j] = 0;
		}
		G->V[i].vertex = i;
	}
}//그래프 초기화 함수

void addEdge(int u, int v) {
	G->E[G->edgesize].start_vertex = u;
	G->E[G->edgesize].end_vertex = v;
	//1. edge추가
	G->adj_matrix[u][v] = 1;
	//2. u의 인접행렬에 edge 추가 
	if (u != v) {
		G->adj_matrix[v][u] = 1;
	}//3. 무방향이니까 반대쪽 edge 추가
	G->edgesize++;//edgesize 증가
}//무방향 간선 추가 함수

void Make_Graph() {
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}
}//그래프 생성 함수

void Init_Queue() {
	Q = (queue *)malloc(sizeof(queue));
	Q->front = 0;
	Q->rear = 0;
}//큐 초기화 함수

void enqueue(int i) {
	Q->rear = (Q->rear + 1) % 1000;
	Q->queue[Q->rear] = i;
}//큐에 값 넣어주는 함수

int dequeue() {
	Q->front = (Q->front + 1) % 1000;
	return Q->queue[Q->front];
}//큐에서 값 빼주는 함수

void BFS(int start) {
	Init_Queue();
	int *visited = (int *)calloc(n + 1, sizeof(int));
	enqueue(start);
	visited[start] = 1;
	while (Q->front != Q->rear) {
		int dq = dequeue();
		printf("%d\n", dq);
		for (int i = 1; i <= n; i++) {
			if (G->adj_matrix[dq][i] == 1 && visited[i]==0) {
				enqueue(i);
				visited[i] = 1;
			}
		}
	}
	free(visited);
	free(Q);
}//BFS

int main(void) {
	Init_Graph();
	Make_Graph();
	BFS(s);
	return 0;
}