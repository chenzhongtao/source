/*
 * multiset1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    /* multiset container for int values */
    multiset_t* pmset_coll = create_multiset(int);
    multiset_iterator_t it_pos;

    if(pmset_coll == NULL)
    {
        return -1;
    }

    multiset_init(pmset_coll);

    /*
     * insert elements for 1 to 6 in arbitray order
     * - value 1 gets inserted twice
     */
    multiset_insert(pmset_coll, 3);
    multiset_insert(pmset_coll, 1);
    multiset_insert(pmset_coll, 6);
    multiset_insert(pmset_coll, 4);
    multiset_insert(pmset_coll, 1);
    multiset_insert(pmset_coll, 2);
    multiset_insert(pmset_coll, 5);

    /*
     * print all elements
     * - iterate over all elements
     */
    for(it_pos = multiset_begin(pmset_coll);
        !iterator_equal(it_pos, multiset_end(pmset_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    multiset_destroy(pmset_coll);

    return 0;
}
