#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **arr;
    int row,col;
    scanf("%d",&row);
    scanf("%d",&col);
    arr=(int**)malloc(row*sizeof(int*));
    for(int i=0;i<row;i++)
    {
        arr[i]=(int*)malloc(col*sizeof(int));
    }
    int value=1;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            arr[i][j]=value;
            value++;
        }
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            printf("%d  ",arr[i][j]);
        }
        printf("\n");
    }

    for(int i=0;i<row;i++)
    {
        free(arr[i]);
    }
    free(arr);
}