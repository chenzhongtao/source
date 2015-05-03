/*
 * mapfind.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>
#include <cstl/calgorithm.h>

static void _find_valud(const void* cpv_input, void* pv_output)
{
    if(*(int*)pair_second((pair_t*)cpv_input) == 3)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

int main(int argc, char* argv[])
{
    map_t* pmap_coll = create_map(int, int);
    map_iterator_t it_pos;

    if(pmap_coll == NULL)
    {
        return -1;
    }

    map_init(pmap_coll);

    *(int*)map_at(pmap_coll, 1) = 7;
    *(int*)map_at(pmap_coll, 2) = 4;
    *(int*)map_at(pmap_coll, 3) = 2;
    *(int*)map_at(pmap_coll, 4) = 3;
    *(int*)map_at(pmap_coll, 5) = 6;
    *(int*)map_at(pmap_coll, 6) = 1;
    *(int*)map_at(pmap_coll, 7) = 7;

    /* search an element with key 3 */
    it_pos = map_find(pmap_coll, 3);
    if(!iterator_equal(it_pos, map_end(pmap_coll)))
    {
        printf("%d : %d\n",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
    }
    /* search an element with value 3 */
    it_pos = algo_find_if(map_begin(pmap_coll), map_end(pmap_coll), _find_valud);
    if(!iterator_equal(it_pos, map_end(pmap_coll)))
    {
        printf("%d : %d\n",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
    }

    map_destroy(pmap_coll);

    return 0;
}
