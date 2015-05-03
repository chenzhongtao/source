/*
 * set_lower_bound.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    set_t* pset_s1 = create_set(int);
    set_iterator_t it_s;

    if(pset_s1 == NULL)
    {
        return -1;
    }

    set_init(pset_s1);

    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);

    it_s = set_lower_bound(pset_s1, 20);
    printf("The element of set s1 with a key of 20 is: %d.\n", *(int*)iterator_get_pointer(it_s));

    it_s = set_lower_bound(pset_s1, 40);
    /* If no match is found for the key, end() is is returend */
    if(iterator_equal(it_s, set_end(pset_s1)))
    {
        printf("The set s1 doesn't have an element with a key of 40.\n");
    }
    else
    {
        printf("The element of set s1 with a key of 40 is: %d.\n", *(int*)iterator_get_pointer(it_s));
    }

    /* 
     * The element at a specific location in the set can be found
     * by using a dereferenced iterator that addreses the location.
     */
    it_s = set_end(pset_s1);
    it_s = iterator_prev(it_s);
    it_s = set_lower_bound(pset_s1, *(int*)iterator_get_pointer(it_s));
    printf("The element of s1 with a key matching that of the last element is: %d.\n", *(int*)iterator_get_pointer(it_s));

    set_destroy(pset_s1);

    return 0;
}
