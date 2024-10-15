#ifndef lcthw_list_algos_h
#define lcthw_list_algos_h

#include <lcthw/list.h>

typedef int (*List_compare) (const void *a, const void *b);

int List_bubble_sort(List * list, List_compare f_compare);
List *List_merge_sort(List * list, List_compare f_compare);

#endif
