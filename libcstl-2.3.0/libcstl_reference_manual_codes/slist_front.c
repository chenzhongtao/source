/*
 * slist_front.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cslist.h>

int main(int argc, char* argv[])
{
    slist_t* pslist_l1 = create_slist(int);
    int* pn_i = NULL;
    int* pn_j = NULL;

    if(pslist_l1 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1);

    slist_push_front(pslist_l1, 10);

    pn_i = (int*)slist_front(pslist_l1);
    pn_j = (int*)slist_front(pslist_l1);

    printf("The first integer of l1 is %d\n", *pn_i);
    (*pn_i)++;
    printf("The modified first integer of l1 is %d\n", *pn_j);

    slist_destroy(pslist_l1);

    return 0;
}
