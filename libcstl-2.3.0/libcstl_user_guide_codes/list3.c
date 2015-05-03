/*
 * list3.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

static void _print(const void* cpv_input, void* pv_output)
{
    printf("%d ", *(int*)cpv_input);
}

static void _print_list(const list_t* cplist_coll1, const list_t* cplist_coll2)
{
    printf("list1: ");
    algo_for_each(list_begin(cplist_coll1), list_end(cplist_coll1), _print);
    printf("\n");
    printf("list2: ");
    algo_for_each(list_begin(cplist_coll2), list_end(cplist_coll2), _print);
    printf("\n");
}

int main(int argc, char* argv[])
{
    list_t* plist_coll1 = create_list(int);
    list_t* plist_coll2 = create_list(int);
    list_iterator_t it_pos;
    int i = 0;

    if(plist_coll1 == NULL || plist_coll2 == NULL)
    {
        return -1;
    }

    list_init(plist_coll1);
    list_init(plist_coll2);

    for(i = 0; i < 6; ++i)
    {
        list_push_back(plist_coll1, i);
        list_push_front(plist_coll2, i);
    }
    _print_list(plist_coll1, plist_coll2);

    it_pos = algo_find(list_begin(plist_coll1), list_end(plist_coll1), 3);
    list_splice(plist_coll1, it_pos, plist_coll2);

    _print_list(plist_coll1, plist_coll2);

    list_splice_pos(plist_coll1, list_end(plist_coll1),
        plist_coll1, list_begin(plist_coll1));
    _print_list(plist_coll1, plist_coll2);

    list_sort(plist_coll1);

    list_assign(plist_coll2, plist_coll1);
    list_unique(plist_coll2);
    _print_list(plist_coll1, plist_coll2);

    list_merge(plist_coll1, plist_coll2);
    _print_list(plist_coll1, plist_coll2);

    list_destroy(plist_coll1);
    list_destroy(plist_coll2);

    return 0;
}
