/*
 * set3.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h> /* for fun_greater_int */

int main(int argc, char* argv[])
{
    set_t* pset_coll1 = create_set(int);
    set_t* pset_coll2 = create_set(int);
    set_iterator_t it_pos;
    size_t t_count = 0;


    if(pset_coll1 == NULL || pset_coll2 == NULL)
    {
        return -1;
    }

    /* empty set container and descending order */
    set_init_ex(pset_coll1, fun_greater_int);

    /* insert elements in random order */
    set_insert(pset_coll1, 4);
    set_insert(pset_coll1, 3);
    set_insert(pset_coll1, 5);
    set_insert(pset_coll1, 1);
    set_insert(pset_coll1, 6);
    set_insert(pset_coll1, 2);
    set_insert(pset_coll1, 5);

    /* iterate over all elements and print them */
    for(it_pos = set_begin(pset_coll1);
        !iterator_equal(it_pos, set_end(pset_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* insert 4 again */
    it_pos = set_insert(pset_coll1, 4);
    if(iterator_equal(it_pos, set_end(pset_coll1)))
    {
        printf("4 already exists\n");
    }
    else
    {
        printf("4 inserted as element %d\n",
            iterator_distance(set_begin(pset_coll1), it_pos));
    }

    /* initialize set_t with another and ascending order */
    set_init_copy_range(pset_coll2, set_begin(pset_coll1), set_end(pset_coll1));

    /* print all elements of the copy */
    for(it_pos = set_begin(pset_coll2);
        !iterator_equal(it_pos, set_end(pset_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* remove all elements up to element with value 3 */
    set_erase_range(pset_coll2, set_begin(pset_coll2), set_find(pset_coll2, 3));

    /* remove all elements with value 5 */
    t_count = set_erase(pset_coll2, 5);
    printf("%u elements removed\n", t_count);

    /* print all elements of the copy */
    for(it_pos = set_begin(pset_coll2);
        !iterator_equal(it_pos, set_end(pset_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    set_destroy(pset_coll1);
    set_destroy(pset_coll2);

    return 0;
}
