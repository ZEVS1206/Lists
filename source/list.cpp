#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static Errors_of_list constructor(struct MyList *list);
static Errors_of_list destructor(struct MyList *list);

static Errors_of_list constructor(struct MyList *list)
{
    list->size_of_list = size_of_list;
    list->data = (Data *) calloc((list->size_of_list), sizeof(Data));
    for (size_t i = 1; i < (list->size_of_list); i++)
    {
        (list->data)[i].next_index = -1;
        (list->data)[i].prev_index = -1;
    }
    if (list->data == NULL)
    {
        return ERROR_OF_CONSTRUCTOR;
    }
    list->head = 0;
    list->tail = 0;
    return NO_ERRORS;
}

int main()
{
    struct MyList list = {0};
    Errors_of_list error = NO_ERRORS;
    error = constructor(&list);
    // printf("next: ");
    // for (size_t i = 0; i < (list.size_of_list); i++)
    // {
    //     printf("%d ", (list.data)[i].next_index);
    // }
    // printf("\nprev: ");
    // for (size_t i = 0; i < (list.size_of_list); i++)
    // {
    //     printf("%d ", (list.data)[i].prev_index);
    // }
    // printf("\n");
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "error = %d\n", error);
        return 0;
    }
    error = list_push(&list, 0, 10);
    error = list_print(&list);
    error = list_push(&list, 1, 20);
    error = list_push(&list, 2, 30);
    error = list_push(&list, 3, 40);
    error = list_push(&list, 4, 50);
    error = list_push(&list, 5, 60);
    error = list_print(&list);
    error = list_push(&list, 1, 25);
    error = list_push(&list, 2, 35);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "error = %d\n", error);
        return 0;
    }
    error = list_print(&list);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "error = %d\n", error);
        return 0;
    }
    error = destructor(&list);
    return 0;
}


static Errors_of_list destructor(struct MyList *list)
{
    if (list == NULL)
    {
        return ERROR_OF_DESTRUCTOR;
    }
    for (size_t i = 0; i < list->size_of_list; i++)
    {
        (list->data)[i].element = 0;
        (list->data)[i].next_index = 0;
        (list->data)[i].prev_index = 0;
    }
    list->size_of_list = 0;
    list->head = 0;
    list->tail = 0;
    free(list->data);
    return NO_ERRORS;
}
