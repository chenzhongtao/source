/*
 * algo_inner_product.c
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
    vector_t* pvec_v3 = create_vector(int);
    vector_iterator_t it_v;
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;
    int i = 0;
    int n_result = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL || pvec_v3 == NULL || plist_l1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init_n(pvec_v2, 7);
    vector_init_n(pvec_v3, 7);
    list_init(plist_l1);

    for(i = 1; i <= 7; ++i)
    {
        vector_push_back(pvec_v1, i);
        list_push_back(plist_l1, i);
    }

    printf("The original vector v1 is:\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("The original list l1 is:\n( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, list_end(plist_l1));
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");

    /* The first function for the inner product */
    algo_inner_product(vector_begin(pvec_v1), vector_end(pvec_v1),
        list_begin(plist_l1), 0, &n_result);

    printf("The inner_product of the vector v1 and the list l1 is: %d.\n", n_result);

    /* Constructing a vector of partial inner_products between v1 and l1 */
    for(it_v = vector_begin(pvec_v1), i = 0;
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v), ++i)
    {
        algo_inner_product(vector_begin(pvec_v1), iterator_next(it_v),
            list_begin(plist_l1), 0, vector_at(pvec_v2, i));
    }

    printf("The vector of partial inner_products between v1 and l1 is:\n( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* The second function used to compute the product of the element-wise sums */
    algo_inner_product_if(vector_begin(pvec_v1), vector_end(pvec_v1),
        list_begin(plist_l1), 1, fun_multiplies_int, fun_plus_int, &n_result);

    printf("The sum of the element-wise products of v1 and l1 is: %d.\n", n_result);

    /* Constructing a vector of partial sums of element-wise products */
    for(it_v = vector_begin(pvec_v1), i = 0;
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v), ++i)
    {
        algo_inner_product_if(vector_begin(pvec_v1), iterator_next(it_v),
            list_begin(plist_l1), 1, fun_multiplies_int, fun_plus_int, vector_at(pvec_v3, i));
    }

    printf("The vector of partial sums of element-wise products between v1 and l1 is:\n( ");
    for(it_v = vector_begin(pvec_v3);
        !iterator_equal(it_v, vector_end(pvec_v3));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    vector_destroy(pvec_v3);
    list_destroy(plist_l1);

    return 0;
}
