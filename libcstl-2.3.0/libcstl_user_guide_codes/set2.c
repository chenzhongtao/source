/*
 * set2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>

int main(int argc, char* argv[])
{
    set_t* pset_coll = create_set(int);
    set_iterator_t it_lower;
    set_iterator_t it_upper;
    range_t t_range;

    if(pset_coll == NULL)
    {
        return -1;
    }

    set_init(pset_coll);

    set_insert(pset_coll, 1);
    set_insert(pset_coll, 2);
    set_insert(pset_coll, 4);
    set_insert(pset_coll, 5);
    set_insert(pset_coll, 6);

    it_lower = set_lower_bound(pset_coll, 3);
    it_upper = set_upper_bound(pset_coll, 3);
    t_range = set_equal_range(pset_coll, 3);
    printf("set_lower_bound(3) : %d\n", *(int*)iterator_get_pointer(it_lower));
    printf("set_upper_bound(3) : %d\n", *(int*)iterator_get_pointer(it_upper));
    printf("set_equal_range(3) : %d %d\n",
        *(int*)iterator_get_pointer(t_range.it_begin),
        *(int*)iterator_get_pointer(t_range.it_end));

    printf("\n");
    it_lower = set_lower_bound(pset_coll, 5);
    it_upper = set_upper_bound(pset_coll, 5);
    t_range = set_equal_range(pset_coll, 5);
    printf("set_lower_bound(5) : %d\n", *(int*)iterator_get_pointer(it_lower));
    printf("set_upper_bound(5) : %d\n", *(int*)iterator_get_pointer(it_upper));
    printf("set_equal_range(5) : %d %d\n",
        *(int*)iterator_get_pointer(t_range.it_begin),
        *(int*)iterator_get_pointer(t_range.it_end));

    set_destroy(pset_coll);

    return 0;
}
