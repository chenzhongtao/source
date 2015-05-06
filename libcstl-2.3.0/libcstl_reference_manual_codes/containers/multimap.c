/*
file: multimap.c

多重映射multimap_t

多重映射multimap_t是关联容器，容器中保存的数据是pair_t类型。pair_t的第一个数据是键，multimap_t中
的数据就是根据这个键排序的，在multimap_t中键允许重复，不可以直接或者间接修改键。pair_t的第二个数据是值，
值与键没有直接的关系，值对于multimap_t中的数据排序没有影响，可以直接或者间接修改值。
multimap_t的迭代器是双向迭代器，插入新的数据不会破坏原有的迭代器，删除一个数据的时候只有指向该数
据的迭代器失效。在multimap_t中查找，插入或者删除数据都是高效的。
multimap_t中的数据根据键按照指定规则自动排序，默认规则是与键相关的小于操作，用户也可以在初始化时
指定自定义的规则。

Typedefs
    multimap_t 多重映射容器类型。
    multimap_iterator_t 多重映射容器迭代器类型。

Operation Functions
    create_multimap 创建多重映射容器类型。
    multimap_assign 为多重映射容器类型赋值。
    multimap_begin 返回指向多重映射容器中的第一个数据的迭代器。
    multimap_clear 删除多重映射容器中所有的数据。
    multimap_count 返回多重映射容器中包含指定键的数据的个数。
    multimap_destroy 销毁多重映射容器。
    multimap_empty 测试多重映射容器是否为空。
    multimap_end 返回指向多重映射容器末尾的迭代器。
    multimap_equal 测试两个多重映射容器是否相等。
    multimap_equal_range 返回多重映射容器中包含拥有指定键的数据的数据区间。
    multimap_erase 删除多重映射容器中包含指定键的数据。
    multimap_erase_pos 删除多重映射容器中指定位置的数据。
    multimap_erase_range 删除多重映射容器中指定数据区间的数据。
    multimap_find 在多重映射容器中查找包含指定键的数据。
    multimap_greater 测试第一个多重映射容器是否大于第二个多重映射容器。
    multimap_greater_equal 测试第一个多重映射容器是否大于等于第二个多重映射容器。
    multimap_init 初始化一个空的多重映射容器。
    multimap_init_copy 使用多重映射容器初始化当前多重映射容器。
    multimap_init_copy_range 使用指定的数据区间初始化多重映射容器。
    multimap_init_copy_range_ex 使用指定的数据区间和指定的排序规则初始化多重映射容器。
    multimap_init_ex 使用指定的排序规则初始化一个空的多重映射容器。
    multimap_insert 向多重映射容器中插入一个指定的数据。
    multimap_insert_hint 向多重映射容器中插入一个指定的数据，同时给出位置提示。
    multimap_insert_range 向多重映射容器中插入指定的数据区间。
    multimap_key_comp 返回多重映射容器使用的键比较规则。
    multimap_less 测试第一个多重映射容器是否小于第二个多重映射容器。
    multimap_less_equal 测试第一个多重映射容器是否小于等于第二个多重映射容器。
    multimap_lower_bound 返回多重映射容器中包含指定键的第一个数据的迭代器。
    multimap_max_size 返回多重映射容器中能够保存的数据数量的最大可能值。
    multimap_not_equal 测试两个多重映射容器是否不等。
    multimap_size 返回多重映射容器中数据的数量。
    multimap_swap 交换两个多重映射容器的内容。
    multimap_upper_bound 返回多重映射容器中包含大于指定键的第一个数据的迭代器。
    multimap_value_comp 返回多重映射容器中数据的比较规则。

*/


#include <stdio.h>
#include <cstl/cmap.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int); //创建multimap_t类型
    multimap_t* pmmap_m2 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int); //创建pair_t类型
    multimap_iterator_t it_m;  //multimap_t类型的迭代器类型

    if(pmmap_m1 == NULL || pmmap_m2 == NULL)
    {
        return -1;
    }
    
    pair_init(ppair_p);//初始化pair_t类型
    multimap_init(pmmap_m1); //初始化multimap_t类型
    multimap_init(pmmap_m2);

    
    //向多重映射中插入一个数据。
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);

    pair_make(ppair_p, 4, 40);
    multimap_insert(pmmap_m2, ppair_p);
    pair_make(ppair_p, 5, 50);
    multimap_insert(pmmap_m2, ppair_p);
    pair_make(ppair_p, 6, 60);
    multimap_insert(pmmap_m2, ppair_p);

    //multimap_begin: 返回指向multimap_t第一个数据的迭代器
    //multimap_end: 返回指向multimap_t末尾位置的迭代器
    printf("m1 =");
    for(it_m = multimap_begin(pmmap_m1);
        !iterator_equal(it_m, multimap_end(pmmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    // <1, 10> <2, 20> <3, 30>
    printf("\n");
    
    //使用multimap_t类型为当前的multimap_t赋值
    multimap_assign(pmmap_m1, pmmap_m2);
    printf("m1 =");
    for(it_m = multimap_begin(pmmap_m1);
        !iterator_equal(it_m, multimap_end(pmmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    // <4, 40> <5, 50> <6, 60>
    printf("\n");


    //删除multimap_t中的所有数据。
    multimap_clear(pmmap_m1);
    
    pair_make(ppair_p, 1, 1);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 1, 4); 
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1); // 不会覆盖或忽略，有两个1
    multimap_insert(pmmap_m1, ppair_p);
    
    //multimap_count 返回容器中包含指定数据的个数
    /* Keys must be unique in multimap, so duplicates are ignored */
    printf("The number of elements in m1 with a sort key of 1 is: %d.\n",
        multimap_count(pmmap_m1, 1)); // 2
    printf("The number of elements in m1 with a sort key of 2 is: %d.\n",
        multimap_count(pmmap_m1, 2)); // 2
    printf("The number of elements in m1 with a sort key of 3 is: %d.\n",
        multimap_count(pmmap_m1, 3)); // 0

    printf("m1 =");
    for(it_m = multimap_begin(pmmap_m1);
        !iterator_equal(it_m, multimap_end(pmmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    // 测试multimap_t容器是否为空
    if(multimap_empty(pmmap_m1))
    {
        printf("The multimap m1 is empty.\n");
    }

    //测试两个multimap_t是否相等
    if(multimap_equal(pmmap_m1, pmmap_m2))
    {
        printf("The multimaps m1 and m2 are equal.\n");
    }

    //测试第一个multimap_t容器是否大于第二个multimap_t容器
    if(multimap_greater(pmmap_m1, pmmap_m2))
    {
        printf("The multimap m1 is greater than the multimap m2.\n");
    }

    //测试第一个multimap_t是否大于等于第二个multimap_t
    if(multimap_greater_equal(pmmap_m1, pmmap_m2))
    {
        printf("The multimap m1 is greater than or equal to the multimap m2.\n");
    }

    //测试第一个multimap_t是否小于第二个multimap_t
    if(multimap_less(pmmap_m1, pmmap_m2))
    {
        printf("The multimap m1 is less than the multimap m2.\n");
    }

    //测试第一个multimap_t是否小于等于第二个multimap_t
    if(multimap_less_equal(pmmap_m1, pmmap_m2))
    {
        printf("The multimap m1 is less than or equal to the multimap m2.\n");
    }
    
    //测试两个multimap_t是否不等
    if(multimap_not_equal(pmmap_m1, pmmap_m2))
    {
        printf("The multimaps m1 and m2 are not equal.\n");
    }
    
    range_t r_r;
    multimap_clear(pmmap_m1);
    
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);

    //返回multimap_t中包含指定数据的数据区间
    r_r = multimap_equal_range(pmmap_m1, 2); //返回数据区间大于等于20的

    printf("The lower bound of the element with a key of 2 in the multimap m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_begin)));//30
    printf("The upper bound of the element with a key of 2 in the multimap m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_end))); //20

    //返回multimap_t中大于指定数据的第一个数据的迭代器
    it_m = multimap_upper_bound(pmmap_m1, 2);
    printf("A direct call of upper_bound(2) gives %d, matching "
        "the second element of the range returned by equal_range(2).\n",
        *(int*)pair_second(iterator_get_pointer(it_m))); //30

    r_r = multimap_equal_range(pmmap_m1, 4);
    /* If no match is found for the key, both elements of the range return end() */
    if(iterator_equal(r_r.it_begin, multimap_end(pmmap_m1)) &&
        iterator_equal(r_r.it_end, multimap_end(pmmap_m1)))
    {
        printf("The multimap m1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of multimap m1 with a key >= 40 is %d.\n",
            *(int*)pair_first(iterator_get_pointer(r_r.it_begin)));
    }

    multimap_clear(pmmap_m1);
    
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 5, 50);
    multimap_insert(pmmap_m1, ppair_p);
    
    //multimap_erase 删除多重映射容器中与指定数据相等的数据
    int t_count = multimap_erase(pmmap_m1, 4); // <1, 10> <2, 20> <3, 30>  <5, 50> t_count = 1

    //multimap_erase_pos 删除多重映射容器中指定位置的数据
    multimap_erase_pos(pmmap_m1, iterator_next(multimap_begin(pmmap_m1))); //<1, 10> <3, 30>  <5, 50>

    //multimap_erase_range 删除多重映射容器中指定数据区间的数据
    multimap_erase_range(pmmap_m1, iterator_next(multimap_begin(pmmap_m1)),
        iterator_prev(multimap_end(pmmap_m1))); // <1, 10> <5, 50>

    //在multimap_t中查找指定的数据
    it_m = multimap_find(pmmap_m1, 1);
    printf("The element of multimap m1 with a key of 1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));
    
    /* If no match is found for the key, end() is returned */
    it_m = multimap_find(pmmap_m1, 4);
    if(iterator_equal(it_m, multimap_end(pmmap_m1)))
    {
        printf("The multimap m1 doesn't have an element with a key of 4.\n");
    }
    
    multimap_clear(pmmap_m1);
    multimap_clear(pmmap_m2);

    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    multimap_insert(pmmap_m1, ppair_p);

    //向multimap_t中插入数据,成功后返回指向该数据的迭代器，如果multimap_t中包含了该数据那么插入失败，返回multimap_end()
    pair_make(ppair_p, 1, 10);
    it_m = multimap_insert(pmmap_m1, ppair_p);
    if(!iterator_equal(it_m, multimap_end(pmmap_m1)))
    {
        printf("The element 10 was inserted in m1 successfully.\n");
    }
    else
    {
        printf("The number 1 already exists in m1.\n");
    }

    // 向multimap_t中插入一个指定的数据，同时给出一个该数据被插入后的提示位置迭代器，如果这个位置
    //符合multimap_t的排序规则就把这个数据放在提示位置中成功后返回指向该数据的迭代器，如果提示位置不正确则忽略提
    //示位置，(是不是为了加速)当数据插入成功后返回数据的实际位置迭代器，如果multimap_t中包含了该数据那么插入失败，返回multimap_end()
    pair_make(ppair_p, 5, 50);
    multimap_insert_hint(pmmap_m1, iterator_prev(multimap_end(pmmap_m1)), ppair_p);
    printf("After the insertions, the key values of m1 =");
    for(it_m = multimap_begin(pmmap_m1);
        !iterator_equal(it_m, multimap_end(pmmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
      //  <1, 10> <2, 20> <3, 30> <4, 40> <5, 50>
    printf("\n");

    pair_make(ppair_p, 10, 100);
    multimap_insert(pmmap_m2, ppair_p);
    //插入指定的数据区间
    multimap_insert_range(pmmap_m2, iterator_next(multimap_begin(pmmap_m1)),
        iterator_prev(multimap_end(pmmap_m1)));
    printf("After the insertions, the key values of m2 =");
    for(it_m = multimap_begin(pmmap_m2);
        !iterator_equal(it_m, multimap_end(pmmap_m2));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    //<2, 20> <3, 30> <4, 40> <10, 100>
    printf("\n");

    multimap_clear(pmmap_m1);
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);
    
     //获得multimap_t中等于或者大于指定数据的第一个数据的迭代器
    it_m = multimap_lower_bound(pmmap_m1, 2);
    printf("The first element of multimap m1 with a key of 2 is: %d.\n",// 20
        *(int*)pair_second(iterator_get_pointer(it_m)));

    //返回multimap_t中大于指定数据的第一个数据的迭代器
    it_m = multimap_upper_bound(pmmap_m1, 2);
    printf("The first element of multimap m1 with a key greater than 2 is: %d.\n", // 30
        *(int*)pair_second(iterator_get_pointer(it_m)));
    
    /* If no match is found for this key, end() is returned */
    it_m = multimap_lower_bound(pmmap_m1, 4);
    if(iterator_equal(it_m, multimap_end(pmmap_m1)))
    {
        printf("The multimap m1 doesn't have an element with a key of 4.\n");
    }
    else
    {
        printf("The element of multimap m1 with key of 4 is: %d.\n",
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }

    //返回multimap_t中能够保存的数据个数的最大可能值
    printf("The maximum possible length of the multimap is %u.\n",
        multimap_max_size(pmmap_m1));

    //返回multimap_t中保存的数据的数量
    printf("The multimap length is %d.\n", multimap_size(pmmap_m1));

    //交换两个multimap_t中的内容
    multimap_swap(pmmap_m1, pmmap_m2);

    binary_function_t bfun_vc = NULL;
    binary_function_t bfun_kc = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;
    multimap_iterator_t it_m1;  //multimap_t类型的迭代器类型
    multimap_iterator_t it_m2;  //multimap_t类型的迭代器类型

    multimap_destroy(pmmap_m1);
    multimap_destroy(pmmap_m2);
    pmmap_m1 = create_multimap(int, int);
    pmmap_m2 = create_multimap(int, int);

    multimap_init_ex(pmmap_m1, fun_less_int);
    
    //返回multimap_t的键比较规则
    bfun_kc = multimap_key_comp(pmmap_m1);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m1.\n");
    }

    multimap_destroy(pmmap_m1);

    multimap_init_ex(pmmap_m2, fun_greater_int);

    bfun_kc = multimap_key_comp(pmmap_m2);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m2.\n");
    }
    
    multimap_destroy(pmmap_m2);
    
    pmmap_m1 = create_multimap(int, int);
    multimap_init_ex(pmmap_m1, fun_less_int);

    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 5);
    multimap_insert(pmmap_m1, ppair_p);

    it_m1 = multimap_find(pmmap_m1, 1);
    it_m2 = multimap_find(pmmap_m1, 2);
    //返回multimap_t中数据的比较规则,这个规则是针对数据本身的比较规则而不是键或者值
    bfun_vc = multimap_value_comp(pmmap_m1);

    (*bfun_vc)(iterator_get_pointer(it_m1), iterator_get_pointer(it_m2), &b_result);
    if(b_result)
    {
        printf("The element (1, 10) precedes the element (2, 5).\n");
    }
    else
    {
        printf("The element (1, 10) does not precedes the element (2, 5).\n");
    }

    (*bfun_vc)(iterator_get_pointer(it_m2), iterator_get_pointer(it_m1), &b_result);
    if(b_result)
    {
        printf("The element (2, 5) precedes the element (1, 10).\n");
    }
    else
    {
        printf("The element (2, 5) does not precedes the element (1, 10).\n");
    }
    multimap_destroy(pmmap_m1);

    multimap_t* pmmap_m0 = create_multimap(int, int);
    pmmap_m1 = create_multimap(int, int);
    pmmap_m2 = create_multimap(int, int);
    multimap_t* pmmap_m3 = create_multimap(int, int);
    multimap_t* pmmap_m4 = create_multimap(int, int);
    multimap_t* pmmap_m5 = create_multimap(int, int);

    if(pmmap_m0 == NULL || pmmap_m1 == NULL || pmmap_m2 == NULL || pmmap_m3 == NULL || pmmap_m4 == NULL || pmmap_m5 == NULL)
    {
        return -1;
    }
    
    //multimap_init 初始化一个空的多重映射容器
    multimap_init(pmmap_m0);

    //multimap_init_ex 使用指定的排序规则初始化一个空的多重映射容器
    multimap_init_ex(pmmap_m1, fun_less_int);
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    multimap_insert(pmmap_m1, ppair_p);//10 20 30 40

    //multimap_init_ex 使用指定的排序规则初始化一个空的多重映射容器
    multimap_init_ex(pmmap_m2, fun_greater_int);
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m2, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m2, ppair_p);// 20 10

    //multimap_init_copy 使用一个多重映射容器的内容来初始化当前多重映射容器。
    multimap_init_copy(pmmap_m3, pmmap_m1); //10 20 30 40 

    //multimap_init_copy_range 使用指定的数据区间初始化多重映射容器。
    multimap_init_copy_range(pmmap_m4, multimap_begin(pmmap_m1), iterator_advance(multimap_begin(pmmap_m1), 2)); //10 20

    //multimap_init_copy_range_ex 使用指定的数据区间和指定的排序规则初始化多重映射容器。
    multimap_init_copy_range_ex(pmmap_m5, multimap_begin(pmmap_m3), iterator_next(multimap_begin(pmmap_m3)), fun_less_int);//10 

    multimap_destroy(pmmap_m0);
    multimap_destroy(pmmap_m1);
    multimap_destroy(pmmap_m2);
    multimap_destroy(pmmap_m3);
    multimap_destroy(pmmap_m4);
    multimap_destroy(pmmap_m5);
    pair_destroy(ppair_p);

    return 0;
}

