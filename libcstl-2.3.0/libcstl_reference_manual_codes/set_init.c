/*
 * set_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    set_t* pset_s0 = create_set(int);
    set_t* pset_s1 = create_set(int);
    set_t* pset_s2 = create_set(int);
    set_t* pset_s3 = create_set(int);
    set_t* pset_s4 = create_set(int);
    set_t* pset_s5 = create_set(int);
    set_iterator_t it_s;

    if(pset_s0 == NULL || pset_s1 == NULL || pset_s2 == NULL || pset_s3 == NULL || pset_s4 == NULL || pset_s5 == NULL)
    {
        return -1;
    }

    /* Create an empty set s0 f key type integer */
    set_init(pset_s0);

    /* 
     * Create an empty set s1 with the key comparison
     * function of less than, then insert 4 elements.
     */
    set_init_ex(pset_s1, fun_less_int);
    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    set_insert(pset_s1, 40);

    /*
     * Create an empty set s2 with the key comparison
     * function of greater than, then insert 2 elements.
     */
    set_init_ex(pset_s2, fun_greater_int);
    set_insert(pset_s2, 10);
    set_insert(pset_s2, 20);

    /* Create a copy, set s3, of set s1 */
    set_init_copy(pset_s3, pset_s1);

    /* Create a set s4 by copying the range s1[first, last) */
    set_init_copy_range(pset_s4, set_begin(pset_s1), iterator_advance(set_begin(pset_s1), 2));

    /*
     * Create a set s5 by copying the range s3[first, last)
     * and with the key comparison function of less than.
     */
    set_init_copy_range_ex(pset_s5, set_begin(pset_s3), iterator_next(set_begin(pset_s3)), fun_less_int);

    printf("s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    printf("s2 =");
    for(it_s = set_begin(pset_s2); !iterator_equal(it_s, set_end(pset_s2)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    printf("s3 =");
    for(it_s = set_begin(pset_s3); !iterator_equal(it_s, set_end(pset_s3)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    printf("s4 =");
    for(it_s = set_begin(pset_s4); !iterator_equal(it_s, set_end(pset_s4)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    printf("s5 =");
    for(it_s = set_begin(pset_s5); !iterator_equal(it_s, set_end(pset_s5)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    set_destroy(pset_s0);
    set_destroy(pset_s1);
    set_destroy(pset_s2);
    set_destroy(pset_s3);
    set_destroy(pset_s4);
    set_destroy(pset_s5);

    return 0;
}
