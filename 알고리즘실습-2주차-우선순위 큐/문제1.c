#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//�ִ밪�� ���ִ� �ε��� ���� �޾Ƽ� �ٲ��ָ� ��

int main()
{
    int n, * arr, i, j, t, arrnumber;
    int num;

    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        scanf("%d", &num);
        arr[i] = num;
    }
    for (i = 0; i < n; i++) {
        arrnumber = 0;
        for (j = 1; j < n - i; j++) {
            if (arr[j] > arr[arrnumber]) {
                arrnumber = j;//�ִ밪�� �ε����� arrnumber�� ����
            }
        }
        //arrnumber�ε����� ���� ���ڸ� �ڸ��ٲ�
        t = arr[n - 1 - i];
        arr[n - 1 - i] = arr[arrnumber];
        arr[arrnumber] = t;
    }
    for (i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    free(arr);
    return 0;
}