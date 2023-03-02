
#include <stdio.h>
#include <stdlib.h>
int *init(int *arr, int n)
{
    arr = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++)
    {
        arr[i] = i;
    }
    return arr;
}
int main()
{
    int *arr = NULL;
    int *mas, n = 10;
    mas=init(arr, n);
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d\n", mas[i]);
    }
    return 0;
}