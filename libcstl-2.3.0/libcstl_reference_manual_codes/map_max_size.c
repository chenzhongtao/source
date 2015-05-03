/*
 * map_max_size.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int);

    if(pmap_m1 == NULL)
    {
        return -1;
    }

    map_init(pmap_m1);

    printf("The maximum possible length of the map is %d.\n", map_max_size(pmap_m1));
    printf("(Magnitude is machine specific.)\n");

    map_destroy(pmap_m1);

    return 0;
}
