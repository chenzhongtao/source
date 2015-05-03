/*
 * set_greater.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    set_t* pset_s1 = create_set(int);
    set_t* pset_s2 = create_set(int);
    set_t* pset_s3 = create_set(int);
    int i = 0;

    if(pset_s1 == NULL || pset_s2 == NULL || pset_s3 == NULL)
    {
        return -1;
    }

    set_init(pset_s1);
    set_init(pset_s2);
    set_init(pset_s3);

    for(i = 0; i < 3; ++i)
    {
        set_insert(pset_s1, i);
        set_insert(pset_s2, i * i);
        set_insert(pset_s3, i - 1);
    }

    if(set_greater(pset_s1, pset_s2))
    {
        printf("The set s1 is greater than the set s2.\n");
    }
    else
    {
        printf("The set s1 is not greater than the set s2.\n");
    }

    if(set_greater(pset_s1, pset_s3))
    {
        printf("The set s1 is greater than the set s3.\n");
    }
    else
    {
        printf("The set s1 is not greater than the set s3.\n");
    }

    set_destroy(pset_s1);
    set_destroy(pset_s2);
    set_destroy(pset_s3);

    return 0;
}
