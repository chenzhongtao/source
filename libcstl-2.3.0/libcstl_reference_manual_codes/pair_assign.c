/*
 * pair_assign.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cutility.h>

int main(int argc, char* argv[])
{
    pair_t* ppr_pr1 = create_pair(int, double);
    pair_t* ppr_pr2 = create_pair(int, double);

    if(ppr_pr1 == NULL || ppr_pr2 == NULL)
    {
        return -1;
    }

    pair_init(ppr_pr1);
    pair_init(ppr_pr2);

    pair_make(ppr_pr1, 10, 1.1e-2);
    pair_make(ppr_pr2, -345, -1.9e-4);

    printf("The pair pr1 is (%d, %lf).\n",
        *(int*)pair_first(ppr_pr1), *(double*)pair_second(ppr_pr1));

    pair_assign(ppr_pr1, ppr_pr2);

    printf("After assignment, the pair pr1 is (%d, %lf).\n",
        *(int*)pair_first(ppr_pr1), *(double*)pair_second(ppr_pr1));

    pair_destroy(ppr_pr1);
    pair_destroy(ppr_pr2);

    return 0;
}
