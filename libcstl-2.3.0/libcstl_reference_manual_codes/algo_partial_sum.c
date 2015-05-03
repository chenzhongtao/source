/*
 * algo_partial_sum.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/cnumeric.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_iterator_t it_v;
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;
    iterator_t it_end;

    if(pvec_v1 == NULL || pvec_v2 == NULL || plist_l1 == NULL)
    {
        return -1;
    }

    vector_init_n(pvec_v1, 10);
    vector_init_n(pvec_v2, 10);
    list_init_n(plist_l1, 10);

    algo_iota(list_begin(plist_l1), list_end(plist_l1), 1);
    printf("The input list l1 is:\n( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, list_end(plist_l1));
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");

    /* 
     * The first function for the partial sums of
     * elements in a list output to a vector.
     */
    it_end = algo_partial_sum(list_begin(plist_l1), list_end(plist_l1),
        vector_begin(pvec_v1));
    printf("The output vector conatining the partial sums is:\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, it_end);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* 
     * The second function used to compute
     * the partial product of the elements in a list.
     */
    it_end = algo_partial_sum_if(list_begin(plist_l1), list_end(plist_l1),
        vector_begin(pvec_v2), fun_multiplies_int);
    printf("The output vector with the partial products is:\n( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, it_end);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Computation of partial sums in place */
    it_end = algo_partial_sum(list_begin(plist_l1), list_end(plist_l1), list_begin(plist_l1));
    printf("The in place output partial_sum list l1 is:\n( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, it_end);
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    list_destroy(plist_l1);

    return 0;
}
