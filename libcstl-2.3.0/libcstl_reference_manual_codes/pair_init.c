/*
 * pair_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cutility.h>

int main(int argc, char* argv[])
{
    pair_t* ppr_pr1 = create_pair(int, double);
    pair_t* ppr_pr2 = create_pair(int, double);
    pair_t* ppr_pr3 = create_pair(int, double);

    if(ppr_pr1 == NULL || ppr_pr2 == NULL || ppr_pr3 == NULL)
    {
        return -1;
    }

    /* Using the specific elements to initialize the pair */
    pair_init_elem(ppr_pr1, 10, 1.1e-2);

    /* Using the default elements to initialize the pair */
    pair_init(ppr_pr2);

    /* Making a copy of a pair */
    pair_init_copy(ppr_pr3, ppr_pr1);

    printf("The pair pr1 is (%d, %lf).\n",
        *(int*)pair_first(ppr_pr1), *(double*)pair_second(ppr_pr1));
    printf("The pair pr2 is (%d, %lf).\n",
        *(int*)pair_first(ppr_pr2), *(double*)pair_second(ppr_pr2));
    printf("The pair pr3 is (%d, %lf).\n",
        *(int*)pair_first(ppr_pr3), *(double*)pair_second(ppr_pr3));

    pair_destroy(ppr_pr1);
    pair_destroy(ppr_pr2);
    pair_destroy(ppr_pr3);

    return 0;
}
