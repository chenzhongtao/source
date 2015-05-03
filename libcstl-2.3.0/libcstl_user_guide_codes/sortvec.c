/*
 * sortvec.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    int n_random = 0;
    int n_input = 1000000;
    int i = 0;

    if(pvec_coll == NULL)
    {
        return -1;
    }

    vector_init_n(pvec_coll, 1000000);

    for(i = 0; i < 1000000; ++i)
    {
        fun_random_number(&n_input, &n_random);
        *(int*)vector_at(pvec_coll, i) = n_random;
    }

    algo_sort(vector_begin(pvec_coll), vector_end(pvec_coll));

    vector_destroy(pvec_coll);

    return 0;
}
