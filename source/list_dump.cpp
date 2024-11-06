#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_dump.h"
#include "list.h"

Errors_of_list create_command_for_console(const char *file_in_name, const char *file_out_name)
{
    if (file_in_name == NULL || file_out_name == NULL)
    {
        return ERROR_OF_CREATING_COMMAND;
    }
    char command_for_console[100] = "";
    sprintf(command_for_console, "sudo dot -Tps %s -o %s.ps", file_in_name, file_out_name);
    system(command_for_console);
    return NO_ERRORS;
}

Errors_of_list create_file_for_dump(struct MyList *list, FILE *file_pointer)
{
    if (file_pointer == NULL)
    {
        return ERROR_OF_OPEN_DUMP_FILE;
    }
    fprintf(file_pointer, "digraph List {\n");
    fprintf(file_pointer, "node [margin = \"0.01\"];\nrankdir = \"LR\";\n");
    int j = 1;
    while (j != -1)
    {
        if ((list->data)[j].next_index == -1)
        {
            break;
        }
        fprintf(file_pointer, "\"box%d\" [shape = \"record\", label = \"element = %d|next_index = %d|prev_index = %d\"];\n", j,
                                                                                                (list->data)[j].element,
                                                                                                (list->data)[j].next_index,
                                                                                                (list->data)[j].prev_index);
        j = (list->data)[j].next_index;
    }
    j = 1;
    while (j != -1)
    {
        if ((list->data)[j].next_index == -1)
        {
            break;
        }
        fprintf(file_pointer, "\"box%d\"->\"box%d\";\n", j, (list->data)[j].next_index);
        j = (list->data)[j].next_index;
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
        return ERROR_OF_OPEN_DUMP_FILE;
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
    return error;
}