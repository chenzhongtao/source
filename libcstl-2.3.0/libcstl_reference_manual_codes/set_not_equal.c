/*
 * set_not_equal.c
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
        set_insert(pset_s3, i);
    }

    if(set_not_equal(pset_s1, pset_s2))
    {
        printf("The sets s1 and s2 are not equal.\n");
    }
    else
    {
        printf("The sets s1 and s2 are equal.\n");
    }

    if(set_not_equal(pset_s1, pset_s3))
    {
        printf("The sets s1 and s3 are not equal.\n");
    }
    else
    {
        printf("The sets s1 and s3 are equal.\n");
    }

    set_destroy(pset_s1);
    set_destroy(pset_s2);
    set_destroy(pset_s3);

    return 0;
}
