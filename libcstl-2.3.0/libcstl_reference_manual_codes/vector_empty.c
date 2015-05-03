/*
 * vector_empty.c
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

    if(vector_empty(pvec_v1))
    {
        printf("The vector is empty.\n");
    }
    else
    {
        printf("The vector is not empty.\n");
    }

    vector_destroy(pvec_v1);

    return 0;
}
