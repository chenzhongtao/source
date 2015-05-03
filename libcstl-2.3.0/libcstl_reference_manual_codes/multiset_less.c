/*
 * multiset_less.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int);
    multiset_t* pmset_s2 = create_multiset(int);
    multiset_t* pmset_s3 = create_multiset(int);
    int i = 0;

    if(pmset_s1 == NULL || pmset_s2 == NULL || pmset_s3 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1);
    multiset_init(pmset_s2);
    multiset_init(pmset_s3);

    for(i = 0; i < 3; ++i)
    {
        multiset_insert(pmset_s1, i);
        multiset_insert(pmset_s2, i * i);
        multiset_insert(pmset_s3, i - 1);
    }

    if(multiset_less(pmset_s1, pmset_s2))
    {
        printf("The multiset s1 is less than the multiset s2.\n");
    }
    else
    {
        printf("The multiset s1 is not less than the multiset s2.\n");
    }

    if(multiset_less(pmset_s1, pmset_s3))
    {
        printf("The multiset s1 is less than the multiset s3.\n");
    }
    else
    {
        printf("The multset s1 is not less than the multiset s3.\n");
    }

    multiset_destroy(pmset_s1);
    multiset_destroy(pmset_s2);
    multiset_destroy(pmset_s3);

    return 0;
}
