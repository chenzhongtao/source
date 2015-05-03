/*
 * multimap_max_size.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int);

    if(pmmap_m1 == NULL)
    {
        return -1;
    }

    multimap_init(pmmap_m1);

    printf("The maximum possible length of the multimap is %d.\n", multimap_max_size(pmmap_m1));
    printf("(Magnitude is machine specific.)\n");

    multimap_destroy(pmmap_m1);

    return 0;
}
