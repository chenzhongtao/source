/*
 * find1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(int);
    list_iterator_t it_pos;
    list_iterator_t it_pos25;
    list_iterator_t it_pos35;
    int i = 0;

    if(plist_coll == NULL)
    {
        return -1;
    }

    list_init(plist_coll);

    /* insert elements from 20 to 40 */
    for(i = 20; i <= 40; ++i)
    {
        list_push_back(plist_coll, i);
    }

    /*
     * find position of element with value 3
     * - there is none, so it_pos gets end()
     */
    it_pos = algo_find(list_begin(plist_coll), list_end(plist_coll), 3);

    /*
     * reverse the order of element between found element and then end
     * - because the it_pos is end(), it reverses an empty range
     */
    algo_reverse(it_pos, list_end(plist_coll));

    /* find the position of value 25 and 35 */
    it_pos25 = algo_find(list_begin(plist_coll), list_end(plist_coll), 25);
    it_pos35 = algo_find(list_begin(plist_coll), list_end(plist_coll), 35);

    /* 
     * print the maximum of corresponding range
     * - note: including pos25 and exculding pos35
     */
    printf("max: %d\n", *(int*)iterator_get_pointer(algo_max_element(it_pos25, it_pos35)));

    list_destroy(plist_coll);

    return 0;
}
