/*
 * vector_begin.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    vector_push_back(pvec_v1, 1);
    vector_push_back(pvec_v1, 2);

    printf("The vector v1 contains elements:");
    it_v = vector_begin(pvec_v1);
    for(; !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    printf("The vector v1 now contains elements:");
    it_v = vector_begin(pvec_v1);
    *(int*)iterator_get_pointer(it_v) = 20;
    for(; !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_destroy(pvec_v1);

    return 0;
}
