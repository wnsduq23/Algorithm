#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Heap 
{
    int         is_min_heap;
    int         *heap;
    int         n;
}               H;

void isMinHeap(H* h, int index); //min-heap���� Ȯ���ϴ� �Լ�

int main(void) 
{
    H       Heap, * h;
    int     N, i;

    scanf("%d", &N);
    h = &Heap; //h�� Heap ����ü�� ����Ű�� ����ü ������
    h->heap = (int*)malloc(sizeof(int) * (N + 1)); //N+1 ũ�⸸ŭ ���� �Ҵ��Ͽ� �迭 ����
    h->n = N;
    h->is_min_heap = 1; //1�� �ʱ�ȭ
    for (i = 1;i <= N;i++) { //���ǻ� index�� 1����
        scanf("%d", &h->heap[i]);
    }
    isMinHeap(h, 1);
    if (h->is_min_heap) //is_min_heap�� 1�̸�(min-heap�̸�)
        printf("Yes\n");
    else 
        printf("No\n");
    //������ ���γ��� ������ �ܺ� ����� �θ��̱� ������
    printf("%d\n", h->heap[N / 2]);


    return 0;
}
void isMinHeap(H* h, int index) 
{
    if (h->n < index * 2) { //�ܺ� ����
        return;
    }

    if (h->n == index * 2) 
    { //���� �ڽĸ� ������,
        //���� �ڽ��� �θ𺸴� ������(min-heap�� �ƴ�)
        if (h->heap[index] > h->heap[index * 2]) 
        {
            h->is_min_heap = 0; //is_min_heap�� 0 ����
        }
    }
    else 
    { //�ڽ��� ��� ������(�ܺ� ����� ���� �̹� return��)
        //�� �ڽ��� �ϳ��� �θ𺸴� ������
        if ((h->heap[index] > h->heap[index * 2]) || (h->heap[index] > h->heap[index * 2 + 1])) 
            h->is_min_heap = 0;
    }

    isMinHeap(h, index * 2); //���� �ڽ� Ž��
    isMinHeap(h, index * 2 + 1); //������ �ڽ� Ž��
}