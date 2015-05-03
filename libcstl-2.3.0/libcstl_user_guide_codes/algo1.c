/*
 * algo1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    vector_iterator_t it_pos;

    if(pvec_coll == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);

    /* insert elements from 1 to 6 in arbitrary order */
    vector_push_back(pvec_coll, 3);
    vector_push_back(pvec_coll, 2);
    vector_push_back(pvec_coll, 5);
    vector_push_back(pvec_coll, 6);
    vector_push_back(pvec_coll, 4);
    vector_push_back(pvec_coll, 1);

    /* find and print minimum and maximum element */
    it_pos = algo_min_element(vector_begin(pvec_coll), vector_end(pvec_coll));
    printf("min: %d\n", *(int*)iterator_get_pointer(it_pos));
    it_pos = algo_max_element(vector_begin(pvec_coll), vector_end(pvec_coll));
    printf("max: %d\n", *(int*)iterator_get_pointer(it_pos));

    /* sort all elements */
    algo_sort(vector_begin(pvec_coll), vector_end(pvec_coll));

    /* find the first element with value 3 */
    it_pos = algo_find(vector_begin(pvec_coll), vector_end(pvec_coll), 3);

    /*
     * reverse the order of the found element with value 3
     * and all following elements
     */
    algo_reverse(it_pos, vector_end(pvec_coll));

    /* print all elements */
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
