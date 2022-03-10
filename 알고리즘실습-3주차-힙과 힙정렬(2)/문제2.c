#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;
int keynum;
void inPlaceHeapSort();
void printArray();
void downHeap();
void insertItem();
void upHeap();
void rBuildHeap();

int main() {
	int i;
	int data;
	int num;

	scanf("%d", &keynum);
	for (i = 1; i <= keynum; i++) 
	{
		scanf("%d", &num);
		insertItem(num);
	}
	inPlaceHeapSort();
	printArray();
	return 0;
}

void inPlaceHeapSort() 
{
	int i;
	int temp;
	for (i = n; i >= 2; i--) {
		temp = H[1];
		H[1] = H[i];
		H[i] = temp;
		downHeap(1, i - 1);
	}
	return;
}

void printArray() {
	int i;

	for (i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
	return;
}

void downHeap(int i, int last) 
{
	int left, right;
	int big;
	int temp;

	left = 2 * i;
	right = 2 * i + 1;
	if (left > last) {
		return;
	}
	big = left;
	if (right <= last) {
		if (H[right] > H[big])
			big = right;
	}
	if (H[i] >= H[big]) {
		return;
	}
	temp = H[i];
	H[i] = H[big];
	H[big] = temp;
	downHeap(big, last);
}

void insertItem(int num) {
	n = n + 1;
	H[n] = num;
	if (n > 1)
		upHeap(n);
	return 0;
}

void upHeap(int i) {
	int temp;

	if (i <= 1)
		return;
	else {
		if (H[i] > H[i / 2]) {
			temp = H[i];
			H[i] = H[i / 2];
			H[i / 2] = temp;
		}
		upHeap(i / 2);
	}
}

void rBuildHeap() {
	int i = 1;
	
	if (i > n)
		return;
	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(1, i);
	return;
}