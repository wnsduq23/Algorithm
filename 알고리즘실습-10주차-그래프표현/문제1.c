#include<stdio.h>

struct edge // a: node , b: 인접 node , w: 간선 가중치
{
	int a, b, w;
};
struct node
{
	int edge_index;
	struct node* next;
};
struct key
{
	struct node* H;
	int key;
};

struct node* getnode()
{
	struct node* ptr;
	ptr = (struct node*)malloc(sizeof(struct node));
	return ptr;
}

void add_edge(struct edge edge[], int* edge_end, int a, int b, int w)
{
	edge[*edge_end].a = a;
	edge[*edge_end].b = b;
	edge[*edge_end].w = w;
	(*edge_end)++;
}

void add_node(struct key ar[], int i, struct edge edge[], int edge_index)
{
	struct node* H = ar[i].H;
	struct node* newnode;
	struct node* p;

	while (H != NULL)
	{
		p = H;
		H = H->next;
		if (H == NULL)
			break;
		else {
			if (edge[H->edge_index].a == edge[edge_index].a)
			{
				if (edge[H->edge_index].b > edge[edge_index].b)
					break;
			}
			else if (edge[H->edge_index].b == edge[edge_index].a)
			{
				if (edge[H->edge_index].a > edge[edge_index].b)
					break;
			}
			else if (edge[H->edge_index].a == edge[edge_index].b)
			{
				if (edge[H->edge_index].b > edge[edge_index].a)
					break;
			}
			else if (edge[H->edge_index].b == edge[edge_index].b)
			{
				if (edge[H->edge_index].a > edge[edge_index].a)
					break;
			}
		}
	}
	newnode = getnode();
	newnode->edge_index = edge_index;
	p->next = newnode;
	newnode->next = H;
}

int search_index(struct key ar[], int key)
{
	int i;

	for (i = 0; i < 6; i++)
	{
		if (ar[i].key == key)
			return i;
	}
	return -1;
}

void print_key(struct key ar[], int ar_index, struct edge edge[])
{
	struct node* p = ar[ar_index].H;

	p = p->next;
	while (p != NULL)
	{
		if (edge[p->edge_index].a == edge[p->edge_index].b)
			printf(" %d", edge[p->edge_index].a);
		else
		{
			if (ar[ar_index].key != edge[p->edge_index].a)
				printf(" %d", edge[p->edge_index].a);
			else if (ar[ar_index].key != edge[p->edge_index].b)
				printf(" %d", edge[p->edge_index].b);
		}
		printf(" %d", edge[p->edge_index].w);
		//printf(" %d %d %d", p->edge->a, p->edge->b, p->edge->w);
		p = p->next;
	}
	printf("\n");
}

void delete_node(struct key ar[], int a_index, int b_index, int edge_index)
{
	struct node* p1 = ar[a_index].H;
	struct node* p2 = ar[b_index].H;
	struct node* p;

	while (p1 != NULL)
	{
		p = p1;
		p1 = p1->next;
		if (p1->edge_index == edge_index)
		{
			p->next = p1->next;
			//free(p1);
			break;
		}
	}
	if (a_index == b_index)
		return;
	while (p2 != NULL)
	{
		p = p2;
		p2 = p2->next;
		if (p2->edge_index == edge_index)
		{
			p->next = p2->next;
			//free(p2);
			break;
		}
	}
}

void modify_w(struct key ar[], struct edge edge[], int a, int b, int w, int* edge_end)
{
	int i;
	int a_index = search_index(ar, a);
	int b_index = search_index(ar, b);

	if (a_index == -1 || b_index == -1)
	{
		//둘 중 하나라도 없는 정점이면.
		printf("-1\n");
		return;
	}
	for (i = 0; i < *edge_end; i++) { //*edge_end 까지 반복문 돌리기 
		if (edge[i].a == ar[a_index].key && edge[i].b == ar[b_index].key)
		{
			if (w == 0)
			{
				edge[i].a = -9999;
				edge[i].b = -9999;
				edge[i].w = 0;
				delete_node(ar, a_index, b_index, i); //@@
				return;
			}
			else {
				edge[i].w = w;
				return;
			}
		}
		//리턴이 안되고 내려왔다.
	}
	//삭제, 수정, 추가
	add_edge(edge, edge_end, a, b, w);
	add_node(ar, a_index, edge, (*edge_end) - 1);
	if (a_index == b_index)
		return;
	add_node(ar, b_index, edge, (*edge_end) - 1);
}

int main()
{
	//vertex 저장 배열ar , (양 끝 vertex, 가중치 저장) 배열 edge
	struct key ar[6];
	struct edge edge[100];
	char ch;
	int key, a, b, w, i, j, temp, ar_index;
	int edge_end = 0;

	ar[0].key = 1;
	ar[1].key = 2;
	ar[2].key = 3;
	ar[3].key = 4;
	ar[4].key = 5;
	ar[5].key = 6;
	for (i = 0; i < 6; i++)
	{
		ar[i].H = getnode();
		ar[i].H->next = NULL;
	}
	add_edge(edge, &edge_end, 1, 2, 1);
	add_edge(edge, &edge_end, 1, 3, 1);
	add_edge(edge, &edge_end, 1, 4, 1);
	add_edge(edge, &edge_end, 1, 6, 2);
	add_edge(edge, &edge_end, 2, 3, 1);
	add_edge(edge, &edge_end, 3, 5, 4);
	add_edge(edge, &edge_end, 5, 5, 4);
	add_edge(edge, &edge_end, 5, 6, 3);
	//edge_end = 간선의 총 개수 
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < edge_end; j++)
		{
			if (ar[i].key == edge[j].a || ar[i].key == edge[j].b)
				add_node(ar, i, edge, j);
		}
	}
	while (1)
	{
		scanf("%c", &ch);
		if (ch == 'a')
		{
			scanf("%d", &key);
			ar_index = search_index(ar, key);
			if (ar_index == -1)
				printf("-1\n");
			else
				print_key(ar, ar_index, edge);
		}
		else if (ch == 'm')
		{
			scanf("%d%d%d", &a, &b, &w);
			if (a > b)
			{
				temp = a;
				a = b;
				b = temp;
			}
			modify_w(ar, edge, a, b, w, &edge_end);
		}
		else if (ch == 'q')
			break;
		getchar();
	}
	return 0;
}