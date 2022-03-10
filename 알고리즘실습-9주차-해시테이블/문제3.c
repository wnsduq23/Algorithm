#include<stdio.h>

void insert(int* h, int key, int index, int M, int q)
{
    if (h[index] == 0)
    {
        h[index] = key;
        printf("%d\n", index);
    }
    else
    {
        printf("C");
        insert(h, key, (index + (q - (key % q))) % M, M, q);//여기만 바꿔주면됌
    }
}

void search(int* h, int key, int M)
{
    for (int i = 0;i < M;i++)
    {
        if (h[i] == key)
        {
            printf("%d %d\n", i, key);
            return;
        }
    }
    printf("-1\n");
    return;
}

void print(int* h, int M)
{
    for (int i = 0;i < M;i++)
        printf(" %d", h[i]);
    printf("\n");
}

int main(void)
{
    int* hash;
    int M, n, q, key;
    char ch;

    scanf("%d %d %d", &M, &n, &q);
    hash = (int*)malloc(sizeof(int) * M);
    for (int i = 0;i < M;i++)
        hash[i] = 0;
    while (1)
    {
        scanf("%c", &ch);
        if (ch == 'i')
        {
            scanf("%d", &key);
            insert(hash, key, key % M, M, q);
        }
        if (ch == 's')
        {
            scanf("%d", &key);
            search(hash, key, M);
        }
        if (ch == 'p')
            print(hash, M);
        if (ch == 'e')
        {
            print(hash, M);
            break;
        }
    }
    return 0;
}