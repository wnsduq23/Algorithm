#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//최대값이 들어가있는 인덱스 값만 받아서 바꿔주면 됌

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
                arrnumber = j;//최대값의 인덱스를 arrnumber에 넣음
            }
        }
        //arrnumber인덱스의 값과 뒷자리 자리바꿈
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