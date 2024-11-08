#ifndef LIST_H
#define LIST_H

typedef int List_Elem_t;

const size_t size_of_list = 11;
const int TOXIC = -1985;

enum Errors_of_list
{
    NO_ERRORS                 = 0,
    ERROR_OF_PUSH             = 1,
    ERROR_OF_POP              = 2,
    ERROR_OF_INDEX            = 3,
    ERROR_OF_CONSTRUCTOR      = 4,
    ERROR_OF_DESTRUCTOR       = 5,
    ERROR_OF_PRINT            = 6,
    ERROR_OF_NO_ELEMENT       = 7,
    ERROR_OF_CREATING_COMMAND = 8,
    ERROR_OF_DUMP             = 9
};

struct Data
{
    List_Elem_t element;
    int next_index;
    int prev_index;
};

struct Free_Cells
{
    int *array_of_free_cells;
    int free_index;
};

struct MyList
{
    Data *data;
    size_t size_of_list;
    Free_Cells free;
    int free_cell;
    int head;
    int tail;
};

Errors_of_list list_push(struct MyList *list, int index, List_Elem_t elem);
Errors_of_list list_pop(struct MyList *list, List_Elem_t elem);
Errors_of_list list_print(struct MyList *list);


#endif
