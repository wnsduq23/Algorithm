#include<stdio.h>
#include <stdlib.h>
#include <string.h>

//과제2
//a, b는 pivot과 같은 인덱스 , l,r은 임의로 pivot 앞 뒤 에서 뽑은 인덱스
//기본 조건1. left는 Pivot<left일때까지 우측이동, right는 right=<Pivot일때까지 좌측이동 후 값 교환
//기본 조건2. l,r교차하면 pivot<=>right

int findPivot();
int inPlacePartition();
void inPlaceQuickSort();

//a, b는 pivot과 같은 인덱스 , l,r은 임의로 pivot 앞 뒤 에서 뽑은 인덱스
int main(void)
{
    int N;
    int* A;
    int l, r;

    scanf("%d", &N);
    A = (int*)malloc(sizeof(int) * N);
    for (int i = 0;i < N;i++)
    {
        scanf("%d", &A[i]);
    }
    l = 0;
    r = N - 1;

    inPlaceQuickSort(A, l, r);

    for (int i = 0;i < N;i++)
    {
        printf(" %d", A[i]);
    }
    free(A);
    return 0;
}


int findPivot(int* A, int l, int r)
{
    int a, b, c, mid;
    a = l + 1;
    c = r - 1;
    b = l + 2;
    mid = (a + b + c) / 3;
    return mid;
}

int inPlacePartition(int* A, int l, int r, int k)//l에서 피봇보다 큰값과 r에서 피봇보다 작은 값을 서로 바꿈.
{
    int tmp = 0;
    int i, j;
    int p;

    p = A[k];//p는 피봇

    tmp = A[k];//무작위로 섞음. hide pivot
    A[k] = A[r];
    A[r] = tmp;

    i = l;
    j = r - 1;
    while (i <= j)
    {
        while (i <= j && A[i] <= p)//A[i]가 pivot보다 값도 작고 인덱스도 작으면 패스
            i = i + 1;
        while (j >= i && A[j] >= p)//A[j]가 pivot보다 값도 크고 인덱스도 크면 패스
            j = j - 1;

        if (i < j)// l에서 피봇보다 큰값인경우, r에서 피봇보다 작은 값인 경우 서로 바꿈
        {
            tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }

    tmp = A[i];//replace pivot
    A[i] = A[r];
    A[r] = tmp;

    return i;
}
void inPlaceQuickSort(int* A, int l, int r)
{
    int k;
    int a, b;
    if (l >= r)
        return;
    else
    {
        k = findPivot(A, l, r);//임시 pivot의 인덱스 = k  
        a = inPlacePartition(A, l, r, k);
        b = a;
        inPlaceQuickSort(A, l, a - 1);//l과 a-1사이 퀵정렬
        inPlaceQuickSort(A, b + 1, r);//b+1과 r사이 퀵정렬
    }

}