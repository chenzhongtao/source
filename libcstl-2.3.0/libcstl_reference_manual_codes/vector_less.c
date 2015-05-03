/*
 * vector_less.c
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
    vector_push_back(pvec_v1, 4);

    vector_push_back(pvec_v2, 1);
    vector_push_back(pvec_v2, 3);

    if(vector_less(pvec_v1, pvec_v2))
    {
        printf("Vector v1 is less than vector v2.\n");
    }
    else
    {
        printf("Vector v1 is not less than vector v2.\n");
    }

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);

    return 0;
}
