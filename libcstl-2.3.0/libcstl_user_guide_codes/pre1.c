/*
 * pre1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>
#include <cstl/cnumeric.h>

static void _mod3(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 3 == 0 ? true : false;
}

static void _print(const void* cpv_input, void* pv_output)
{
    printf("%d ", *(int*)cpv_input);
}

int main(int argc, char* argv[])
{
   list_t* plist_coll = create_list(int);
   iterator_t it_end;

   if(plist_coll == NULL)
   {
       return -1;
   }

   list_init_n(plist_coll, 10);

   algo_iota(list_begin(plist_coll), list_end(plist_coll), 1);
   algo_for_each(list_begin(plist_coll), list_end(plist_coll), _print);
   printf("\n");

   it_end = algo_remove_if(list_begin(plist_coll), list_end(plist_coll), _mod3);
   algo_for_each(list_begin(plist_coll), it_end, _print);
   printf("\n");

   list_destroy(plist_coll);

   return 0; 
}
