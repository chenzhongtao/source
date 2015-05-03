/*
 * algo_iota.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cnumeric.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_vec1 = create_vector(int);
    vector_iterator_t it_vec;

    if(pvec_vec1 == NULL)
    {
        return -1;
    }

    vector_init_n(pvec_vec1, 10);

    algo_iota(vector_begin(pvec_vec1), vector_end(pvec_vec1), 7);
    printf("The vector vec1 is:");
    for(it_vec = vector_begin(pvec_vec1);
        !iterator_equal(it_vec, vector_end(pvec_vec1));
        it_vec = iterator_next(it_vec))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_vec));
    }
    printf("\n");

    vector_destroy(pvec_vec1);

    return 0;
}
