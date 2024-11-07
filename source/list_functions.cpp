#include <stdio.h>
#include <stdlib.h>

#include "list_dump.h"
#include "list.h"

int is_first_add = 1;

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
        if ((list->data)[j].next_index == -1)
        {
            break;
        }
        printf("%d ", (list->data)[j].element);
        j = (list->data)[j].next_index;
    }
    printf("\n");
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
    printf("\nfree_cells: ");
    for (size_t i = 1; i < (list->size_of_list); i++)
    {
        printf("%2d ", ((list->free).array_of_free_cells)[i]);
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
        (list->free).array_of_free_cells[(list->free).free_index] = -1;
        (list->free).free_index++;
        list->free_cell = (list->free).array_of_free_cells[(list->free).free_index];
        (list->data)[free_index].element = elem;
        (list->data)[free_index].next_index = index + 2;
        (list->data)[free_index].prev_index = index;
    }
    else
    {
        // for (int i = 0; i < (list->size_of_list); i++)
        // {
        //     if (flag == 0 && (list->data)[i].next_index == -1)
        //     {
        //         flag = 1;
        //     }
        //     else if ((list->data)[i].next_index == -1)
        //     {
        //         free_index = i;
        //         break;
        //     }
        // }
        if (is_first_add == 1)
        {
            (list->free).free_index++;
            list->free_cell = (list->free).array_of_free_cells[(list->free).free_index];
            is_first_add = 0;
        }
        free_index = list->free_cell;
        (list->free).array_of_free_cells[(list->free).free_index] = -1;
        (list->free).free_index++;
        list->free_cell = (list->free).array_of_free_cells[(list->free).free_index];
        (list->data)[free_index].element = elem;
        (list->data)[free_index].prev_index = index + 1;
        (list->data)[index + 2].prev_index = free_index;
        (list->data)[free_index].next_index = (list->data)[index + 1].next_index;
        (list->data)[index + 1].next_index = free_index;
    }
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
    return NO_ERRORS;
}

Errors_of_list list_pop(struct MyList *list, List_Elem_t elem)
{
    if (list == NULL)
    {
        return ERROR_OF_POP;
    }
    int j = 1;
    while (j != -1)
    {
        if ((list->data)[j].element == elem)
        {
            break;
        }
        j = (list->data)[j].next_index;
    }
    if (j == -1)
    {
        return ERROR_OF_POP;
    }
    (list->data)[j].element = TOXIC;
    (list->data)[(list->data)[j].prev_index].next_index = (list->data)[j].next_index;
    (list->data)[(list->data)[j].next_index].prev_index = (list->data)[j].prev_index;
    list->free_cell = j;
    (list->free).array_of_free_cells[j] = j;
    (list->free).free_index = j;
    char operation[100] = "";
    sprintf(operation, "pop_element_%d", elem);
    Errors_of_list error = list_dump(list, operation);
    if (error != NO_ERRORS)
    {
        return error;
    }
    return NO_ERRORS;
}
