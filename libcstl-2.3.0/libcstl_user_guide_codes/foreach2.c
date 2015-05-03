/*
 * foreach2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _print(const void* cpv_input, void* pv_output)
{
    printf("%d ", *(int*)cpv_input);
}

static void _plus_10(const void* cpv_input, void* pv_output)
{
    *(int*)cpv_input += 10;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    int i = 0;

    if(pvec_coll == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);

    for(i = 1; i <= 9; ++i)
    {
        vector_push_back(pvec_coll, i);
    }

    algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print);
    printf("\n");


    algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _plus_10);

    algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print);
    printf("\n");

    vector_destroy(pvec_coll);

    return 0;
}
