/*
 * algo_unique.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

static void _mod_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) == abs(*(int*)cpv_second) ? true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    vector_iterator_t it_end;
    int i = 0;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    for(i = 0; i <= 3; ++i)
    {
        vector_push_back(pvec_v1, 5);
        vector_push_back(pvec_v1, -5);
    }
    for(i = 0; i <= 3; ++i)
    {
        vector_push_back(pvec_v1, 4);
    }
    vector_push_back(pvec_v1, 7);

    printf("Vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    it_end = algo_unique(vector_begin(pvec_v1), vector_end(pvec_v1));
    printf("Removing adjacent duplicates from vector v1 gives\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, it_end);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    it_end = algo_unique_if(vector_begin(pvec_v1), it_end, _mod_equal);
    printf("Removing adjacent duplicates from vector v1 under the mod_equal gives\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, it_end);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    it_end = algo_unique_if(vector_begin(pvec_v1), it_end, fun_greater_int);
    printf("Removing adjacent duplicates from vector v1 under the greater gives\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, it_end);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    vector_destroy(pvec_v1);

    return 0;
}
