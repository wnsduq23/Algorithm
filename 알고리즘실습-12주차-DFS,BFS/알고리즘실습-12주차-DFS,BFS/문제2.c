#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n, m, s;//���� ��, ���� ��, ���� ���� �������� ����

typedef struct Queue {
	int queue[1001];
	int front;
	int rear;
}queue;//ť ����ü

typedef struct edge {
	int start_vertex;
	int end_vertex;
}edge;//���� ����ü

typedef struct vertex {
	int vertex;
}vertex;//���� ����ü

typedef struct Graph {
	vertex V[101];
	edge E[1000];
	int adj_matrix[101][101];
	int edgesize;
}graph;//�׷��� ����ü : ������ı��� ����

graph *G;
queue *Q;//�������� ����

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
}//�׷��� �ʱ�ȭ �Լ�

void addEdge(int u, int v) {
	G->E[G->edgesize].start_vertex = u;
	G->E[G->edgesize].end_vertex = v;
	//1. edge�߰�
	G->adj_matrix[u][v] = 1;
	//2. u�� ������Ŀ� edge �߰� 
	if (u != v) {
		G->adj_matrix[v][u] = 1;
	}//3. �������̴ϱ� �ݴ��� edge �߰�
	G->edgesize++;//edgesize ����
}//������ ���� �߰� �Լ�

void Make_Graph() {
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}
}//�׷��� ���� �Լ�

void Init_Queue() {
	Q = (queue *)malloc(sizeof(queue));
	Q->front = 0;
	Q->rear = 0;
}//ť �ʱ�ȭ �Լ�

void enqueue(int i) {
	Q->rear = (Q->rear + 1) % 1000;
	Q->queue[Q->rear] = i;
}//ť�� �� �־��ִ� �Լ�

int dequeue() {
	Q->front = (Q->front + 1) % 1000;
	return Q->queue[Q->front];
}//ť���� �� ���ִ� �Լ�

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