/*
 * remove3.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    set_t* pset_coll = create_set(int);
    set_iterator_t it_pos;
    size_t t_num = 0;
    int i = 0;

    if(pset_coll == NULL)
    {
        return -1;
    }

    set_init(pset_coll);

    for(i = 1; i <= 9; ++i)
    {
        set_insert(pset_coll, i);
    }

    /* print all elements of set */
    for(it_pos = set_begin(pset_coll);
        !iterator_equal(it_pos, set_end(pset_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* remove all element with value 3 */
    t_num = set_erase(pset_coll, 3);
    printf("number of removed elements: %u.\n", t_num);

    /* printf all elements of the modified set */
    for(it_pos = set_begin(pset_coll);
        !iterator_equal(it_pos, set_end(pset_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    set_destroy(pset_coll);

    return 0;
}
