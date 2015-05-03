/*
 * random2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll1 = create_vector(int);
    vector_t* pvec_coll2 = create_vector(int);
    iterator_t it_pos;
    iterator_t it_end;
    int i = 0;

    if(pvec_coll1 == NULL || pvec_coll2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll1);
    vector_init_n(pvec_coll2, 10);

    for(i = 1; i <= 19; ++i)
    {
        vector_push_back(pvec_coll1, i);
    }
    printf("coll1: ");
    for(it_pos = vector_begin(pvec_coll1);
        !iterator_equal(it_pos, vector_end(pvec_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_random_sample(vector_begin(pvec_coll1), vector_end(pvec_coll1),
        vector_begin(pvec_coll2), vector_end(pvec_coll2));
    printf("coll2: ");
    for(it_pos = vector_begin(pvec_coll2);
        !iterator_equal(it_pos, vector_end(pvec_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_random_sample_if(vector_begin(pvec_coll1), vector_end(pvec_coll1),
        vector_begin(pvec_coll2), vector_end(pvec_coll2), fun_random_number);
    printf("coll2: ");
    for(it_pos = vector_begin(pvec_coll2);
        !iterator_equal(it_pos, vector_end(pvec_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_end = algo_random_sample_n(vector_begin(pvec_coll1),
        vector_end(pvec_coll1), vector_begin(pvec_coll2), 5);
    printf("coll2: ");
    for(it_pos = vector_begin(pvec_coll2);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_end = algo_random_sample_n_if(vector_begin(pvec_coll1), vector_end(pvec_coll1),
        vector_begin(pvec_coll2), 8, fun_random_number);
    printf("coll2: ");
    for(it_pos = vector_begin(pvec_coll2);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_destroy(pvec_coll1);
    vector_destroy(pvec_coll2);

    return 0;
}
