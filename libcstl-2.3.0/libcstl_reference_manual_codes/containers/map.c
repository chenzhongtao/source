/*
file: map.c

映射map_t

映射map_t是关联容器，容器中保存的数据是pair_t类型。pair_t的第一个数据是键，map_t中的数据就是根据
这个键排序的，在map_t中键不允许重复，也不可以直接或者间接修改键。pair_t的第二个数据是值，值与键没有直
接的关系，map_t中对于值的唯一性没有要求，值对于map_t中的数据排序没有影响，可以直接或者间接修改值。
map_t的迭代器是双向迭代器，插入新的数据不会破坏原有的迭代器，删除一个数据的时候只有指向该数据的
迭代器失效。在map_t中查找，插入或者删除数据都是高效的，同时还可以使用键作为下标直接访问相应的值。
map_t中的数据根据键按照指定规则自动排序，默认规则是与键相关的小于操作，用户也可以在初始化时指定
自定义的规则。

Typedefs
    map_t 映射容器类型。
    map_iterator_t 映射容器迭代器类型。

Operation Functions
    create_map 创建映射容器类型。
    map_assign 为映射容器赋值。
    map_at 通过下键直接访问值。
    map_begin 返回指向映射中第一个数据的迭代器。
    map_clear 删除映射中的所有数据。
    map_count 统计映射中拥有指定键的数据的个数。
    map_destroy 销毁映射容器。
    map_empty 测试映射容器是否为空。
    map_end 返回指向容器末尾的迭代器。
    map_equal 测试两个映射容器是否相等。
    map_equal_range 返回与指定键相等的数据区间。
    map_erase 删除映射中与指定键值相等的数据。
    map_erase_pos 删除映射中指定位置的数据。
    map_erase_range 删除映射中指定的数据区间。
    map_find 查找容器中拥有指定键的数据。
    map_greater 测试第一个映射是否大于第二个映射。
    map_greater_equal 测试第一个映射是否大于等于第二个映射。
    map_init 初始化一个空映射。
    map_init_copy 使用另一个映射初始化当前映射容器。
    map_init_copy_range 使用指定的数据区间初始化映射容器。
    map_init_copy_range_ex 使用指定的数据区间和指定的排序规则初始化映射容器。
    map_init_ex 使用指定的排序规则初始化一个空的映射容器。
    map_insert 在映射容器中插入数据。
    map_insert_hint 在映射容器中插入数据，同时给出位置提示。
    map_insert_range 在映射容器中插入数据区间。
    map_key_comp 返回映射容器使用的键比较规则。
    map_less 测试第一个映射容器是否小于第二个映射容器。
    map_less_equal 测试第一个映射容器是否小于等于第二个映射容器。
    map_lower_bound 返回与指定键相等的第一个数据的迭代器。
    map_max_size 返回映射容器中能够保存数据的最大数量的可能值。
    map_not_equal 测试两个映射容器是否不等。
    map_size 返回映射容器中数据的数量。
    map_swap 交换两个映射容器的内容。
    map_upper_bound 返回大于指定键的第一个数据的迭代器。
    map_value_comp 返回映射容器使用的数据比较规则。

*/


#include <stdio.h>
#include <cstl/cmap.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int); //创建map_t类型
    map_t* pmap_m2 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int); //创建pair_t类型
    map_iterator_t it_m;  //map_t类型的迭代器类型

    if(pmap_m1 == NULL || pmap_m2 == NULL)
    {
        return -1;
    }
    
    pair_init(ppair_p);//初始化pair_t类型
    map_init(pmap_m1); //初始化map_t类型
    map_init(pmap_m2);

    
    //向映射中插入一个数据。
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);

    pair_make(ppair_p, 4, 40);
    map_insert(pmap_m2, ppair_p);
    pair_make(ppair_p, 5, 50);
    map_insert(pmap_m2, ppair_p);
    pair_make(ppair_p, 6, 60);
    map_insert(pmap_m2, ppair_p);

    //map_begin: 返回指向map_t第一个数据的迭代器
    //map_end: 返回指向map_t末尾位置的迭代器
    printf("m1 =");
    for(it_m = map_begin(pmap_m1);
        !iterator_equal(it_m, map_end(pmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    // <1, 10> <2, 20> <3, 30>
    printf("\n");
    
    //使用map_t类型为当前的map_t赋值
    map_assign(pmap_m1, pmap_m2);
    printf("m1 =");
    for(it_m = map_begin(pmap_m1);
        !iterator_equal(it_m, map_end(pmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    // <4, 40> <5, 50> <6, 60>
    printf("\n");

    //通过键作为下标直接访问map_t中相应数据的值
    //这个操作函数通过指定的键来访问map_t中相应数据的值，如果map_t中包含这个键，那么就返回指向相应数
    //据的值的指针，如果map_t中不包含这个键，那么首先在map_t中插入一个数据，这个数据以指定的键为键，以值的
    //默认数据为值，然后返回指向这个数据的值的指针。
    *(int*)map_at(pmap_m1, 4) = 45; // <4, 45> <5, 50> <6, 60>
    map_at(pmap_m1, 7); // <4, 45> <5, 50> <6, 60> <7, 0>
    printf("m1 =");
    for(it_m = map_begin(pmap_m1);
        !iterator_equal(it_m, map_end(pmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    //删除map_t中的所有数据。
    map_clear(pmap_m1);
    
    pair_make(ppair_p, 1, 1);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 1, 4); //忽略而不是覆盖
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1);
    map_insert(pmap_m1, ppair_p);
    
    //map_count 返回容器中包含指定数据的个数
    /* Keys must be unique in map, so duplicates are ignored */
    printf("The number of elements in m1 with a sort key of 1 is: %d.\n",
        map_count(pmap_m1, 1)); // 1
    printf("The number of elements in m1 with a sort key of 2 is: %d.\n",
        map_count(pmap_m1, 2)); // 1
    printf("The number of elements in m1 with a sort key of 3 is: %d.\n",
        map_count(pmap_m1, 3)); // 0

    printf("m1 =");
    for(it_m = map_begin(pmap_m1);
        !iterator_equal(it_m, map_end(pmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    // 测试map_t容器是否为空
    if(map_empty(pmap_m1))
    {
        printf("The map m1 is empty.\n");
    }

    //测试两个map_t是否相等
    if(map_equal(pmap_m1, pmap_m2))
    {
        printf("The maps m1 and m2 are equal.\n");
    }

    //测试第一个map_t容器是否大于第二个map_t容器
    if(map_greater(pmap_m1, pmap_m2))
    {
        printf("The map m1 is greater than the map m2.\n");
    }

    //测试第一个map_t是否大于等于第二个map_t
    if(map_greater_equal(pmap_m1, pmap_m2))
    {
        printf("The map m1 is greater than or equal to the map m2.\n");
    }

    //测试第一个map_t是否小于第二个map_t
    if(map_less(pmap_m1, pmap_m2))
    {
        printf("The map m1 is less than the map m2.\n");
    }

    //测试第一个map_t是否小于等于第二个map_t
    if(map_less_equal(pmap_m1, pmap_m2))
    {
        printf("The map m1 is less than or equal to the map m2.\n");
    }
    
    //测试两个map_t是否不等
    if(map_not_equal(pmap_m1, pmap_m2))
    {
        printf("The maps m1 and m2 are not equal.\n");
    }
    
    range_t r_r;
    map_clear(pmap_m1);
    
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);

    //返回map_t中包含指定数据的数据区间
    r_r = map_equal_range(pmap_m1, 2); //返回数据区间大于等于20的

    printf("The lower bound of the element with a key of 2 in the map m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_begin)));//30
    printf("The upper bound of the element with a key of 2 in the map m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_end))); //20

    //返回map_t中大于指定数据的第一个数据的迭代器
    it_m = map_upper_bound(pmap_m1, 2);
    printf("A direct call of upper_bound(2) gives %d, matching "
        "the second element of the range returned by equal_range(2).\n",
        *(int*)pair_second(iterator_get_pointer(it_m))); //30

    r_r = map_equal_range(pmap_m1, 4);
    /* If no match is found for the key, both elements of the range return end() */
    if(iterator_equal(r_r.it_begin, map_end(pmap_m1)) &&
        iterator_equal(r_r.it_end, map_end(pmap_m1)))
    {
        printf("The map m1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of map m1 with a key >= 40 is %d.\n",
            *(int*)pair_first(iterator_get_pointer(r_r.it_begin)));
    }

    map_clear(pmap_m1);
    
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 5, 50);
    map_insert(pmap_m1, ppair_p);
    
    //map_erase 删除映射容器中与指定数据相等的数据
    int t_count = map_erase(pmap_m1, 4); // <1, 10> <2, 20> <3, 30>  <5, 50> t_count = 1

    //map_erase_pos 删除映射容器中指定位置的数据
    map_erase_pos(pmap_m1, iterator_next(map_begin(pmap_m1))); //<1, 10> <3, 30>  <5, 50>

    //map_erase_range 删除映射容器中指定数据区间的数据
    map_erase_range(pmap_m1, iterator_next(map_begin(pmap_m1)),
        iterator_prev(map_end(pmap_m1))); // <1, 10> <5, 50>

    //在map_t中查找指定的数据
    it_m = map_find(pmap_m1, 1);
    printf("The element of map m1 with a key of 1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));
    
    /* If no match is found for the key, end() is returned */
    it_m = map_find(pmap_m1, 4);
    if(iterator_equal(it_m, map_end(pmap_m1)))
    {
        printf("The map m1 doesn't have an element with a key of 4.\n");
    }
    
    map_clear(pmap_m1);
    map_clear(pmap_m2);

    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    map_insert(pmap_m1, ppair_p);

    //向map_t中插入数据,成功后返回指向该数据的迭代器，如果map_t中包含了该数据那么插入失败，返回map_end()
    pair_make(ppair_p, 1, 10);
    it_m = map_insert(pmap_m1, ppair_p);
    if(!iterator_equal(it_m, map_end(pmap_m1)))
    {
        printf("The element 10 was inserted in m1 successfully.\n");
    }
    else
    {
        printf("The number 1 already exists in m1.\n");
    }

    // 向map_t中插入一个指定的数据，同时给出一个该数据被插入后的提示位置迭代器，如果这个位置
    //符合map_t的排序规则就把这个数据放在提示位置中成功后返回指向该数据的迭代器，如果提示位置不正确则忽略提
    //示位置，(是不是为了加速)当数据插入成功后返回数据的实际位置迭代器，如果map_t中包含了该数据那么插入失败，返回map_end()
    pair_make(ppair_p, 5, 50);
    map_insert_hint(pmap_m1, iterator_prev(map_end(pmap_m1)), ppair_p);
    printf("After the insertions, the key values of m1 =");
    for(it_m = map_begin(pmap_m1);
        !iterator_equal(it_m, map_end(pmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
      //  <1, 10> <2, 20> <3, 30> <4, 40> <5, 50>
    printf("\n");

    pair_make(ppair_p, 10, 100);
    map_insert(pmap_m2, ppair_p);
    //插入指定的数据区间
    map_insert_range(pmap_m2, iterator_next(map_begin(pmap_m1)),
        iterator_prev(map_end(pmap_m1)));
    printf("After the insertions, the key values of m2 =");
    for(it_m = map_begin(pmap_m2);
        !iterator_equal(it_m, map_end(pmap_m2));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    //<2, 20> <3, 30> <4, 40> <10, 100>
    printf("\n");

    map_clear(pmap_m1);
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);
    
     //获得map_t中等于或者大于指定数据的第一个数据的迭代器
    it_m = map_lower_bound(pmap_m1, 2);
    printf("The first element of map m1 with a key of 2 is: %d.\n",// 20
        *(int*)pair_second(iterator_get_pointer(it_m)));

    //返回map_t中大于指定数据的第一个数据的迭代器
    it_m = map_upper_bound(pmap_m1, 2);
    printf("The first element of map m1 with a key greater than 2 is: %d.\n", // 30
        *(int*)pair_second(iterator_get_pointer(it_m)));
    
    /* If no match is found for this key, end() is returned */
    it_m = map_lower_bound(pmap_m1, 4);
    if(iterator_equal(it_m, map_end(pmap_m1)))
    {
        printf("The map m1 doesn't have an element with a key of 4.\n");
    }
    else
    {
        printf("The element of map m1 with key of 4 is: %d.\n",
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }

    //返回map_t中能够保存的数据个数的最大可能值
    printf("The maximum possible length of the map is %u.\n",
        map_max_size(pmap_m1));

    //返回map_t中保存的数据的数量
    printf("The map length is %d.\n", map_size(pmap_m1));

    //交换两个map_t中的内容
    map_swap(pmap_m1, pmap_m2);

    binary_function_t bfun_vc = NULL;
    binary_function_t bfun_kc = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;
    map_iterator_t it_m1;  //map_t类型的迭代器类型
    map_iterator_t it_m2;  //map_t类型的迭代器类型

    map_destroy(pmap_m1);
    map_destroy(pmap_m2);
    pmap_m1 = create_map(int, int);
    pmap_m2 = create_map(int, int);

    map_init_ex(pmap_m1, fun_less_int);
    
    //返回map_t的键比较规则
    bfun_kc = map_key_comp(pmap_m1);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m1.\n");
    }

    map_destroy(pmap_m1);

    map_init_ex(pmap_m2, fun_greater_int);

    bfun_kc = map_key_comp(pmap_m2);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m2.\n");
    }
    
    map_destroy(pmap_m2);
    
    pmap_m1 = create_map(int, int);
    map_init_ex(pmap_m1, fun_less_int);

    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 5);
    map_insert(pmap_m1, ppair_p);

    it_m1 = map_find(pmap_m1, 1);
    it_m2 = map_find(pmap_m1, 2);
    //返回map_t中数据的比较规则,这个规则是针对数据本身的比较规则而不是键或者值
    bfun_vc = map_value_comp(pmap_m1);

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
    map_destroy(pmap_m1);

    map_t* pmap_m0 = create_map(int, int);
    pmap_m1 = create_map(int, int);
    pmap_m2 = create_map(int, int);
    map_t* pmap_m3 = create_map(int, int);
    map_t* pmap_m4 = create_map(int, int);
    map_t* pmap_m5 = create_map(int, int);

    if(pmap_m0 == NULL || pmap_m1 == NULL || pmap_m2 == NULL || pmap_m3 == NULL || pmap_m4 == NULL || pmap_m5 == NULL)
    {
        return -1;
    }
    
    //map_init 初始化一个空的映射容器
    map_init(pmap_m0);

    //map_init_ex 使用指定的排序规则初始化一个空的映射容器
    map_init_ex(pmap_m1, fun_less_int);
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    map_insert(pmap_m1, ppair_p);//10 20 30 40

    //map_init_ex 使用指定的排序规则初始化一个空的映射容器
    map_init_ex(pmap_m2, fun_greater_int);
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m2, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m2, ppair_p);// 20 10

    //map_init_copy 使用一个映射容器的内容来初始化当前映射容器。
    map_init_copy(pmap_m3, pmap_m1); //10 20 30 40 

    //map_init_copy_range 使用指定的数据区间初始化映射容器。
    map_init_copy_range(pmap_m4, map_begin(pmap_m1), iterator_advance(map_begin(pmap_m1), 2)); //10 20

    //map_init_copy_range_ex 使用指定的数据区间和指定的排序规则初始化映射容器。
    map_init_copy_range_ex(pmap_m5, map_begin(pmap_m3), iterator_next(map_begin(pmap_m3)), fun_less_int);//10 

    map_destroy(pmap_m0);
    map_destroy(pmap_m1);
    map_destroy(pmap_m2);
    map_destroy(pmap_m3);
    map_destroy(pmap_m4);
    map_destroy(pmap_m5);
    pair_destroy(ppair_p);

    return 0;
}

