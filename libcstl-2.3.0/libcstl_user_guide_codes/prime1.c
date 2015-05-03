/*
 * prime1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

static void _is_prime(const void* cpv_input, void* pv_output)
{
    int number = abs(*(int*)cpv_input);
    int divisor = 0;

    /* 0 and 1 are prime number */
    if(number == 0 || number == 1)
    {
        *(bool_t*)pv_output = true;
        return;
    }

    for(divisor = number / 2; number % divisor != 0; --divisor)
    {
        continue;
    }

    *(bool_t*)pv_output = divisor == 1 ? true : false;
}

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(int);
    list_iterator_t it_pos;
    int i = 0;

    if(plist_coll == NULL)
    {
        return -1;
    }

    list_init(plist_coll);

    for(i = 24; i <= 30; ++i)
    {
        list_push_back(plist_coll, i);
    }

    /* search for prime number */
    it_pos = algo_find_if(list_begin(plist_coll), list_end(plist_coll), _is_prime);
    if(iterator_equal(it_pos, list_end(plist_coll)))
    {
        printf("no prime number found.\n");
    }
    else
    {
        printf("%d is the first prime.\n", *(int*)iterator_get_pointer(it_pos));
    }

    list_destroy(plist_coll);

    return 0;
}
