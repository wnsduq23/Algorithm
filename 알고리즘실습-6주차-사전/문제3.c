#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int main()
{
	int A, B, num, K = 0, i, M;
	char* YN;

	scanf("%d%d%d", &A, &B, &num);
	YN = (char*)malloc(num * sizeof(char));
	getchar();
	scanf("%s", YN);
	for (i = 0; i <= num; i++)
	{
		M = (A + B) / 2;
		if (A == B)
			K = A;
		if (YN[i] == 'Y')
		{
			A = M + 1;
		}
		if (YN[i] == 'N')
		{
			B = M;
		}
	}
	printf("%d", K);
	return 0;
}