/*
 * set_empty.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    set_t* pset_s1 = create_set(int);
    set_t* pset_s2 = create_set(int);

    if(pset_s1 == NULL || pset_s2 == NULL)
    {
        return -1;
    }

    set_init(pset_s1);
    set_init(pset_s2);

    set_insert(pset_s1, 1);

    if(set_empty(pset_s1))
    {
        printf("The set s1 is empty.\n");
    }
    else
    {
        printf("The set s1 is not empty.\n");
    }

    if(set_empty(pset_s2))
    {
        printf("The set s2 is empty.\n");
    }
    else
    {
        printf("The set s2 is not empty.\n");
    }

    set_destroy(pset_s1);
    set_destroy(pset_s2);

    return 0;
}
