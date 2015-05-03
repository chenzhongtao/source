/*
 * hash_map_max_size.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);

    if(phm_hm1 == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);

    printf("The maximum possible length of the hash_map hm1 is: %d.\n",
        hash_map_max_size(phm_hm1));

    hash_map_destroy(phm_hm1);

    return 0;
}
