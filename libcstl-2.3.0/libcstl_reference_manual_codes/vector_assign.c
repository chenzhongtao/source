/*
 * vector_assign.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_t* pvec_v3 = create_vector(int);
    vector_t* pvec_v4 = create_vector(int);
    vector_iterator_t it_v;

    if(pvec_v1 == NULL || pvec_v2 == NULL || pvec_v3 == NULL || pvec_v4 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init(pvec_v2);
    vector_init(pvec_v3);
    vector_init(pvec_v4);

    vector_push_back(pvec_v1, 10);
    vector_push_back(pvec_v1, 20);
    vector_push_back(pvec_v1, 30);
    vector_push_back(pvec_v1, 40);
    vector_push_back(pvec_v1, 50);

    printf("v1 =");
    for(it_v = vector_begin(pvec_v1); !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_assign(pvec_v2, pvec_v1);
    printf("v2 =");
    for(it_v = vector_begin(pvec_v2); !iterator_equal(it_v, vector_end(pvec_v2)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_assign_range(pvec_v3, vector_begin(pvec_v1), vector_end(pvec_v1));
    printf("v3 =");
    for(it_v = vector_begin(pvec_v3); !iterator_equal(it_v, vector_end(pvec_v3)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_assign_elem(pvec_v4, 7, 4);
    printf("v4 =");
    for(it_v = vector_begin(pvec_v4); !iterator_equal(it_v, vector_end(pvec_v4)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    vector_destroy(pvec_v3);
    vector_destroy(pvec_v4);

    return 0;
}
