/*
 * pair_less.c
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

    pair_init(ppr_pr1);
    pair_init(ppr_pr2);
    pair_init(ppr_pr3);

    pair_make(ppr_pr1, 10, 2.22e-1);
    pair_make(ppr_pr2, 100, 1.11e-1);
    pair_make(ppr_pr3, 10, 1.11e-1);

    printf("The pair pr1 is: (%d, %lf).\n",
        *(int*)pair_first(ppr_pr1), *(double*)pair_second(ppr_pr1));
    printf("The pair pr2 is: (%d, %lf).\n",
        *(int*)pair_first(ppr_pr2), *(double*)pair_second(ppr_pr2));
    printf("The pair pr3 is: (%d, %lf).\n",
        *(int*)pair_first(ppr_pr3), *(double*)pair_second(ppr_pr3));

    if(pair_less(ppr_pr1, ppr_pr2))
    {
        printf("The pair pr1 is less than the pair pr2.\n");
    }
    else
    {
        printf("The pair pr1 is not less than the pair pr2.\n");
    }

    if(pair_less(ppr_pr1, ppr_pr3))
    {
        printf("The pair pr1 is less than the pair pr3.\n");
    }
    else
    {
        printf("The pair pr1 is not less than the pair pr3.\n");
    }

    pair_destroy(ppr_pr1);
    pair_destroy(ppr_pr2);
    pair_destroy(ppr_pr3);

    return 0;
}
