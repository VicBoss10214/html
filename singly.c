#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int value;
    struct node* next;
}node;

node* list=NULL;

void prepend(int x)
{
    node* n=malloc(sizeof(node));
    n->value=x;
    n->next=NULL;
    n->next=list;
    list=n;
}

void append(int x)
{
    node* n=malloc(sizeof(node));
    n->value=x;
    n->next=NULL;
    if(list==NULL)
    {
        list=n;
        return;
    }
    for(node* curr=list;curr!=NULL;curr=curr->next)
    {
        if(curr->next == NULL)
        {
            curr->next=n;
            break;
        }
    }
}

void insert_sorted(int x)
{
    node* n=malloc(sizeof(node));
    n->value=x;
    n->next=NULL;
    if(list==NULL)
    {
        list=n;
        return;
    }
    else if(n->value < list->value)
    {
        n->next=list;
        list=n;
    }
    else
    {
        for(node* curr=list;curr!=NULL;curr=curr->next)
        {
            if(curr->next == NULL)
            {
                curr->next=n;
                break;
            }
            if(n->value < curr->next->value)
            {
                n->next=curr->next;
                curr->next=n;
                break;
            }
        }
    }
}

void insert_after(int x,int pred)
{
    node* n=malloc(sizeof(node));
    n->value=x;
    n->next=NULL;
    node* curr=list;
    while(curr->value != pred)
    {
        curr=curr->next;
    }
    n->next=curr->next;
    curr->next=n;
}

void destroy(node* n)
{
    if(n==NULL)
    {
        printf("The list is empty\n");
        return;
    }
    destroy(n->next);
    free(n);
}

void delete_node(int element)
{
    if(list==NULL)
    {
        printf("List is empty\n");
        return;
    }
    node* prev;
    node* curr;
    prev=NULL;
    curr=list;
    while(curr->value!=element)
    {
        prev=curr;
        curr=curr->next;
    }
    if(prev!=NULL)
    {
        prev->next=curr->next;   
    }
    free(curr);
}

void delete_front()
{
    if(list==NULL)
    {
        printf("The list is empty\n");
        return;
    }
    node* temp=list;
    list=list->next;
    free(temp);
}

void delete_back()
{
    if(list==NULL)
    {
        printf("The list is empty\n");
        return;
    }
    node* prev;
    node* curr;
    prev=NULL;
    curr=list;
    while(curr!=NULL)
    {
        prev=curr;
        curr=curr->next;
    }
    if(prev!=NULL)
    {
        prev->next=curr->next;
    }
    free(curr);
}

void print_list()
{
    if(list==NULL)
    {
        printf("The list is empty\n");
        return;
    }
    node* curr=list;
    while(curr!=NULL)
    {
        printf("%d ",curr->value);
        curr=curr->next;
    }
    printf("\n");
}


bool find(int x)
{
    for(node* curr=list;curr!=NULL;curr=curr->next)
    {
        if(curr->value == x)
        {
            return true;
        }
    }
    return false;
}


int main()
{
    int x;
    while(scanf("%d", &x) != EOF)
    {
        append(x);
    }
    print_list();

    // int k = 3, new_element = 13;
    insert_after(4,6);
    print_list();

    // if(find(3))
    // {
    //     printf("3 is present!\n");
    // }
    // else
    // {
    //     printf("3 is NOT present!");
    // }

    // int k = 3;
    // delete_node(k);
    // printf("%d has been deleted.\n", k);
    // print_list();

    // delete_front();
    // printf("The first element has been deleted.\n");
    // print_list();

    // delete_back();
    // printf("The last element has been deleted.\n");
    // print_list();

    return 0;
}