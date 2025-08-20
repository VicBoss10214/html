#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node* next;
    struct node* prev;
} node;

node* list = NULL;

void prepend(int element) {
    node* n = (node*)malloc(sizeof(node));
    n->value = element;
    n->prev = NULL;
    n->next = list;
    if (list != NULL)
        list->prev = n;
    list = n;
}

void append(int element) {
    node* n = (node*)malloc(sizeof(node));
    n->value = element;
    n->next = NULL;
    if (list == NULL) {
        n->prev = NULL;
        list = n;
        return;
    }
    node* temp = list;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = n;
    n->prev = temp;
}

void insert_sorted(int element) {
    node* n = (node*)malloc(sizeof(node));
    n->value = element;
    n->next = n->prev = NULL;

    if (list == NULL || element < list->value) {
        n->next = list;
        if (list != NULL) list->prev = n;
        list = n;
        return;
    }
    node* curr = list;
    while (curr->next != NULL && curr->next->value < element)
        curr = curr->next;

    n->next = curr->next;
    if (curr->next != NULL) curr->next->prev = n;
    curr->next = n;
    n->prev = curr;
}

void insert_after(int element, int pred) {
    node* curr = list;
    while (curr != NULL && curr->value != pred)
        curr = curr->next;
    if (curr == NULL) return; // pred not found
    node* n = (node*)malloc(sizeof(node));
    n->value = element;
    n->next = curr->next;
    n->prev = curr;
    if (curr->next != NULL)
        curr->next->prev = n;
    curr->next = n;
}

void destroy(node* n) {
    while (n != NULL) {
        node* next = n->next;
        free(n);
        n = next;
    }
    list = NULL;
}

void delete_node(int element) {
    node* curr = list;
    while (curr != NULL && curr->value != element)
        curr = curr->next;
    if (curr == NULL) return;

    if (curr->prev != NULL)
        curr->prev->next = curr->next;
    else
        list = curr->next;

    if (curr->next != NULL)
        curr->next->prev = curr->prev;

    free(curr);
}

void delete_front() {
    if (list == NULL) return;
    node* temp = list;
    list = list->next;
    if (list != NULL) list->prev = NULL;
    free(temp);
}

void delete_back() {
    if (list == NULL) return;
    node* curr = list;
    while (curr->next != NULL)
        curr = curr->next;
    if (curr->prev != NULL)
        curr->prev->next = NULL;
    else
        list = NULL;
    free(curr);
}

void print_list() {
    node* ptr = list;
    while (ptr != NULL) {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
    printf("\n");
}

bool find(int element) {
    node* curr = list;
    while (curr != NULL) {
        if (curr->value == element) return true;
        curr = curr->next;
    }
    return false;
}

int main()
{
    for(int i=1;i<=5;i++)
    {
        append(i);
    }
    insert_sorted(2);
    insert_after(100,2);
    //destroy(list);
    //delete_node(5);
    //delete_front();
    delete_back();
    print_list();
    if(find(100))
    {
        printf("100 is present");
    }
    else
    {
        printf("absent");
    }
}
https://www.facebook.com/messages/t/100092511220985/
