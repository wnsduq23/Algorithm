#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int main()
{
	int N, K, * array, i;
	int l, r, pos = -1, mid;

	scanf("%d%d", &N, &K);
	array = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++)
	{
		scanf("%d", &array[i]);
	}
	l = 0, r = N - 1;
	while (1)
	{
		mid = (l + r) / 2;
		if (l > r)
		{
			if (K > array[N - 1])
			{
				pos = N;
				break;
			}
			if (array[l] > K)
			{
				pos = l;
				break;
			}
			else if (array[l] < K)
			{
				pos = l + 1;
				break;
			}
		}
		if (K == array[mid])
		{
			pos = mid;
			break;
		}
		else if (K < array[mid])
		{
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf(" %d", pos);
	return 0;
}