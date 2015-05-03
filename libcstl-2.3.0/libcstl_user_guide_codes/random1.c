/*
 * random1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    iterator_t it_pos;
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
    printf("coll: ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_random_shuffle(vector_begin(pvec_coll), vector_end(pvec_coll));
    printf("shuffle: ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_sort(vector_begin(pvec_coll), vector_end(pvec_coll));
    printf("sort: ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_random_shuffle_if(vector_begin(pvec_coll),
        vector_end(pvec_coll), fun_random_number);
    printf("shuffle: ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_destroy(pvec_coll);

    return 0;
}
