/*
 * count1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _is_even(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 2 == 0 ? true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    iterator_t it_pos;
    size_t t_count = 0;
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

    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    t_count = algo_count(vector_begin(pvec_coll), vector_end(pvec_coll), 4);
    printf("number of elements equal to 4: %u.\n", t_count);

    t_count = algo_count_if(vector_begin(pvec_coll),
        vector_end(pvec_coll), _is_even);
    printf("number of elements with even values: %u.\n", t_count);

    vector_destroy(pvec_coll);

    return 0;
}
