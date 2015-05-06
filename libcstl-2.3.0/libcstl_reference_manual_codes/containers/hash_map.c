/*
file: hash_map.c

基于哈希结构的映射hash_map_t

基于哈希结构的映射hash_map_t是关联容器，容器中保存的数据是pair_t类型。pair_t的第一个数据是键，
hash_map_t中的数据就是根据这个键排序的，在hash_map_t中键不允许重复，也不可以直接或者间接修改键。pair_t
的第二个数据是值，值与键没有直接的关系，hash_map_t中对于值的唯一性没有要求，值对于hash_map_t中的数据
排序没有影响，可以直接或者间接修改值。
hash_map_t的迭代器是双向迭代器，插入新的数据不会破坏原有的迭代器，删除一个数据的时候只有指向该
数据的迭代器失效。在hash_map_t中查找，插入或者删除数据都是高效的，同时还可以使用键作为下标直接访问相应
的值。
hash_map_t中的数据保存在哈希表中，根据数据和指定的哈希函数计算数据在哈希表中的位置，同时根据键
按照指定规则自动排序，默认规则是与键相关的小于操作，用户也可以在初始化时指定自定义的规则。hash_map_t在
数据的插入删除查找等操作上与基于平衡二叉树的关联容器相比效率更高，可以达到接近常数级别，但是数据不是完
全有序的。

Typedefs
    hash_map_t 基于哈希结构的映射容器类型。
    hash_map_iterator_t 基于哈希结构的映射容器迭代器类型。

Operation Functions
    create_hash_map 创建基于哈希结构的映射容器类型。
    hash_map_assign 为基于哈希结构的映射容器迭代器类型赋值。
    hash_map_at 使用键为下标随机访问基于哈希结构的映射容器中相应数据的值。
    hash_map_begin 返回指向基于哈希结构的映射容器中的第一个数据的迭代器。
    hash_map_bucket_count 返回基于哈希结构的映射容器使用的哈希表的存储单元个数。
    hash_map_clear 删除基于哈希结构的映射容器中的所有数据。
    hash_map_count 统计基于哈希结构的映射容器中包含指定数据的个数。
    hash_map_destroy 销毁基于哈希结构的映射容器。
    hash_map_empty 测试基于哈希结构的映射容器是否为空。
    hash_map_end 返回指向基于哈希结构的映射容器末尾的迭代器。
    hash_map_equal 测试两个基于哈希结构的映射容器是否相等。
    hash_map_equal_range 返回基于哈希结构的映射容器中包含指定键的数据区间。
    hash_map_erase 删除基于哈希结构的映射容器中包含指定键的数据。
    hash_map_erase_pos 删除基于哈希结构的映射容器中指定位置的数据。
    hash_map_erase_range 删除基于哈希结构的映射容器中指定的数据区间。
    hash_map_find 在基于哈希结构的映射容器中查找包含指定键的数据。
    hash_map_greater 测试第一个基于哈希结构的映射是否大于第二个基于哈希结构的映射。
    hash_map_greater_equal 测试第一个基于哈希结构的映射是否大于等于第二个基于哈希结构的映射。
    hash_map_hash 返回基于哈希结构的映射容器使用的哈希函数。
    hash_map_init 初始化一个空的基于哈希结构的映射容器。
    hash_map_init_copy 使用拷贝的方式初始化一个基于哈希结构的映射容器，所有内容都来自于源容器。
    hash_map_init_copy_range 使用指定的数据区间初始化一个基于哈希结构的映射容器。
    hash_map_init_copy_range_ex 使用指定的数据区间，哈希函数，比较规则，存储单元数量来初始化容器。
    hash_map_init_ex 使用指定的哈希函数，比较规则，存储单元数量初始化一个空的基于哈希结构的映射。
    hash_map_insert 向基于哈希结构的映射中插入一个数据。
    hash_map_insert_range 向基于哈希结构的映射中插入一个数据区间。
    hash_map_key_comp 返回基于哈希结构的映射容器使用的键比较规则。
    hash_map_less 测试第一个基于哈希结构的映射是否小于第二个基于哈希结构的映射。
    hash_map_less_equal 测试第一个基于哈希结构的映射是否小于等于第二个基于哈希结构的映射。
    hash_map_max_size 返回基于哈希结构的映射容器中能够保存数据数量的最大值。
    hash_map_not_equal 测试两个基于哈希结构的映射容器是否不等。
    hash_map_resize 重新设置基于哈希结构的映射容器的哈希表存储单元个数。
    hash_map_size 返回基于哈希结构的映射容器中保存数据的个数。
    hash_map_swap 交换两个基于哈希结构的映射容器的内容。
    hash_map_value_comp 返回基于哈希结构的映射容器使用的数据比较规则。

*/


#include <stdio.h>
#include <cstl/chash_map.h>
#include <cstl/cfunctional.h>

static void _hash_function(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input + 20;
}

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int); //创建hash_map_t类型
    hash_map_t* phm_hm2 = create_hash_map(int, int);
    pair_t* ppair_p = create_pair(int, int); //创建pair_t类型
    hash_map_iterator_t it_hm;  //hash_map_t类型的迭代器类型

    if(phm_hm1 == NULL || phm_hm2 == NULL)
    {
        return -1;
    }
    
    pair_init(ppair_p);//初始化pair_t类型
    hash_map_init(phm_hm1); //初始化hash_map_t类型
    hash_map_init(phm_hm2);

    
    //向基于哈希结构的映射中插入一个数据。
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);

    pair_make(ppair_p, 4, 40);
    hash_map_insert(phm_hm2, ppair_p);
    pair_make(ppair_p, 5, 50);
    hash_map_insert(phm_hm2, ppair_p);
    pair_make(ppair_p, 6, 60);
    hash_map_insert(phm_hm2, ppair_p);

    //hash_map_begin: 返回指向hash_map_t第一个数据的迭代器
    //hash_map_end: 返回指向hash_map_t末尾位置的迭代器
    printf("m1 =");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hm)),
            *(int*)pair_second(iterator_get_pointer(it_hm)));
    }
    // <1, 10> <2, 20> <3, 30>
    printf("\n");
    
    //使用hash_map_t类型为当前的hash_map_t赋值
    hash_map_assign(phm_hm1, phm_hm2);
    printf("m1 =");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hm)),
            *(int*)pair_second(iterator_get_pointer(it_hm)));
    }
    // <4, 40> <5, 50> <6, 60>
    printf("\n");

    //通过键作为下标直接访问hash_map_t中相应数据的值
    //这个操作函数通过指定的键来访问hash_map_t中相应数据的值，如果hash_map_t中包含这个键，那么就返回指向相应数
    //据的值的指针，如果hash_map_t中不包含这个键，那么首先在hash_map_t中插入一个数据，这个数据以指定的键为键，以值的
    //默认数据为值，然后返回指向这个数据的值的指针。
    *(int*)hash_map_at(phm_hm1, 4) = 45; // <4, 45> <5, 50> <6, 60>
    hash_map_at(phm_hm1, 7); // <4, 45> <5, 50> <6, 60> <7, 0>
    printf("m1 =");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hm)),
            *(int*)pair_second(iterator_get_pointer(it_hm)));
    }
    printf("\n");

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    phm_hm1 = create_hash_map(int, int);
    phm_hm2 = create_hash_map(int, int);
    hash_map_init(phm_hm1);
    hash_map_init_ex(phm_hm2, 100, NULL, NULL);

    // 返回hash_map_t中哈希表的存储单元的个数。
    printf("The default bucket count of hm1 is %d.\n",
    hash_map_bucket_count(phm_hm1)); //53
    printf("The custom bucket count of hm2 is %d.\n",
    hash_map_bucket_count(phm_hm2)); //193

    hash_map_destroy(phm_hm2);
    phm_hm2 = create_hash_map(int, int);
    hash_map_init(phm_hm2);

    //删除hash_map_t中的所有数据。
    hash_map_clear(phm_hm1);
    
    pair_make(ppair_p, 1, 1);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 1);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 1, 4); //忽略而不是覆盖
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 1);
    hash_map_insert(phm_hm1, ppair_p);
    
    //hash_map_count 返回容器中包含指定数据的个数
    /* Keys must be unique in hash_map, so duplicates are ignored */
    printf("The number of elements in m1 with a sort key of 1 is: %d.\n",
        hash_map_count(phm_hm1, 1)); // 1
    printf("The number of elements in m1 with a sort key of 2 is: %d.\n",
        hash_map_count(phm_hm1, 2)); // 1
    printf("The number of elements in m1 with a sort key of 3 is: %d.\n",
        hash_map_count(phm_hm1, 3)); // 0

    printf("m1 =");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hm)),
            *(int*)pair_second(iterator_get_pointer(it_hm)));
    }
    printf("\n");

    // 测试hash_map_t容器是否为空
    if(hash_map_empty(phm_hm1))
    {
        printf("The hash_map m1 is empty.\n");
    }

    //测试两个hash_map_t是否相等
    if(hash_map_equal(phm_hm1, phm_hm2))
    {
        printf("The hash_maps m1 and m2 are equal.\n");
    }

    //测试第一个hash_map_t容器是否大于第二个hash_map_t容器
    if(hash_map_greater(phm_hm1, phm_hm2))
    {
        printf("The hash_map m1 is greater than the hash_map m2.\n");
    }

    //测试第一个hash_map_t是否大于等于第二个hash_map_t
    if(hash_map_greater_equal(phm_hm1, phm_hm2))
    {
        printf("The hash_map m1 is greater than or equal to the hash_map m2.\n");
    }

    //测试第一个hash_map_t是否小于第二个hash_map_t
    if(hash_map_less(phm_hm1, phm_hm2))
    {
        printf("The hash_map m1 is less than the hash_map m2.\n");
    }

    //测试第一个hash_map_t是否小于等于第二个hash_map_t
    if(hash_map_less_equal(phm_hm1, phm_hm2))
    {
        printf("The hash_map m1 is less than or equal to the hash_map m2.\n");
    }
    
    //测试两个hash_map_t是否不等
    if(hash_map_not_equal(phm_hm1, phm_hm2))
    {
        printf("The hash_maps m1 and m2 are not equal.\n");
    }

    // 返回hash_map_t使用的哈希函数
    if(hash_map_hash(phm_hm2) == _hash_function)
    {
        printf("The hash function of hash_map hs2 is _hash_function.\n");
    }
    
    range_t r_r;
    hash_map_clear(phm_hm1);
    
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);

    //返回hash_map_t中包含指定数据的数据区间
    r_r = hash_map_equal_range(phm_hm1, 2); //返回数据区间大于等于20的

    printf("The lower bound of the element with a key of 2 in the hash_map m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_begin)));//30
    printf("The upper bound of the element with a key of 2 in the hash_map m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_end))); //20

    r_r = hash_map_equal_range(phm_hm1, 4);
    /* If no match is found for the key, both elements of the range return end() */
    if(iterator_equal(r_r.it_begin, hash_map_end(phm_hm1)) &&
        iterator_equal(r_r.it_end, hash_map_end(phm_hm1)))
    {
        printf("The hash_map m1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of hash_map m1 with a key >= 40 is %d.\n",
            *(int*)pair_first(iterator_get_pointer(r_r.it_begin)));
    }

    hash_map_clear(phm_hm1);
    
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 5, 50);
    hash_map_insert(phm_hm1, ppair_p);
    
    //hash_map_erase 删除基于哈希结构的映射容器中与指定数据相等的数据
    int t_count = hash_map_erase(phm_hm1, 4); // <1, 10> <2, 20> <3, 30>  <5, 50> t_count = 1

    //hash_map_erase_pos 删除基于哈希结构的映射容器中指定位置的数据
    hash_map_erase_pos(phm_hm1, iterator_next(hash_map_begin(phm_hm1))); //<1, 10> <3, 30>  <5, 50>

    //hash_map_erase_range 删除基于哈希结构的映射容器中指定数据区间的数据
    hash_map_erase_range(phm_hm1, iterator_next(hash_map_begin(phm_hm1)),
        iterator_prev(hash_map_end(phm_hm1))); // <1, 10> <5, 50>

    //在hash_map_t中查找指定的数据
    it_hm = hash_map_find(phm_hm1, 1);
    printf("The element of hash_map m1 with a key of 1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_hm)));
    
    /* If no match is found for the key, end() is returned */
    it_hm = hash_map_find(phm_hm1, 4);
    if(iterator_equal(it_hm, hash_map_end(phm_hm1)))
    {
        printf("The hash_map m1 doesn't have an element with a key of 4.\n");
    }
    
    hash_map_clear(phm_hm1);
    hash_map_clear(phm_hm2);

    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_map_insert(phm_hm1, ppair_p);

    //向hash_map_t中插入数据,成功后返回指向该数据的迭代器，如果hash_map_t中包含了该数据那么插入失败，返回hash_map_end()
    pair_make(ppair_p, 1, 10);
    it_hm = hash_map_insert(phm_hm1, ppair_p);
    if(!iterator_equal(it_hm, hash_map_end(phm_hm1)))
    {
        printf("The element 10 was inserted in m1 successfully.\n");
    }
    else
    {
        printf("The number 1 already exists in m1.\n");
    }


    pair_make(ppair_p, 10, 100);
    hash_map_insert(phm_hm2, ppair_p);
    //插入指定的数据区间
    hash_map_insert_range(phm_hm2, iterator_next(hash_map_begin(phm_hm1)),
        iterator_prev(hash_map_end(phm_hm1)));
    printf("After the insertions, the key values of m2 =");
    for(it_hm = hash_map_begin(phm_hm2);
        !iterator_equal(it_hm, hash_map_end(phm_hm2));
        it_hm = iterator_next(it_hm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hm)),
            *(int*)pair_second(iterator_get_pointer(it_hm)));
    }
    //<2, 20> <3, 30> <4, 40> <10, 100>
    printf("\n");

    hash_map_clear(phm_hm1);
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);
    

    //返回hash_map_t中能够保存的数据个数的最大可能值
    printf("The maximum possible length of the hash_map is %u.\n",
        hash_map_max_size(phm_hm1));

    //返回hash_map_t中保存的数据的数量
    printf("The hash_map length is %d.\n", hash_map_size(phm_hm1));

    //交换两个hash_map_t中的内容
    hash_map_swap(phm_hm1, phm_hm2);

    binary_function_t bfun_vc = NULL;
    binary_function_t bfun_kc = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;
    hash_map_iterator_t it_hm1;  //hash_map_t类型的迭代器类型
    hash_map_iterator_t it_hm2;  //hash_map_t类型的迭代器类型

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    phm_hm1 = create_hash_map(int, int);
    phm_hm2 = create_hash_map(int, int);

    hash_map_init_ex(phm_hm1, 0, NULL, fun_less_int);
    
    //返回hash_map_t的键比较规则
    bfun_kc = hash_map_key_comp(phm_hm1);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m1.\n");
    }

    hash_map_destroy(phm_hm1);

    hash_map_init_ex(phm_hm2, 0, NULL, fun_greater_int);

    bfun_kc = hash_map_key_comp(phm_hm2);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m2.\n");
    }
    
    hash_map_destroy(phm_hm2);
    
    phm_hm1 = create_hash_map(int, int);
    hash_map_init_ex(phm_hm1, 0, NULL, fun_less_int);

    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 5);
    hash_map_insert(phm_hm1, ppair_p);

    it_hm1 = hash_map_find(phm_hm1, 1);
    it_hm2 = hash_map_find(phm_hm1, 2);
    //返回hash_map_t中数据的比较规则,这个规则是针对数据本身的比较规则而不是键或者值
    bfun_vc = hash_map_value_comp(phm_hm1);

    (*bfun_vc)(iterator_get_pointer(it_hm1), iterator_get_pointer(it_hm2), &b_result);
    if(b_result)
    {
        printf("The element (1, 10) precedes the element (2, 5).\n");
    }
    else
    {
        printf("The element (1, 10) does not precedes the element (2, 5).\n");
    }

    (*bfun_vc)(iterator_get_pointer(it_hm2), iterator_get_pointer(it_hm1), &b_result);
    if(b_result)
    {
        printf("The element (2, 5) precedes the element (1, 10).\n");
    }
    else
    {
        printf("The element (2, 5) does not precedes the element (1, 10).\n");
    }
    hash_map_destroy(phm_hm1);

    hash_map_t* phm_hm0 = create_hash_map(int, int);
    phm_hm1 = create_hash_map(int, int);
    phm_hm2 = create_hash_map(int, int);
    hash_map_t* phm_hm3 = create_hash_map(int, int);
    hash_map_t* phm_hm4 = create_hash_map(int, int);
    hash_map_t* phm_hm5 = create_hash_map(int, int);

    if(phm_hm0 == NULL || phm_hm1 == NULL || phm_hm2 == NULL || phm_hm3 == NULL || phm_hm4 == NULL || phm_hm5 == NULL)
    {
        return -1;
    }
    
    //hash_map_init 初始化一个空的基于哈希结构的映射容器。
    hash_map_init(phm_hm0);

    //hash_map_init_ex 使用指定的排序规则初始化一个空的基于哈希结构的映射容器
    hash_map_init_ex(phm_hm1, 0, _hash_function, fun_less_int);
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_map_insert(phm_hm1, ppair_p);

    //hash_map_init_ex 使用指定的哈希函数，比较规则，存储单元数量初始化一个空的基于哈希结构的映射
    hash_map_init_ex(phm_hm2, 0, _hash_function, fun_greater_int);
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm2, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm2, ppair_p);

    //hash_map_init_copy 使用拷贝的方式初始化一个基于哈希结构的映射容器，所有内容都来自于源容器。
    hash_map_init_copy(phm_hm3, phm_hm1); 

    //hash_map_init_copy_range 使用指定的数据区间初始化一个基于哈希结构的映射容器。
    hash_map_init_copy_range(phm_hm4, hash_map_begin(phm_hm1), iterator_advance(hash_map_begin(phm_hm1), 2)); 

    //hash_map_init_copy_range_ex 使用指定的数据区间，哈希函数，比较规则，存储单元数量来初始化容器。
    hash_map_init_copy_range_ex(phm_hm5, hash_map_begin(phm_hm3),
        hash_map_end(phm_hm3), 100, _hash_function, fun_less_int);

    hash_map_destroy(phm_hm0);
    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    hash_map_destroy(phm_hm3);
    hash_map_destroy(phm_hm4);
    hash_map_destroy(phm_hm5);
    pair_destroy(ppair_p);

    return 0;
}

