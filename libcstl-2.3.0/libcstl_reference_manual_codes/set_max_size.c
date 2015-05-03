/*
 * set_max_size.c
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

    printf("The maximum possible length of the set is %d.\n", set_max_size(pset_s1));

    set_destroy(pset_s1);

    return 0;
}
