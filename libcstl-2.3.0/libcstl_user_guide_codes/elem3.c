/*
 * elem3.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstl/clist.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    list_t* pt_list = create_list(vector_t<int>);
    vector_t* pt_vec = create_vector(int);
    iterator_t t_it_list;
    iterator_t t_it_vec;
    size_t t_i = 0;
    size_t t_j = 0;
    size_t t_count = 0;
    if(pt_list == NULL || pt_vec == NULL)
    {
        return -1;
    }

    list_init(pt_list);
    vector_init(pt_vec);

    srand((unsigned)time(NULL));
    for(t_i = 0; t_i < 10; ++t_i)
    {
        t_count = rand() % 10;
        vector_clear(pt_vec);
        for(t_j = 0; t_j < t_count; ++t_j)
        {
            vector_push_back(pt_vec, rand() - rand());
        }
        list_push_back(pt_list, pt_vec);
    }

    printf("before sorting:\n");
    for(t_it_list = list_begin(pt_list);
        !iterator_equal(t_it_list, list_end(pt_list));
        t_it_list = iterator_next(t_it_list))
    {
        for(t_it_vec = vector_begin(iterator_get_pointer(t_it_list));
            !iterator_equal(t_it_vec, vector_end(iterator_get_pointer(t_it_list)));
            t_it_vec = iterator_next(t_it_vec))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_it_vec));
        }
        printf("\n");
    }
    printf("\n");

    list_sort(pt_list);

    printf("before sorting:\n");
    for(t_it_list = list_begin(pt_list);
        !iterator_equal(t_it_list, list_end(pt_list));
        t_it_list = iterator_next(t_it_list))
    {
        for(t_it_vec = vector_begin(iterator_get_pointer(t_it_list));
            !iterator_equal(t_it_vec, vector_end(iterator_get_pointer(t_it_list)));
            t_it_vec = iterator_next(t_it_vec))
        {
            printf("%d, ", *(int*)iterator_get_pointer(t_it_vec));
        }
        printf("\n");
    }
    printf("\n");

    list_destroy(pt_list);
    vector_destroy(pt_vec);

    return 0;
}
