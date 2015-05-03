/*
 * iterator_set_value.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    iterator_t it_vec;
    iterator_t it_pos;
    int n_value = 0;
    int i = 0;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    for(i = 0; i < 6; ++i)
    {
        vector_push_back(pvec_v1, i * 2);
    }

    printf("The vector v1 is ( ");
    for(it_vec = vector_begin(pvec_v1);
        !iterator_equal(it_vec, vector_end(pvec_v1));
        it_vec = iterator_next(it_vec))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_vec));
    }
    printf(")\n");

    it_pos = vector_begin(pvec_v1);
    n_value = 100;
    iterator_set_value(it_pos, &n_value);

    it_pos = iterator_next_n(it_pos, 3);
    n_value = -999;
    iterator_set_value(it_pos, &n_value);

    printf("After setting value, the vector v1 is ( ");
    for(it_vec = vector_begin(pvec_v1);
        !iterator_equal(it_vec, vector_end(pvec_v1));
        it_vec = iterator_next(it_vec))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_vec));
    }
    printf(")\n");

    vector_destroy(pvec_v1);

    return 0;
}
