/*
 * algo_max.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cset.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(set_t<int>);
    vector_iterator_t it_v;
    set_t* pset_s1 = create_set(int);
    set_iterator_t it_s;
    int i = 0;

    if(pvec_v1 == NULL || pset_s1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    set_init(pset_s1);

    set_insert(pset_s1, 0);
    set_insert(pset_s1, 1);
    set_insert(pset_s1, 2);
    vector_push_back(pvec_v1, pset_s1);
    vector_push_back(pvec_v1, pset_s1);
    set_clear(pset_s1);
    set_insert(pset_s1, 0);
    set_insert(pset_s1, 2);
    set_insert(pset_s1, 4);
    vector_push_back(pvec_v1, pset_s1);

    for(it_v = vector_begin(pvec_v1), i = 1;
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v), ++i)
    {
        printf("Set s%d ( ", i);
        for(it_s = set_begin((set_t*)iterator_get_pointer(it_v));
            !iterator_equal(it_s, set_end((set_t*)iterator_get_pointer(it_v)));
            it_s = iterator_next(it_s))
        {
            printf("%d ", *(int*)iterator_get_pointer(it_s));
        }
        printf(")\n");
    }

    it_v = algo_max(vector_begin(pvec_v1), iterator_next(vector_begin(pvec_v1)));
    printf("The max set between the frist and the second is ( ");
    for(it_s = set_begin((set_t*)iterator_get_pointer(it_v));
        !iterator_equal(it_s, set_end((set_t*)iterator_get_pointer(it_v)));
        it_s = iterator_next(it_s))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_s));
    }
    printf(")\n");

    it_v = algo_max(vector_begin(pvec_v1), iterator_prev(vector_end(pvec_v1)));
    printf("The max set between the frist and the third is ( ");
    for(it_s = set_begin((set_t*)iterator_get_pointer(it_v));
        !iterator_equal(it_s, set_end((set_t*)iterator_get_pointer(it_v)));
        it_s = iterator_next(it_s))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_s));
    }
    printf(")\n");

    it_v = algo_max_if(vector_begin(pvec_v1), iterator_next(vector_begin(pvec_v1)), fun_greater_set);
    printf("The max set between the frist and the second under greater than is ( ");
    for(it_s = set_begin((set_t*)iterator_get_pointer(it_v));
        !iterator_equal(it_s, set_end((set_t*)iterator_get_pointer(it_v)));
        it_s = iterator_next(it_s))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_s));
    }
    printf(")\n");

    it_v = algo_max_if(vector_begin(pvec_v1), iterator_prev(vector_end(pvec_v1)), fun_greater_set);
    printf("The max set between the frist and the third under greater than is ( ");
    for(it_s = set_begin((set_t*)iterator_get_pointer(it_v));
        !iterator_equal(it_s, set_end((set_t*)iterator_get_pointer(it_v)));
        it_s = iterator_next(it_s))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_s));
    }
    printf(")\n");

    vector_destroy(pvec_v1);
    set_destroy(pset_s1);

    return 0;
}
