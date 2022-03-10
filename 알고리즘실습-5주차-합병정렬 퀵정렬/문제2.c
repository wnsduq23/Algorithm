#include<stdio.h>
#include <stdlib.h>
#include <string.h>

//����2
//a, b�� pivot�� ���� �ε��� , l,r�� ���Ƿ� pivot �� �� ���� ���� �ε���
//�⺻ ����1. left�� Pivot<left�϶����� �����̵�, right�� right=<Pivot�϶����� �����̵� �� �� ��ȯ
//�⺻ ����2. l,r�����ϸ� pivot<=>right

int findPivot();
int inPlacePartition();
void inPlaceQuickSort();

//a, b�� pivot�� ���� �ε��� , l,r�� ���Ƿ� pivot �� �� ���� ���� �ε���
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

int inPlacePartition(int* A, int l, int r, int k)//l���� �Ǻ����� ū���� r���� �Ǻ����� ���� ���� ���� �ٲ�.
{
    int tmp = 0;
    int i, j;
    int p;

    p = A[k];//p�� �Ǻ�

    tmp = A[k];//�������� ����. hide pivot
    A[k] = A[r];
    A[r] = tmp;

    i = l;
    j = r - 1;
    while (i <= j)
    {
        while (i <= j && A[i] <= p)//A[i]�� pivot���� ���� �۰� �ε����� ������ �н�
            i = i + 1;
        while (j >= i && A[j] >= p)//A[j]�� pivot���� ���� ũ�� �ε����� ũ�� �н�
            j = j - 1;

        if (i < j)// l���� �Ǻ����� ū���ΰ��, r���� �Ǻ����� ���� ���� ��� ���� �ٲ�
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
        k = findPivot(A, l, r);//�ӽ� pivot�� �ε��� = k  
        a = inPlacePartition(A, l, r, k);
        b = a;
        inPlaceQuickSort(A, l, a - 1);//l�� a-1���� ������
        inPlaceQuickSort(A, b + 1, r);//b+1�� r���� ������
    }

}