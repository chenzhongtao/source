/*
 * pair1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cutility.h>

int main(int argc, char* argv[])
{
    pair_t* ppair_p1 = create_pair(int, double);
    pair_t* ppair_p2 = create_pair(int, double);
    pair_t* ppair_p3 = create_pair(int, double);

    if(ppair_p1 == NULL || ppair_p2 == NULL || ppair_p3 == NULL)
    {
        return -1;
    }

    pair_init(ppair_p1);
    pair_init_elem(ppair_p2, 10, 1.1e-2);
    pair_init_copy(ppair_p3, ppair_p2);

    printf("Original pair:\n");
    printf("p1(%d, %lf)\n",
        *(int*)pair_first(ppair_p1),
        *(double*)pair_second(ppair_p1));
    printf("p2(%d, %lf)\n",
        *(int*)pair_first(ppair_p2),
        *(double*)pair_second(ppair_p2));
    printf("p3(%d, %lf)\n",
        *(int*)pair_first(ppair_p3),
        *(double*)pair_second(ppair_p3));

    pair_make(ppair_p1, 10, 2.222);
    pair_assign(ppair_p3, ppair_p1);
    printf("After modifying:\n");
    printf("p1(%d, %lf)\n",
        *(int*)pair_first(ppair_p1),
        *(double*)pair_second(ppair_p1));
    printf("p2(%d, %lf)\n",
        *(int*)pair_first(ppair_p2),
        *(double*)pair_second(ppair_p2));
    printf("p3(%d, %lf)\n",
        *(int*)pair_first(ppair_p3),
        *(double*)pair_second(ppair_p3));

    printf("Compare:\n");
    if(pair_equal(ppair_p1, ppair_p3))
    {
        printf("p1(%d, %lf) == p3(%d, %lf)\n",
            *(int*)pair_first(ppair_p1),
            *(double*)pair_second(ppair_p1),
            *(int*)pair_first(ppair_p3),
            *(double*)pair_second(ppair_p3));
    }
    else
    {
        printf("p1(%d, %lf) != p3(%d, %lf)\n",
            *(int*)pair_first(ppair_p1),
            *(double*)pair_second(ppair_p1),
            *(int*)pair_first(ppair_p3),
            *(double*)pair_second(ppair_p3));
    }
    if(pair_not_equal(ppair_p1, ppair_p2))
    {
        printf("p1(%d, %lf) != p2(%d, %lf)\n",
            *(int*)pair_first(ppair_p1),
            *(double*)pair_second(ppair_p1),
            *(int*)pair_first(ppair_p2),
            *(double*)pair_second(ppair_p2));
    }
    else
    {
        printf("p1(%d, %lf) == p2(%d, %lf)\n",
            *(int*)pair_first(ppair_p1),
            *(double*)pair_second(ppair_p1),
            *(int*)pair_first(ppair_p2),
            *(double*)pair_second(ppair_p2));
    }

    pair_make(ppair_p1, 22, 35.2);
    pair_make(ppair_p2, 62, 35.2);
    pair_make(ppair_p3, 22, 70.0);
    if(pair_less(ppair_p1, ppair_p2))
    {
        printf("p1(%d, %lf) < p2(%d, %lf)\n",
            *(int*)pair_first(ppair_p1),
            *(double*)pair_second(ppair_p1),
            *(int*)pair_first(ppair_p2),
            *(double*)pair_second(ppair_p2));
    }
    else
    {
        printf("p1(%d, %lf) >= p2(%d, %lf)\n",
            *(int*)pair_first(ppair_p1),
            *(double*)pair_second(ppair_p1),
            *(int*)pair_first(ppair_p2),
            *(double*)pair_second(ppair_p2));
    }
    if(pair_less(ppair_p1, ppair_p3))
    {
        printf("p1(%d, %lf) < p3(%d, %lf)\n",
            *(int*)pair_first(ppair_p1),
            *(double*)pair_second(ppair_p1),
            *(int*)pair_first(ppair_p3),
            *(double*)pair_second(ppair_p3));
    }
    else
    {
        printf("p1(%d, %lf) >= p3(%d, %lf)\n",
            *(int*)pair_first(ppair_p1),
            *(double*)pair_second(ppair_p1),
            *(int*)pair_first(ppair_p3),
            *(double*)pair_second(ppair_p3));
    }

    pair_destroy(ppair_p1);
    pair_destroy(ppair_p2);
    pair_destroy(ppair_p3);

    return 0;
}
