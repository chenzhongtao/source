/*
 * map1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    /* map container for c-string/double value */
    map_t* pmap_coll = create_map(char*, double);
    map_iterator_t it_pos;

    if(pmap_coll == NULL)
    {
        return -1;
    }

    map_init(pmap_coll);

    /* insert some element into the collection */
    *(double*)map_at(pmap_coll, "VAT") = 0.15;
    *(double*)map_at(pmap_coll, "Pi") = 3.1415;
    *(double*)map_at(pmap_coll, "an arbitray number") = 445.903;
    *(double*)map_at(pmap_coll, "Null") = 0.0;

    /*
     * print all element values
     * - iterate over all elements
     * - element member first is key
     * - element member second is value
     */
    for(it_pos = map_begin(pmap_coll);
        !iterator_equal(it_pos, map_end(pmap_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("key: \"%s\" value: %lf\n",
            (char*)pair_first(iterator_get_pointer(it_pos)),
            *(double*)pair_second(iterator_get_pointer(it_pos)));
    }

    map_destroy(pmap_coll);

    return 0;
}
