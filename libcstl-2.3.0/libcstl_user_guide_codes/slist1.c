/*
 * slist1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cslist.h>
#include <cstl/calgorithm.h>

static void _print(const void* cpv_input, void* pv_output)
{
    printf("%d ", *(int*)cpv_input);
}

static void _print_slist(const slist_t* cpslist_coll1, const slist_t* cpslist_coll2,
    const slist_t* cpslist_coll3, const slist_t* cpslist_coll4)
{
    printf("slist1: ");
    algo_for_each(slist_begin(cpslist_coll1), slist_end(cpslist_coll1), _print);
    printf("\n");
    printf("slist2: ");
    algo_for_each(slist_begin(cpslist_coll2), slist_end(cpslist_coll2), _print);
    printf("\n");
    printf("slist3: ");
    algo_for_each(slist_begin(cpslist_coll3), slist_end(cpslist_coll3), _print);
    printf("\n");
    printf("slist4: ");
    algo_for_each(slist_begin(cpslist_coll4), slist_end(cpslist_coll4), _print);
    printf("\n\n");
}

int main(int argc, char* argv[])
{
    slist_t* pslist_coll1 = create_slist(int);
    slist_t* pslist_coll2 = create_slist(int);
    slist_t* pslist_coll3 = create_slist(int);
    slist_t* pslist_coll4 = create_slist(int);
    int i = 0;

    if(pslist_coll1 == NULL || pslist_coll2 == NULL ||
       pslist_coll3 == NULL || pslist_coll4 == NULL)
    {
        return -1;
    }

    slist_init(pslist_coll1);
    slist_init(pslist_coll2);
    slist_init(pslist_coll3);
    slist_init(pslist_coll4);

    for(i = 0; i < 6; ++i)
    {
        slist_push_front(pslist_coll1, i + 1);
        slist_push_front(pslist_coll2, - i - 1);
        slist_push_front(pslist_coll3, i + 1);
        slist_push_front(pslist_coll4, - i - 1);
    }
    _print_slist(pslist_coll1, pslist_coll2, pslist_coll3, pslist_coll4);

    slist_splice_pos(
        pslist_coll1,
        algo_find(slist_begin(pslist_coll1), slist_end(pslist_coll1), 3),
        pslist_coll2,
        algo_find(slist_begin(pslist_coll2), slist_end(pslist_coll2), -3));
    slist_splice_after_pos(
        pslist_coll3,
        algo_find(slist_begin(pslist_coll3), slist_end(pslist_coll3), 3),
        pslist_coll4,
        algo_find(slist_begin(pslist_coll4), slist_end(pslist_coll4), -3));

    _print_slist(pslist_coll1, pslist_coll2, pslist_coll3, pslist_coll4);

    slist_destroy(pslist_coll1);
    slist_destroy(pslist_coll2);
    slist_destroy(pslist_coll3);
    slist_destroy(pslist_coll4);

    return 0;
}
