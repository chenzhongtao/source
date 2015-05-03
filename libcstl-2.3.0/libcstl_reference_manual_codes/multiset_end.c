/*
 * multiset_end.c
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

    multiset_insert(pmset_s1, 1);
    multiset_insert(pmset_s1, 2);
    multiset_insert(pmset_s1, 3);

    it_s = iterator_prev(multiset_end(pmset_s1));
    printf("The last element of s1 is %d\n", *(int*)iterator_get_pointer(it_s));

    multiset_erase_pos(pmset_s1, it_s);

    it_s = iterator_prev(multiset_end(pmset_s1));
    printf("The last element of s1 is now %d\n", *(int*)iterator_get_pointer(it_s));

    multiset_destroy(pmset_s1);

    return 0;
}
