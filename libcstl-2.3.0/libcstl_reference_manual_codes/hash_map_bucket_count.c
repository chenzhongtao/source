/*
 * hash_map_bucket_count.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    hash_map_t* phm_hm2 = create_hash_map(int, int);

    if(phm_hm1 == NULL || phm_hm2 == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);
    hash_map_init_ex(phm_hm2, 100, NULL, NULL);

    printf("The default bucket count of hm1 is %d.\n", hash_map_bucket_count(phm_hm1));
    printf("The custom bucket count of hm2 is %d.\n", hash_map_bucket_count(phm_hm2));

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);

    return 0;
}
