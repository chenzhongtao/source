/*
 * algo_for_each.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _print(const void* cpv_input, void* pv_output)
{
    printf("%d ", *(int*)cpv_input);
}

static void _mult_5(const void* cpv_input, void* pv_output)
{
    *(int*)cpv_input *= 5;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    int i = 0;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    for(i = -4; i <= 2; ++i)
    {
        vector_push_back(pvec_v1, i);
    }

    /* Using for_each to print each elements of vector */
    printf("The original vector v1 = ( ");
    algo_for_each(vector_begin(pvec_v1), vector_end(pvec_v1), _print);
    printf(")\n");

    /* Using for_each to multiply each elements */
    algo_for_each(vector_begin(pvec_v1), vector_end(pvec_v1), _mult_5);

    /* Using for_each to print each elements of vector */
    printf("The modified vector v1 = ( ");
    algo_for_each(vector_begin(pvec_v1), vector_end(pvec_v1), _print);
    printf(")\n");

    vector_destroy(pvec_v1);

    return 0;
}
