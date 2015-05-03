/*
 * fun_random_number.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

static void _print_int(const void* cpv_input, void* pv_output)
{
    printf("%d ", *(int*)cpv_input);
}

static void _fill_random(const void* cpv_input, void* pv_output)
{
    int n_upuer_bound = 10000;
    fun_random_number(&n_upuer_bound, (int*)cpv_input);
}

int main(int argc, char* argv[])
{
    vector_t* pvec_v = create_vector(int);

    if(pvec_v == NULL)
    {
        return -1;
    }

    vector_init_n(pvec_v, 10);

    printf("The original vector v = ( ");
    algo_for_each(vector_begin(pvec_v), vector_end(pvec_v), _print_int);
    printf(")\n");

    algo_for_each(vector_begin(pvec_v), vector_end(pvec_v), _fill_random);

    printf("The filled vector v = ( ");
    algo_for_each(vector_begin(pvec_v), vector_end(pvec_v), _print_int);
    printf(")\n");

    vector_destroy(pvec_v);

    return 0;
}
