/*
 * multiset_upper_bound.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int);
    multiset_iterator_t it_s;

    if(pmset_s1 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1);

    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);

    it_s = multiset_upper_bound(pmset_s1, 20);
    printf("The first element of multiset s1 with a key greater than 20 is: %d.\n", *(int*)iterator_get_pointer(it_s));

    it_s = multiset_upper_bound(pmset_s1, 30);
    /* If no match is found for the key, end() is returned */
    if(iterator_equal(it_s, multiset_end(pmset_s1)))
    {
        printf("The multiset s1 doesn't have an element with a key greater than 30.\n");
    }
    else
    {
        printf("the element of multiset s1 with a key > 30 is: %d.\n", *(int*)iterator_get_pointer(it_s));
    }

    /*
     * The element at a specific location in the multiset can be found
     * by using a dereferenced iterator addressing the location.
     */
    it_s = multiset_begin(pmset_s1);
    it_s = multiset_upper_bound(pmset_s1, *(int*)iterator_get_pointer(it_s));
    printf("The first element of s1 with a key greater than that of the initial element of s1 is: %d.\n", *(int*)iterator_get_pointer(it_s));

    multiset_destroy(pmset_s1);

    return 0;
}
