/*
 * algo_unique_copy.c
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

    for(i = 0; i <= 1; ++i)
    {
        vector_push_back(pvec_v1, 5);
        vector_push_back(pvec_v1, -5);
    }
    for(i = 0; i <= 2; ++i)
    {
        vector_push_back(pvec_v1, 4);
    }
    vector_push_back(pvec_v1, 7);
    for(i = 0; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, 10);
    }

    printf("Vector v1 is\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    it_end = algo_unique_copy(vector_begin(pvec_v1),
        iterator_next_n(vector_begin(pvec_v1), 8),
        iterator_next_n(vector_begin(pvec_v1), 8));
    printf("Copying the first half of the vector to the second half\n"
           "while removing adjacent duplicates gives\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, it_end);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    for(i = 0; i <= 7; ++i)
    {
        vector_push_back(pvec_v1, 10);
    }

    it_end = algo_unique_copy_if(vector_begin(pvec_v1),
        iterator_next_n(vector_begin(pvec_v1), 14),
        iterator_next_n(vector_begin(pvec_v1), 14), _mod_equal);
    printf("Copying the first half of the vector to the second half\n"
           "while removing adjacent duplicates under mod_equal gives\n( ");
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
