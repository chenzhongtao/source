/*
 * slist_max_size.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cslist.h>

int main(int argc, char* argv[])
{
    slist_t* pslist_l1 = create_slist(int);

    if(pslist_l1 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1);

    printf("Maximum possible length of the slist is %d\n", slist_max_size(pslist_l1));

    slist_destroy(pslist_l1);

    return 0;
}
