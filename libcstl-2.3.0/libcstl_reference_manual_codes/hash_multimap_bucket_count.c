/*
 * hash_multimap_bucket_count.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm2 = create_hash_multimap(int, int);

    if(phmm_hmm1 == NULL || phmm_hmm2 == NULL)
    {
        return -1;
    }

    hash_multimap_init(phmm_hmm1);
    hash_multimap_init_ex(phmm_hmm2, 100, NULL, NULL);

    printf("The default bucket count of hmm1 is %d.\n", hash_multimap_bucket_count(phmm_hmm1));
    printf("The custom bucket count of hmm2 is %d.\n", hash_multimap_bucket_count(phmm_hmm2));

    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);

    return 0;
}
