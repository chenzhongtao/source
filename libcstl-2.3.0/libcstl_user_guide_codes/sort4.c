/*
 * sort4.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <string.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _less_length(const void* cpv_first,
    const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = strlen((char*)cpv_first) < strlen((char*)cpv_second) ?
        true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_coll1 = create_vector(char*);
    vector_t* pvec_coll2 = create_vector(char*);
    iterator_t it_pos;

    if(pvec_coll1 == NULL || pvec_coll2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll1);
    vector_init(pvec_coll2);

    vector_push_back(pvec_coll1, "1xxx");
    vector_push_back(pvec_coll1, "2x");
    vector_push_back(pvec_coll1, "3x");
    vector_push_back(pvec_coll1, "4x");
    vector_push_back(pvec_coll1, "5xx");
    vector_push_back(pvec_coll1, "6xxxx");
    vector_push_back(pvec_coll1, "7xx");
    vector_push_back(pvec_coll1, "8xxx");
    vector_push_back(pvec_coll1, "9xx");
    vector_push_back(pvec_coll1, "10xxx");
    vector_push_back(pvec_coll1, "11");
    vector_push_back(pvec_coll1, "12");
    vector_push_back(pvec_coll1, "13");
    vector_push_back(pvec_coll1, "14xx");
    vector_push_back(pvec_coll1, "15");
    vector_push_back(pvec_coll1, "16");
    vector_push_back(pvec_coll1, "17");
    vector_assign(pvec_coll2, pvec_coll1);

    printf("on entry:\n");
    for(it_pos = vector_begin(pvec_coll1);
        !iterator_equal(it_pos, vector_end(pvec_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%s ", (char*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_sort_if(vector_begin(pvec_coll1),
        vector_end(pvec_coll1), _less_length);
    algo_stable_sort_if(vector_begin(pvec_coll2),
        vector_end(pvec_coll2), _less_length);
    printf("with algo_sort_if():\n");
    for(it_pos = vector_begin(pvec_coll1);
        !iterator_equal(it_pos, vector_end(pvec_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%s ", (char*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("with algo_stable_sort_if():\n");
    for(it_pos = vector_begin(pvec_coll2);
        !iterator_equal(it_pos, vector_end(pvec_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%s ", (char*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_destroy(pvec_coll1);
    vector_destroy(pvec_coll2);

    return 0;
}
