#include <stdio.h>
#include <string.h>
#include "hello.h"

char *hello(char *name) {
    int name_len = strlen(name);
    int hello_len = strlen("hello ");
    char result[name_len + hello_len + 1];
    strcpy(result, "hello ");
    strcat(result, name);
    return result;
}
