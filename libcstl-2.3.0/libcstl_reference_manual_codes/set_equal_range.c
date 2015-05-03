/*
 * set_equal_range.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    set_t* pset_s1 = create_set(int);
    set_iterator_t it_s;
    range_t r_r1;

    if(pset_s1 == NULL)
    {
        return -1;
    }

    set_init(pset_s1);

    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);

    r_r1 = set_equal_range(pset_s1, 20);

    printf("The upper bound of the element with a key of 20 in the set s1 is: %d.\n", *(int*)iterator_get_pointer(r_r1.it_end));
    printf("The lower bound of the element with a key of 20 in the set s1 is: %d.\n", *(int*)iterator_get_pointer(r_r1.it_begin));

    /* Compare the upper_bound called directly */
    it_s = set_upper_bound(pset_s1, 20);
    printf("A direct call of upper_bound(20), gives %d,\n", *(int*)iterator_get_pointer(it_s));
    printf("matching the 2nd element of the range returned by equal_range(20).\n");

    r_r1 = set_equal_range(pset_s1, 40);
    /* If no match is found for the key. both elements of the range return end() */
    if(iterator_equal(r_r1.it_begin, set_end(pset_s1)) && iterator_equal(r_r1.it_end, set_end(pset_s1)))
    {
        printf("The set s1 doesn't have and element with a key less than 40.\n");
    }
    else
    {
        printf("The element of set s1 with a key >= 40 is: %d.\n", *(int*)iterator_get_pointer(r_r1.it_begin));
    }

    set_destroy(pset_s1);

    return 0;
}
