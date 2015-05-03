/*
 * findof1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _doubled(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first == *(int*)cpv_second * 2 ? true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    list_t* plist_searchcoll = create_list(int);
    iterator_t it_pos;
    int i = 0;

    if(pvec_coll == NULL || plist_searchcoll == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);
    list_init(plist_searchcoll);

    for(i = 1; i <= 11; ++i)
    {
        vector_push_back(pvec_coll, i);
    }
    for(i = 3; i <= 5; ++i)
    {
        list_push_back(plist_searchcoll, i);
    }

    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    for(it_pos = list_begin(plist_searchcoll);
        !iterator_equal(it_pos, list_end(plist_searchcoll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* search first occurrence of an element of searchcoll in coll */
    it_pos = algo_find_first_of(vector_begin(pvec_coll), vector_end(pvec_coll),
        list_begin(plist_searchcoll), list_end(plist_searchcoll));
    if(!iterator_equal(it_pos, vector_end(pvec_coll)))
    {
        printf("first element of searchcoll in coll is element %d\n",
            iterator_distance(vector_begin(pvec_coll), it_pos) + 1);
    }

    it_pos = algo_find_first_of_if(vector_begin(pvec_coll), vector_end(pvec_coll),
        list_begin(plist_searchcoll), list_end(plist_searchcoll), _doubled);
    if(!iterator_equal(it_pos, vector_end(pvec_coll)))
    {
        printf("first doubled element of searchcoll in coll is element %d\n",
            iterator_distance(vector_begin(pvec_coll), it_pos) + 1);
    }

    vector_destroy(pvec_coll);
    list_destroy(plist_searchcoll);

    return 0;
}
