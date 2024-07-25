#!/bin/bash

# compile dynamic lib
cc -c libex29.c -o libex29.o
cc -shared -o libex29.so libex29.o

# compile loader program
cc -Wall -DNDEBUG -g ex29.c -ldl -o ex29

### run
./ex29 libex29.so print_a_message abc
./ex29 libex29.so print_a_message ABC

./ex29 libex29.so lowercase ABC
./ex29 libex29.so lowercase abc

./ex29 libex29.so uppercase ABC
./ex29 libex29.so uppercase abc

./ex29 libex29.so fail_on_purpose abc

./ex29 libex29.so not_exists abc
