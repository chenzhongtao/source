/*
 * vector_at.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    int* pn_i = NULL;
    int n_j = 0;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    vector_push_back(pvec_v1, 10);
    vector_push_back(pvec_v1, 20);

    pn_i = (int*)vector_at(pvec_v1, 0);
    n_j = *(int*)vector_at(pvec_v1, 1);
    printf("The first element is %d\n", *pn_i);
    printf("The second element is %d\n", n_j);

    vector_destroy(pvec_v1);

    return 0;
}
