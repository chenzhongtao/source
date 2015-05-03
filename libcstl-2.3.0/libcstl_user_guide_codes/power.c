/*
 * power.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cnumeric.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(int);
    int n_result = 0;

    if(plist_coll == 0)
    {
        return -1;
    }

    list_init_elem(plist_coll, 1, -2);

    algo_power(list_begin(plist_coll), 4, &n_result);
    printf("-2 * -2 * -2 * -2 = %d\n", n_result);
    algo_power_if(list_begin(plist_coll), 4, fun_plus_int, &n_result);
    printf("-2 + -2 + -2 + -2 = %d\n", n_result);

    list_destroy(plist_coll);

    return 0;
}
