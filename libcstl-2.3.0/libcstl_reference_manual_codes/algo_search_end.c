/*
 * algo_search_end.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

static void _twice(const void* cpv_first, const void* cpv_second, void* pv_output);

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    list_t* plist_l1 = create_list(int);
    vector_iterator_t it_v;
    list_iterator_t it_l;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL || plist_l1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init(pvec_v2);
    list_init(plist_l1);

    for(i = 0; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i * 5);
    }
    for(i = 0; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i * 5);
    }
    for(i = 2; i <= 4; ++i)
    {
        vector_push_back(pvec_v2, i * 10);
    }
    for(i = 1; i <= 4; ++i)
    {
        list_push_back(plist_l1, i * 5);
    }

    printf("Vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("List l1 = ( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, list_end(plist_l1));
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");
    printf("Vector v2 = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Searching v1 for first match to l1 under identity */
    it_v = algo_search_end(vector_begin(pvec_v1), vector_end(pvec_v1),
        list_begin(plist_l1), list_end(plist_l1));

    if(iterator_equal(it_v, vector_end(pvec_v1)))
    {
        printf("There is no match of l1 in v1.\n");
    }
    else
    {
        printf("There is at least one match of l1 in v1\n"
               "and the last one begins at position %d.\n",
               iterator_distance(vector_begin(pvec_v1), it_v));
    }

    /* Searching v1 for a match to v2 under the binary predicate twice */
    it_v = algo_search_end_if(vector_begin(pvec_v1), vector_end(pvec_v1),
        vector_begin(pvec_v2), vector_end(pvec_v2), _twice);
    if(iterator_equal(it_v, vector_end(pvec_v1)))
    {
        printf("There is no match of v2 in v1.\n");
    }
    else
    {
        printf("There is a sequence of elements in v1 that are equivalent\n"
               "to those in v2 under the binary predicate twice\n"
               "and the last one begins at position %d.\n",
                iterator_distance(vector_begin(pvec_v1), it_v));
    }

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    list_destroy(plist_l1);

    return 0;
}

static void _twice(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first * 2 == *(int*)cpv_second ? true : false;
}
