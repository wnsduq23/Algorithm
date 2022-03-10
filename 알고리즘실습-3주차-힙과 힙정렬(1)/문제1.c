#include<stdio.h>
#include <string.h>

void insertItem();
void upHeap();
void downHeap();
void printHeap();
int removeMax();

int main(void)
{
	char ip;
	int key;
	int H[100];
	int n = 0;

	while (1)
	{
		scanf("%c", &ip);
		if (ip == 'i')
		{
			scanf("%d", &key);
			n += 1;
			insertItem(key, H, n);
		}
		if (ip == 'd')
		{
			printf("%d\n", removeMax(n, H));
			n -= 1;
		}
		if (ip == 'p')
			printHeap(n, H);
		if (ip == 'q')
			break;
	}
	return 0;
}

void insertItem(int key, int* H, int n)
{
	H[n] = key;
	upHeap(n, H);
	printf("0\n");
}

void upHeap(int i, int* H)
{
	int tmp = 0;

	if (i <= 1)
		return;
	else
	{
		if (H[i] > H[i / 2])
		{
			tmp = H[i];
			H[i] = H[i / 2];
			H[i / 2] = tmp;
		}
	}
	upHeap(i / 2, H);
}

int removeMax(int n, int* H)
{
	int key;

	key = H[1];
	H[1] = H[n];//root에 마지막 노드를 넣음
	n -= 1;
	downHeap(1, n, H);
	return key;
}

void downHeap(int i, int n, int* H)
{
	int left, right;
	int big;
	int temp;

	left = 2 * i;
	right = 2 * i + 1;
	if (left > n)
		return;
	big = left;
	if (right <= n)//오른쪽 노드도 있는 경우
	{
		if (H[right] > H[big])//
			big = right;
	}

	if (H[i] < H[big])
	{
		temp = H[i];
		H[i] = H[big];
		H[big] = temp;
	}
	downHeap(big, n, H);
}

void printHeap(int n, int* H)
{
	for (int i = 1;i <= n;i++)
	{
		printf(" %d", H[i]);
	}
}