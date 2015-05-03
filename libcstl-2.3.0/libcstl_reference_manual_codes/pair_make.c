/*
 * pair_make.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cutility.h>

int main(int argc, char* argv[])
{
    pair_t* ppr_pr1 = create_pair(int, double);

    if(ppr_pr1 == NULL)
    {
        return -1;
    }

    pair_init(ppr_pr1);

    printf("The original pair is (%d, %lf).\n",
        *(int*)pair_first(ppr_pr1), *(double*)pair_second(ppr_pr1));

    pair_make(ppr_pr1, 10, 1.1e-2);
    printf("The pair is now (%d, %lf).\n",
        *(int*)pair_first(ppr_pr1), *(double*)pair_second(ppr_pr1));

    pair_destroy(ppr_pr1);

    return 0;
}
