#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Heap {
    int* heap;
    int n;
}H;
void bigNum(H* h, int num); //num�� ������ �ּ����� ��Ʈ(�ּڰ�)���� ũ�� ���� ����
void rBuildHeap(H* h, int index);
void downHeap(H* h, int index);
void swapElements(H* h, int index1, int index2); //�� �ε����� ���� ���� ���� ��ȯ
int removeMin(H* h);
int main() {
    H Heap, * h;
    int N, i, K, num;
    scanf("%d", &N);
    scanf("%d", &K);
    h = &Heap; //h�� Heap ����ü�� ����Ű�� ����ü ������
    h->heap = (int*)malloc(sizeof(int) * (K + 1)); //K+1 ũ�⸸ŭ ���� �Ҵ��Ͽ� �迭 ����
    h->n = K;
    for (i = 1;i <= K;i++) { //���ǻ� index�� 1����
        scanf("%d", &h->heap[i]);
    }
    rBuildHeap(h, 1);

    for (i = 0;i < N - K;i++) { //N-K�� �߰� �Է�
        scanf("%d", &num); //�񱳸� ������ ���� �Է�
        bigNum(h, num);
    }
    //���� ���� �ּ������� �����Ǿ������Ƿ� �������� ������ �ϱ� ���ؼ� 
    //removeMax�� �̿��� ������ ȿ�����̴�.
    //in-place sort�� �������� ������ �Ϸ��� �ִ����̾���ϱ� �����̴�.
    for (i = 0;i < K;i++) {
        printf("%d ", removeMin(h));
    }

    return 0;
}
void bigNum(H* h, int num) {
    if (num > h->heap[1]) { //�Է¹��� num�� ��Ʈ���� ũ��
        h->heap[1] = num; //��Ʈ�� num�� �ְ�
        downHeap(h, 1); //num�� downHeap�Ѵ�.(����)
    }
}
int removeMin(H* h) {
    int min_num;
    min_num = h->heap[1]; //min_num�� ��Ʈ�� ����
    h->heap[1] = h->heap[h->n]; //��Ʈ�� lastnode�� ����
    h->n--;
    downHeap(h, 1); //��Ʈ downHeap
    return min_num;
}
void rBuildHeap(H* h, int index) {
    int i;
    if (index * 2 > h->n) return; //�ܺ� ���� return(����)
    rBuildHeap(h, index * 2); //���� �ڽĺ��� BuildHeap
    rBuildHeap(h, index * 2 + 1); //������ �ڽ� BuildHeap
    downHeap(h, index); //���������� DownHeap ����
}
void downHeap(H* h, int index) {
    int min_index;
    if (index * 2 > h->n) { //�ܺ� ���� return
        return;
    }
    else if (index * 2 == h->n) { //���� �ڽĸ� ������,
        if (h->heap[index] > h->heap[index * 2]) { //���� �ڽĺ��� ũ��
            swapElements(h, index, index * 2); //swap
            downHeap(h, index * 2);
        }
    }
    else { //�ڽ��� ��� ������
        min_index = index * 2;
        if (h->heap[index * 2 + 1] < h->heap[min_index]) { //������ �ڽ��� �� ������
            min_index = index * 2 + 1;
        }
        if (h->heap[index] > h->heap[min_index]) { //����, ������ �� �� ���� ������ �θ� �� ũ��
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