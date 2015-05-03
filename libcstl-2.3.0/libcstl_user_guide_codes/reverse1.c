/*
 * reverse1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

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
    vector_init(pvec_coll2);

    for(i = 1; i <= 9; ++i)
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

    algo_reverse(vector_begin(pvec_coll1), vector_end(pvec_coll1));
    printf("after reversing coll1: ");
    for(it_pos = vector_begin(pvec_coll1);
        !iterator_equal(it_pos, vector_end(pvec_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_resize(pvec_coll2, vector_size(pvec_coll1));
    it_end = algo_reverse_copy(iterator_next_n(vector_begin(pvec_coll1), 3),
        iterator_prev(vector_end(pvec_coll1)), vector_begin(pvec_coll2));
    printf("after reversing coll2: ");
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
