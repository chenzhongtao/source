/*
 * multiset_insert.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int);
    multiset_t* pmset_s2 = create_multiset(int);
    multiset_iterator_t it_s;

    if(pmset_s1 == NULL || pmset_s2 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1);
    multiset_init(pmset_s2);

    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    multiset_insert(pmset_s1, 40);

    printf("The original s1 =");
    for(it_s = multiset_begin(pmset_s1); !iterator_equal(it_s, multiset_end(pmset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    multiset_insert(pmset_s1, 20);
    multiset_insert_hint(pmset_s1, iterator_prev(multiset_end(pmset_s1)), 50);
    printf("After the insertions, s1 =");
    for(it_s = multiset_begin(pmset_s1); !iterator_equal(it_s, multiset_end(pmset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    multiset_insert(pmset_s2, 100);
    multiset_insert_range(pmset_s2, iterator_next(multiset_begin(pmset_s1)), iterator_prev(multiset_end(pmset_s1)));
    printf("s2 =");
    for(it_s = multiset_begin(pmset_s2); !iterator_equal(it_s, multiset_end(pmset_s2)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    multiset_destroy(pmset_s1);
    multiset_destroy(pmset_s2);

    return 0;
}
