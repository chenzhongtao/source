/*
 * vector_swap.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);

    if(pvec_v1 == NULL || pvec_v2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init(pvec_v2);

    vector_push_back(pvec_v1, 1);
    vector_push_back(pvec_v1, 2);
    vector_push_back(pvec_v1, 3);

    vector_push_back(pvec_v2, 10);
    vector_push_back(pvec_v2, 20);

    printf("The number of elements in v1 = %d\n", vector_size(pvec_v1));
    printf("The number of elements in v2 = %d\n", vector_size(pvec_v2));
    printf("\n");

    vector_swap(pvec_v1, pvec_v2);

    printf("The number of elements in v1 = %d\n", vector_size(pvec_v1));
    printf("The number of elements in v2 = %d\n", vector_size(pvec_v2));

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);

    return 0;
}
