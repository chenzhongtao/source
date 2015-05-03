/*
 * copy1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll1 = create_list(int);
    vector_t* pvec_coll2 = create_vector(int);
    int i = 0;

    if(plist_coll1 == NULL || pvec_coll2 == NULL)
    {
        return -1;
    }

    list_init(plist_coll1);
    vector_init(pvec_coll2);

    for(i = 1; i <= 9; ++i)
    {
        list_push_back(plist_coll1, i);
    }

    /*
     * RUNTIME ERROR.
     * overwrites nonexisting elements in the destination.
     */
    algo_copy(list_begin(plist_coll1), list_end(plist_coll1), /* source */
        vector_begin(pvec_coll2));                            /* destination */

    list_destroy(plist_coll1);
    vector_destroy(pvec_coll2);

    return 0;
}
