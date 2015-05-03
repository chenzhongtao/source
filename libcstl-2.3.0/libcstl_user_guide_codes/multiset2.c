/*
 * multiset2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h> /* for fun_greater_int */

int main(int argc, char* argv[])
{
    multiset_t* pmset_coll1 = create_multiset(int);
    multiset_t* pmset_coll2 = create_multiset(int);
    multiset_iterator_t it_pos;
    size_t t_count = 0;


    if(pmset_coll1 == NULL || pmset_coll2 == NULL)
    {
        return -1;
    }

    /* empty multiset container and descending order */
    multiset_init_ex(pmset_coll1, fun_greater_int);

    /* insert elements in random order */
    multiset_insert(pmset_coll1, 4);
    multiset_insert(pmset_coll1, 3);
    multiset_insert(pmset_coll1, 5);
    multiset_insert(pmset_coll1, 1);
    multiset_insert(pmset_coll1, 6);
    multiset_insert(pmset_coll1, 2);
    multiset_insert(pmset_coll1, 5);

    /* iterate over all elements and print them */
    for(it_pos = multiset_begin(pmset_coll1);
        !iterator_equal(it_pos, multiset_end(pmset_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* insert 4 again */
    it_pos = multiset_insert(pmset_coll1, 4);
    if(iterator_equal(it_pos, multiset_end(pmset_coll1)))
    {
        printf("4 already exists\n");
    }
    else
    {
        printf("4 inserted as element %d\n",
            iterator_distance(multiset_begin(pmset_coll1), it_pos));
    }

    /* initialize multiset_t with another and ascending order */
    multiset_init_copy_range(pmset_coll2,
        multiset_begin(pmset_coll1), multiset_end(pmset_coll1));

    /* print all elements of the copy */
    for(it_pos = multiset_begin(pmset_coll2);
        !iterator_equal(it_pos, multiset_end(pmset_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* remove all elements up to element with value 3 */
    multiset_erase_range(pmset_coll2,
        multiset_begin(pmset_coll2), multiset_find(pmset_coll2, 3));

    /* remove all elements with value 5 */
    t_count = multiset_erase(pmset_coll2, 5);
    printf("%u elements removed\n", t_count);

    /* print all elements of the copy */
    for(it_pos = multiset_begin(pmset_coll2);
        !iterator_equal(it_pos, multiset_end(pmset_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    multiset_destroy(pmset_coll1);
    multiset_destroy(pmset_coll2);

    return 0;
}
