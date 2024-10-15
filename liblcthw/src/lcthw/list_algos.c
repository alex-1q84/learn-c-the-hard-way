#include <lcthw/list_algos.h>
#include <lcthw/list.h>
#include <lcthw/dbg.h>

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

List *merge(List * left, List * right, List_compare f_compare);

List *List_merge_sort(List * list, List_compare f_compare)
{
    if (list == NULL || List_count(list) <= 1) return list;

    List *left = List_create();
    check_mem(left);
    List *right = List_create();
    check_mem(right);

    int middle = List_count(list)/2;
    int i = 0;
    LIST_FOREACH(list, first, next, cur) {
        if (i < middle) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }
        i++;
    }

    List *sorted_left = List_merge_sort(left, f_compare);
    List *sorted_right = List_merge_sort(right, f_compare);
    
    List *result = merge(sorted_left, sorted_right, f_compare);

    List_destroy(left);
    List_destroy(right);

    return result;

error:
    if (left) List_destroy(left);
    if (right) List_destroy(right);
    return NULL;
}

List *merge(List * left, List * right, List_compare f_compare)
{
    List * result = List_create();
    check_mem(result);

    ListNode * left_cur = left->first;
    ListNode * right_cur = right->first;

    while (left_cur != NULL && right_cur != NULL) {
        if (f_compare(left_cur->value, right_cur->value) <= 0) {
            List_push(result, left_cur->value);
            left_cur = left_cur->next;
        } else {
            List_push(result, right_cur->value);
            right_cur = right_cur->next;
        }
    }

    while (left_cur != NULL) {
        List_push(result, left_cur->value);
        left_cur = left_cur->next;
    }

    while (right_cur != NULL) {
        List_push(result, right_cur->value);
        right_cur = right_cur->next;
    }

    return result;

error:
    if (result) List_destroy(result);
    return NULL;
}
