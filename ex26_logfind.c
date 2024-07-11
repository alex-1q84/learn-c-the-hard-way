#include <string.h>
#include <stdlib.h>
#include "dbg.h"

int find_log(char *log_path, char *search_term)
{
    FILE *file = fopen(log_path, "r");
    check(file != NULL, "Failed to open log file.");

    while (!feof(file)) {
        char *line = NULL;
        line = fgetln(file, 2048);

        // if (strstr(line, search_term)) {
            printf("%s", line);
        // }
    }

error:
    return -1;
}

int main(int argc, char *argv[])
{

    return 0;
}