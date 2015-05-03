/*
 * type1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

typedef struct _tagabc
{
    int n_elem;
}abc_t;

static void _abc_init(const void* cpv_input, void* pv_output)
{
    ((abc_t*)cpv_input)->n_elem = 0;
    *(bool_t*)pv_output = true;
}

static void _abc_copy(const void* cpv_first,
    const void* cpv_second, void* pv_output)
{
    ((abc_t*)cpv_first)->n_elem = ((abc_t*)cpv_second)->n_elem;
    *(bool_t*)pv_output = true;
}

static void _abc_less(const void* cpv_first,
    const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        ((abc_t*)cpv_first)->n_elem < ((abc_t*)cpv_second)->n_elem ?
        true : false;
}

static void _abc_destroy(const void* cpv_input, void* pv_output)
{
    ((abc_t*)cpv_input)->n_elem = 0;
    *(bool_t*)pv_output = true;
}

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(abc_t);

    printf("before type register: ");
    if(plist_coll == NULL)
    {
        printf("creation of abc_t type container failed!\n");
    }
    else
    {
        printf("creation of abc_t type container success!\n");
    }

    type_register(abc_t, _abc_init, _abc_copy, _abc_less, _abc_destroy);
    plist_coll = create_list(abc_t);

    printf("after type register: ");
    if(plist_coll == NULL)
    {
        printf("creation of abc_t type container failed!\n");
    }
    else
    {
        printf("creation of abc_t type container success!\n");
    }

    return 0;
}
