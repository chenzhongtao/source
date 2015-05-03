/*
 * vector_resize.c
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

    vector_push_back(pvec_v1, 10);
    vector_push_back(pvec_v1, 20);
    vector_push_back(pvec_v1, 30);

    vector_resize_elem(pvec_v1, 4, 40);
    printf("The size of v1 is %d\n", vector_size(pvec_v1));
    printf("The value of the last object is %d\n", *(int*)vector_back(pvec_v1));

    vector_resize(pvec_v1, 5);
    printf("The size of v1 is now %d\n", vector_size(pvec_v1));
    printf("The value of the last object is now %d\n", *(int*)vector_back(pvec_v1));

    vector_destroy(pvec_v1);

    return 0;
}
