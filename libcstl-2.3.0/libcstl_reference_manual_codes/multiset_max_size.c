/*
 * multiset_max_size.c
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

    printf("The maximum possible length of the multiset is %d.\n", multiset_max_size(pmset_s1));

    multiset_destroy(pmset_s1);

    return 0;
}
