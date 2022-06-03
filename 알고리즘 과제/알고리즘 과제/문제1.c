#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Heap 
{
    int         is_min_heap;
    int         *heap;
    int         n;
}               H;

void isMinHeap(H* h, int index); //min-heap인지 확인하는 함수

int main(void) 
{
    H       Heap, * h;
    int     N, i;

    scanf("%d", &N);
    h = &Heap; //h는 Heap 구조체를 가리키는 구조체 포인터
    h->heap = (int*)malloc(sizeof(int) * (N + 1)); //N+1 크기만큼 동적 할당하여 배열 생성
    h->n = N;
    h->is_min_heap = 1; //1로 초기화
    for (i = 1;i <= N;i++) { //편의상 index는 1부터
        scanf("%d", &h->heap[i]);
    }
    isMinHeap(h, 1);
    if (h->is_min_heap) //is_min_heap이 1이면(min-heap이면)
        printf("Yes\n");
    else 
        printf("No\n");
    //마지막 내부노드는 마지막 외부 노드의 부모이기 때문에
    printf("%d\n", h->heap[N / 2]);


    return 0;
}
void isMinHeap(H* h, int index) 
{
    if (h->n < index * 2) { //외부 노드면
        return;
    }

    if (h->n == index * 2) 
    { //왼쪽 자식만 있으면,
        //왼쪽 자식이 부모보다 작으면(min-heap이 아님)
        if (h->heap[index] > h->heap[index * 2]) 
        {
            h->is_min_heap = 0; //is_min_heap에 0 저장
        }
    }
    else 
    { //자식이 모두 있으면(외부 노드인 경우는 이미 return함)
        //두 자식중 하나라도 부모보다 작으면
        if ((h->heap[index] > h->heap[index * 2]) || (h->heap[index] > h->heap[index * 2 + 1])) 
            h->is_min_heap = 0;
    }

    isMinHeap(h, index * 2); //왼쪽 자식 탐색
    isMinHeap(h, index * 2 + 1); //오른쪽 자식 탐색
}