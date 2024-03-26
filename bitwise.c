#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned int a = 0b001;
    printf("a=%u\n", a);
    unsigned int b = ~a;
    printf("b=%u\n", b);
    printf("c=%u\n", ~b);

    return 0;
}
