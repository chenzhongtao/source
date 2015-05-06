/*
file: list.c

Ë«ÏòÁ´±ílist_t
Ë«ÏòÁ´±íÊÇĞòÁĞÈİÆ÷µÄÒ»ÖÖ£¬ËüÒÔÏßĞÔµÄ·½Ê½±£´æÊı¾İ£¬Í¬Ê±ÔÊĞíÔÚÈÎÒâÎ»ÖÃ¸ßĞ§µÄ²åÈë»òÕßÉ¾³ıÊı¾İ£¬µ«
ÊÇ²»ÄÜ¹»Ëæ»úµÄ·ÃÎÊÁ´±íÖĞµÄÊı¾İ¡£µ±´Ólist_tÖĞÉ¾³ıÊı¾İµÄÊ±ºò£¬Ö¸Ïò±»É¾³ıÊı¾İµÄµü´úÆ÷Ê§Ğ§¡£

Typedefs
    list_t Ë«ÏòÁ´±íÈİÆ÷ÀàĞÍ¡£
    list_iterator_t Ë«ÏòÁ´±íµü´úÆ÷ÀàĞÍ¡

Operation Functions
    create_list ´´½¨Ë«ÏòÁ´±íÈİÆ÷¡£
    list_assign ½«ÁíÒ»¸öË«ÏòÁ´±í¸³Öµ¸øµ±Ç°µÄË«ÏòÁ´±í¡£
    list_assign_elem Ê¹ÓÃÖ¸¶¨Êı¾İÎªË«ÏòÁ´±í¸³Öµ¡£
    list_assign_range Ê¹ÓÃÖ¸¶¨Êı¾İÇø¼äÎªË«ÏòÁ´±í¸³Öµ¡£
    list_back ·ÃÎÊ×îºóÒ»¸öÊı¾İ¡£
    list_begin ·µ»ØÖ¸ÏòµÚÒ»¸öÊı¾İµÄµü´úÆ÷¡£
    list_clear É¾³ıËùÓĞÊı¾İ¡£
    list_destroy Ïú»ÙË«ÏòÁ´±íÈİÆ÷¡£
    list_empty ²âÊÔÈİÆ÷ÊÇ·ñÎª¿Õ¡£
    list_end ·µ»ØÈİÆ÷Ä©Î²µÄµü´úÆ÷¡£
    list_equal ²âÊÔÁ½¸öË«ÏòÁ´±íÊÇ·ñÏàµÈ¡£
    list_erase É¾³ıÖ¸¶¨Î»ÖÃµÄÊı¾İ¡£
    list_erase_range É¾³ıÖ¸¶¨Êı¾İÇø¼äµÄÊı¾İ¡£
    list_front ·ÃÎÊÈİÆ÷ÖĞµÄµÚÒ»¸öÊı¾İ¡£
    list_greater ²âÊÔµÚÒ»¸öË«ÏòÁ´±íÊÇ·ñ´óÓÚµÚ¶ş¸öË«ÏòÁ´±í¡£
    list_greater_equal ²âÊÔµÚÒ»¸öË«ÏòÁ´±íÊÇ·ñ´óÓÚµÈÓÚµÚ¶ş¸öË«ÏòÁ´±í¡£
    list_init ³õÊ¼»¯Ò»¸ö¿ÕµÄË«ÏòÁ´±íÈİÆ÷¡£
    list_init_copy Ê¹ÓÃÁíÒ»¸öË«ÏòÁ´±í³õÊ¼»¯µ±Ç°µÄË«ÏòÁ´±í¡£
    list_init_copy_range Ê¹ÓÃÖ¸¶¨µÄÊı¾İÇø¼ä³õÊ¼»¯Ë«ÏòÁ´±í¡£
    list_init_elem Ê¹ÓÃÖ¸¶¨Êı¾İ³õÊ¼»¯Ë«ÏòÁ´±í¡£
    list_init_n Ê¹ÓÃÖ¸¶¨¸öÊıµÄÄ¬ÈÏÊı¾İ³õÊ¼»¯Ë«ÏòÁ´±í¡£
    list_insert ÔÚÖ¸¶¨Î»ÖÃ²åÈëÒ»¸öÊı¾İ¡£
    list_insert_range ÔÚÖ¸¶¨Î»ÖÃ²åÈëÒ»¸öÊı¾İÇø¼ä¡£
    list_insert_n ÔÚÖ¸¶¨Î»ÖÃ²åÈë¶à¸öÊı¾İ¡£
    list_less ²âÊÔµÚÒ»¸öË«ÏòÁ´±íÊÇ·ñĞ¡ÓÚµÚ¶ş¸öË«ÏòÁ´±í¡£
    list_less_equal ²âÊÔµÚÒ»¸öË«ÏòÁ´±íÊÇ·ñĞ¡ÓÚµÈÓÚµÚ¶ş¸öË«ÏòÁ´±í¡£
    list_max_size ·µ»ØË«ÏòÁ´±íÄÜ¹»±£´æµÄ×î´óÊı¾İ¸öÊı¡£
    list_merge ºÏ²¢Á½¸öÓĞĞòµÄË«ÏòÁ´±í¡£
    list_merge_if °´ÕÕÌØ¶¨¹æÔòºÏ²¢Á½¸öÓĞĞòµÄË«ÏòÁ´±í¡£
    list_not_equal ²âÊÔÁ½¸öË«ÏòÁ´±íÊÇ·ñ²»µÈ¡£
    list_pop_back É¾³ı×îºóÒ»¸öÊı¾İ¡£
    list_pop_front É¾³ıµÚÒ»¸öÊı¾İ¡£
    list_push_back ÔÚË«ÏòÁ´±íµÄÄ©Î²Ìí¼ÓÒ»¸öÊı¾İ¡£
    list_push_front ÔÚË«ÏòÁ´±íµÄ¿ªÍ·Ìí¼ÓÒ»¸öÊı¾İ¡£
    list_remove É¾³ıË«ÏòÁ´±íÖĞÓëÖ¸¶¨µÄÊı¾İÏàµÈµÄÊı¾İ¡£
    list_remove_if É¾³ıË«ÏòÁ´±íÖĞ·ûºÏÌØ¶¨¹æÔòµÄÊı¾İ¡£
    list_resize ÖØĞÂÉèÖÃË«ÏòÁ´±íÖĞµÄÊı¾İ¸öÊı£¬²»×ãµÄ²¿·Ö²ÉÓÃÄ¬ÈÏÊı¾İÌî³ä
    list_resize_elem ÖØĞÂÉèÖÃË«ÏòÁ´±íÖĞµÄÊı¾İ¸öÊı£¬²»×ãµÄ²¿·Ö²ÉÓÃÖ¸¶¨Êı¾İÌî³ä¡£
    list_reverse °ÑË«ÏòÁ´±íÖĞµÄÊı¾İÄæĞò¡£
    list_size ·µ»ØË«ÏòÁ´±íÖĞÊı¾İµÄ¸öÊı¡£
    list_sort ÅÅĞòË«ÏòÁ´±íÖĞµÄÊı¾İ¡£
    list_sort_if °´ÕÕ¹æÔòÅÅĞòË«ÏòÁ´±íÖĞµÄÊı¾İ¡£
    list_splice ½«Ë«ÏòÁ´±íÖĞµÄÊı¾İ×ªÒÆµ½ÁíÒ»¸öË«ÏòÁ´±íÖĞ¡£
    list_splice_pos ½«ÖÆ¶¨Î»ÖÃµÄÊı¾İ×ªÒÆµ½ÁíÒ»¸öË«ÏòÁ´±íÖĞ¡£
    list_splice_range ½«ÖÆ¶¨Çø¼äµÄÊı¾İ×ªÒÆµ½ÁíÒ»¸öË«ÏòÁ´±íÖĞ¡£
    list_swap ½»»»Á½¸öË«ÏòÁ´±íµÄÄÚÈİ¡£
    list_unique É¾³ıÏàÁÚµÄÖØ¸´Êı¾İ¡£
    list_unique_if É¾³ıÏàÁÚµÄÂú×ã¹æÔòµÄÊı¾İ¡£
*/

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cfunctional.h>

//ÊÇ·ñÊÇÆæÊı
static void is_odd(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int); //´´½¨Ò»¸öË«ÏòÁ´±íÈİÆ÷ÀàĞÍ
    list_t* plist_l2 = create_list(int);
    list_iterator_t it_l; // Ë«ÏòÁ´±íµÄµü´úÆ÷ÀàĞÍ

    int* pn_i = NULL;
    int* pn_j = NULL;

    if(plist_l1 == NULL || plist_l2 == NULL)
    {
        return -1;
    }

    list_init(plist_l1); //³õÊ¼»¯Ò»¸ö¿ÕµÄË«ÏòÁ´±íÈİÆ÷¡£
    list_init(plist_l2);

    list_push_back(plist_l1, 10);//Ïòlist_tÄ©Î²Ìí¼ÓÒ»¸öÊı¾İ¡£
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 30);
    list_push_back(plist_l2, 40);
    list_push_back(plist_l2, 50);
    list_push_back(plist_l2, 60);
/*
list_assign ½«ÁíÒ»¸öË«ÏòÁ´±í¸³Öµ¸øµ±Ç°µÄË«ÏòÁ´±í¡£
list_assign_elem Ê¹ÓÃÖ¸¶¨Êı¾İÎªË«ÏòÁ´±í¸³Öµ¡£
list_assign_range Ê¹ÓÃÖ¸¶¨Êı¾İÇø¼äÎªË«ÏòÁ´±í¸³Öµ¡£
*/
    printf("l1 =");
    //list_begin: ·µ»ØÖ¸Ïòlist_tÖĞµÚÒ»¸öÊı¾İµÄµü´úÆ÷¡£
    //list_end: ·µ»ØÖ¸Ïòlist_tÄ©Î²µÄµü´úÆ÷¡£
    for(it_l = list_begin(plist_l1); !iterator_equal(it_l, list_end(plist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    //10 20 30
    printf("\n");

    //½«ÁíÒ»¸öË«ÏòÁ´±í¸³Öµ¸øµ±Ç°µÄË«ÏòÁ´±í¡£
    list_assign(plist_l1, plist_l2); //plist_l1 = 40 50 60

    //Ê¹ÓÃÖ¸¶¨Êı¾İÇø¼äÎªË«ÏòÁ´±í¸³Öµ¡£
    list_assign_range(plist_l1, iterator_next(list_begin(plist_l2)), list_end(plist_l2));
    //plist_l1 = 50 60

    //Ê¹ÓÃÖ¸¶¨Êı¾İÎªË«ÏòÁ´±í¸³Öµ¡£
    list_assign_elem(plist_l1, 5, 4); //plist_l1 = 4 4 4 4 4

    //É¾³ılist_tÖĞµÄËùÓĞÊı¾İ¡£
    list_clear(plist_l1);
    
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    
    //·ÃÎÊË«ÏòÁ´±íÈİÆ÷ÖĞ×îºóÒ»¸öÊı¾İ¡£
    pn_i = (int*)list_back(plist_l1);
    printf("The last integer of l1 is %d\n", *pn_i);//20

    //·ÃÎÊlist_tÖĞµÄµÚÒ»¸öÊı¾İ¡£
    pn_i = (int*)list_front(plist_l1);
    printf("The first integer of l1 is %d\n", *pn_i);//10

    //²âÊÔlist_tÊÇ·ñÎª¿Õ¡£
    if(list_empty(plist_l1))
    {
        printf("The list is empty.\n");
    }
    else
    {
        printf("The list is not empty.\n");
    }
    
    //²âÊÔÁ½¸ölist_tÊÇ·ñÏàµÈ¡£ 
    if(list_equal(plist_l1, plist_l2))
    {
        ;
    }

    //²âÊÔÁ½¸ölist_tÊÇ·ñ²»µÈ
    if(list_not_equal(plist_l1, plist_l2))
    {
        ;
    }

    //²âÊÔµÚÒ»¸ölist_tÊÇ·ñ´óÓÚµÚ¶ş¸ölist_t
    if(list_greater(plist_l1, plist_l2))
    {
        ;
    }

    // ²âÊÔµÚÒ»¸ölist_tÊÇ·ñ´óÓÚµÈÓÚµÚ¶ş¸ölist_t¡£
    if(list_greater_equal(plist_l1, plist_l2))
    {
        ;
    }

    //²âÊÔµÚÒ»¸ölist_tÊÇ·ñĞ¡ÓÚµÚ¶ş¸ölist_t¡£
    if(list_less(plist_l1, plist_l2))
    {
        ;
    }

    //²âÊÔµÚÒ»¸ölist_tÊÇ·ñĞ¡ÓÚµÈÓÚµÚ¶ş¸ölist_t
    if(list_less_equal(plist_l1, plist_l2))
    {
        ;
    }

    list_push_back(plist_l1, 30);
    list_push_back(plist_l1, 40);
    list_push_back(plist_l1, 50); // 10 20 30 40 50 

    //É¾³ılist_tÖĞÖ¸¶¨Î»ÖÃµÄÊı¾İ¡£
    list_erase(plist_l1, list_begin(plist_l1));//20 30 40 50

    //É¾³ılist_tÖĞÖ¸¶¨Êı¾İÇø¼äµÄÊı¾İ¡£
    list_erase_range(plist_l1, iterator_next(list_begin(plist_l1)),
        list_end(plist_l1)); //20

    list_clear(plist_l1);
    list_clear(plist_l2);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 30);// 10 20 30 
    list_push_back(plist_l2, 40);
    list_push_back(plist_l2, 50);
    list_push_back(plist_l2, 60);//40 50 60
    //list_insert ÔÚÖ¸¶¨Î»ÖÃ²åÈëÒ»¸öÊı¾İ¡£
    //list_insert_range ÔÚÖ¸¶¨Î»ÖÃ²åÈëÒ»¸öÊı¾İÇø¼ä¡£
    //list_insert_n ÔÚÖ¸¶¨Î»ÖÃ²åÈë¶à¸öÊı¾İ¡£

    //ÔÚÖ¸¶¨Î»ÖÃ²åÈëÒ»¸öÊı¾İ¡£ 10 100 20 30
    list_insert(plist_l1, iterator_next(list_begin(plist_l1)), 100); 
    

    //ÔÚÖ¸¶¨Î»ÖÃ²åÈë¶à¸öÊı¾İ¡£10 100 200 200 20 30
    list_insert_n(plist_l1, iterator_advance(list_begin(plist_l1), 2), 2, 200);

    //ÔÚÖ¸¶¨Î»ÖÃ²åÈëÒ»¸öÊı¾İÇø¼ä 10 40 50 100 200 200 20 30
    list_insert_range(plist_l1, iterator_next(list_begin(plist_l1)), list_begin(plist_l2), iterator_prev(list_end(plist_l2)));

    //·µ»Ølist_tÖĞ±£´æÊı¾İµÄ¿ÉÄÜµÄ×î´óÊıÁ¿¡£ ÕâÊÇÒ»¸öÓëÏµÍ³Ïà¹ØµÄ³£Á¿¡£
    printf("Maximum possible length of the list is %u\n",
        list_max_size(plist_l1));

    //list_pop_back É¾³ı×îºóÒ»¸öÊı¾İ¡£
    list_pop_back(plist_l1);//10 40 50 100 200 200 20

    //list_pop_front É¾³ıµÚÒ»¸öÊı¾İ¡£
    list_pop_front(plist_l1);//40 50 100 200 200 20
    
    //list_push_back ÔÚË«ÏòÁ´±íµÄÄ©Î²Ìí¼ÓÒ»¸öÊı¾İ¡£
    list_push_back(plist_l1, 1);//40 50 100 200 200 20 1

    //list_push_front ÔÚË«ÏòÁ´±íµÄ¿ªÍ·Ìí¼ÓÒ»¸öÊı¾İ¡£
    list_push_front(plist_l1, 2);//2 //2 40 50 100 200 200 20 1

    //É¾³ılist_tÖĞÓëÖ¸¶¨Êı¾İÏàµÈµÄÊı¾İ¡£
    list_remove(plist_l1, 200); // 2 40 50 100 20 1

    //É¾³ıË«ÏòÁ´±íÖĞ·ûºÏÌØ¶¨¹æÔòµÄÊı¾İ¡£
    list_remove_if(plist_l1, is_odd); //2 //40 50 100 20

    //ÖØÉèlist_tÖĞÊı¾İµÄ¸öÊı£¬µ±ĞÂµÄÊı¾İ¸öÊı±Èµ±Ç°¸öÊı¶à£¬¶à´¦µÄÊı¾İÊ¹ÓÃÄ¬ÈÏÊı¾İ0Ìî³ä
    list_resize(plist_l1, 2); // 40 50
    list_resize(plist_l1, 4); // 40 50 0 0

    //ÖØÉèlist_tÖĞÊı¾İµÄ¸öÊı£¬µ±ĞÂµÄÊı¾İ¸öÊı±Èµ±Ç°¸öÊı¶à£¬¶à´¦µÄÊı¾İÊ¹ÓÃÖ¸¶¨Êı¾İÌî³ä¡£
    list_resize_elem(plist_l1, 5, 60); // 40 50 0 0 60

    //½«list_tÖĞµÄÊı¾İÄæĞò¡£
    list_reverse(plist_l1);// 60 0 0 50 40

    //·µ»Ølist_tÖĞÊı¾İµÄ¸öÊı
    printf("List length is %d\n", list_size(plist_l1)); //5
    

    //Ê¹ÓÃÄ¬ÈÏµÄ¹æÔòÅÅĞò£¬ÅÅĞòºóÊı¾İµÄË³Ğò´ÓĞ¡µ½´ó¡£
    list_sort(plist_l1); // 0 0 40 50 60

    //Ê¹ÓÃÖ¸¶¨¹æÔòbfun_opÅÅĞò
    list_sort_if(plist_l1, fun_greater_int); // 60 50 40 0 0

    list_clear(plist_l1);
    list_clear(plist_l2);
    
    list_push_back(plist_l1, 3);
    list_push_back(plist_l1, 6); // 3 6
    list_push_back(plist_l2, 2);
    list_push_back(plist_l2, 4); // 2 4
    
    //list_merge ºÏ²¢Á½¸öÓĞĞòµÄË«ÏòÁ´±í¡£
    list_merge(plist_l2, plist_l1);
    // plist_l2 = 2 3 4 6
    // plist_l = []
    
    list_push_back(plist_l1, 5);
    list_push_back(plist_l1, 1); // 5 1
    list_sort_if(plist_l2, fun_greater_int);
    
    //list_merge_if °´ÕÕÌØ¶¨¹æÔòºÏ²¢Á½¸öÓĞĞòµÄË«ÏòÁ´±í
    list_merge_if(plist_l2, plist_l1, fun_greater_int);
    for(it_l = list_begin(plist_l2);
        !iterator_equal(it_l, list_end(plist_l2));
    it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");
    // plist_l2 = 6 5 4 3 2 1
    // plist_l = []
  
    //list_splice ½«Ë«ÏòÁ´±íÖĞµÄÊı¾İ×ªÒÆµ½ÁíÒ»¸öË«ÏòÁ´±íÖĞ¡£
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 11);
    list_splice(plist_l2, iterator_next(list_begin(plist_l2)), plist_l1);
    // plist_l2 = 6 10 11 5 4 3 2 1
    // plist_l = []
    list_push_back(plist_l1, 12);
    list_push_back(plist_l1, 13); // 12 13
    
    //list_splice_pos ½«ÖÆ¶¨Î»ÖÃµÄÊı¾İ×ªÒÆµ½ÁíÒ»¸öË«ÏòÁ´±íÖĞ¡£
    list_splice_pos(plist_l2, iterator_next(list_begin(plist_l2)),
        plist_l1, list_begin(plist_l1));
    // plist_l2 = 6 12 10 11 5 4 3 2 1
    // plist_l = 13

    list_push_back(plist_l1, 14); 
    list_push_back(plist_l1, 15); // 13 14 15

    //list_splice_range ½«ÖÆ¶¨Çø¼äµÄÊı¾İ×ªÒÆµ½ÁíÒ»¸öË«ÏòÁ´±íÖĞ¡£
    list_splice_range(plist_l2, iterator_next(list_begin(plist_l2)),
        plist_l1, list_begin(plist_l1), iterator_prev(list_end(plist_l1)));
    // plist_l2 = 6 13 14 12 10 11 5 4 3 2 1
    // plist_l = 15

    // ½»»»Á½¸ölist_tÖĞµÄÄÚÈİ
    list_swap(plist_l1, plist_l2);

    list_clear(plist_l1);
    list_clear(plist_l2);
    list_push_back(plist_l1, -10);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, -10);
    
    //list_unique É¾³ıÏàÁÚµÄÖØ¸´Êı¾İ¡£
    list_assign(plist_l2, plist_l1); //-10 10 20 -10
        
    //list_unique_if É¾³ıÏàÁÚµÄÂú×ã¹æÔòµÄÊı¾İ¡£
    list_unique(plist_l1); // -10 -10

    //Ïú»Ùlist_t
    list_destroy(plist_l1);
    list_destroy(plist_l2);

    
    list_t* plist_l0 = create_list(int);
    plist_l1 = create_list(int);
    plist_l2 = create_list(int);
    list_t* plist_l3 = create_list(int);
    list_t* plist_l4 = create_list(int);

    if(plist_l0 == NULL || plist_l1 == NULL || plist_l2 == NULL || plist_l3 == NULL || plist_l4 == NULL)
    {
        return -1;
    }

    //list_init ³õÊ¼»¯Ò»¸ö¿ÕµÄË«ÏòÁ´±íÈİÆ÷¡£
    list_init(plist_l0);

    //list_init_n Ê¹ÓÃÖ¸¶¨¸öÊıµÄÄ¬ÈÏÊı¾İ³õÊ¼»¯Ë«ÏòÁ´±í¡£
    list_init_n(plist_l1, 3);//0 0 0

    //list_init_elem Ê¹ÓÃÖ¸¶¨Êı¾İ³õÊ¼»¯Ë«ÏòÁ´±í¡£
    list_init_elem(plist_l2, 5, 2);// 2 2 2 2 2

    //list_init_copy Ê¹ÓÃÁíÒ»¸öË«ÏòÁ´±í³õÊ¼»¯µ±Ç°µÄË«ÏòÁ´±í¡£
    list_init_copy(plist_l3, plist_l2); //2 // 2 2 2 2 2 

    //list_init_copy_range Ê¹ÓÃÖ¸¶¨µÄÊı¾İÇø¼ä³õÊ¼»¯Ë«ÏòÁ´±í¡£
    list_init_copy_range(plist_l4, iterator_advance(list_begin(plist_l3), 2), list_end(plist_l3));//2 // 2 2 2

    //Ïú»Ùlist_t
    list_destroy(plist_l0);
    list_destroy(plist_l1);
    list_destroy(plist_l2);
    list_destroy(plist_l3);
    list_destroy(plist_l4);

    return 0;
}

static void is_odd(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    if(*(int*)cpv_input % 2 == 1)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
