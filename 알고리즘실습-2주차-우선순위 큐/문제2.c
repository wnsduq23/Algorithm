#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    int n, * arr, i, j, t, arrnumber;
    int num;

    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &num);
        arr[i] = num;
    }
    for (i = 1; i < n; i++)
    {
        t = arr[i];//(1)
        j = i - 1;
        while (j >= 0 && arr[j] > t) //(2)-1
        {
            arr[j + 1] = arr[j];//(2)-2
            j = j - 1;
        }
        arr[j + 1] = t;//(3)
    }
    for (i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }
    free(arr);
    return 0;
}