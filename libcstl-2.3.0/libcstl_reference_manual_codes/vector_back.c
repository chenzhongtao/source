/*
 * vector_back.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    int* pn_i = NULL;
    int* pn_j = NULL;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    vector_push_back(pvec_v1, 10);
    vector_push_back(pvec_v1, 11);

    pn_i = (int*)vector_back(pvec_v1);
    pn_j = (int*)vector_back(pvec_v1);

    printf("The last integer of v1 is %d\n", *pn_i);
    (*pn_i)++;
    printf("The modified last integer of v1 is %d\n", *pn_j);

    vector_destroy(pvec_v1);

    return 0;
}
