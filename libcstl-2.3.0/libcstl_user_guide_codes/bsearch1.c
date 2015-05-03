/*
 * bsearch1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(int);
    iterator_t it_pos;
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

    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    if(algo_binary_search(list_begin(plist_coll), list_end(plist_coll), 5))
    {
        printf("5 is present\n");
    }
    else
    {
        printf("5 is not present\n");
    }

    if(algo_binary_search(list_begin(plist_coll), list_end(plist_coll), 43))
    {
        printf("43 is present\n");
    }
    else
    {
        printf("43 is not present\n");
    }

    list_destroy(plist_coll);

    return 0;
}
