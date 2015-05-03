/*
 * hash_map1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phmap_stocks = create_hash_map(char*, double);
    hash_map_iterator_t it_pos;

    if(phmap_stocks == NULL)
    {
        return -1;
    }

    hash_map_init(phmap_stocks);

    *(double*)hash_map_at(phmap_stocks, "Google") = 834.50;
    *(double*)hash_map_at(phmap_stocks, "IBM") = 431.93;
    *(double*)hash_map_at(phmap_stocks, "Apple") = 557.28;
    *(double*)hash_map_at(phmap_stocks, "MS") = 691.03;
    *(double*)hash_map_at(phmap_stocks, "Oracle") = 670.37;

    /* print all elements */
    for(it_pos = hash_map_begin(phmap_stocks);
        !iterator_equal(it_pos, hash_map_end(phmap_stocks));
        it_pos = iterator_next(it_pos))
    {
        printf("stock:%s\tprice:%lf\n",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_pos)),
            *(double*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
    }
    printf("\n");

    /* all price double */
    for(it_pos = hash_map_begin(phmap_stocks);
        !iterator_equal(it_pos, hash_map_end(phmap_stocks));
        it_pos = iterator_next(it_pos))
    {
        *(double*)pair_second((pair_t*)iterator_get_pointer(it_pos)) *= 2;
    }

    /* print all elements */
    for(it_pos = hash_map_begin(phmap_stocks);
        !iterator_equal(it_pos, hash_map_end(phmap_stocks));
        it_pos = iterator_next(it_pos))
    {
        printf("stock:%s\tprice:%lf\n",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_pos)),
            *(double*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
    }
    printf("\n");

    /* rename the key from "MS" to "Microsoft" */
    *(double*)hash_map_at(phmap_stocks, "Microsoft") = *(double*)hash_map_at(phmap_stocks, "MS");
    hash_map_erase(phmap_stocks, "MS");

    /* print all elements */
    for(it_pos = hash_map_begin(phmap_stocks);
        !iterator_equal(it_pos, hash_map_end(phmap_stocks));
        it_pos = iterator_next(it_pos))
    {
        printf("stock:%s\tprice:%lf\n",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_pos)),
            *(double*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
    }
    printf("\n");

    hash_map_destroy(phmap_stocks);

    return 0;
}
