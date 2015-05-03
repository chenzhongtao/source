/*
 * iota.c
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

    vector_init_n(pvec_coll, 10);

    algo_iota(vector_begin(pvec_coll), vector_end(pvec_coll), 7);
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
