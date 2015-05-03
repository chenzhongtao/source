/*
 * set_clear.c
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
    set_insert(pset_s1, 2);

    printf("The size of the set is initially %d.\n", set_size(pset_s1));

    set_clear(pset_s1);
    printf("The size of the set after clearing is %d.\n", set_size(pset_s1));

    set_destroy(pset_s1);

    return 0;
}
