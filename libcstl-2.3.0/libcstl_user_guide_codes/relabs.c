/*
 * relabs.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cnumeric.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    iterator_t it_pos;

    if(pvec_coll == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);

    vector_push_back(pvec_coll, 17);
    vector_push_back(pvec_coll, -3);
    vector_push_back(pvec_coll, 22);
    vector_push_back(pvec_coll, 13);
    vector_push_back(pvec_coll, 13);
    vector_push_back(pvec_coll, -9);

    printf("coll: ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_adjacent_difference(vector_begin(pvec_coll),
        vector_end(pvec_coll), vector_begin(pvec_coll));
    printf("relative: ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_partial_sum(vector_begin(pvec_coll),
        vector_end(pvec_coll), vector_begin(pvec_coll));
    printf("absolute: ");
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
