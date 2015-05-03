/*
 * perm1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _print(const void* cpv_input, void* pv_output)
{
    printf("%d ", *(int*)cpv_input);
}

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);

    if(pvec_coll == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);

    vector_push_back(pvec_coll, 1);
    vector_push_back(pvec_coll, 2);
    vector_push_back(pvec_coll, 3);

    printf("on entry: ");
    algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print);
    printf("\n");

    while(algo_next_permutation(vector_begin(pvec_coll), vector_end(pvec_coll)))
    {
        algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print);
        printf("\n");
    }
    printf("afterward: ");
    algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print);
    printf("\n");

    while(algo_prev_permutation(vector_begin(pvec_coll), vector_end(pvec_coll)))
    {
        algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print);
        printf("\n");
    }
    printf("now: ");
    algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print);
    printf("\n");

    while(algo_prev_permutation(vector_begin(pvec_coll), vector_end(pvec_coll)))
    {
        algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print);
        printf("\n");
    }
    printf("afterward: ");
    algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print);
    printf("\n");

    vector_destroy(pvec_coll);

    return 0;
}
