/*
 * multiset_erase.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int);
    multiset_t* pmset_s2 = create_multiset(int);
    multiset_t* pmset_s3 = create_multiset(int);
    multiset_iterator_t it_s;
    int i = 0;
    int n_count = 0;

    if(pmset_s1 == NULL || pmset_s2 == NULL || pmset_s3 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1);
    multiset_init(pmset_s2);
    multiset_init(pmset_s3);

    for(i = 1; i < 5; ++i)
    {
        multiset_insert(pmset_s1, i);
        multiset_insert(pmset_s2, i * i);
        multiset_insert(pmset_s3, i - 1);
    }

    /* The first function removes an element at a given position */
    multiset_erase_pos(pmset_s1, iterator_next(multiset_begin(pmset_s1)));
    printf("After the second element is deleted, the multiset s1 is:");
    for(it_s = multiset_begin(pmset_s1); !iterator_equal(it_s, multiset_end(pmset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    /* The second function remove elements in the range[first, last) */
    multiset_erase_range(pmset_s2, iterator_next(multiset_begin(pmset_s2)), iterator_prev(multiset_end(pmset_s2)));
    printf("After the middle two elements are deleted, the multiset s2 is:");
    for(it_s = multiset_begin(pmset_s2); !iterator_equal(it_s, multiset_end(pmset_s2)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    /* The third function removes elements with a given key */
    multiset_insert(pmset_s3, 2);
    n_count = multiset_erase(pmset_s3, 2);
    printf("The number of elements removed from s3 is: %d.\n", n_count);
    printf("After the element with a key of 2 is deleted, the multiset s3 is:");
    for(it_s = multiset_begin(pmset_s3); !iterator_equal(it_s, multiset_end(pmset_s3)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    multiset_destroy(pmset_s1);
    multiset_destroy(pmset_s2);
    multiset_destroy(pmset_s3);

    return 0;
}
