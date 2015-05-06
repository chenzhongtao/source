/*
file: set.c

集合set_t
集合容器set_t是关联容器，set_t中的数据按照键和指定的规则自动排序并且保证键是唯一的，set_t中的键就
是数据本身。set_t中的数据不可以直接或者通过迭代器修改，因为这样会破会set_t中数据的有序性，要想修改一个
数据只有先删除它然后插入新的数据。set_t支持双向迭代器。插入新数据是不会破坏原有的迭代器，删除数据是只有
指向被删除的数据的迭代器失效。set_t对于数据的查找，插入和删除都是高效的。set_t中的数据根据指定的规则自动
排序，默认的排序规则是使用数据的小于操作符，用户可以在初始化时指定自定义的排序规则。

Typedefs
    set_t 集合容器类型。
    set_iterator_t 集合容器迭代器类型

Operation Functions
    create_set 创建集合容器类型
    set_assign 为集合容器赋值。
    set_begin 返回指向集合中第一个数据的迭代器。
    set_clear 删除集合容器中的所有数据。
    set_count 返回集合容器中包含指定数据的个数。
    set_destroy 销毁集合容器。
    set_empty 测试集合容器是否为空。
    set_end 返回指向集合容器末尾位置的迭代器。
    set_equal 测试两个集合容器是否相等。
    set_equal_range 返回一个集合容器中包含指定数据的数据区间。
    set_erase 删除集合容器中与指定数据相等的数据。
    set_erase_pos 删除集合容器中指定位置的数据。
    set_erase_range 删除集合容器中指定数据区间的数据。
    set_find 在集合容器中查找指定的数据。
    set_greater 测试第一个集合是否大于第二个集合。
    set_greater_equal 测试第一个集合是否大于等于第二个集合。
    set_init 初始化一个空的集合容器。
    set_init_copy 使用一个集合容器的内容来初始化当前集合容器。
    set_init_copy_range 使用指定的数据区间初始化集合容器。
    set_init_copy_range_ex 使用指定的数据区间和指定的排序规则初始化集合容器。
    set_init_ex 使用指定的排序规则初始化一个空的集合容器。
    set_insert 向集合中插入一个数据。
    set_insert_hint 向集合中插入一个数据同时给出位置提示。
    set_insert_range 向集合中插入指定数据区间的数据。
    set_key_comp 返回集合容器的键比较规则。
    set_less 测试第一个集合容器是否小于第二个集合容器。
    set_less_equal 测试第一个集合容器是否小于等于第二个集合容器。
    set_lower_bound 返回集合中与指定数据相等的第一个数据的迭代器。
    set_max_size 返回集合中能够保存的数据个数的最大可能值。
    set_not_equal 测试两个集合是否不等。
    set_size 返回集合中保存的数据的数量。
    set_swap 交换两个集合的内容。
    set_upper_bound 返回集合中大于指定数据的第一个数据的迭代器。
    set_value_comp 获得集合中的数据比较规则。

*/


#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    set_t* pset_s1 = create_set(int); //创建set_t类型
    set_t* pset_s2 = create_set(int);
    set_iterator_t it_s;  //set_t类型的迭代器类型

    if(pset_s1 == NULL || pset_s2 == NULL)
    {
        return -1;
    }

    set_init(pset_s1); //初始化set_t类型
    set_init(pset_s2);

    set_insert(pset_s1, 10);//向集合中插入一个数据。
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    
    set_insert(pset_s2, 40);
    set_insert(pset_s2, 50);
    set_insert(pset_s2, 60);

    //set_begin: 返回指向set_t第一个数据的迭代器
    //set_end: 返回指向set_t末尾位置的迭代器
    printf("s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    // 10 20 30
    printf("\n");
    
    //使用set_t类型为当前的set_t赋值
    set_assign(pset_s1, pset_s2);
    printf("s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    // 40 50 60
    printf("\n");

    //删除set_t中的所有数据。
    set_clear(pset_s1);
    
    set_insert(pset_s1, 1);
    set_insert(pset_s1, 1);
    
    //set_count 返回容器中包含指定数据的个数
    printf("The number of elements in s1 with a sort key of 1 is: %d.\n",
        set_count(pset_s1, 1)); //1// 1
    printf("The number of elements in s1 with a sort key of 2 is: %d.\n",
        set_count(pset_s1, 2)); //1// 0

    // 测试set_t容器是否为空
    if(set_empty(pset_s1))
    {
        printf("The set s1 is empty.\n");
    }

    //测试两个set_t是否相等
    if(set_equal(pset_s1, pset_s2))
    {
        printf("The sets s1 and s2 are equal.\n");
    }

    //测试第一个set_t容器是否大于第二个set_t容器
    if(set_greater(pset_s1, pset_s2))
    {
        printf("The set s1 is greater than the set s2.\n");
    }

    //测试第一个set_t是否大于等于第二个set_t
    if(set_greater_equal(pset_s1, pset_s2))
    {
        printf("The set s1 is greater than or equal to the set s2.\n");
    }

    //测试第一个set_t是否小于第二个set_t
    if(set_less(pset_s1, pset_s2))
    {
        printf("The set s1 is less than the set s2.\n");
    }

    //测试第一个set_t是否小于等于第二个set_t
    if(set_less_equal(pset_s1, pset_s2))
    {
        printf("The set s1 is less than or equal to the set s2.\n");
    }
    
    //测试两个set_t是否不等
    if(set_not_equal(pset_s1, pset_s2))
    {
        printf("The sets s1 and s2 are not equal.\n");
    }
    
    range_t r_r1;
    set_clear(pset_s1);
    
    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);

    //返回set_t中包含指定数据的数据区间
    r_r1 = set_equal_range(pset_s1, 20); //返回数据区间大于等于20的

    printf("The upper bound of the element with a key of 20 in the set s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_end)); //30
    printf("The lower bound of the element with a key of 20 in the set s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_begin)); //20

    //返回set_t中大于指定数据的第一个数据的迭代器
    it_s = set_upper_bound(pset_s1, 20);
    printf("A direct call of upper_bound(20), gives %d,\n", *(int*)iterator_get_pointer(it_s));//30
    printf("matching the 2nd element of the range returned by equal_range(20).\n");

    r_r1 = set_equal_range(pset_s1, 40);
    /* If no match is found for the key. both elements of the range return end() */
    if(iterator_equal(r_r1.it_begin, set_end(pset_s1)) && iterator_equal(r_r1.it_end, set_end(pset_s1)))
    {
        printf("The set s1 doesn't have and element with a key less than 40.\n");
    }
    else
    {
        printf("The element of set s1 with a key >= 40 is: %d.\n", *(int*)iterator_get_pointer(r_r1.it_begin));
    }

    set_clear(pset_s1);
    
    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    set_insert(pset_s1, 40);
    set_insert(pset_s1, 50);
    
    //set_erase 删除集合容器中与指定数据相等的数据
    int t_count = set_erase(pset_s1, 40); // 10 20 30 50  t_count = 1

    //set_erase_pos 删除集合容器中指定位置的数据
    set_erase_pos(pset_s1, iterator_next(set_begin(pset_s1))); //10 30 50

    //set_erase_range 删除集合容器中指定数据区间的数据
    set_erase_range(pset_s1, iterator_next(set_begin(pset_s1)),
        iterator_prev(set_end(pset_s1))); // 10 50

    //在set_t中查找指定的数据
    it_s = set_find(pset_s1, 10);
    printf("The element of set s1 with a key of 20 is: %d.\n",
        *(int*)iterator_get_pointer(it_s));
    
    it_s = set_find(pset_s1, 40);
    /* If no match is found for the key, end() is returned */
    if(iterator_equal(it_s, set_end(pset_s1)))
    {
        printf("The set s1 doesn't have an element with a key of 40.\n");
    }
    
    set_clear(pset_s1);
    set_clear(pset_s2);

    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    set_insert(pset_s1, 40);

    //向set_t中插入数据,成功后返回指向该数据的迭代器，如果set_t中包含了该数据那么插入失败，返回set_end()
    it_s = set_insert(pset_s1, 10);
    if(iterator_equal(it_s, set_end(pset_s1)))
    {
        printf("The element 10 already exists in s1.\n");
    }
    else
    {
        printf("The element 10 was inserted in s1 successfully.\n");
    }

    // 向set_t中插入一个指定的数据，同时给出一个该数据被插入后的提示位置迭代器，如果这个位置
    //符合set_t的排序规则就把这个数据放在提示位置中成功后返回指向该数据的迭代器，如果提示位置不正确则忽略提
    //示位置，(是不是为了加速)当数据插入成功后返回数据的实际位置迭代器，如果set_t中包含了该数据那么插入失败，返回set_end()
    set_insert_hint(pset_s1, iterator_prev(set_end(pset_s1)), 50);  //10 20 30 40 50
    printf("After the insertions, s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    set_insert(pset_s2, 100);
    set_insert_range(pset_s2, iterator_next(set_begin(pset_s1)), iterator_prev(set_end(pset_s1)));
    printf("s2 =");
    for(it_s = set_begin(pset_s2); !iterator_equal(it_s, set_end(pset_s2)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    //20 30 40 100
    printf("\n");

    set_clear(pset_s1);
    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    
     //获得set_t中等于或者大于指定数据的第一个数据的迭代器
    it_s = set_lower_bound(pset_s1, 20);
    printf("The element of set s1 with a key of 20 is: %d.\n", //20
        *(int*)iterator_get_pointer(it_s));

    //返回set_t中大于指定数据的第一个数据的迭代器
    it_s = set_upper_bound(pset_s1, 20);
    printf("A direct call of upper_bound(20), gives %d,\n", *(int*)iterator_get_pointer(it_s));//30
    printf("matching the 2nd element of the range returned by equal_range(20).\n");
    
    it_s = set_lower_bound(pset_s1, 40);
    /* If no match is found for the key, end() is is returend */
    if(iterator_equal(it_s, set_end(pset_s1)))
    {
        printf("The set s1 doesn't have an element with a key of 40.\n");
    }
    else
    {
        printf("The element of set s1 with a key of 40 is: %d.\n",
            *(int*)iterator_get_pointer(it_s));
    }

    //返回set_t中能够保存的数据个数的最大可能值
    printf("The maximum possible length of the set is %u.\n",
        set_max_size(pset_s1));

    //返回set_t中保存的数据的数量
    printf("The set length is %d.\n", set_size(pset_s1));

    //交换两个set_t中的内容
    set_swap(pset_s1, pset_s2);

    binary_function_t bfun_vl = NULL;
    binary_function_t bfun_kl = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;

    set_clear(pset_s1);
    set_destroy(pset_s2);
    pset_s2 = create_set(int);
    
    //返回set_t中数据的比较规则,由于set_t中数据本身就是键，所以这个函数的返回值与set_key_comp()相同
    bfun_vl = set_value_comp(pset_s1);

    //返回set_t的键比较规则,由于set_t中数据本身就是键，所以这个函数的返回值与set_value_comp()相同
    bfun_kl = set_key_comp(pset_s1);
    n_element1 = 2;
    n_element2 = 3;
    (*bfun_vl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_vl)(2, 3) returns value of true, where bfun_vl is the function of s1.\n");
    }
    else
    {
        printf("(*bfun_vl)(2, 3) returns value of false, where bfun_vl is the function of s1.\n");
    }
    
    set_init_ex(pset_s2, fun_greater_int);

    bfun_vl = set_value_comp(pset_s2);
    bfun_kl = set_key_comp(pset_s1);
    (*bfun_vl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_vl)(2, 3) returns value of true, where bfun_vl is the function of s2.\n");
    }
    else
    {
        printf("(*bfun_vl)(2, 3) returns value of false, where bfun_vl is the function of s2.\n");
    }

    
    set_destroy(pset_s1);
    set_destroy(pset_s2);

    set_t* pset_s0 = create_set(int);
    pset_s1 = create_set(int);
    pset_s2 = create_set(int);
    set_t* pset_s3 = create_set(int);
    set_t* pset_s4 = create_set(int);
    set_t* pset_s5 = create_set(int);

    if(pset_s0 == NULL || pset_s1 == NULL || pset_s2 == NULL || pset_s3 == NULL || pset_s4 == NULL || pset_s5 == NULL)
    {
        return -1;
    }
    
    //set_init 初始化一个空的集合容器
    set_init(pset_s0);

    //set_init_ex 使用指定的排序规则初始化一个空的集合容器
    set_init_ex(pset_s1, fun_less_int);
    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    set_insert(pset_s1, 40); // 10 20 30 40

    //set_init_ex 使用指定的排序规则初始化一个空的集合容器
    set_init_ex(pset_s2, fun_greater_int);
    set_insert(pset_s2, 10);
    set_insert(pset_s2, 20); //20 10

    //set_init_copy 使用一个集合容器的内容来初始化当前集合容器。
    set_init_copy(pset_s3, pset_s1); //10 20 30 40 

    //set_init_copy_range 使用指定的数据区间初始化集合容器。
    set_init_copy_range(pset_s4, set_begin(pset_s1), iterator_advance(set_begin(pset_s1), 2)); //10 20

    //set_init_copy_range_ex 使用指定的数据区间和指定的排序规则初始化集合容器。
    set_init_copy_range_ex(pset_s5, set_begin(pset_s3), iterator_next(set_begin(pset_s3)), fun_less_int);//10 20

    set_destroy(pset_s0);
    set_destroy(pset_s1);
    set_destroy(pset_s2);
    set_destroy(pset_s3);
    set_destroy(pset_s4);
    set_destroy(pset_s5);

    return 0;
}

