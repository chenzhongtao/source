/*
 * sortmset.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_coll = create_multiset(int);
    int n_randmo = 0;
    int n_input = 1000000;
    int i = 0;

    if(pmset_coll == NULL)
    {
        return -1;
    }

    multiset_init(pmset_coll);

    for(i = 0; i < 1000000; ++i)
    {
        fun_random_number(&n_input, &n_randmo);
        multiset_insert(pmset_coll, n_randmo);
    }

    multiset_destroy(pmset_coll);

    return 0;
}
