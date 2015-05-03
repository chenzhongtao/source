/*
 * multiset_clear.c
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

    printf("The size of the multiset is initially %d.\n", multiset_size(pmset_s1));

    multiset_clear(pmset_s1);
    printf("The size of the multiset after clearing is %d.\n", multiset_size(pmset_s1));

    multiset_destroy(pmset_s1);

    return 0;
}
