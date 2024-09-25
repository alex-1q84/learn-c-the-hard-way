#include <lcthw/list_algos.h>
#include <lcthw/list.h>

int List_bubble_sort(List * list, List_compare f_compare)
{
    if (list == NULL || f_compare == NULL) return 1;

    int swapped = 1;
    while(swapped != 0) {
        swapped = 0;
        LIST_FOREACH(list, first, next, cur) {
            ListNode *prev_node = cur->prev;
            ListNode *next_node = cur->next;

            if(next_node != NULL) {
                //compare and swap
                if (f_compare(cur->value, cur->next->value) > 0) {
                    //swap
                    if (list->first == cur) {
                        list->first = next_node;
                    } else {
                        prev_node->next = next_node;
                    }

                    if (next_node == list->last) {
                        list->last = cur;
                    } else {
                        next_node->next->prev = cur;
                    }

                    next_node->prev = prev_node;
                    cur->next = next_node->next;
                    next_node->next = cur;
                    cur->prev = next_node;

                    swapped = 1;
                }
            }
        }
    }

    return 0;
}

List *List_merge_sort(List * list, List_compare f_compare)
{
    return list;
}
