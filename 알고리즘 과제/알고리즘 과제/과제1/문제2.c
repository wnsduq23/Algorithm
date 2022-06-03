#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Heap {
    int* heap;
    int n;
}H;
void bigNum(H* h, int num); //num이 형성된 최소힙의 루트(최솟값)보다 크면 힙에 삽입
void rBuildHeap(H* h, int index);
void downHeap(H* h, int index);
void swapElements(H* h, int index1, int index2); //각 인덱스에 따른 값을 서로 교환
int removeMin(H* h);
int main() {
    H Heap, * h;
    int N, i, K, num;
    scanf("%d", &N);
    scanf("%d", &K);
    h = &Heap; //h는 Heap 구조체를 가리키는 구조체 포인터
    h->heap = (int*)malloc(sizeof(int) * (K + 1)); //K+1 크기만큼 동적 할당하여 배열 생성
    h->n = K;
    for (i = 1;i <= K;i++) { //편의상 index는 1부터
        scanf("%d", &h->heap[i]);
    }
    rBuildHeap(h, 1);

    for (i = 0;i < N - K;i++) { //N-K번 추가 입력
        scanf("%d", &num); //비교를 진행할 숫자 입력
        bigNum(h, num);
    }
    //현재 힙은 최소힙으로 구현되어있으므로 오름차순 정렬을 하기 위해선 
    //removeMax를 이용한 정렬이 효율적이다.
    //in-place sort로 오름차순 정렬을 하려면 최대힙이어야하기 때문이다.
    for (i = 0;i < K;i++) {
        printf("%d ", removeMin(h));
    }

    return 0;
}
void bigNum(H* h, int num) {
    if (num > h->heap[1]) { //입력받은 num이 루트보다 크면
        h->heap[1] = num; //루트에 num을 넣고
        downHeap(h, 1); //num을 downHeap한다.(삽입)
    }
}
int removeMin(H* h) {
    int min_num;
    min_num = h->heap[1]; //min_num에 루트값 저장
    h->heap[1] = h->heap[h->n]; //루트에 lastnode값 저장
    h->n--;
    downHeap(h, 1); //루트 downHeap
    return min_num;
}
void rBuildHeap(H* h, int index) {
    int i;
    if (index * 2 > h->n) return; //외부 노드면 return(질문)
    rBuildHeap(h, index * 2); //왼쪽 자식부터 BuildHeap
    rBuildHeap(h, index * 2 + 1); //오른쪽 자식 BuildHeap
    downHeap(h, index); //마지막으로 DownHeap 진행
}
void downHeap(H* h, int index) {
    int min_index;
    if (index * 2 > h->n) { //외부 노드면 return
        return;
    }
    else if (index * 2 == h->n) { //왼쪽 자식만 있으면,
        if (h->heap[index] > h->heap[index * 2]) { //왼쪽 자식보다 크면
            swapElements(h, index, index * 2); //swap
            downHeap(h, index * 2);
        }
    }
    else { //자식이 모두 있으면
        min_index = index * 2;
        if (h->heap[index * 2 + 1] < h->heap[min_index]) { //오른쪽 자식이 더 작으면
            min_index = index * 2 + 1;
        }
        if (h->heap[index] > h->heap[min_index]) { //왼쪽, 오른쪽 중 더 작은 값보다 부모가 더 크면
            swapElements(h, index, min_index); //swap
            downHeap(h, min_index);
        }
    }
}
void swapElements(H* h, int index1, int index2) {
    int tmp;
    tmp = h->heap[index1];
    h->heap[index1] = h->heap[index2];
    h->heap[index2] = tmp;
}