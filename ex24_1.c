#include <stdio.h>
#include "dbg.h"

int main(int argc, char *argv[])
{
    char in[100];
    printf("Please input string: ");
    // fscanf just throw overflowed charactors
    /* int rc = fscanf(stdin, "%3s", in); */
    /* check(rc > 0, "Faild to read string."); */
    char *r = fgets(in, 2, stdin);

    printf("in: %s\n", in);
    r = fgets(in, 3, stdin);
    check(r != NULL, "Faild to read string.");
    printf("in2: %s\n", in);

    return 0;

error:
    return 1;
}
