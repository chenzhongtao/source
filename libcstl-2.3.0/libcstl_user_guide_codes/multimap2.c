/*
 * multimap2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <string.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_dict = create_multimap(char*, char*);
    pair_t* ppair_item = create_pair(char*, char*);
    multimap_iterator_t it_pos;

    if(pmmap_dict == NULL || ppair_item == NULL)
    {
        return -1;
    }

    multimap_init(pmmap_dict);
    pair_init(ppair_item);

    pair_make(ppair_item, "day", "Tag");
    multimap_insert(pmmap_dict, ppair_item);
    pair_make(ppair_item, "strange", "fremd");
    multimap_insert(pmmap_dict, ppair_item);
    pair_make(ppair_item, "car", "Auto");
    multimap_insert(pmmap_dict, ppair_item);
    pair_make(ppair_item, "smart", "elegant");
    multimap_insert(pmmap_dict, ppair_item);
    pair_make(ppair_item, "trait", "Merkmal");
    multimap_insert(pmmap_dict, ppair_item);
    pair_make(ppair_item, "strange", "seltsam");
    multimap_insert(pmmap_dict, ppair_item);
    pair_make(ppair_item, "smart", "raffiniert");
    multimap_insert(pmmap_dict, ppair_item);
    pair_make(ppair_item, "smart", "klug");
    multimap_insert(pmmap_dict, ppair_item);
    pair_make(ppair_item, "clever", "raffiniert");
    multimap_insert(pmmap_dict, ppair_item);

    /* print all elements */
    printf("english\t\tgerman\n");
    printf("--------------------------------\n");
    for(it_pos = multimap_begin(pmmap_dict);
        !iterator_equal(it_pos, multimap_end(pmmap_dict));
        it_pos = iterator_next(it_pos))
    {
        printf("%s\t\t%s\n",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_pos)),
            (char*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
    }
    printf("\n");

    /* print all values for key "smart" */
    printf("smart:\n");
    for(it_pos = multimap_begin(pmmap_dict);
        !iterator_equal(it_pos, multimap_end(pmmap_dict));
        it_pos = iterator_next(it_pos))
    {
        if(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_pos)), "smart") == 0)
        {
            printf("\t%s\n", (char*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
        }
    }
    printf("\n");

    /* print all keys for value "raffiniert" */
    printf("raffiniert:\n");
    for(it_pos = multimap_begin(pmmap_dict);
        !iterator_equal(it_pos, multimap_end(pmmap_dict));
        it_pos = iterator_next(it_pos))
    {
        if(strcmp((char*)pair_second((pair_t*)iterator_get_pointer(it_pos)), "raffiniert") == 0)
        {
            printf("\t%s\n", (char*)pair_first((pair_t*)iterator_get_pointer(it_pos)));
        }
    }
    printf("\n");

    multimap_destroy(pmmap_dict);
    pair_destroy(ppair_item);

    return 0;
}
