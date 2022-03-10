#include<stdio.h>

typedef struct node
{
	int number;
	struct node* next;
}Node;

Node* hashTable;
int M;

int h(int x)
{
	return (x % M);
}

void insertItem(int x)//�浹 �� ����Ʈ�� �� �տ� �ֱ�
{
	int v = h(x);
	Node* p = hashTable + v;

	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->number = x;
	if (p->next == NULL)
	{
		newnode->next = NULL;
		p->next = newnode;
		p = p->next;
	}
	else
	{
		newnode->next = p->next;
		p->next = newnode;
		p = p->next;
	}
}

int searchItem(int x)
{
	int v = h(x), count = 0;
	Node* p = hashTable + v;
	if (p->next == NULL)//����Ʈ�� �ƹ��͵� ���� ��
		return 0;
	else
	{
		while (1)
		{
			if (p->next == NULL)//����Ʈ ������ Ȯ���ߴµ� ���� ��
			{
				return 0;
			}
			p = p->next;
			count++;
			if (p->number == x)
			{
				return count;
			}
		}
	}
}

int deleteItem(int x)
{
	int v = h(x), count = 0;
	Node* pt = hashTable + v, * p = hashTable + v;

	if (p->next == NULL)
		return 0;
	else
	{
		while (1)
		{
			p = p->next;
			count++;
			if (p->number == x)
			{
				while (pt->next != p)
				{
					pt = pt->next;
				}
				pt->next = p->next;
				free(p);
				return count;
			}
			if (p->next == NULL)
				return 0;
		}
	}
}

void printTable()
{
	Node* p;

	for (int i = 0; i < M; i++)
	{
		p = hashTable + i;
		if (p->next != NULL)
		{
			while (p->next != NULL)
			{
				p = p->next;
				printf(" %d", p->number);
			}
		}
	}
	printf("\n");
}

void freeTable()
{
	Node* p, * q;

	for (int i = 0; i < M; i++)
	{
		if ((hashTable + i)->next != NULL)
		{
			p = (hashTable + i)->next;
			q = p;
			while (q->next != NULL)
			{
				p = p->next;
				free(q);
				q = p;
			}
		}
	}
	free(hashTable);
}

int main(void)
{
	int key;
	char input;

	scanf("%d", &M);
	getchar();
	hashTable = (struct node*)malloc(sizeof(struct node) * M);
	for (int i = 0; i < M; i++) //�ؽ����̺� �� ���� ����ü �ʱ�ȭ
	{
		(hashTable + i)->number = NULL;
		(hashTable + i)->next = NULL;
	}
	while (1)
	{
		scanf("%c", &input);
		if (input == 'i')
		{
			scanf("%d", &key);
			insertItem(key);
		}
		if (input == 's')
		{
			scanf("%d", &key);
			printf("%d\n", searchItem(key));
		}
		if (input == 'd')
		{
			scanf("%d", &key);
			printf("%d\n", deleteItem(key));
		}
		if (input == 'p')
			printTable();
		if (input == 'e')
			break;
		getchar();
	}
	freeTable();
}