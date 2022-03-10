#include<stdio.h>

//중간을 기점으로 앞뒤 배열 무한 분할, 후에 무한 합병 정렬

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
        N = N->next;//포인터 N의 위치를 num-1까지 옮김
    N->next = new;//num-1위치 N의 다음노드를 new로(즉 N노드를 new로)
}

Node* partition(Node* N, int num) //num은 노드 수 
{
    Node* newhead;
    int i;

    newhead = (Node*)malloc(sizeof(Node));
    if (num % 2 == 0)
    {
        for (i = 0; i < num / 2; i++)
            N = N->next;//포인터 N의 위치를 num/2-1까지
    }
    else
    {
        for (i = 0; i <= num / 2; i++)//포인터 N의 위치를 num/2까지
            N = N->next;
    }
    newhead->next = N->next;//newhead가 N(num/2)를 가리키기 시작==L2
    N->next = NULL;//여기까지가 L1
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
            newHead = newHead->next;//newhead 포인터 위치를 다음으로
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