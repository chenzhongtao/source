/*
 * algo_mismatch.c
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
    vector_iterator_t it_v;
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;
    range_t r_result;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL || plist_l1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init(pvec_v2);
    list_init(plist_l1);

    for(i = 0; i < 6; ++i)
    {
        vector_push_back(pvec_v1, i * 5);
        vector_push_back(pvec_v2, i * 10);
    }
    for(i = 0; i < 8; ++i)
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
    printf("Vector v2 = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
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

    /* Test v1 and l1 for mismatch under identity */
    r_result = algo_mismatch(vector_begin(pvec_v1), vector_end(pvec_v1), list_begin(plist_l1));
    if(iterator_equal(r_result.it_begin, vector_end(pvec_v1)))
    {
        printf("The two ranges do not differ.\n");
    }
    else
    {
        printf("The first mismatch is between %d and %d.\n",
            *(int*)iterator_get_pointer(r_result.it_begin),
            *(int*)iterator_get_pointer(r_result.it_end));
    }

    /* Modifying l1 */
    list_insert(plist_l1, iterator_advance(list_begin(plist_l1), 2), 100);
    printf("Modified l1 = ( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, list_end(plist_l1));
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");

    /* Testing v1 with modified l1 for mismatch under identity */
    r_result = algo_mismatch(vector_begin(pvec_v1), vector_end(pvec_v1), list_begin(plist_l1));
    if(iterator_equal(r_result.it_begin, vector_end(pvec_v1)))
    {
        printf("The two ranges do not differ.\n");
    }
    else
    {
        printf("The first mismatch is between %d and %d.\n",
            *(int*)iterator_get_pointer(r_result.it_begin),
            *(int*)iterator_get_pointer(r_result.it_end));
    }

    /* Test v1 and v2 for mismatch under the binary predicate twice */
    r_result = algo_mismatch_if(vector_begin(pvec_v1), vector_end(pvec_v1),
        vector_begin(pvec_v2), _twice);
    if(iterator_equal(r_result.it_begin, vector_end(pvec_v1)))
    {
        printf("The two ranges do not differ under the binary predicate twice.\n");
    }
    else
    {
        printf("The first mismatch is between %d and %d.\n",
            *(int*)iterator_get_pointer(r_result.it_begin),
            *(int*)iterator_get_pointer(r_result.it_end));
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
