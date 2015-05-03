/*
 * vector_erase.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

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

    vector_erase(pvec_v1, vector_begin(pvec_v1));
    printf("v1 =");
    for(it_v = vector_begin(pvec_v1); !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_erase_range(pvec_v1, iterator_next(vector_begin(pvec_v1)), iterator_next_n(vector_begin(pvec_v1), 3));
    printf("v1 =");
    for(it_v = vector_begin(pvec_v1); !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    printf("\n");

    vector_destroy(pvec_v1);

    return 0;
}
