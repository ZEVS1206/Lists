#ifndef LIST_DUMP_H
#define LIST_DUMP_H

#include "list.h"

Errors_of_list create_file_for_dump(struct MyList *list, FILE *file_pointer);
Errors_of_list create_command_for_console(const char *file_in_name, const char *file_out_name);
Errors_of_list list_dump(struct MyList *list, char *operation);

#endif
