/*
 * algo_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _twice(const void* cpv_first, const void* cpv_second, void* pv_output);

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_t* pvec_v3 = create_vector(int);
    vector_iterator_t it_v;
    bool_t b_result = false;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL || pvec_v3 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init(pvec_v2);
    vector_init(pvec_v3);

    for(i = 0; i < 6; ++i)
    {
        vector_push_back(pvec_v1, i * 5);
        vector_push_back(pvec_v2, i * 5);
        vector_push_back(pvec_v3, i * 10);
    }

    printf("v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    printf("v2 = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    printf("v3 = ( ");
    for(it_v = vector_begin(pvec_v3);
        !iterator_equal(it_v, vector_end(pvec_v3));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Test v1 and v2 for equality under identity */
    if(algo_equal(vector_begin(pvec_v1), vector_end(pvec_v1), vector_begin(pvec_v2)))
    {
        printf("The vectors v1 and v2 are equal under equality.\n");
    }
    else
    {
        printf("The vectors v1 and v2 are not equal under equality.\n");
    }

    /* Test v1 and v3 for equality under identity */
    if(algo_equal(vector_begin(pvec_v1), vector_end(pvec_v1), vector_begin(pvec_v3)))
    {
        printf("The vectors v1 and v3 are equal under equality.\n");
    }
    else
    {
        printf("The vectors v1 and v3 are not equal under equality.\n");
    }

    /* Test v1 and v3 for equality under twice */
    if(algo_equal_if(vector_begin(pvec_v1), vector_end(pvec_v1),
        vector_begin(pvec_v3), _twice))
    {
        printf("The vectors v1 and v3 are equal under twice.\n");
    }
    else
    {
        printf("The vectors v1 and v3 are not equal under twice.\n");
    }

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    vector_destroy(pvec_v3);

    return 0;
}

static void _twice(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first * 2 == *(int*)cpv_second ? true : false;
}
