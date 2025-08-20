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

    if (list == NULL) {
        n->next = n->prev = n;
        list = n;
        return;
    }

    node* last = list->prev;
    n->next = list;
    n->prev = last;
    last->next = n;
    list->prev = n;
    list = n;
}


void append(int element) {
    node* n = (node*)malloc(sizeof(node));
    n->value = element;
    if (list == NULL) {
        n->next = n->prev = n;
        list = n;
        return;
    }
    node* last = list->prev;
    n->next = list;
    n->prev = last;
    last->next = n;
    list->prev = n;
}


void insert_sorted(int element) {
    if (list == NULL || element < list->value) {
        prepend(element);
        return;
    }
    node* curr = list;
    do {
        if (element < curr->next->value || curr->next == list) {
            node* n = (node*)malloc(sizeof(node));
            n->value = element;
            n->next = curr->next;
            n->prev = curr;
            curr->next->prev = n;
            curr->next = n;
            return;
        }
        curr = curr->next;
    } while (curr != list);
}


void insert_after(int element, int pred) {
    if (list == NULL) return;
    node* curr = list;
    do {
        if (curr->value == pred) {
            node* n = (node*)malloc(sizeof(node));
            n->value = element;
            n->next = curr->next;
            n->prev = curr;
            curr->next->prev = n;
            curr->next = n;
            return;
        }
        curr = curr->next;
    } while (curr != list);
}


void destroy(node* n) {
    if (list == NULL) return;
    node* curr = list->next;
    while (curr != list) {
        node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(list);
    list = NULL;
}


void delete_node(int element) {
    if (list == NULL) return;
    node* curr = list;
    do {
        if (curr->value == element) {
            if (curr->next == curr) {
                free(curr);
                list = NULL;
                return;
            }
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            if (curr == list) list = curr->next;
            free(curr);
            return;
        }
        curr = curr->next;
    } while (curr != list);
}


void delete_front() {
    if (list == NULL) return;
    delete_node(list->value);
}


void delete_back() {
    if (list == NULL) return;
    delete_node(list->prev->value);
}


void print_list() {
    if (list == NULL) {
        printf("List is empty!\n");
        return;
    }
    node* curr = list;
    do {
        printf("%d ", curr->value);
        curr = curr->next;
    } while (curr != list);
    printf("\n");
}


bool find(int element) {
    if (list == NULL) return false;
    node* curr = list;
    do {
        if (curr->value == element) return true;
        curr = curr->next;
    } while (curr != list);
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
//      delete_node(5);
//      delete_front();
//      delete_back();
//      print_list();
        if(find(100))
        {
            printf("100 is present");
        }
        else
        {
            printf("absent");
        }

}
