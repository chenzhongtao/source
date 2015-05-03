/*
 * algo_replace_copy.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;
    int i = 0;

    if(pvec_v1 == NULL || plist_l1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    list_init_n(plist_l1, 15);

    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    for(i = 0; i < 4; ++i)
    {
        vector_push_back(pvec_v1, 7);
    }

    algo_random_shuffle(vector_begin(pvec_v1), vector_end(pvec_v1));
    for(i = 0; i < 16; ++i)
    {
        vector_push_back(pvec_v1, 1);
    }

    printf("The original vector v1 is:\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* 
     * Replace elements in one part of a vector with a value of 7
     * with a value 70 and copy into another part of the vector
     */
    algo_replace_copy(vector_begin(pvec_v1), iterator_next_n(vector_begin(pvec_v1), 14),
        iterator_prev_n(vector_end(pvec_v1), 15), 7, 70);

    printf("The vector v1 with a value 70 replacing that of 7 is:\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /*
     * Replace elements in a vector with a value of 70
     * with a value of 1 and copy into a list
     */
    algo_replace_copy(vector_begin(pvec_v1), iterator_next_n(vector_begin(pvec_v1), 14),
        list_begin(plist_l1), 7, 1);

    printf("The list copy l1 of v1 with the value 0 replacing that of 7 is:\n( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, list_end(plist_l1));
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");

    vector_destroy(pvec_v1);
    list_destroy(plist_l1);

    return 0;
}
