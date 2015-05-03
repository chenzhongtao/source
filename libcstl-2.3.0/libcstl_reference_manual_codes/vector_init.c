/*
 * vector_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v0 = create_vector(int);
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_t* pvec_v3 = create_vector(int);
    vector_t* pvec_v4 = create_vector(int);
    vector_iterator_t it_v;

    if(pvec_v0 == NULL || pvec_v1 == NULL || pvec_v2 == NULL || pvec_v3 == NULL || pvec_v4 == NULL)
    {
        return -1;
    }

    /* Create an empty vector v0 */
    vector_init(pvec_v0);

    /* Create a vector v1 with 3 elements of default value 0 */
    vector_init_n(pvec_v1, 3);
    
    /* Create a vector v2 with 5 elements of value 2 */
    vector_init_elem(pvec_v2, 5, 2);

    /* Create a copy, vector v3, of vector v2 */
    vector_init_copy(pvec_v3, pvec_v2);

    /* Create a vector v4 by copying the range v4[first, last) */
    vector_init_copy_range(pvec_v4, iterator_next(vector_begin(pvec_v3)), iterator_next_n(vector_begin(pvec_v3), 3));

    printf("v1 =");
    for(it_v = vector_begin(pvec_v1); !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    printf("v2 =");
    for(it_v = vector_begin(pvec_v2); !iterator_equal(it_v, vector_end(pvec_v2)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    printf("v3 =");
    for(it_v = vector_begin(pvec_v3); !iterator_equal(it_v, vector_end(pvec_v3)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    printf("v4 =");
    for(it_v = vector_begin(pvec_v4); !iterator_equal(it_v, vector_end(pvec_v4)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_destroy(pvec_v0);
    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    vector_destroy(pvec_v3);
    vector_destroy(pvec_v4);

    return 0;
}
