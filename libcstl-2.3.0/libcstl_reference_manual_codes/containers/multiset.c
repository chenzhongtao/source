/*
file: multiset.c

多重集合multiset_t

多重集合容器multiset_t是关联容器，multiset_t中的数据是按照键和指定的规则自动排序但它允许多个相同的
键存在，multiset_t中的键就是数据本身。multiset_t中的数据不可以直接或者通过迭代器修改，因为这样会破坏
multiset_t中数据的有序性，要想修改一个数据只有先删除它然后插入新的数据。multiset_t支持双向迭代器。插入新
数据是不会破坏原有的迭代器，删除数据是只有指向被删除的数据的迭代器失效。multiset_t对于数据的查找，插入和
删除都是高效的。multiset_t中的数据根据指定的规则自动排序，默认的排序规则是使用数据的小于操作符，用户可以
在初始化时指定自定义的排序规则。

Typedefs
    multiset_t 多重集合容器类型。
    multiset_iterator_t 多重集合容器迭代器类型。
Operation Functions
    create_multiset 创建多重集合容器类型。
multiset_assign 为多重集合容器赋值。
multiset_begin 返回指向多重集合容器中第一个数据的迭代器。
multiset_clear 删除多重集合中的所有数据。
multiset_count 返回多重集合容器中包含指定数据的个数。
multiset_destroy 销毁多重集合容器。
multiset_empty 测试多重集合容器是否为空。
multiset_end 返回指向多重集合容器末尾的迭代器。
multiset_equal 测试两个多重集合容器是否相等。
multiset_equal_range 获得多重集合容器中包含指定数据的数据区间。
multiset_erase 删除指定数据。
multiset_erase_pos 删除指定位置的数据。
multiset_erase_range 删除指定数据区间的数据。
multiset_find 在多重集合容器中查找指定的数据。
multiset_greater 测试第一个多重集合容器是否大于第二个多重集合容器。
multiset_greater_equal 测试第一个多重集合容器是否大于等于第二个多重集合容器。
multiset_init 初始化一个空的多重集合容器。
multiset_init_copy 使用一个已经存在的多重集合容器来初始化当前的多重集合容器。
multiset_init_copy_range 使用指定区间中的数据初始化多重集合容器。
multiset_init_copy_range_ex 使用指定的数据区间和指定的排序规则初始化多重集合容器。
multiset_init_ex 使用指定的排序规则初始化一个空的多重集合容器。
multiset_insert 向多重集合容器中插入一个指定的数据。
multiset_insert_hint 向多重集合容器中插入一个指定的数据，并给出位置提示。
multiset_insert_range 向多重集合容器中插入一个指定的数据区间。
multiset_key_comp 返回多重集合容器使用的键比较规则。
multiset_less 测试第一个多重集合容器是否小于第二个多重集合容器。
multiset_less_equal 测试第一个多重集合容器是否小于等于第二个多重集合容器。
multiset_lower_bound 返回多重集合容器中等于指定数据的第一个数据的迭代器。
multiset_max_size 返回多重集合容器能够保存的数据数量的最大可能值。
multiset_not_equal 测试两个多重集合容器是否不等。
multiset_size 返回多重集合容器中数据的数量。
multiset_swap 交换两个多重集合容器的内容。
multiset_upper_bound 返回多重集合容器中大于指定数据的第一个数据的迭代器。
multiset_value_comp 返回多重集合容器使用的数据比较规则。

*/


#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int); //创建multiset_t类型
    multiset_t* pmset_s2 = create_multiset(int);
    multiset_iterator_t it_s;  //multiset_t类型的迭代器类型

    if(pmset_s1 == NULL || pmset_s2 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1); //初始化multiset_t类型
    multiset_init(pmset_s2);

    multiset_insert(pmset_s1, 10);//向多重集合中插入一个数据。
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    
    multiset_insert(pmset_s2, 40);
    multiset_insert(pmset_s2, 50);
    multiset_insert(pmset_s2, 60);

    //multiset_begin: 返回指向multiset_t第一个数据的迭代器
    //multiset_end: 返回指向multiset_t末尾位置的迭代器
    printf("s1 =");
    for(it_s = multiset_begin(pmset_s1); !iterator_equal(it_s, multiset_end(pmset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    // 10 20 30
    printf("\n");
    
    //使用multiset_t类型为当前的multiset_t赋值
    multiset_assign(pmset_s1, pmset_s2);
    printf("s1 =");
    for(it_s = multiset_begin(pmset_s1); !iterator_equal(it_s, multiset_end(pmset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    // 40 50 60
    printf("\n");

    //删除multiset_t中的所有数据。
    multiset_clear(pmset_s1);
    
    multiset_insert(pmset_s1, 1);
    multiset_insert(pmset_s1, 1);
    
    //multiset_count 返回容器中包含指定数据的个数
    printf("The number of elements in s1 with a sort key of 1 is: %d.\n",
        multiset_count(pmset_s1, 1)); //1// 2
    printf("The number of elements in s1 with a sort key of 2 is: %d.\n",
        multiset_count(pmset_s1, 2)); //1// 0

    // 测试multiset_t容器是否为空
    if(multiset_empty(pmset_s1))
    {
        printf("The multiset s1 is empty.\n");
    }

    //测试两个multiset_t是否相等
    if(multiset_equal(pmset_s1, pmset_s2))
    {
        printf("The multisets s1 and s2 are equal.\n");
    }

    //测试第一个multiset_t容器是否大于第二个multiset_t容器
    if(multiset_greater(pmset_s1, pmset_s2))
    {
        printf("The multiset s1 is greater than the multiset s2.\n");
    }

    //测试第一个multiset_t是否大于等于第二个multiset_t
    if(multiset_greater_equal(pmset_s1, pmset_s2))
    {
        printf("The multiset s1 is greater than or equal to the multiset s2.\n");
    }

    //测试第一个multiset_t是否小于第二个multiset_t
    if(multiset_less(pmset_s1, pmset_s2))
    {
        printf("The multiset s1 is less than the multiset s2.\n");
    }

    //测试第一个multiset_t是否小于等于第二个multiset_t
    if(multiset_less_equal(pmset_s1, pmset_s2))
    {
        printf("The multiset s1 is less than or equal to the multiset s2.\n");
    }
    
    //测试两个multiset_t是否不等
    if(multiset_not_equal(pmset_s1, pmset_s2))
    {
        printf("The multisets s1 and s2 are not equal.\n");
    }
    
    range_t r_r1;
    multiset_clear(pmset_s1);
    
    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);

    //返回multiset_t中包含指定数据的数据区间
    r_r1 = multiset_equal_range(pmset_s1, 20); //返回数据区间大于等于20的

    printf("The upper bound of the element with a key of 20 in the multiset s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_end)); //30
    printf("The lower bound of the element with a key of 20 in the multiset s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_begin)); //20

    //返回multiset_t中大于指定数据的第一个数据的迭代器
    it_s = multiset_upper_bound(pmset_s1, 20);
    printf("A direct call of upper_bound(20), gives %d,\n", *(int*)iterator_get_pointer(it_s));//30
    printf("matching the 2nd element of the range returned by equal_range(20).\n");

    r_r1 = multiset_equal_range(pmset_s1, 40);
    /* If no match is found for the key. both elements of the range return end() */
    if(iterator_equal(r_r1.it_begin, multiset_end(pmset_s1)) && iterator_equal(r_r1.it_end, multiset_end(pmset_s1)))
    {
        printf("The multiset s1 doesn't have and element with a key less than 40.\n");
    }
    else
    {
        printf("The element of multiset s1 with a key >= 40 is: %d.\n", *(int*)iterator_get_pointer(r_r1.it_begin));
    }

    multiset_clear(pmset_s1);
    
    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    multiset_insert(pmset_s1, 40);
    multiset_insert(pmset_s1, 50);
    
    //multiset_erase 删除多重集合容器中与指定数据相等的数据
    int t_count = multiset_erase(pmset_s1, 40); // 10 20 30 50  t_count = 1

    //multiset_erase_pos 删除多重集合容器中指定位置的数据
    multiset_erase_pos(pmset_s1, iterator_next(multiset_begin(pmset_s1))); //10 30 50

    //multiset_erase_range 删除多重集合容器中指定数据区间的数据
    multiset_erase_range(pmset_s1, iterator_next(multiset_begin(pmset_s1)),
        iterator_prev(multiset_end(pmset_s1))); // 10 50

    //在multiset_t中查找指定的数据
    it_s = multiset_find(pmset_s1, 10);
    printf("The element of multiset s1 with a key of 20 is: %d.\n",
        *(int*)iterator_get_pointer(it_s));
    
    it_s = multiset_find(pmset_s1, 40);
    /* If no match is found for the key, end() is returned */
    if(iterator_equal(it_s, multiset_end(pmset_s1)))
    {
        printf("The multiset s1 doesn't have an element with a key of 40.\n");
    }
    
    multiset_clear(pmset_s1);
    multiset_clear(pmset_s2);

    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    multiset_insert(pmset_s1, 40);

    //向multiset_t中插入一个指定的数据，成功后返回指向该数据的迭代器，如果插入失败，返回multiset_end()。
    it_s = multiset_insert(pmset_s1, 10);  // 10 10 20 30 40
    if(iterator_equal(it_s, multiset_end(pmset_s1)))
    {
        printf("Insert value error.\n");
    }

    // 向multiset_t中插入一个指定的数据，同时给出一个该数据被插入后的提示位置迭代器，如果这个位置
    //符合multiset_t的排序规则就把这个数据放在提示位置中成功后返回指向该数据的迭代器，如果提示位置不正确则忽略提
    //示位置，(是不是为了加速)当数据插入成功后返回数据的实际位置迭代器，如果multiset_t中包含了该数据那么插入失败，返回multiset_end()
    multiset_insert_hint(pmset_s1, iterator_prev(multiset_end(pmset_s1)), 50);  //10 10 20 30 40 50
    printf("After the insertions, s1 =");
    for(it_s = multiset_begin(pmset_s1); !iterator_equal(it_s, multiset_end(pmset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    multiset_insert(pmset_s2, 100);
    multiset_insert_range(pmset_s2, iterator_next(multiset_begin(pmset_s1)), iterator_prev(multiset_end(pmset_s1)));
    printf("s2 =");
    for(it_s = multiset_begin(pmset_s2); !iterator_equal(it_s, multiset_end(pmset_s2)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    //10 20 30 40 100
    printf("\n");

    multiset_clear(pmset_s1);
    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    
     //获得multiset_t中等于或者大于指定数据的第一个数据的迭代器
    it_s = multiset_lower_bound(pmset_s1, 20);
    printf("The element of multiset s1 with a key of 20 is: %d.\n", //20
        *(int*)iterator_get_pointer(it_s));

    //返回multiset_t中大于指定数据的第一个数据的迭代器
    it_s = multiset_upper_bound(pmset_s1, 20);
    printf("A direct call of upper_bound(20), gives %d,\n", *(int*)iterator_get_pointer(it_s));//30
    printf("matching the 2nd element of the range returned by equal_range(20).\n");
    
    it_s = multiset_lower_bound(pmset_s1, 40);
    /* If no match is found for the key, end() is is returend */
    if(iterator_equal(it_s, multiset_end(pmset_s1)))
    {
        printf("The multiset s1 doesn't have an element with a key of 40.\n");
    }
    else
    {
        printf("The element of multiset s1 with a key of 40 is: %d.\n",
            *(int*)iterator_get_pointer(it_s));
    }

    //返回multiset_t中能够保存的数据个数的最大可能值
    printf("The maximum possible length of the multiset is %u.\n",
        multiset_max_size(pmset_s1));

    //返回multiset_t中保存的数据的数量
    printf("The multiset length is %d.\n", multiset_size(pmset_s1));

    //交换两个multiset_t中的内容
    multiset_swap(pmset_s1, pmset_s2);

    binary_function_t bfun_vl = NULL;
    binary_function_t bfun_kl = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;

    multiset_clear(pmset_s1);
    multiset_destroy(pmset_s2);
    pmset_s2 = create_multiset(int);
    
    //返回multiset_t中数据的比较规则,由于multiset_t中数据本身就是键，所以这个函数的返回值与multiset_key_comp()相同
    bfun_vl = multiset_value_comp(pmset_s1);

    //返回multiset_t的键比较规则,由于multiset_t中数据本身就是键，所以这个函数的返回值与multiset_value_comp()相同
    bfun_kl = multiset_key_comp(pmset_s1);
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
    
    multiset_init_ex(pmset_s2, fun_greater_int);

    bfun_vl = multiset_value_comp(pmset_s2);
    bfun_kl = multiset_key_comp(pmset_s1);
    (*bfun_vl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_vl)(2, 3) returns value of true, where bfun_vl is the function of s2.\n");
    }
    else
    {
        printf("(*bfun_vl)(2, 3) returns value of false, where bfun_vl is the function of s2.\n");
    }

    
    multiset_destroy(pmset_s1);
    multiset_destroy(pmset_s2);

    multiset_t* pmset_s0 = create_multiset(int);
    pmset_s1 = create_multiset(int);
    pmset_s2 = create_multiset(int);
    multiset_t* pmset_s3 = create_multiset(int);
    multiset_t* pmset_s4 = create_multiset(int);
    multiset_t* pmset_s5 = create_multiset(int);

    if(pmset_s0 == NULL || pmset_s1 == NULL || pmset_s2 == NULL || pmset_s3 == NULL || pmset_s4 == NULL || pmset_s5 == NULL)
    {
        return -1;
    }
    
    //multiset_init 初始化一个空的多重集合容器
    multiset_init(pmset_s0);

    //multiset_init_ex 使用指定的排序规则初始化一个空的多重集合容器
    multiset_init_ex(pmset_s1, fun_less_int);
    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    multiset_insert(pmset_s1, 40); // 10 20 30 40

    //multiset_init_ex 使用指定的排序规则初始化一个空的多重集合容器
    multiset_init_ex(pmset_s2, fun_greater_int);
    multiset_insert(pmset_s2, 10);
    multiset_insert(pmset_s2, 20); //20 10

    //multiset_init_copy 使用一个多重集合容器的内容来初始化当前多重集合容器。
    multiset_init_copy(pmset_s3, pmset_s1); //10 20 30 40 

    //multiset_init_copy_range 使用指定的数据区间初始化多重集合容器。
    multiset_init_copy_range(pmset_s4, multiset_begin(pmset_s1), iterator_advance(multiset_begin(pmset_s1), 2)); //10 20

    //multiset_init_copy_range_ex 使用指定的数据区间和指定的排序规则初始化多重集合容器。
    multiset_init_copy_range_ex(pmset_s5, multiset_begin(pmset_s3), iterator_next(multiset_begin(pmset_s3)), fun_less_int);//10 20

    multiset_destroy(pmset_s0);
    multiset_destroy(pmset_s1);
    multiset_destroy(pmset_s2);
    multiset_destroy(pmset_s3);
    multiset_destroy(pmset_s4);
    multiset_destroy(pmset_s5);

    return 0;
}

