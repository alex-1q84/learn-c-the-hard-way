#include <stdio.h> // for print out
#include <assert.h> // assertion
#include <stdlib.h> // using malloc free functions
#include <string.h> // using string operation functions such as strdup

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person Person_create(char *name, int age, int height, int weight)
{
    struct Person who; // defion structure on stack

    who.name = strdup(name); // copy the string into the structure own reference to make sure it actually own it
    who.age = age; // get structure attributes using dot when the structure is created on stack
    who.height = height;
    who.weight = weight;

    return who;
}

// pass on stack structure to function by value
void Person_print(struct Person who)
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    struct Person joe = Person_create("Joe Alex", 32, 64, 140);

    struct Person frank = Person_create("Frank Blank", 20, 72, 180);

    // print them out
    Person_print(joe);

    Person_print(frank);

    // make everyone age 20 years and print them again
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);
 }
