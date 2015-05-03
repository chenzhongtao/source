/*
 * map2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    map_t* pmap_stocks = create_map(char*, double);
    map_iterator_t it_pos;

    if(pmap_stocks == NULL)
    {
        return -1;
    }

    map_init(pmap_stocks);

    *(double*)map_at(pmap_stocks, "Google") = 834.50;
    *(double*)map_at(pmap_stocks, "IBM") = 431.93;
    *(double*)map_at(pmap_stocks, "Apple") = 557.28;
    *(double*)map_at(pmap_stocks, "MS") = 691.03;
    *(double*)map_at(pmap_stocks, "Oracle") = 670.37;

    /* print all elements */
    for(it_pos = map_begin(pmap_stocks);
        !iterator_equal(it_pos, map_end(pmap_stocks));
        it_pos = iterator_next(it_pos))
    {
        printf("stock:%s\tprice:%lf\n",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_pos)),
            *(double*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
    }
    printf("\n");

    /* all price double */
    for(it_pos = map_begin(pmap_stocks);
        !iterator_equal(it_pos, map_end(pmap_stocks));
        it_pos = iterator_next(it_pos))
    {
        *(double*)pair_second((pair_t*)iterator_get_pointer(it_pos)) *= 2;
    }

    /* print all elements */
    for(it_pos = map_begin(pmap_stocks);
        !iterator_equal(it_pos, map_end(pmap_stocks));
        it_pos = iterator_next(it_pos))
    {
        printf("stock:%s\tprice:%lf\n",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_pos)),
            *(double*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
    }
    printf("\n");

    /* rename the key from "MS" to "Microsoft" */
    *(double*)map_at(pmap_stocks, "Microsoft") = *(double*)map_at(pmap_stocks, "MS");
    map_erase(pmap_stocks, "MS");

    /* print all elements */
    for(it_pos = map_begin(pmap_stocks);
        !iterator_equal(it_pos, map_end(pmap_stocks));
        it_pos = iterator_next(it_pos))
    {
        printf("stock:%s\tprice:%lf\n",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_pos)),
            *(double*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
    }
    printf("\n");

    map_destroy(pmap_stocks);

    return 0;
}
