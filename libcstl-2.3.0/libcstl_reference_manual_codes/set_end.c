/*
 * set_end.c
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

    set_insert(pset_s1, 1);
    set_insert(pset_s1, 2);
    set_insert(pset_s1, 3);

    it_s = set_end(pset_s1);
    it_s = iterator_prev(it_s);
    printf("The last element of s1 is %d\n", *(int*)iterator_get_pointer(it_s));

    set_erase_pos(pset_s1, it_s);

    it_s = set_end(pset_s1);
    it_s = iterator_prev(it_s);
    printf("The last element of s1 is now %d\n", *(int*)iterator_get_pointer(it_s));

    set_destroy(pset_s1);

    return 0;
}
