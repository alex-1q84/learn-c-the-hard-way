#include <lcthw/list.h>
#include <lcthw/dbg.h>

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List * list)
{
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void List_clear(List * list)
{
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}

void List_clear_destroy(List * list)
{
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void List_push(List * list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List * list)
{
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List * list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->first->prev = node;
        node->next = list->first;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List * list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List * list, ListNode * node)
{
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        list->first = node->next;
        check(list->first != NULL,
              "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL,
              "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}

List *List_copy(List * list)
{
    if (!list) {
        return NULL;
    }

    List *new_list = List_create();
    check_mem(new_list);
    LIST_FOREACH(list, first, next, cur) {
        ListNode *node = calloc(1, sizeof(ListNode));
        check_mem(node);
        node->value = cur->value;

        if (new_list->first == NULL) {
            new_list->first = node;
            new_list->last = node;
        } else {
            new_list->last->next = node;
            node->prev = new_list->last;
            new_list->last = node;
        }

        new_list->count++;
    }

    return new_list;
error:
    List_destroy(new_list);
    return NULL;
}

int List_split(List * list, ListNode *split_at, List * a_list, List * b_list)
{
    if (list == NULL || list->first == NULL || split_at == NULL) {
        return -1;
    }

    int a_list_count = 0;
    LIST_FOREACH(list, first, next,  cur) {
        if (cur == split_at) {
            break;
        }
        a_list_count++;
    }

    List_clear(a_list);
    List_clear(b_list);

    a_list->first = list->first;
    a_list->last = split_at->prev;
    a_list->count = a_list_count;

    b_list->first = split_at;
    b_list->last = list->last;
    b_list->count = List_count(list) - a_list_count;

    return 0;
}

List *List_join(List * alist, List * blist)
{
    if (alist == NULL) return blist;
    if (blist == NULL) return alist;
    if (alist->first == NULL) return blist;
    if (blist->first == NULL) return alist;

    alist->last->next = blist->first;
    blist->first->prev = alist->last;
    alist->last = blist->last;
    alist->count += blist->count;

    blist->first = NULL;
    blist->last = NULL;
    blist->count = 0;

    return alist;
}
