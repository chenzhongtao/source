/*
 * transform1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cset.h>
#include <cstl/calgorithm.h>

static void _print(const void* cpv_input, void* pv_output)
{
    printf("%d ", *(int*)cpv_input);
}

static void _square(const void* cpv_input, void* pv_output)
{
    *(int*)pv_output = *(int*)cpv_input * *(int*)cpv_input;
}

int main(int argc, char* argv[])
{
    set_t* pset_coll1 = create_set(int);
    vector_t* pvec_coll2 = create_vector(int);
    int i = 0;

    if(pset_coll1 == NULL || pvec_coll2 == NULL)
    {
        return -1;
    }

    set_init(pset_coll1);
    vector_init(pvec_coll2);

    for(i = 1; i <= 9; ++i)
    {
        set_insert(pset_coll1, i);
    }

    printf("initialized: ");
    algo_for_each(set_begin(pset_coll1), set_end(pset_coll1), _print);
    printf("\n");

    /* transform each element from coll1 to coll2 */
    vector_resize(pvec_coll2, set_size(pset_coll1));
    algo_transform(set_begin(pset_coll1), set_end(pset_coll1),
        vector_begin(pvec_coll2), _square);

    printf("squared: ");
    algo_for_each(vector_begin(pvec_coll2), vector_end(pvec_coll2), _print);
    printf("\n");

    set_destroy(pset_coll1);
    vector_destroy(pvec_coll2);

    return 0;
}
