/*
 * multiset_equal_range.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int);
    range_t r_s;
    multiset_iterator_t it_s;

    if(pmset_s1 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1);

    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);

    r_s = multiset_equal_range(pmset_s1, 20);

    printf("The upper bound of the element with a key of 20 in the multiset s1 is: %d.\n", *(int*)iterator_get_pointer(r_s.it_end));
    printf("The lower bound of the element with a key of 20 in the multiset s1 is: %d.\n", *(int*)iterator_get_pointer(r_s.it_begin));

    /* Compare the upper_bound called directly */
    it_s = multiset_upper_bound(pmset_s1, 20);
    printf("A direct call of upper_bound(20) gives %d, matching the 2nd element of the range returned by equal_range(20).\n", *(int*)iterator_get_pointer(it_s));

    r_s = multiset_equal_range(pmset_s1, 40);
    /* If no match is found for the key, both elements of the range return end(). */
    if(iterator_equal(r_s.it_begin, multiset_end(pmset_s1)) && iterator_equal(r_s.it_end, multiset_end(pmset_s1)))
    {
        printf("The multiset s1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of multiset s1 with a key >= 40 is: %d.\n", *(int*)iterator_get_pointer(r_s.it_begin));
    }

    multiset_destroy(pmset_s1);

    return 0;
}
