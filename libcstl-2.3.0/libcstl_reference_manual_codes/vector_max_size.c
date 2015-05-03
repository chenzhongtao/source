/*
 * vector_max_size.c
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

    printf("The maximum possible length of the vector is %d.\n", vector_max_size(pvec_v1));

    vector_destroy(pvec_v1);

    return 0;
}
