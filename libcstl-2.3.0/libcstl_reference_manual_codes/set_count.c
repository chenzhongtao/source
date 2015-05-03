/*
 * set_count.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    set_t* pset_s1 = create_set(int);

    if(pset_s1 == NULL)
    {
        return -1;
    }

    set_init(pset_s1);

    set_insert(pset_s1, 1);
    set_insert(pset_s1, 1);

    /* Keys must be unique in set, so duplicates are ignored */
    printf("The number of elements in s1 with a sort key of 1 is: %d.\n", set_count(pset_s1, 1));
    printf("The number of elements in s1 with a sort key of 2 is: %d.\n", set_count(pset_s1, 2));

    set_destroy(pset_s1);

    return 0;
}
