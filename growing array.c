#include <stdio.h>
#include <stdlib.h>

const int INITIAL_SIZE=6;

typedef struct dynamic_array
{
    int *array;
    unsigned int size;
    unsigned int capacity;
}da;

void init_array(da **arr_ptr)
{
    da *container;
    container=(da*)malloc(sizeof(da));
    container->size=0;
    container->capacity=INITIAL_SIZE;
    container->array=(int*)malloc(INITIAL_SIZE*sizeof(int));
    *arr_ptr=container;
}

void insertItem(da *container,int item)
{
    if(container->size==container->capacity)
    {
        int *temp=container->array;
        container->capacity*=2;
        container->array=realloc(container->array,container->capacity * sizeof(int));
        if(container->array == NULL)
        {
            printf("OUT OF MEMORY MADARCHOD!!!");
            container->array=temp;
            return;
        }
    }
    container->array[container->size]=item;
    container->size++;
}

void print(da *container)
{
    for(int i=0;i<container->size;i++)
    {
        printf("%d ",container->array[i]);
    }
    printf("\n");
    printf("Size: %d",container->size);
    printf("Capacity: %d",container->capacity);
}

void delete(da *container,int index)
{
    for(int i=index;i<container->size;i++)
    {
        container->array[i]=container->array[i+1];
    }
    container->size--;
}

int getItem(da *container,int index)
{
    if(index >= container->size)
    {
        printf("Index out of bounds");
        return -1;
    }
    return container->array[index];
}

void free_array(da *container)
{
    free(container->array);
    free(container);
}

int main()
{
    da *akta_array;
    init_array(&akta_array);

    for(int i=0;i<=50;i++)
    {
        insertItem(akta_array,i);
    }
    print(akta_array);
    delete(akta_array,2);
    int a=getItem(akta_array,2);

    for(int i=60;i<=100;i++)
    {
        insertItem(akta_array,i);
    }
    print(akta_array);
    free_array(akta_array);
    return 0;
}