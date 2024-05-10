#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void person_destroy(struct Person *who)
{
    assert(who != NULL);

    free(who->name);
    free(who);
}

void person_print(struct Person *who)
{
    assert(who != NULL);

    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    struct Person *joe = person_create("Joe Alex", 32, 64, 140);

    struct Person *frank = person_create("Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("joe is at memory location %p:\n", joe);
    person_print(joe);

    printf("frank is at memory location %p:\n", frank);
    person_print(frank);

    // make everyone age 20 years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    person_print(frank);

    // destroy both them so we clean up
    person_destroy(joe);
    person_destroy(frank);
}
