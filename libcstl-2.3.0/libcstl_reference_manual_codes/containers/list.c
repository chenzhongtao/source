/*
file: list.c

双向链表list_t
双向链表是序列容器的一种，它以线性的方式保存数据，同时允许在任意位置高效的插入或者删除数据，但
是不能够随机的访问链表中的数据。当从list_t中删除数据的时候，指向被删除数据的迭代器失效。

Typedefs
    list_t 双向链表容器类型。
    list_iterator_t 双向链表迭代器类型�

Operation Functions
    create_list 创建双向链表容器。
    list_assign 将另一个双向链表赋值给当前的双向链表。
    list_assign_elem 使用指定数据为双向链表赋值。
    list_assign_range 使用指定数据区间为双向链表赋值。
    list_back 访问最后一个数据。
    list_begin 返回指向第一个数据的迭代器。
    list_clear 删除所有数据。
    list_destroy 销毁双向链表容器。
    list_empty 测试容器是否为空。
    list_end 返回容器末尾的迭代器。
    list_equal 测试两个双向链表是否相等。
    list_erase 删除指定位置的数据。
    list_erase_range 删除指定数据区间的数据。
    list_front 访问容器中的第一个数据。
    list_greater 测试第一个双向链表是否大于第二个双向链表。
    list_greater_equal 测试第一个双向链表是否大于等于第二个双向链表。
    list_init 初始化一个空的双向链表容器。
    list_init_copy 使用另一个双向链表初始化当前的双向链表。
    list_init_copy_range 使用指定的数据区间初始化双向链表。
    list_init_elem 使用指定数据初始化双向链表。
    list_init_n 使用指定个数的默认数据初始化双向链表。
    list_insert 在指定位置插入一个数据。
    list_insert_range 在指定位置插入一个数据区间。
    list_insert_n 在指定位置插入多个数据。
    list_less 测试第一个双向链表是否小于第二个双向链表。
    list_less_equal 测试第一个双向链表是否小于等于第二个双向链表。
    list_max_size 返回双向链表能够保存的最大数据个数。
    list_merge 合并两个有序的双向链表。
    list_merge_if 按照特定规则合并两个有序的双向链表。
    list_not_equal 测试两个双向链表是否不等。
    list_pop_back 删除最后一个数据。
    list_pop_front 删除第一个数据。
    list_push_back 在双向链表的末尾添加一个数据。
    list_push_front 在双向链表的开头添加一个数据。
    list_remove 删除双向链表中与指定的数据相等的数据。
    list_remove_if 删除双向链表中符合特定规则的数据。
    list_resize 重新设置双向链表中的数据个数，不足的部分采用默认数据填充
    list_resize_elem 重新设置双向链表中的数据个数，不足的部分采用指定数据填充。
    list_reverse 把双向链表中的数据逆序。
    list_size 返回双向链表中数据的个数。
    list_sort 排序双向链表中的数据。
    list_sort_if 按照规则排序双向链表中的数据。
    list_splice 将双向链表中的数据转移到另一个双向链表中。
    list_splice_pos 将制定位置的数据转移到另一个双向链表中。
    list_splice_range 将制定区间的数据转移到另一个双向链表中。
    list_swap 交换两个双向链表的内容。
    list_unique 删除相邻的重复数据。
    list_unique_if 删除相邻的满足规则的数据。
*/

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cfunctional.h>

//是否是奇数
static void is_odd(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int); //创建一个双向链表容器类型
    list_t* plist_l2 = create_list(int);
    list_iterator_t it_l; // 双向链表的迭代器类型

    int* pn_i = NULL;
    int* pn_j = NULL;

    if(plist_l1 == NULL || plist_l2 == NULL)
    {
        return -1;
    }

    list_init(plist_l1); //初始化一个空的双向链表容器。
    list_init(plist_l2);

    list_push_back(plist_l1, 10);//向list_t末尾添加一个数据。
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 30);
    list_push_back(plist_l2, 40);
    list_push_back(plist_l2, 50);
    list_push_back(plist_l2, 60);
/*
list_assign 将另一个双向链表赋值给当前的双向链表。
list_assign_elem 使用指定数据为双向链表赋值。
list_assign_range 使用指定数据区间为双向链表赋值。
*/
    printf("l1 =");
    //list_begin: 返回指向list_t中第一个数据的迭代器。
    //list_end: 返回指向list_t末尾的迭代器。
    for(it_l = list_begin(plist_l1); !iterator_equal(it_l, list_end(plist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    //10 20 30
    printf("\n");

    //将另一个双向链表赋值给当前的双向链表。
    list_assign(plist_l1, plist_l2); //plist_l1 = 40 50 60

    //使用指定数据区间为双向链表赋值。
    list_assign_range(plist_l1, iterator_next(list_begin(plist_l2)), list_end(plist_l2));
    //plist_l1 = 50 60

    //使用指定数据为双向链表赋值。
    list_assign_elem(plist_l1, 5, 4); //plist_l1 = 4 4 4 4 4

    //删除list_t中的所有数据。
    list_clear(plist_l1);
    
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    
    //访问双向链表容器中最后一个数据。
    pn_i = (int*)list_back(plist_l1);
    printf("The last integer of l1 is %d\n", *pn_i);//20

    //访问list_t中的第一个数据。
    pn_i = (int*)list_front(plist_l1);
    printf("The first integer of l1 is %d\n", *pn_i);//10

    //测试list_t是否为空。
    if(list_empty(plist_l1))
    {
        printf("The list is empty.\n");
    }
    else
    {
        printf("The list is not empty.\n");
    }
    
    //测试两个list_t是否相等。 
    if(list_equal(plist_l1, plist_l2))
    {
        ;
    }

    //测试两个list_t是否不等
    if(list_not_equal(plist_l1, plist_l2))
    {
        ;
    }

    //测试第一个list_t是否大于第二个list_t
    if(list_greater(plist_l1, plist_l2))
    {
        ;
    }

    // 测试第一个list_t是否大于等于第二个list_t。
    if(list_greater_equal(plist_l1, plist_l2))
    {
        ;
    }

    //测试第一个list_t是否小于第二个list_t。
    if(list_less(plist_l1, plist_l2))
    {
        ;
    }

    //测试第一个list_t是否小于等于第二个list_t
    if(list_less_equal(plist_l1, plist_l2))
    {
        ;
    }

    list_push_back(plist_l1, 30);
    list_push_back(plist_l1, 40);
    list_push_back(plist_l1, 50); // 10 20 30 40 50 

    //删除list_t中指定位置的数据。
    list_erase(plist_l1, list_begin(plist_l1));//20 30 40 50

    //删除list_t中指定数据区间的数据。
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
    //list_insert 在指定位置插入一个数据。
    //list_insert_range 在指定位置插入一个数据区间。
    //list_insert_n 在指定位置插入多个数据。

    //在指定位置插入一个数据。 10 100 20 30
    list_insert(plist_l1, iterator_next(list_begin(plist_l1)), 100); 
    

    //在指定位置插入多个数据。10 100 200 200 20 30
    list_insert_n(plist_l1, iterator_advance(list_begin(plist_l1), 2), 2, 200);

    //在指定位置插入一个数据区间 10 40 50 100 200 200 20 30
    list_insert_range(plist_l1, iterator_next(list_begin(plist_l1)), list_begin(plist_l2), iterator_prev(list_end(plist_l2)));

    //返回list_t中保存数据的可能的最大数量。 这是一个与系统相关的常量。
    printf("Maximum possible length of the list is %u\n",
        list_max_size(plist_l1));

    //list_pop_back 删除最后一个数据。
    list_pop_back(plist_l1);//10 40 50 100 200 200 20

    //list_pop_front 删除第一个数据。
    list_pop_front(plist_l1);//40 50 100 200 200 20
    
    //list_push_back 在双向链表的末尾添加一个数据。
    list_push_back(plist_l1, 1);//40 50 100 200 200 20 1

    //list_push_front 在双向链表的开头添加一个数据。
    list_push_front(plist_l1, 2);//2 //2 40 50 100 200 200 20 1

    //删除list_t中与指定数据相等的数据。
    list_remove(plist_l1, 200); // 2 40 50 100 20 1

    //删除双向链表中符合特定规则的数据。
    list_remove_if(plist_l1, is_odd); //2 //40 50 100 20

    //重设list_t中数据的个数，当新的数据个数比当前个数多，多处的数据使用默认数据0填充
    list_resize(plist_l1, 2); // 40 50
    list_resize(plist_l1, 4); // 40 50 0 0

    //重设list_t中数据的个数，当新的数据个数比当前个数多，多处的数据使用指定数据填充。
    list_resize_elem(plist_l1, 5, 60); // 40 50 0 0 60

    //将list_t中的数据逆序。
    list_reverse(plist_l1);// 60 0 0 50 40

    //返回list_t中数据的个数
    printf("List length is %d\n", list_size(plist_l1)); //5
    

    //使用默认的规则排序，排序后数据的顺序从小到大。
    list_sort(plist_l1); // 0 0 40 50 60

    //使用指定规则bfun_op排序
    list_sort_if(plist_l1, fun_greater_int); // 60 50 40 0 0

    list_clear(plist_l1);
    list_clear(plist_l2);
    
    list_push_back(plist_l1, 3);
    list_push_back(plist_l1, 6); // 3 6
    list_push_back(plist_l2, 2);
    list_push_back(plist_l2, 4); // 2 4
    
    //list_merge 合并两个有序的双向链表。
    list_merge(plist_l2, plist_l1);
    // plist_l2 = 2 3 4 6
    // plist_l = []
    
    list_push_back(plist_l1, 5);
    list_push_back(plist_l1, 1); // 5 1
    list_sort_if(plist_l2, fun_greater_int);
    
    //list_merge_if 按照特定规则合并两个有序的双向链表
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
  
    //list_splice 将双向链表中的数据转移到另一个双向链表中。
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 11);
    list_splice(plist_l2, iterator_next(list_begin(plist_l2)), plist_l1);
    // plist_l2 = 6 10 11 5 4 3 2 1
    // plist_l = []
    list_push_back(plist_l1, 12);
    list_push_back(plist_l1, 13); // 12 13
    
    //list_splice_pos 将制定位置的数据转移到另一个双向链表中。
    list_splice_pos(plist_l2, iterator_next(list_begin(plist_l2)),
        plist_l1, list_begin(plist_l1));
    // plist_l2 = 6 12 10 11 5 4 3 2 1
    // plist_l = 13

    list_push_back(plist_l1, 14); 
    list_push_back(plist_l1, 15); // 13 14 15

    //list_splice_range 将制定区间的数据转移到另一个双向链表中。
    list_splice_range(plist_l2, iterator_next(list_begin(plist_l2)),
        plist_l1, list_begin(plist_l1), iterator_prev(list_end(plist_l1)));
    // plist_l2 = 6 13 14 12 10 11 5 4 3 2 1
    // plist_l = 15

    // 交换两个list_t中的内容
    list_swap(plist_l1, plist_l2);

    list_clear(plist_l1);
    list_clear(plist_l2);
    list_push_back(plist_l1, -10);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, -10);
    
    //list_unique 删除相邻的重复数据。
    list_assign(plist_l2, plist_l1); //-10 10 20 -10
        
    //list_unique_if 删除相邻的满足规则的数据。
    list_unique(plist_l1); // -10 -10

    //销毁list_t
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

    //list_init 初始化一个空的双向链表容器。
    list_init(plist_l0);

    //list_init_n 使用指定个数的默认数据初始化双向链表。
    list_init_n(plist_l1, 3);//0 0 0

    //list_init_elem 使用指定数据初始化双向链表。
    list_init_elem(plist_l2, 5, 2);// 2 2 2 2 2

    //list_init_copy 使用另一个双向链表初始化当前的双向链表。
    list_init_copy(plist_l3, plist_l2); //2 // 2 2 2 2 2 

    //list_init_copy_range 使用指定的数据区间初始化双向链表。
    list_init_copy_range(plist_l4, iterator_advance(list_begin(plist_l3), 2), list_end(plist_l3));//2 // 2 2 2

    //销毁list_t
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
