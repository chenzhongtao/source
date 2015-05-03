/*
 * algo_min_element.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _mod_lesser(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) < abs(*(int*)cpv_second) ? true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    int i = 0;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    for(i = 0; i <= 3; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    for(i = 1; i <= 4; ++i)
    {
        vector_push_back(pvec_v1, i * -2);
    }

    printf("Vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    it_v = algo_min_element(vector_begin(pvec_v1), vector_end(pvec_v1));
    printf("The smallest element in v1 is : %d.\n", *(int*)iterator_get_pointer(it_v));

    it_v = algo_min_element_if(vector_begin(pvec_v1),
        vector_end(pvec_v1), _mod_lesser);
    printf("The smallest element in v1 under the mod_lesser is : %d.\n",
        *(int*)iterator_get_pointer(it_v));

    vector_destroy(pvec_v1);

    return 0;
}
