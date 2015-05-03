/*
 * multiset_empty.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int);
    multiset_t* pmset_s2 = create_multiset(int);

    if(pmset_s1 == NULL || pmset_s2 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1);
    multiset_init(pmset_s2);

    multiset_insert(pmset_s1, 1);

    if(multiset_empty(pmset_s1))
    {
        printf("The multiset s1 is empty.\n");
    }
    else
    {
        printf("The multiset s1 is not empty.\n");
    }

    if(multiset_empty(pmset_s2))
    {
        printf("The multiset s2 is empty.\n");
    }
    else
    {
        printf("The multiset s2 is not empty.\n");
    }

    multiset_destroy(pmset_s1);
    multiset_destroy(pmset_s2);

    return 0;
}
