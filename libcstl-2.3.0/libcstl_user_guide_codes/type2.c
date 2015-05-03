/*
 * type2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

typedef unsigned int uint_t;

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(uint_t);

    printf("before type duplication: ");
    if(plist_coll == NULL)
    {
        printf("creation of uint_t type container failed!\n");
    }
    else
    {
        printf("creation of uint_t type container success!\n");
    }

    type_duplicate(unsigned int, uint_t);
    plist_coll = create_list(uint_t);

    printf("after type duplication: ");
    if(plist_coll == NULL)
    {
        printf("creation of uint_t type container failed!\n");
    }
    else
    {
        printf("creation of uint_t type container success!\n");
    }

    return 0;
}
