#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>
#include "hashtable.h"
#include "hashfn.h"

int32_t main(int32_t argc, char **argv)
{
    Hashtable * hashtable = hashtable_init(10);
    int a = 1;
    hashtable_put(hashtable, "a", (char *)&a);
    hashtable_put(hashtable, "b", "2");
    hashtable_put(hashtable, "c", "3");
    hashtable_put(hashtable, "d", "4");
    hashtable_put(hashtable, "e", "5");
    hashtable_put(hashtable, "f", "6");
    hashtable_put(hashtable, "g", "7");
    hashtable_put(hashtable, "h", "8");
    hashtable_put(hashtable, "i", "9");
    hashtable_put(hashtable, "j", "10");
    hashtable_put(hashtable, "k", "11");
    hashtable_put(hashtable, "l", "12");
    hashtable_put(hashtable, "f", "8");
    hashtable_remove(hashtable, "f");
    hashtable_print(hashtable);

    char * s = hashtable_get(hashtable, "a");
    memcpy( &a, s, 4);
    printf("a=%d",*(int *)s);

    hashtable_destroy(hashtable);
    getchar();
    return 0;
}

#ifdef __cplusplus
}
#endif