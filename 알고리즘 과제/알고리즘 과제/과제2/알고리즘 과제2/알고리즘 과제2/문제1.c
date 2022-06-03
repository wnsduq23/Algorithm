#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inPlaceQuickSort(int* arr, int l, int r);

typedef struct Index { //a,b를 모두 반환하기 위한 구조체 선언
    int a;
    int b;
}I;

int findPivot(int* arr, int l, int r);
void swapElements(int* arr, int a, int b);
I inPlacePartition(int* arr, int l, int r, int k);

int main(void) 
{
    int i, n, * arr;
    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    for (i = 0;i < n;i++) scanf("%d", &arr[i]); //입력
    inPlaceQuickSort(arr, 0, n - 1); //0부터 n-1까지의 index에 대해서 제자리 퀵 정렬 진행
    for (i = 0;i < n;i++) printf(" %d", arr[i]);
    free(arr);
    return 0;
}

void inPlaceQuickSort(int* arr, int l, int r) 
{
    int k;
    I index;
    if (l >= r) return; //l이 r보다 같거나 크면 return
    k = findPivot(arr, l, r); //첫 번째 원소값으로 pivot의 index를 반환해줌
    index = inPlacePartition(arr, l, r, k); //index 구조체로 값을 받고 
    inPlaceQuickSort(arr, l, index.a - 1); //구조체에 들어있는 a와 b를 이용해서 각 파티션에 대한 퀵 정렬 수행
    inPlaceQuickSort(arr, index.b + 1, r);
}

int findPivot(int* arr, int l, int r)
{
    //랜덤으로 Pivot을 설정해주는 버전(4)
    // int i;
    // srand(time(NULL)); 
    // i = rand()%(l-r+1)+l; //l~r사이의 값 중 랜덤으로 값을 받음
    // return i;

    //가장 첫 번째 원소를 Pivot으로 사용하는 버전(1)
    return l;
}
I inPlacePartition(int* arr, int l, int r, int k) {
    int tmp, a;
    int i, j, pivot;
    I index;
    //Pivot이 매번 첫 번째 원소를 사용하면 Pivot을 숨길 필요가 없지만,
    //어떤 상황이 올지 모르니 k를 l이라고 생각하지 않고 코드를 쓰자.
    pivot = arr[k];
    swapElements(arr, k, r); //Pivot 숨겨줌
    i = l; //l부터
    j = r - 1; //r-1까지의 범위에 대해 수행
    while (i <= j) {
        while (i < r && arr[i] < pivot) {
            i++;
        }
        while (l <= j && arr[j] >= pivot) {
            j--;
        }
        if (i < j) { //i와 j가 엇갈리지 않았다면,
            swapElements(arr, i, j);
        }
    }
    //지금까지는 오른쪽엔 pivot과 같거나 큰 값, 왼쪽엔 pivot보다 작은 값으로 구성되어 있다.

    //오른쪽에서 다시 pivot과 같은 값들을 모아주면 된다.

    a = i;
    j = r - 1;
    while (i <= j) {
        while (i < r && arr[i] == pivot) { //i에 위치한 값이 pivot이 아니면 탈출
            i++;
        }
        while (l <= j && arr[j] != pivot) { //이미 i~j사이에는 pivot보다 크거나 같은 값들이므로
            j--;                      //j에 위치한 값이 pivot이면 탈출
        }
        if (i < j) { //i와 j가 엇갈리지 않았다면,
            swapElements(arr, i, j);
        }
    }
    //i와 j가 엇갈려서 반복문을 탈출 했다면
    swapElements(arr, i, r); //pivot과 i의 원소를 swap
    index.a = a;
    index.b = i;
    return index;
}

void swapElements(int* arr, int a, int b) // 교환함수
{
    int tmp;
    tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}