#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_dump.h"
#include "list.h"
static Errors_of_list create_boxes_of_info(struct MyList *list, FILE *file_pointer);
static Errors_of_list create_next_connections(struct MyList *list, FILE *file_pointer);
static Errors_of_list create_prev_connections(struct MyList *list, FILE *file_pointer);

Errors_of_list create_command_for_console(const char *file_in_name, const char *file_out_name)
{
    if (file_in_name == NULL || file_out_name == NULL)
    {
        return ERROR_OF_CREATING_COMMAND;
    }
    char command_for_console[100] = "";
    sprintf(command_for_console, "sudo dot -Tpng %s -o %s.png", file_in_name, file_out_name);
    system(command_for_console);
    return NO_ERRORS;
}

static Errors_of_list create_boxes_of_info(struct MyList *list, FILE *file_pointer)
{
    if (list == NULL || file_pointer == NULL)
    {
        return ERROR_OF_DUMP;
    }
    for (size_t index = 0; index < (list->size_of_list); index++)
    {
        fprintf(file_pointer, "box%lu [shape = record, label = \"index = %lu|<elem%lu_elem> element = %d|<elem%lu_ni> next_index = %d|<elem%lu_pi> prev_index = %d\"];\n", index, index, index,
                                                                                                                                                                         (list->data)[index].element, index,
                                                                                                                                                                         (list->data)[index].next_index, index,
                                                                                                                                                                         (list->data)[index].prev_index);

    }
    fprintf(file_pointer, "info [shape = record, label = \"free_cell = %d\"];\n", (list->free_cell));
    for (size_t index = 0; index < (list->size_of_list) - 1; index++)
    {
        fprintf(file_pointer, "box%lu->box%lu [weight = 1000, color = white];\n", index, index + 1);
    }
    return NO_ERRORS;
}

static Errors_of_list create_next_connections(struct MyList *list, FILE *file_pointer)
{
    if (list == NULL || file_pointer == NULL)
    {
        return ERROR_OF_DUMP;
    }
    int index = 1;
    while (index != -1)
    {
        int k = (list->data)[index].next_index;
        if (k == -1)
        {
            break;
        }
        fprintf(file_pointer, "box%d:<elem%d_ni>->box%d:<elem%d_ni> [color = red];\n", index, index, (list->data)[index].next_index, (list->data)[index].next_index);
        index = (list->data)[index].next_index;
    }
    return NO_ERRORS;
}

static Errors_of_list create_prev_connections(struct MyList *list, FILE *file_pointer)
{
    if (list == NULL || file_pointer == NULL)
    {
        return ERROR_OF_DUMP;
    }
    int index = 1;
    while (index != -1)
    {
        fprintf(file_pointer, "box%d:<elem%d_pi>->box%d:<elem%d_pi> [color = blue];\n", index, index, (list->data)[index].prev_index, (list->data)[index].prev_index);
        index = (list->data)[index].next_index;
    }
    return NO_ERRORS;
}

Errors_of_list create_file_for_dump(struct MyList *list, FILE *file_pointer)
{
    if (list == NULL || file_pointer == NULL)
    {
        return ERROR_OF_DUMP;
    }
    fprintf(file_pointer, "digraph List {\n");
    fprintf(file_pointer, "node [margin = \"0.01\"];\nrankdir = \"LR\";\n");
    Errors_of_list error = create_boxes_of_info(list, file_pointer);
    if (error != NO_ERRORS)
    {
        return error;
    }
    error = create_next_connections(list, file_pointer);
    if (error != NO_ERRORS)
    {
        return error;
    }
    error = create_prev_connections(list, file_pointer);
    if (error != NO_ERRORS)
    {
        return error;
    }
    fprintf(file_pointer, "}\n");
    fclose(file_pointer);
    return NO_ERRORS;
}

Errors_of_list list_dump(struct MyList *list, char *operation)
{
    if (list == NULL)
    {
        return ERROR_OF_DUMP;
    }
    FILE *file_pointer = fopen("dump/test.txt", "w");
    if (file_pointer == NULL)
    {
        return ERROR_OF_DUMP;
    }
    char file_out_name[100] = "dump/";
    strcat(file_out_name, operation);
    Errors_of_list error = NO_ERRORS;
    error = create_file_for_dump(list, file_pointer);
    if (error != NO_ERRORS)
    {
        return error;
    }
    error = create_command_for_console("dump/test.txt", file_out_name);
    if (error != NO_ERRORS)
    {
        return error;
    }
    return error;
}
