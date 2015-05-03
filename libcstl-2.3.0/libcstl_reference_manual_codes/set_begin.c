/*
 * set_begin.c
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
    set_insert(pset_s1, 3);

    printf("The first element of s1 is %d\n", *(int*)iterator_get_pointer(set_begin(pset_s1)));

    set_erase_pos(pset_s1, set_begin(pset_s1));
    printf("The first element of s1 is now %d\n", *(int*)iterator_get_pointer(set_begin(pset_s1)));

    set_destroy(pset_s1);

    return 0;
}
