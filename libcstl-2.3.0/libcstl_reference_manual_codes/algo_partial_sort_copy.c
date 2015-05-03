/*
 * algo_partial_sort_copy.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_iterator_t it_v;
    vector_iterator_t it_end;
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL || plist_l1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init(pvec_v2);
    list_init(plist_l1);

    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    algo_random_shuffle(vector_begin(pvec_v1), vector_end(pvec_v1));

    list_push_back(plist_l1, 60);
    list_push_back(plist_l1, 50);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 30);
    list_push_back(plist_l1, 40);
    list_push_back(plist_l1, 10);

    printf("Vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    printf("List l1 = ( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, list_end(plist_l1));
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");

    /* Copying a partially sorted copy of l1 into v1 */
    it_end = algo_partial_sort_copy(list_begin(plist_l1), list_end(plist_l1),
        vector_begin(pvec_v1), iterator_next_n(vector_begin(pvec_v1), 3));
    printf("List l1 vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("The first v1 element one position beyond\n"
           "the first l1 element inserted was %d.\n",
           *(int*)iterator_get_pointer(it_end));

    /* Copying a partially sorted with greater copy of l1 to v2 */
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec_v2, i);
    }
    algo_random_shuffle(vector_begin(pvec_v2), vector_end(pvec_v2));
    it_end = algo_partial_sort_copy_if(list_begin(plist_l1), list_end(plist_l1),
        vector_begin(pvec_v2), iterator_next_n(vector_begin(pvec_v2), 6),
        fun_greater_int);
    printf("List l1 vector v2 = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("The first v2 element one position beyond\n"
           "the first l1 element inserted was %d.\n",
           *(int*)iterator_get_pointer(it_end));

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    list_destroy(plist_l1);

    return 0;
}
