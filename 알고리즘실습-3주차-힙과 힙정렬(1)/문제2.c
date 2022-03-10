#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void insertItem();
int removeMax();
void printHeap();
void downHeap();
void upHeap();
void buildHeap();

int main(void)
{
	int H[100];
	int n;
	scanf("%d", &n);
	for (int i = 1;i <= n;i++)
	{
		scanf("%d", &H[i]);
	}
	buildHeap(H, n);
	printHeap(H, n);
}

void downHeap(int* H, int i, int n)
{
	int tmp = 0;
	int big = 0;
	if (2 * i > n)
		return;
	big = 2 * i;
	if (2 * i + 1 <= n)
	{
		if (H[2 * i + 1] > H[big])
			big = 2 * i + 1;
	}
	if (H[big] > H[i])
	{
		tmp = H[i];
		H[i] = H[big];
		H[big] = tmp;
	}
	downHeap(H, big, n);
}

void buildHeap(int* H, int n)
{
	for (int i = n / 2;i >= 1;i--)
	{
		downHeap(H, i, n);
	}
}

void printHeap(int* H, int n)
{
	for (int i = 1;i <= n;i++)
	{
		printf(" %d", H[i]);
	}
}