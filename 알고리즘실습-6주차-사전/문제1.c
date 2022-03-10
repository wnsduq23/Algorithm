#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

void insertItem();
int removeMax();
void printHeap();
void downHeap();
void upHeap();
void buildHeap();
int findElement();

int main(void)
{
	int n, k;
	int* H;
	int p;

	scanf("%d %d", &n, &k);
	H = (int*)malloc(sizeof(int) * n);
	for (int i = 0;i < n;i++)
	{
		scanf("%d", &H[i]);
	}
	p = findElement(H, k, 0, n - 1);
	printf(" %d", p);
}

int findElement(int* H, int k, int l, int r)
{
	int mid;

	if (l > r)
	{
		if (k < H[0])
			return -1;
		else
			return r;
	}
	mid = (l + r) / 2;
	if (k == H[mid])
		return mid;
	else if (k < H[mid])
		return findElement(H, k, l, mid - 1);
	else
		return findElement(H, k, mid + 1, r);
}