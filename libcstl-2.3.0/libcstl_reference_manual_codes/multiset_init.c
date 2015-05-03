/*
 * multiset_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s0 = create_multiset(int);
    multiset_t* pmset_s1 = create_multiset(int);
    multiset_t* pmset_s2 = create_multiset(int);
    multiset_t* pmset_s3 = create_multiset(int);
    multiset_t* pmset_s4 = create_multiset(int);
    multiset_t* pmset_s5 = create_multiset(int);
    multiset_iterator_t it_s;

    if(pmset_s0 == NULL || pmset_s1 == NULL || pmset_s2 == NULL || pmset_s3 == NULL || pmset_s4 == NULL || pmset_s5 == NULL)
    {
        return -1;
    }

    /* Create an empty multiset s0 of key type integer */
    multiset_init(pmset_s0);

    /* 
     * Create an empty multiset s1 with the key comparison
     * function of less than, then insert 4 elements
     */
    multiset_init_ex(pmset_s1, fun_less_int);
    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 40);

    /*
     * Create an empty multiset s2 with the key comparison
     * function of greater than, then insert 2 elements.
     */
    multiset_init_ex(pmset_s2, fun_greater_int);
    multiset_insert(pmset_s2, 10);
    multiset_insert(pmset_s2, 20);

    /* Create a copy, multiset s3, of multiset s1 */
    multiset_init_copy(pmset_s3, pmset_s1);

    /* Create a multiset s4 by copy the range s1[first, last) */
    multiset_init_copy_range(pmset_s4, multiset_begin(pmset_s1), iterator_advance(multiset_begin(pmset_s1), 2));

    /*
     * Create a multiset s5 by copying the range s3[first, last)
     * and with the key comparison function of less than.
     */
    multiset_init_copy_range_ex(pmset_s5, multiset_begin(pmset_s3), iterator_next(multiset_begin(pmset_s3)), fun_less_int);

    printf("s1 =");
    for(it_s = multiset_begin(pmset_s1); !iterator_equal(it_s, multiset_end(pmset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    printf("s2 =");
    for(it_s = multiset_begin(pmset_s2); !iterator_equal(it_s, multiset_end(pmset_s2)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    printf("s3 =");
    for(it_s = multiset_begin(pmset_s3); !iterator_equal(it_s, multiset_end(pmset_s3)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    printf("s4 =");
    for(it_s = multiset_begin(pmset_s4); !iterator_equal(it_s, multiset_end(pmset_s4)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    printf("s5 =");
    for(it_s = multiset_begin(pmset_s5); !iterator_equal(it_s, multiset_end(pmset_s5)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    multiset_destroy(pmset_s0);
    multiset_destroy(pmset_s1);
    multiset_destroy(pmset_s2);
    multiset_destroy(pmset_s3);
    multiset_destroy(pmset_s4);
    multiset_destroy(pmset_s5);

    return 0;
}
