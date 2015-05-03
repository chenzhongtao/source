/*
 * iterator_next.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    iterator_t it_vec;
    iterator_t it_pos;
    int i = 0;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    for(i = 0; i < 6; ++i)
    {
        vector_push_back(pvec_v1, i * 2);
    }

    printf("The vector v1 is ( ");
    for(it_vec = vector_begin(pvec_v1);
        !iterator_equal(it_vec, vector_end(pvec_v1));
        it_vec = iterator_next(it_vec))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_vec));
    }
    printf(")\n");

    it_pos = vector_begin(pvec_v1);

    printf("The iterator it_pos initially points to the first element: %d\n",
        *(int*)iterator_get_pointer(it_pos));

    it_pos = iterator_next(it_pos);
    printf("The iterator it_pos now points to the second element: %d\n",
        *(int*)iterator_get_pointer(it_pos));

    it_pos = iterator_next_n(it_pos, 3);
    printf("The iterator it_pos now points to the fifth element: %d\n",
        *(int*)iterator_get_pointer(it_pos));

    it_pos = iterator_next_n(it_pos, -2);
    printf("The iterator it_pos now points to the third element: %d\n",
        *(int*)iterator_get_pointer(it_pos));

    vector_destroy(pvec_v1);

    return 0;
}
