/*
 * type_duplicate.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

typedef int integer_t;

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(integer_t);

    printf("before type duplication: ");
    if(plist_coll == NULL)
    {
        printf("creation of integer_t type container failed!\n");
    }
    else
    {
        printf("creation of integer_t type container success!\n");
    }

    type_duplicate(int, integer_t);
    plist_coll = create_list(integer_t);

    printf("after type duplication: ");
    if(plist_coll == NULL)
    {
        printf("creation of integer_t type container failed!\n");
    }
    else
    {
        printf("creation of integer_t type container success!\n");
    }

    return 0;
}
