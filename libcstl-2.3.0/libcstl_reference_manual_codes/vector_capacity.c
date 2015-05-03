/*
 * vector_capacity.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    vector_push_back(pvec_v1, 1);
    printf("The length of storage allocated is %d.\n", vector_capacity(pvec_v1));

    vector_push_back(pvec_v1, 2);
    vector_push_back(pvec_v1, 3);
    printf("The length of storage allocated is now %d.\n", vector_capacity(pvec_v1));

    vector_destroy(pvec_v1);

    return 0;
}
