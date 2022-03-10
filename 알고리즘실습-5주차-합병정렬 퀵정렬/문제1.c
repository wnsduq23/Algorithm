#include<stdio.h>

//�߰��� �������� �յ� �迭 ���� ����, �Ŀ� ���� �պ� ����

typedef struct Node

{
    struct Node* next;
    int data;
    int num;
}Node;

void mergeSort();
void merge();
Node* partition();
void add();

void main()
{
    Node* H, * node;
    int n;
    int i, data;

    H = (Node*)malloc(sizeof(Node));
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &data);
        add(H, data, i);
    }
    mergeSort(H, n);
    node = H->next;
    for (i = 0; i < n; i++)
    {
        printf(" %d", node->data);
        node = node->next;
    }
    free(H);
    return 0;
}

void add(Node* N, int data, int num)
{
    Node* new;
    int i;

    new = (Node*)malloc(sizeof(Node));
    new->data = data;
    new->num = num;
    new->next = NULL;

    for (i = 0; i < num; i++)
        N = N->next;//������ N�� ��ġ�� num-1���� �ű�
    N->next = new;//num-1��ġ N�� ������带 new��(�� N��带 new��)
}

Node* partition(Node* N, int num) //num�� ��� �� 
{
    Node* newhead;
    int i;

    newhead = (Node*)malloc(sizeof(Node));
    if (num % 2 == 0)
    {
        for (i = 0; i < num / 2; i++)
            N = N->next;//������ N�� ��ġ�� num/2-1����
    }
    else
    {
        for (i = 0; i <= num / 2; i++)//������ N�� ��ġ�� num/2����
            N = N->next;
    }
    newhead->next = N->next;//newhead�� N(num/2)�� ����Ű�� ����==L2
    N->next = NULL;//��������� L1
    return newhead;
}

void merge(Node* L1, Node* L2, int n)
{
    int i;
    Node* newHead, * N;

    newHead = (Node*)malloc(sizeof(Node));
    N = (Node*)malloc(sizeof(Node));
    N = newHead;
    while (L1->next != NULL && L2->next != NULL)
    {
        if (L1->next->data <= L2->next->data)
        {
            newHead->next = L1->next;
            newHead = newHead->next;//newhead ������ ��ġ�� ��������
            L1->next = L1->next->next;
        }
        else
        {
            newHead->next = L2->next;
            newHead = newHead->next;
            L2->next = L2->next->next;
        }
    }
    while (L1->next != NULL)
    {
        newHead->next = L1->next;
        newHead = newHead->next;
        L1->next = L1->next->next;
    }
    while (L2->next != NULL)
    {
        newHead->next = L2->next;
        newHead = newHead->next;
        L2->next = L2->next->next;
    }
    L1->next = N->next;
}

void mergeSort(Node* L1, int n)
{
    Node* L2;
    
    if (n < 1)
        return;
    L2 = partition(L1, n);
    mergeSort(L1, n / 2);
    mergeSort(L2, n / 2);
    merge(L1, L2, n);
}