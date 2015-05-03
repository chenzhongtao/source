/*
 * set_assign.c
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
    set_insert(pset_s2, 40);
    set_insert(pset_s2, 50);
    set_insert(pset_s2, 60);

    printf("s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    set_assign(pset_s1, pset_s2);
    printf("s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    set_destroy(pset_s1);
    set_destroy(pset_s2);

    return 0;
}
