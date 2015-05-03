/*
 * accu1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cnumeric.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    iterator_t it_pos;
    int n_result = 0;

    if(pvec_coll == NULL)
    {
        return -1;
    }

    vector_init_n(pvec_coll, 9);
    algo_iota(vector_begin(pvec_coll), vector_end(pvec_coll), 1);

    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_accumulate(vector_begin(pvec_coll), vector_end(pvec_coll), 0, &n_result);
    printf("sum: %d\n", n_result);
    algo_accumulate(vector_begin(pvec_coll), vector_end(pvec_coll), -100, &n_result);
    printf("sum: %d\n", n_result);
    algo_accumulate_if(vector_begin(pvec_coll), vector_end(pvec_coll),
        1, fun_multiplies_int, &n_result);
    printf("product: %d\n", n_result);
    algo_accumulate_if(vector_begin(pvec_coll), vector_end(pvec_coll),
        0, fun_multiplies_int, &n_result);
    printf("product: %d\n", n_result);

    vector_destroy(pvec_coll);

    return 0;
}
