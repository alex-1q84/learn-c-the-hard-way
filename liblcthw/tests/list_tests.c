#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char *test_destroy()
{
    List_clear_destroy(list);

    return NULL;

}

char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value.");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value.");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong first value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val = test2, "Wrong remove element.");
    mu_assert(List_count(list) == 2, "Wron count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}

char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}

char *test_copy()
{
    mu_assert(List_count(list) != 0, "Wrong count before copy.");

    List *new_list = List_copy(list);
    mu_assert(List_count(new_list) == List_count(list), "Wrong count of copyed list");

    mu_assert(new_list->first->value == list->first->value, "new list first node value not equals to list first node value");
    mu_assert(new_list->first->next->value == list->first->next->value, "new list second node value not equals to list second node value");
    mu_assert(new_list->last->value == list->last->value, "new list second node value not equals to list second node value");

    return NULL;
}

char *test_split()
{
    List *a_list = List_create();
    mu_assert(a_list != NULL, "create list failed.");
    List *b_list = List_create();
    mu_assert(b_list != NULL, "create list failed.");

    ListNode *split_at = list->first->next;
    int split_status = List_split(list, split_at, a_list, b_list);

    mu_assert(split_status == 0, "split list failed.");
    mu_assert(List_count(a_list) == 1, "Wrong count of split list.");
    mu_assert(a_list->first == list->first, "Wrong first after split.");
    mu_assert(a_list->last == split_at->prev, "Wrong last after split.");
    mu_assert(b_list->first == split_at, "Wrong first after split.");
    mu_assert(b_list->last == list->last, "Wrong last after split.");

    return NULL;
}

char *test_join()
{
    List *alist = List_create();
    List *blist = List_create();

    mu_assert(blist == List_join(NULL, blist), "should be blist");
    mu_assert(alist == List_join(alist, NULL), "should be alist");

    char *a1 = "a1";
    char *a2 = "a2";

    List_push(alist, a1);
    mu_assert(alist == List_join(alist, blist), "should be alist");

    List_pop(alist);
    List_push(blist, a2);
    mu_assert(blist == List_join(alist, blist), "should be blist");

    List_push(alist, a1);
    mu_assert(alist == List_join(alist, blist), "should be alist");
    mu_assert(List_count(alist) == 2, "Wrong count of join list");
    mu_assert(List_first(alist) == a1, "Wrong value of first item of join list");
    mu_assert(List_last(alist) == a2, "Wrong value of last item of join list");
    //check blist status after join
    mu_assert(List_count(blist) == 0, "Wrong count of blist");
    mu_assert(List_first(blist) == NULL, "Wrong value of first itme of blist");

    List_destroy(alist);
    List_destroy(blist);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_copy);
    mu_run_test(test_split);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_join);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
