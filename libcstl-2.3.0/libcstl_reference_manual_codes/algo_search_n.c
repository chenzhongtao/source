/*
 * algo_search_n.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _twice(const void* cpv_first, const void* cpv_second, void* pv_output);

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

    for(i = 0; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i * 5);
    }
    for(i = 0; i <= 2; ++i)
    {
        vector_push_back(pvec_v1, 5);
    }
    for(i = 0; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i * 5);
    }
    for(i = 0; i <= 3; ++i)
    {
        vector_push_back(pvec_v1, 10);
    }
    for(i = 0; i <= 2; ++i)
    {
        vector_push_back(pvec_v1, 5);
    }

    printf("Vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Searching v1 for first match to (5 5 5) under identity */
    it_v = algo_search_n(vector_begin(pvec_v1), vector_end(pvec_v1), 3, 5);
    if(iterator_equal(it_v, vector_end(pvec_v1)))
    {
        printf("There is no match for a sequence (5 5 5) in v1.\n");
    }
    else
    {
        printf("There is at least one match of a sequence (5 5 5)"
               " in v1 and the first one begins at position %d.\n",
               iterator_distance(vector_begin(pvec_v1), it_v));
    }

    /* Searching v1 for first match to (5 5 5 5) under twice */
    it_v = algo_search_n_if(vector_begin(pvec_v1), vector_end(pvec_v1), 4, 5, _twice);
    if(iterator_equal(it_v, vector_end(pvec_v1)))
    {
        printf("There is no match for a sequence (5 5 5 5) in v1"
               " under the equivalence predicate twice.\n");
    }
    else
    {
        printf("There is a match of a sequence (5 5 5 5) "
               "under the equivalence predicate twice"
               " in v1 and the first one begins at position %d.\n",
               iterator_distance(vector_begin(pvec_v1), it_v));
    }

    vector_destroy(pvec_v1);

    return 0;
}

static void _twice(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first == *(int*)cpv_second * 2 ? true : false;
}
