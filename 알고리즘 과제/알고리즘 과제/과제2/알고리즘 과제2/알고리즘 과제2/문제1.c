#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inPlaceQuickSort(int* arr, int l, int r);

typedef struct Index { //a,b�� ��� ��ȯ�ϱ� ���� ����ü ����
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
    for (i = 0;i < n;i++) scanf("%d", &arr[i]); //�Է�
    inPlaceQuickSort(arr, 0, n - 1); //0���� n-1������ index�� ���ؼ� ���ڸ� �� ���� ����
    for (i = 0;i < n;i++) printf(" %d", arr[i]);
    free(arr);
    return 0;
}

void inPlaceQuickSort(int* arr, int l, int r) 
{
    int k;
    I index;
    if (l >= r) return; //l�� r���� ���ų� ũ�� return
    k = findPivot(arr, l, r); //ù ��° ���Ұ����� pivot�� index�� ��ȯ����
    index = inPlacePartition(arr, l, r, k); //index ����ü�� ���� �ް� 
    inPlaceQuickSort(arr, l, index.a - 1); //����ü�� ����ִ� a�� b�� �̿��ؼ� �� ��Ƽ�ǿ� ���� �� ���� ����
    inPlaceQuickSort(arr, index.b + 1, r);
}

int findPivot(int* arr, int l, int r)
{
    //�������� Pivot�� �������ִ� ����(4)
    // int i;
    // srand(time(NULL)); 
    // i = rand()%(l-r+1)+l; //l~r������ �� �� �������� ���� ����
    // return i;

    //���� ù ��° ���Ҹ� Pivot���� ����ϴ� ����(1)
    return l;
}
I inPlacePartition(int* arr, int l, int r, int k) {
    int tmp, a;
    int i, j, pivot;
    I index;
    //Pivot�� �Ź� ù ��° ���Ҹ� ����ϸ� Pivot�� ���� �ʿ䰡 ������,
    //� ��Ȳ�� ���� �𸣴� k�� l�̶�� �������� �ʰ� �ڵ带 ����.
    pivot = arr[k];
    swapElements(arr, k, r); //Pivot ������
    i = l; //l����
    j = r - 1; //r-1������ ������ ���� ����
    while (i <= j) {
        while (i < r && arr[i] < pivot) {
            i++;
        }
        while (l <= j && arr[j] >= pivot) {
            j--;
        }
        if (i < j) { //i�� j�� �������� �ʾҴٸ�,
            swapElements(arr, i, j);
        }
    }
    //���ݱ����� �����ʿ� pivot�� ���ų� ū ��, ���ʿ� pivot���� ���� ������ �����Ǿ� �ִ�.

    //�����ʿ��� �ٽ� pivot�� ���� ������ ����ָ� �ȴ�.

    a = i;
    j = r - 1;
    while (i <= j) {
        while (i < r && arr[i] == pivot) { //i�� ��ġ�� ���� pivot�� �ƴϸ� Ż��
            i++;
        }
        while (l <= j && arr[j] != pivot) { //�̹� i~j���̿��� pivot���� ũ�ų� ���� �����̹Ƿ�
            j--;                      //j�� ��ġ�� ���� pivot�̸� Ż��
        }
        if (i < j) { //i�� j�� �������� �ʾҴٸ�,
            swapElements(arr, i, j);
        }
    }
    //i�� j�� �������� �ݺ����� Ż�� �ߴٸ�
    swapElements(arr, i, r); //pivot�� i�� ���Ҹ� swap
    index.a = a;
    index.b = i;
    return index;
}

void swapElements(int* arr, int a, int b) // ��ȯ�Լ�
{
    int tmp;
    tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}