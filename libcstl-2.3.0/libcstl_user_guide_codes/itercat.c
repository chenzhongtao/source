/*
 * itercat.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    iterator_t it_pos; /* uses iterator_t instead of vector_iterator_t */
    int i = 0;
    int n_value = 0;

    if(pvec_coll == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);

    /* insert from -3 to 9 */
    for(i = -3; i <= 9; ++i)
    {
        vector_push_back(pvec_coll, i);
    }

    /*
     * print number of elements by processing the distance
     * between vector_begin() and vector_end()
     */
    printf("number/distance : %d\n",
        iterator_minus(vector_end(pvec_coll), vector_begin(pvec_coll)));

    /*
     * print all elements
     * uses iterator_less instead of !iterator_equal
     */
    for(it_pos = vector_begin(pvec_coll);
        iterator_less(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* 
     * print all elements
     * uses iterator_at instead of iterator_get_pointer
     */
    for(i = 0; i < vector_size(pvec_coll); ++i)
    {
        printf("%d ", *(int*)iterator_at(vector_begin(pvec_coll), i));
    }
    printf("\n");

    /* print every second element */
    for(it_pos = vector_begin(pvec_coll);
        iterator_less(it_pos, iterator_prev(vector_end(pvec_coll)));
        it_pos = iterator_next_n(it_pos, 2))
    {
        iterator_get_value(it_pos, &n_value);
        printf("%d ", n_value);
    }
    printf("\n");

    vector_destroy(pvec_coll);

    return 0;
}
