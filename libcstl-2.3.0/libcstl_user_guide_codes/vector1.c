/*
 * vector1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    /* vector conatiner for integer elements */
    vector_t* pvec_coll = create_vector(int);
    int i = 0;

    if(pvec_coll == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);

    /* append elements with 1 to 6 */
    for(i = 1; i <= 6; ++i)
    {
        vector_push_back(pvec_coll, i);
    }

    /* print all elements followed by space */
    for(i = 0; i < vector_size(pvec_coll); ++i)
    {
        printf("%d ", *(int*)vector_at(pvec_coll, i));
    }
    printf("\n");

    vector_destroy(pvec_coll);

    return 0;
}
