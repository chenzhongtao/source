/*
file: slist.c

单向链表slist_t

slist_t容器是一种单向链表，支持向前遍历但是不支持向后遍历。在任何位置后面插入和删除数据花费常数时
间，在前面插入或删除数据花费线性时间。在slist_t中插入或删除数据不会使迭代器失效。slist_t是list_t的一种弱化，
它不支持随机访问数据，和双向迭代器。当从slist_t中删除数据时，指向被删除的数据的迭代器失效。

Typedefs
    slist_t 单向链表容器类型。
    slist_iterator_t 单向链表迭代器类型。

Operation Functions
    create_slist 创建单向链表容器类型。
    slist_assign 使用单向链表为当前的单向链表类型赋值。
    slist_assign_elem 使用指定的数据为单向链表赋值。
    slist_assign_range 使用指定数据区间中的数据为单向链表赋值。
    slist_begin 返回指向单向链表第一个数据的迭代器。
    slist_clear 删除单向链表中所有数据。
    slist_destroy 销毁单向链表。
    slist_empty 测试单向链表是否为空。
    slist_end 返回单向链表末尾位置的迭代器。
    slist_equal 测试两个单向链表是否相等。
    slist_erase 删除单向链表中指定位置的数据。
    slist_erase_after 删除单向链表中指定位置后面的那个数据。
    slist_erase_after_range 删除单向链表中指定数据区间后面数据区间的数据。
    slist_erase_range 删除单向链表中指定数据区间的数据。
    slist_front 访问单向链表中第一个数据。
    slist_greater 测试第一个单向链表是否大于第二个单向链表。
    slist_greater_equal 测试第一个单向链表是否大于等于第二个单向链表。
    slist_init 初始化一个空的单向链表。
    slist_init_copy 使用一个单向链表初始化当前单向链表。
    slist_init_copy_range 使用一个指定的数据区间中的数据初始化单向链表。
    slist_init_elem 使用指定的数据初始化单向链表。
    slist_init_n 使用多个默认数据初始化单向链表。
    slist_insert 向单向链表的指定位置插入一个数据。
    slist_insert_after 向单向链表的指定位置的下一个位置插入一个数据。
    slist_insert_after_n 向单向链表的指定位置的下一个位置插入多个数据。
    slist_insert_after_range 向单向链表的指定位置的下一个位置插入数据区间中的数据。
    slist_insert_n 向单向链表的指定位置插入多个数据。
    slist_insert_range 向单向链表的指定位置插入数据区间中的数据。
    slist_less 测试第一个单向链表是否小于第二个单向链表。
    slist_less_equal 测试第一个单向链表是否小于等于第二个单向链表。
    slist_max_size 返回单向链表中能够保存数据的最大数量。
    slist_merge 合并两个单向链表。
    slist_merge_if 按照指定规则合并单向链表。
    slist_not_equal 测试两个单向链表是否不等。
    slist_pop_front 删除单向链表中的第一个数据。
    slist_previous 获得指定位置的前一个位置的迭代器。
    slist_push_front 在单向链表的开头添加一个数据。
    slist_remove 删除单向链表中与指定数据相等的数据。
    slist_remove_if 删除单向链表中与满足指定规则的数据。
    slist_resize 设置新的数据个数。
    slist_resize_elem 设置新的数据个数，如果新的数据个数超过当前数据个数，使用指定数据填充。
    slist_reverse 将单向链表中的数据逆序。
    slist_size 返回单向链表中数据的个数。
    slist_sort 将单向链表中的数据排序。
    slist_sort_if 将单向链表中的数据按照指定规则排序。
    slist_splice 将源单向链表中的数据转移到目的单向链表中的指定位置。
    slist_splice_after_pos 将源单向链表中指定位置后面的那个数据转移到目的单向链表指定位置后面。
    slist_splice_after_range 将源单向链表中指定数据区间下面区间中的数据转移到目的单向链表指定位置后面。
    slist_splice_pos 将源单向链表中指定位置的数据转移到目标单向链表的指定位置。
    slist_splice_range 将源单向链表中指定的数据区间转移到目的单向链表的指定位置。
    slist_swap 交换两个单向链表的内容。
    slist_unique 删除单向链表中相邻的重复数据。
    slist_unique_if 删除单向链表中相邻的满足指定规则的数据。
*/

#include <stdio.h>
#include <cstl/cslist.h>
#include <cstl/cfunctional.h>

//是否是奇数
static void is_odd(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    slist_t* pslist_l1 = create_slist(int); //创建单向链表容器类型。
    slist_t* pslist_l2 = create_slist(int);
    slist_iterator_t it_l; // 单向链表迭代器类型。

    int* pn_i = NULL;
    int* pn_j = NULL;

    if(pslist_l1 == NULL || pslist_l2 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1); //初始化一个空的单向链表容器。
    slist_init(pslist_l2);

    slist_push_front(pslist_l1, 10);//向slist_t开头添加一个数据。
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 30);
    slist_push_front(pslist_l2, 40);
    slist_push_front(pslist_l2, 50);
    slist_push_front(pslist_l2, 60);

    printf("l1 =");
    //slist_begin: 返回指向slist_t中第一个数据的迭代器。
    //slist_end: 返回指向slist_t末尾的迭代器。
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    //30 20 10
    printf("\n");

    //将另一个单向链表赋值给当前的单向链表。
    slist_assign(pslist_l1, pslist_l2); //pslist_l1 = 60 50 40

    //使用指定数据区间为单向链表赋值。
    slist_assign_range(pslist_l1, iterator_next(slist_begin(pslist_l2)), slist_end(pslist_l2));
    //pslist_l1 = 50 40

    //使用指定数据为单向链表赋值。
    slist_assign_elem(pslist_l1, 5, 4); //pslist_l1 = 4 4 4 4 4

    //删除slist_t中的所有数据。
    slist_clear(pslist_l1);
    
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    
    //访问slist_t中的第一个数据。
    pn_i = (int*)slist_front(pslist_l1);
    printf("The first integer of l1 is %d\n", *pn_i);//20

    //测试slist_t是否为空。
    if(slist_empty(pslist_l1))
    {
        printf("The slist is empty.\n");
    }
    else
    {
        printf("The slist is not empty.\n");
    }
    
    //测试两个slist_t是否相等。 
    if(slist_equal(pslist_l1, pslist_l2))
    {
        ;
    }

    //测试两个slist_t是否不等
    if(slist_not_equal(pslist_l1, pslist_l2))
    {
        ;
    }

    //测试第一个slist_t是否大于第二个slist_t
    if(slist_greater(pslist_l1, pslist_l2))
    {
        ;
    }

    // 测试第一个slist_t是否大于等于第二个slist_t。
    if(slist_greater_equal(pslist_l1, pslist_l2))
    {
        ;
    }

    //测试第一个slist_t是否小于第二个slist_t。
    if(slist_less(pslist_l1, pslist_l2))
    {
        ;
    }

    //测试第一个slist_t是否小于等于第二个slist_t
    if(slist_less_equal(pslist_l1, pslist_l2))
    {
        ;
    }

    slist_push_front(pslist_l1, 30);
    slist_push_front(pslist_l1, 40);
    slist_push_front(pslist_l1, 50); //50 40 30 20 10

    //删除slist_t中指定位置的数据。
    slist_erase(pslist_l1, slist_begin(pslist_l1));//40 30 20 10

    //删除slist_t中指定数据区间的数据。
    slist_erase_range(pslist_l1, iterator_next(slist_begin(pslist_l1)),
        slist_end(pslist_l1)); //40

    slist_clear(pslist_l1);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 30);
    slist_push_front(pslist_l1, 40);
    slist_push_front(pslist_l1, 50);

    //slist_erase_after 删除单向链表中指定位置后面的那个数据。
    slist_erase_after(pslist_l1, slist_begin(pslist_l1));//50 30 20 10

    //slist_erase_after_range 删除单向链表中指定数据区间后面数据区间的数据。
    slist_erase_after_range(pslist_l1, slist_begin(pslist_l1),
        slist_end(pslist_l1));//50
    
    slist_clear(pslist_l1);
    slist_clear(pslist_l2);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 30);// 30 20 10
    slist_push_front(pslist_l2, 40);
    slist_push_front(pslist_l2, 50);
    slist_push_front(pslist_l2, 60);//60 50 40

    //slist_insert 向单向链表的指定位置插入一个数据。 30 100 20 10
    slist_insert(pslist_l1, iterator_next(slist_begin(pslist_l1)), 100);

    //slist_insert_n 向单向链表的指定位置插入多个数据。30 100 200 200 20 10
    slist_insert_n(pslist_l1, iterator_advance(slist_begin(pslist_l1), 2), 2, 200);

    //slist_insert_range 向单向链表的指定位置插入数据区间中的数据。30 60 50 40 100 200 200 20 10
    slist_insert_range(pslist_l1, iterator_next(slist_begin(pslist_l1)), slist_begin(pslist_l2), slist_end(pslist_l2));

    //slist_insert_after 向单向链表的指定位置的下一个位置插入一个数据。30 -100 60 50 40 100 200 200 20 10
    slist_insert_after(pslist_l1, slist_begin(pslist_l1), -100);
 
    //slist_insert_after_n 向单向链表的指定位置的下一个位置插入多个数据。30 -200 -200 -100 60 50 40 100 200 200 20 10
    slist_insert_after_n(pslist_l1, slist_begin(pslist_l1), 2, -200); 

    //slist_insert_after_range 向单向链表的指定位置的下一个位置插入数据区间中的数据。
    //30 60 50 40 -200 -200 -100 60 50 40 100 200 200 20 10
    slist_insert_after_range(pslist_l1, slist_begin(pslist_l1), slist_begin(pslist_l2), slist_end(pslist_l2));



    //返回slist_t中保存数据的可能的最大数量。 这是一个与系统相关的常量。
    printf("Maximum possible length of the slist is %u\n",
        slist_max_size(pslist_l1));

    //slist_pop_front 删除第一个数据。
    slist_pop_front(pslist_l1);

    it_l = slist_end(pslist_l1);
    
    // 返回前一个数据的迭代器。
    it_l = slist_previous(pslist_l1, it_l);
    printf("The last element of list is %d\n",
        *(int*)iterator_get_pointer(it_l)); //20
    
    //slist_push_front 在单向链表的开头添加一个数据。
    slist_push_front(pslist_l1, 2);//2 

    slist_clear(pslist_l1);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 21);
    slist_push_front(pslist_l1, 25);
    slist_push_front(pslist_l1, 30);// 30 25 21 10
    //删除slist_t中与指定数据相等的数据。
    slist_remove(pslist_l1, 21); // 30 25 10

    //删除单向链表中符合特定规则的数据。
    slist_remove_if(pslist_l1, is_odd); //2 // 30  10

    //重设slist_t中数据的个数，当新的数据个数比当前个数多，多处的数据使用默认数据0填充
   
    slist_resize(pslist_l1, 4); // 30 10 0 0
    slist_resize(pslist_l1, 2); // 30 10

    //重设slist_t中数据的个数，当新的数据个数比当前个数多，多处的数据使用指定数据填充。
    slist_resize_elem(pslist_l1, 4, 60); // 30 10 60 60

    //将slist_t中的数据逆序。
    slist_reverse(pslist_l1);// 60 60 10 30

    //返回slist_t中数据的个数
    printf("slist length is %d\n", slist_size(pslist_l1)); // 4
    

    //使用默认的规则排序，排序后数据的顺序从小到大。
    slist_sort(pslist_l1); // 10 30 60 60

    //使用指定规则bfun_op排序
    slist_sort_if(pslist_l1, fun_greater_int); // 60 60 30 10

    slist_clear(pslist_l1);
    slist_clear(pslist_l2);
    
    slist_push_front(pslist_l1, 6);
    slist_push_front(pslist_l1, 3); // 3 6
    slist_push_front(pslist_l2, 4);
    slist_push_front(pslist_l2, 2); // 2 4
    
    //slist_merge 合并两个有序的单向链表。
    slist_merge(pslist_l2, pslist_l1);
    // pslist_l2 = 2 3 4 6
    // pslist_l = []
    
    slist_push_front(pslist_l1, 1);
    slist_push_front(pslist_l1, 5); // 5 1
    slist_sort_if(pslist_l2, fun_greater_int);
    
    //slist_merge_if 按照特定规则合并两个有序的单向链表
    slist_merge_if(pslist_l2, pslist_l1, fun_greater_int);
    for(it_l = slist_begin(pslist_l2);
        !iterator_equal(it_l, slist_end(pslist_l2));
    it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");
    // pslist_l2 = 6 5 4 3 2 1
    // pslist_l = []
  
   
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 11);
    //slist_splice 将单向链表中的数据转移到另一个单向链表中。
    slist_splice(pslist_l2, iterator_next(slist_begin(pslist_l2)), pslist_l1);
    // pslist_l2 = 6 11 5 4 3 2 1
    // pslist_l = []
    slist_push_front(pslist_l1, 12);
    slist_push_front(pslist_l1, 13); // 13 12
    
    //slist_splice_pos 将制定位置的数据转移到另一个单向链表中。
    slist_splice_pos(pslist_l2, iterator_next(slist_begin(pslist_l2)),
        pslist_l1, slist_begin(pslist_l1));
    // pslist_l2 = 6 13 10 11 5 4 3 2 1
    // pslist_l = 12

    slist_push_front(pslist_l1, 14); 
    slist_push_front(pslist_l1, 15); // 15 14 12

    //slist_splice_range 将制定区间的数据转移到另一个单向链表中。
    slist_splice_range(pslist_l2, iterator_next(slist_begin(pslist_l2)),
        pslist_l1, slist_begin(pslist_l1), slist_end(pslist_l1));
    // pslist_l2 =  6 15 14 12 13 10 11 5 4 3 2 1
    // pslist_l = 0

    //slist_splice_after_pos 将源单向链表中指定位置后面的那个数据转移到目的单向链表指定位置后面。
    slist_push_front(pslist_l1, 16); 
    slist_push_front(pslist_l1, 17); 
    slist_push_front(pslist_l1, 18);  
    slist_push_front(pslist_l1, 19); //19 18 17 16
    slist_splice_after_pos(pslist_l2, slist_begin(pslist_l2),
        pslist_l1, slist_begin(pslist_l1));
    // pslist_l2 = 6 18 15 14 12 13 10 11 5 4 3 2 1  //为什么不是19
    // pslist_l = 19 17 16
    for(it_l = slist_begin(pslist_l2);
        !iterator_equal(it_l, slist_end(pslist_l2));
    it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");    
    //slist_splice_after_range 将源单向链表中指定数据区间下面区间中的数据转移到目的单向链表指定位置后面。
    slist_splice_after_range(pslist_l2, slist_begin(pslist_l2),
        pslist_l1, slist_begin(pslist_l1),
        iterator_advance(slist_begin(pslist_l1), 2));
    // pslist_l2 = 6 17 16 18 15 14 12 13 10 11 5 4 3 2 1
    // pslist_l = 19
    
    for(it_l = slist_begin(pslist_l2);
    !iterator_equal(it_l, slist_end(pslist_l2));
    it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");
    
    // 交换两个slist_t中的内容
    slist_swap(pslist_l1, pslist_l2);

    slist_clear(pslist_l1);
    slist_clear(pslist_l2);
    slist_push_front(pslist_l1, -10);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, -10);
    
    //slist_unique 删除相邻的重复数据。
    slist_assign(pslist_l2, pslist_l1); //-10 20 10 -10
        
    //slist_unique_if 删除相邻的满足规则的数据。
    slist_unique(pslist_l1); // -10 -10

    //销毁slist_t
    slist_destroy(pslist_l1);
    slist_destroy(pslist_l2);

    
    slist_t* pslist_l0 = create_slist(int);
    pslist_l1 = create_slist(int);
    pslist_l2 = create_slist(int);
    slist_t* pslist_l3 = create_slist(int);
    slist_t* pslist_l4 = create_slist(int);

    if(pslist_l0 == NULL || pslist_l1 == NULL || pslist_l2 == NULL || pslist_l3 == NULL || pslist_l4 == NULL)
    {
        return -1;
    }

    //slist_init 初始化一个空的单向链表容器。
    slist_init(pslist_l0);

    //slist_init_n 使用指定个数的默认数据初始化单向链表。
    slist_init_n(pslist_l1, 3);//0 0 0

    //slist_init_elem 使用指定数据初始化单向链表。
    slist_init_elem(pslist_l2, 5, 2);// 2 2 2 2 2

    //slist_init_copy 使用另一个单向链表初始化当前的单向链表。
    slist_init_copy(pslist_l3, pslist_l2); //2 // 2 2 2 2 2 

    //slist_init_copy_range 使用指定的数据区间初始化单向链表。
    slist_init_copy_range(pslist_l4, iterator_advance(slist_begin(pslist_l3), 2), slist_end(pslist_l3));//2 // 2 2 2

    //销毁slist_t
    slist_destroy(pslist_l0);
    slist_destroy(pslist_l1);
    slist_destroy(pslist_l2);
    slist_destroy(pslist_l3);
    slist_destroy(pslist_l4);

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
