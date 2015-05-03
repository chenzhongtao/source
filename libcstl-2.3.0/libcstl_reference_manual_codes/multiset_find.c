/*
 * multiset_find.c
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
    multiset_insert(pmset_s1, 20);

    it_s = multiset_find(pmset_s1, 20);
    printf("The first element of multiset s1 with a key of 20 is: %d.\n", *(int*)iterator_get_pointer(it_s));

    it_s = multiset_find(pmset_s1, 40);
    /* If no match is found for the key, end() is returned. */
    if(iterator_equal(it_s, multiset_end(pmset_s1)))
    {
        printf("The multiset s1 doesn't have an element with a key of 40.\n");
    }
    else
    {
        printf("The element of multiset s1 with a key of 40 is: %d.\n", *(int*)iterator_get_pointer(it_s));
    }

    /*
     * The element at a specific location in the multiset can be 
     * found using a dereferenced iterator addressing the location.
     */
    it_s = multiset_end(pmset_s1);
    it_s = iterator_prev(it_s);
    it_s = multiset_find(pmset_s1, *(int*)iterator_get_pointer(it_s));
    printf("The first element of s1 with a key matching that of the last element is %d.\n", *(int*)iterator_get_pointer(it_s));

    /*
     * Note that the first element with a key equal to tha key of
     * the last element is not the last element.
     */
    if(iterator_equal(it_s, iterator_prev(multiset_end(pmset_s1))))
    {
        printf("This is the last element of multiset s1.\n");
    }
    else
    {
        printf("The is not the last element of multiset s1.\n");
    }

    multiset_destroy(pmset_s1);

    return 0;
}
