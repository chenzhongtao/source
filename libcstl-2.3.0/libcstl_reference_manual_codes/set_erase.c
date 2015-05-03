/*
 * set_erase.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    set_t* pset_s1 = create_set(int);
    set_t* pset_s2 = create_set(int);
    set_t* pset_s3 = create_set(int);
    set_iterator_t it_s;
    size_t t_count = 0;
    int i = 0;

    if(pset_s1 == NULL || pset_s2 == NULL || pset_s3 == NULL)
    {
        return -1;
    }

    set_init(pset_s1);
    set_init(pset_s2);
    set_init(pset_s3);

    for(i = 1; i < 5; ++i)
    {
        set_insert(pset_s1, i);
        set_insert(pset_s2, i * i);
        set_insert(pset_s3, i - 1);
    }

    /* The first function remove an element at a given position */
    set_erase_pos(pset_s1, iterator_next(set_begin(pset_s1)));
    printf("After the second element is deleted, the set s1 is:");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    /* The second function removes elements in the range [first, last) */
    set_erase_range(pset_s2, iterator_next(set_begin(pset_s2)), iterator_prev(set_end(pset_s2)));
    printf("After the middlet two elements are deleted, the set s2 is:");
    for(it_s = set_begin(pset_s2); !iterator_equal(it_s, set_end(pset_s2)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    /* the third function removes elements with a given key */
    t_count = set_erase(pset_s3, 2);
    printf("After the element with a key of 2 is deleted the set s3 is:");
    for(it_s = set_begin(pset_s3); !iterator_equal(it_s, set_end(pset_s3)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    /* the third function returns the number of elements removed */
    printf("The number of elements removed from s3 is: %d.\n", t_count);

    set_destroy(pset_s1);
    set_destroy(pset_s2);
    set_destroy(pset_s3);

    return 0;
}
