/*
 * multiset_begin.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int);

    if(pmset_s1 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1);

    multiset_insert(pmset_s1, 1);
    multiset_insert(pmset_s1, 2);
    multiset_insert(pmset_s1, 3);

    printf("The first element of s1 is %d\n", *(int*)iterator_get_pointer(multiset_begin(pmset_s1)));

    multiset_erase_pos(pmset_s1, multiset_begin(pmset_s1));
    printf("The first element of s1 is now %d\n", *(int*)iterator_get_pointer(multiset_begin(pmset_s1)));

    multiset_destroy(pmset_s1);

    return 0;
}
