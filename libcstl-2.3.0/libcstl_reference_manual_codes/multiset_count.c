/*
 * multiset_count.c
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
    multiset_insert(pmset_s1, 1);
    multiset_insert(pmset_s1, 2);

    /* 
     * Element do not need to be unique in multiset,
     * so duplicates are allowed and counted.
     */
    printf("The number of element in s1 with a sort key of 1 is: %d.\n", multiset_count(pmset_s1, 1));
    printf("The number of element in s1 with a sort key of 2 is: %d.\n", multiset_count(pmset_s1, 2));
    printf("The number of element in s1 with a sort key of 3 is: %d.\n", multiset_count(pmset_s1, 3));

    multiset_destroy(pmset_s1);

    return 0;
}
