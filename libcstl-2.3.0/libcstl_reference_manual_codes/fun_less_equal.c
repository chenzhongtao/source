/*
 * fun_less_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v = create_vector(int);
    iterator_t it_pos;
    int i = 0;

    if(pvec_v == NULL)
    {
        return -1;
    }

    vector_init(pvec_v);

    for(i = 0; i < 5; ++i)
    {
        vector_push_back(pvec_v, rand() % 10000);
    }
    vector_push_back(pvec_v, 2836);
    vector_push_back(pvec_v, 2836);
    vector_push_back(pvec_v, 2836);

    printf("The original vector v1 = ( ");
    for(it_pos = vector_begin(pvec_v);
        !iterator_equal(it_pos, vector_end(pvec_v));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf(")\n");

    algo_sort_if(vector_begin(pvec_v), vector_end(pvec_v), fun_less_equal_int);
    printf("The sorted vector v1 = ( ");
    for(it_pos = vector_begin(pvec_v);
        !iterator_equal(it_pos, vector_end(pvec_v));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf(")\n");

    vector_destroy(pvec_v);

    return 0;
}
