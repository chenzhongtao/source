/*
 * multiset_greater_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int);
    multiset_t* pmset_s2 = create_multiset(int);
    multiset_t* pmset_s3 = create_multiset(int);
    multiset_t* pmset_s4 = create_multiset(int);
    int i = 0;

    if(pmset_s1 == NULL || pmset_s2 == NULL || pmset_s3 == NULL || pmset_s4 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1);
    multiset_init(pmset_s2);
    multiset_init(pmset_s3);
    multiset_init(pmset_s4);

    for(i = 0; i < 3; ++i)
    {
        multiset_insert(pmset_s1, i);
        multiset_insert(pmset_s2, i * i);
        multiset_insert(pmset_s3, i - 1);
        multiset_insert(pmset_s4, i);
    }

    if(multiset_greater_equal(pmset_s1, pmset_s2))
    {
        printf("The multiset s1 is greater than or equal to the multiset s2.\n");
    }
    else
    {
        printf("The multiset s1 is less than the multiset s2.\n");
    }

    if(multiset_greater_equal(pmset_s1, pmset_s3))
    {
        printf("The multiset s1 is greater than or equal to the multiset s3.\n");
    }
    else
    {
        printf("The multiset s1 is less than the multiset s3.\n");
    }

    if(multiset_greater_equal(pmset_s1, pmset_s4))
    {
        printf("The multiset s1 is greater than or equal to the multiset s4.\n");
    }
    else
    {
        printf("The multiset s1 is less than the multiset s4.\n");
    }

    multiset_destroy(pmset_s1);
    multiset_destroy(pmset_s2);
    multiset_destroy(pmset_s3);
    multiset_destroy(pmset_s4);

    return 0;
}
