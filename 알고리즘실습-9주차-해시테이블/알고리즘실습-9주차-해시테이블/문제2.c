#include<stdio.h>

int* hashTable, M;

int h(int x)
{
	return x % M;
}
int getNextBucket(int v, int i)
{
	return (v + i) % M;
}

void insertItem(int x)
{
	int v = h(x), i = 0, b;//v는 해시테이블 인덱스값

	while (i < M)
	{
		b = getNextBucket(v, i);
		if (hashTable[b] == 0)
		{
			hashTable[b] = x;
			for (int j = 0; j < i; j++)
				printf("C");
			printf("%d\n", b);
			return;
		}
		else
			i = i + 1;
	}
}

void searchItem(int x)
{
	int v = h(x), i = 0, b;

	while (i < M)
	{
		b = getNextBucket(v, i);
		if (hashTable[b] == x)
		{
			printf("%d %d\n", b, hashTable[b]);
			return;
		}
		else
			i = i + 1;
	}
	printf("-1\n");
}

int main(void)
{
	int n, key;
	int cnt = 0;
	char input;

	scanf("%d %d", &M, &n);
	hashTable = (int*)malloc(sizeof(int) * M);
	for (int i = 0; i < M; i++)
		*(hashTable + i) = 0;//hashTable[i]=0;
	while (1)
	{
		scanf("%c", &input);
		if (input == 'i')
		{
			scanf("%d", &key);
			cnt++;
			insertItem(key);
			getchar();
		}
		if (input == 's')
		{
			scanf("%d", &key);
			searchItem(key);
		}
		if (input == 'e')
			break;
	}
	free(hashTable);
}