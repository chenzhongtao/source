/*
 * find2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_pos1;
    list_iterator_t it_pos2;
    int i = 0;

    if(plist_coll == NULL)
    {
        return -1;
    }

    list_init(plist_coll);

    for(i = 1; i <= 9; ++i)
    {
        list_push_back(plist_coll, i);
    }
    for(i = 1; i <= 9; ++i)
    {
        list_push_back(plist_coll, i);
    }
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* find first element with value 4 */
    it_pos1 = algo_find(list_begin(plist_coll), list_end(plist_coll), 4);

    /* find second element with value 4 */
    if(!iterator_equal(it_pos1, list_end(plist_coll)))
    {
        it_pos2 = algo_find(iterator_next(it_pos1), list_end(plist_coll), 4);
    }

    /* print all elements from first to second 4 */
    if(!iterator_equal(it_pos1, list_end(plist_coll)) &&
       !iterator_equal(it_pos2, list_end(plist_coll)))
    {
        for(it_pos = it_pos1;
            !iterator_equal(it_pos, iterator_next(it_pos2));
            it_pos = iterator_next(it_pos))
        {
            printf("%d ", *(int*)iterator_get_pointer(it_pos));
        }
        printf("\n");
    }

    list_destroy(plist_coll);

    return 0;
}
