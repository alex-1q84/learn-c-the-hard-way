#include <stdio.h>

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int *ages = {23, 43, 12, 89, 2};
    char **names = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    //safely get the size of ages
    int count = sizeof(*ages) / sizeof(int);

    printf("count of ages: %d\n", count);

    int i = 0;

    // second way using pointers
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
               *(names + 1), *(ages +1));
    }

    printf("---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; i++) {
        printf("%s is %d years again.\n", names[i], ages[i]);
    }

    printf("---\n");

    // fourth way with pointers in a stupid complex way
    for (; ages < count; names++, ages++) {
        printf("pointer %ld: %s lived %d years so far.\n", ages, *names, *ages);
    }

    return 0;
}
