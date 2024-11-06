#include <stdio.h>
#include <stdlib.h>

#include "list_dump.h"
#include "list.h"

Errors_of_list list_print(struct MyList *list)
{
    if (list == NULL)
    {
        return ERROR_OF_PRINT;
    }
    printf("data: ");
    int j = 1;
    while (j != -1)
    {
        // printf("\n");
        // for (size_t i = 1; i < (list->size_of_list); i++)
        // {
        //     printf("%2d ", (list->data)[i].next_index);
        // }
        // printf("\n");
        // for (size_t i = 1; i < (list->size_of_list); i++)
        // {
        //     printf("%2lu ", i);
        // }
        // printf("\n");
        // getchar();
        //printf("j = %d next_index = %d\n", j, (list->data)[j].next_index);
        if ((list->data)[j].next_index == -1)
        {
            break;
        }
        printf("%d ", (list->data)[j].element);
        j = (list->data)[j].next_index;
    }
    printf("\n");
    // printf("%d ", (list->data)[1].element);
    // for (size_t i = 1; i < (list->size_of_list); i++)
    // {
    //     if ((list->data)[i].next_index == -1)
    //     {
    //         continue;
    //     }
    //     //printf("i = %lu\n", i);
    //     printf("%d ", (list->data)[(list->data)[i].next_index].element);
    // }
    printf("\nnext: ");
    for (size_t i = 1; i < (list->size_of_list); i++)
    {
        printf("%2d ", (list->data)[i].next_index);
    }
    printf("\n");
    printf("\nprev: ");
    for (size_t i = 1; i < (list->size_of_list); i++)
    {
        printf("%2d ", (list->data)[i].prev_index);
    }
    printf("\n");
    return NO_ERRORS;
}

Errors_of_list list_push(struct MyList *list, int index, List_Elem_t elem)
{
    if (list == NULL || index < 0 || index > (list->size_of_list))
    {
        return ERROR_OF_PUSH;
    }
    int free_index = -1;
    int flag = 0;
    if ((list->data)[index + 1].next_index == -1)
    {
        free_index = index + 1;
        (list->data)[free_index].element = elem;
        (list->data)[free_index].next_index = index + 2;
        (list->data)[free_index].prev_index = index;
    }
    else
    {
        for (int i = 0; i < (list->size_of_list); i++)
        {
            if (flag == 0 && (list->data)[i].next_index == -1)
            {
                flag = 1;
            }
            else if ((list->data)[i].next_index == -1)
            {
                free_index = i;
                break;
            }
        }
        (list->data)[free_index].element = elem;
        (list->data)[free_index].prev_index = (list->data)[index].next_index;
        (list->data)[free_index].next_index = (list->data)[index + 1].next_index;
        (list->data)[index + 1].next_index = free_index;
    }
    //printf("free_index = %d\n", free_index);
    if (free_index == -1)
    {
        return ERROR_OF_NO_ELEMENT;
    }
    char operation[100] = "";
    sprintf(operation, "push_%d_after_%d_index", elem, index);
    Errors_of_list error = list_dump(list, operation);
    if (error != NO_ERRORS)
    {
        return error;
    }
    (list->tail)++;
    return NO_ERRORS;
}

