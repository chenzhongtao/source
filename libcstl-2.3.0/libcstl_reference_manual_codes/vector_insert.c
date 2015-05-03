/*
 * vector_insert.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_iterator_t it_v;

    if(pvec_v1 == NULL || pvec_v2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    vector_push_back(pvec_v1, 10);
    vector_push_back(pvec_v1, 20);
    vector_push_back(pvec_v1, 30);

    vector_init_copy(pvec_v2, pvec_v1);

    printf("v1 =");
    for(it_v = vector_begin(pvec_v1); !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_insert(pvec_v1, iterator_next(vector_begin(pvec_v1)), 40);
    printf("v1 =");
    for(it_v = vector_begin(pvec_v1); !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_insert_n(pvec_v1, iterator_next_n(vector_begin(pvec_v1), 2), 4, 50);
    printf("v1 =");
    for(it_v = vector_begin(pvec_v1); !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_insert_range(pvec_v1, iterator_next(vector_begin(pvec_v1)), vector_begin(pvec_v2), vector_end(pvec_v2));
    printf("v1 =");
    for(it_v = vector_begin(pvec_v1); !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);

    return 0;
}
