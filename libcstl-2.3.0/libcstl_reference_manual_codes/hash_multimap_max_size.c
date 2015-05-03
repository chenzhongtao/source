/*
 * hash_multimap_max_size.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);

    if(phmm_hmm1 == NULL)
    {
        return -1;
    }

    hash_multimap_init(phmm_hmm1);

    printf("The maximum possible length of the hash_multimap hmm1 is: %d.\n",
        hash_multimap_max_size(phmm_hmm1));

    hash_multimap_destroy(phmm_hmm1);

    return 0;
}
