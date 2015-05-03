/*
 * set_insert.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    set_t* pset_s1 = create_set(int);
    set_t* pset_s2 = create_set(int);
    set_iterator_t it_s;

    if(pset_s1 == NULL || pset_s2 == NULL)
    {
        return -1;
    }

    set_init(pset_s1);
    set_init(pset_s2);

    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    set_insert(pset_s1, 40);

    printf("The original s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    it_s = set_insert(pset_s1, 10);
    if(iterator_equal(it_s, set_end(pset_s1)))
    {
        printf("The element 10 already exists in s1.\n");
    }
    else
    {
        printf("The element 10 was inserted in s1 successfully.\n");
    }

    set_insert_hint(pset_s1, iterator_prev(set_end(pset_s1)), 50);
    printf("After the insertions, s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    set_insert(pset_s2, 100);
    set_insert_range(pset_s2, iterator_next(set_begin(pset_s1)), iterator_prev(set_end(pset_s1)));
    printf("s2 =");
    for(it_s = set_begin(pset_s2); !iterator_equal(it_s, set_end(pset_s2)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    set_destroy(pset_s1);
    set_destroy(pset_s2);

    return 0;
}
