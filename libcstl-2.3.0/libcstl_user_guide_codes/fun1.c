/*
 * fun1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <string.h>
#include <cstl/cvector.h>
#include <cstl/cutility.h>
#include <cstl/calgorithm.h>

static void _print_name(const void* cpv_input, void* pv_output)
{
    printf("%s. %s\n", (char*)pair_first((pair_t*)cpv_input),
        (char*)pair_second((pair_t*)cpv_input));
}

static void _less_name(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    if(strcmp((char*)pair_second((pair_t*)cpv_first),
        (char*)pair_second((pair_t*)cpv_second)) < 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(pair_t<char*, char*>);
    pair_t* ppair_item = create_pair(char*, char*);

    if(pvec_coll == NULL || ppair_item == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);
    pair_init(ppair_item);

    pair_make(ppair_item, "Douglas E", "Comer");
    vector_push_back(pvec_coll, ppair_item);
    pair_make(ppair_item, "David L", "Stevens");
    vector_push_back(pvec_coll, ppair_item);
    pair_make(ppair_item, "Behdad", "Esfahbod");
    vector_push_back(pvec_coll, ppair_item);
    pair_make(ppair_item, "Guilherme de S", "Pastve");
    vector_push_back(pvec_coll, ppair_item);
    pair_make(ppair_item, "Havoc", "Pennington");
    vector_push_back(pvec_coll, ppair_item);
    pair_make(ppair_item, "Christian", "Persch");
    vector_push_back(pvec_coll, ppair_item);
    pair_make(ppair_item, "Mariano", "Suarez-Alvarez");
    vector_push_back(pvec_coll, ppair_item);

    algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print_name);
    printf("\n------------------\n\n");

    algo_sort_if(vector_begin(pvec_coll), vector_end(pvec_coll), _less_name);

    algo_for_each(vector_begin(pvec_coll), vector_end(pvec_coll), _print_name);

    vector_destroy(pvec_coll);
    pair_destroy(ppair_item);

    return 0;
}
