/*
file: hash_multimap.c

基于哈希结构的多重映射hash_multimap_t

基于哈希结构的多重映射hash_multimap_t是关联容器，容器中保存的数据是pair_t类型。pair_t的第一个数据
是键，hash_multimap_t中的数据就是根据这个键排序的，不可以直接或者间接修改键。pair_t的第二个数据是值，值
与键没有直接的关系，值对于hash_multimap_t中的数据排序没有影响，可以直接或者间接修改值。
hash_multimap_t的迭代器是双向迭代器，插入新的数据不会破坏原有的迭代器，删除一个数据的时候只有指
向该数据的迭代器失效。在hash_multimap_t中查找，插入或者删除数据都是高效的。
hash_multimap_t中的数据保存在哈希表中，根据数据和指定的哈希函数计算数据在哈希表中的位置，同时根
据键按照指定规则自动排序，默认规则是与键相关的小于操作，用户也可以在初始化时指定自定义的规则。
hash_multimap_t在数据的插入删除查找等操作上与基于平衡二叉树的关联容器相比效率更高，可以达到接近常数级别，
但是数据不是完全有序的。

Typedefs
    hash_multimap_t 基于哈希结构的多重映射容器类型。
    hash_multimap_iterator_t 基于哈希结构的多重映射容器迭代器类型。
Operation Functions
    create_hash_multimap 创建基于哈希结构的多重映射容器类型。
    hash_multimap_assign 为基于哈希结构的多重映射容器迭代器类型赋值。
    hash_multimap_begin 返回指向基于哈希结构的多重映射中第一个数据的迭代器。
    hash_multimap_bucket_count 返回基于哈希结构的多重映射使用的哈希表的存储单元个数。
    hash_multimap_clear 删除基于哈希结构的多重映射中包含指定键的数据。
    hash_multimap_count 统计基于哈希结构的多重映射中包含指定键的数据的个数。
    hash_multimap_destroy 销毁基于哈希结构的多重映射容器。
    hash_multimap_empty 测试基于哈希结构的多重映射容器是否为空。
    hash_multimap_end 返回指向基于哈希结构的多重映射容器末尾位置的迭代器。
    hash_multimap_equal 测试两个基于哈希结构的多重映射容器是否相等。
    hash_multimap_equal_range 返回基于哈希结构的多重映射容器中包含指定键的数据区间。
    hash_multimap_erase 删除基于哈希结构的多重映射中包含指定键的数据。
    hash_multimap_erase_pos 删除基于哈希结构的多重映射容器中指定位置的数据。
    hash_multimap_erase_range 删除基于哈希结构的多重映射容器中的指定数据区间。
    hash_multimap_find 查找基于哈希结构的多重映射容器中包含指定键的数据。
    hash_multimap_greater 测试第一个基于哈希结构的多重映射是否大于第二个基于哈希结构的多重映射。
    hash_multimap_greater_equal 测试第一个基于哈希结构的多重映射是否大于等于第二个容器。
    hash_multimap_hash 返回基于哈希结构的多重映射使用的哈希函数。
    hash_multimap_init 初始化一个空的基于哈希结构的多重映射。
    hash_multimap_init_copy 使用拷贝的方式初始化一个基于哈希结构的多重映射。
    hash_multimap_init_copy_range 使用指定的数据区间初始化一个基于哈希结构的多重映射。
    hash_multimap_init_copy_range_ex 使用指定的数据区间，哈希函数，比较规则和存储单元数初始化容器。
    hash_multimap_init_ex 使用指定的哈希函数，比较规则和存储单元数初始化一个空的容器。
    hash_multimap_insert 向基于哈希结构的多重映射容器中插入数据。
    hash_multimap_insert_range 向基于哈希结构的多重映射容器中插入数据区间。
    hash_multimap_key_comp 返回基于哈希结构的多重映射容器使用的键比较规则。
    hash_multimap_less 测试第一个基于哈希结构的多重映射是否小于第二个容器。
    hash_multimap_less_equal 测试第一个基于哈希结构的多重映射是否小于等于第二个容器。
    hash_multimap_max_size 返回基于哈希结构的多重映射容器中能够保存的数据数量的最大值。
    hash_multimap_not_equal 测试两个基于哈希结构的多重映射容器是否不等。
    hash_multimap_resize 重新设置基于哈希结构的多重映射容器使用的哈希表的存储单元个数。
    hash_multimap_size 返回基于哈希结构的多重映射容器中保存的数据的个数。
    hash_multimap_swap 交换两个基于哈希结构的多重映射容器中的内容。
    hash_multimap_value_comp 返回基于哈希结构的多重映射容器使用的数据比较规则。

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
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int); //创建hash_multimap_t类型
    hash_multimap_t* phmm_hmm2 = create_hash_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int); //创建pair_t类型
    hash_multimap_iterator_t it_hmm;  //hash_multimap_t类型的迭代器类型

    if(phmm_hmm1 == NULL || phmm_hmm2 == NULL)
    {
        return -1;
    }
    
    pair_init(ppair_p);//初始化pair_t类型
    hash_multimap_init(phmm_hmm1); //初始化hash_multimap_t类型
    hash_multimap_init(phmm_hmm2);

    
    //向基于哈希结构的多重映射中插入一个数据。
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);

    pair_make(ppair_p, 4, 40);
    hash_multimap_insert(phmm_hmm2, ppair_p);
    pair_make(ppair_p, 5, 50);
    hash_multimap_insert(phmm_hmm2, ppair_p);
    pair_make(ppair_p, 6, 60);
    hash_multimap_insert(phmm_hmm2, ppair_p);

    //hash_multimap_begin: 返回指向hash_multimap_t第一个数据的迭代器
    //hash_multimap_end: 返回指向hash_multimap_t末尾位置的迭代器
    printf("m1 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm1);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hmm)),
            *(int*)pair_second(iterator_get_pointer(it_hmm)));
    }
    // <1, 10> <2, 20> <3, 30>
    printf("\n");
    
    //使用hash_multimap_t类型为当前的hash_multimap_t赋值
    hash_multimap_assign(phmm_hmm1, phmm_hmm2);
    printf("m1 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm1);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hmm)),
            *(int*)pair_second(iterator_get_pointer(it_hmm)));
    }
    // <4, 40> <5, 50> <6, 60>
    printf("\n");


    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    phmm_hmm1 = create_hash_multimap(int, int);
    phmm_hmm2 = create_hash_multimap(int, int);
    hash_multimap_init(phmm_hmm1);
    hash_multimap_init_ex(phmm_hmm2, 100, NULL, NULL);

    // 返回hash_multimap_t中哈希表的存储单元的个数。
    printf("The default bucket count of hm1 is %d.\n",
    hash_multimap_bucket_count(phmm_hmm1)); //53
    printf("The custom bucket count of hm2 is %d.\n",
    hash_multimap_bucket_count(phmm_hmm2)); //193

    hash_multimap_destroy(phmm_hmm2);
    phmm_hmm2 = create_hash_multimap(int, int);
    hash_multimap_init(phmm_hmm2);

    //删除hash_multimap_t中的所有数据。
    hash_multimap_clear(phmm_hmm1);
    
    pair_make(ppair_p, 1, 1);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 1);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 1, 4); //忽略而不是覆盖
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 1);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    
    //hash_multimap_count 返回容器中包含指定数据的个数
    /* Keys must be unique in hash_multimap, so duplicates are ignored */
    printf("The number of elements in m1 with a sort key of 1 is: %d.\n",
        hash_multimap_count(phmm_hmm1, 1)); // 2
    printf("The number of elements in m1 with a sort key of 2 is: %d.\n",
        hash_multimap_count(phmm_hmm1, 2)); // 2
    printf("The number of elements in m1 with a sort key of 3 is: %d.\n",
        hash_multimap_count(phmm_hmm1, 3)); // 0

    printf("m1 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm1);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hmm)),
            *(int*)pair_second(iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    // 测试hash_multimap_t容器是否为空
    if(hash_multimap_empty(phmm_hmm1))
    {
        printf("The hash_multimap m1 is empty.\n");
    }

    //测试两个hash_multimap_t是否相等
    if(hash_multimap_equal(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimaps m1 and m2 are equal.\n");
    }

    //测试第一个hash_multimap_t容器是否大于第二个hash_multimap_t容器
    if(hash_multimap_greater(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimap m1 is greater than the hash_multimap m2.\n");
    }

    //测试第一个hash_multimap_t是否大于等于第二个hash_multimap_t
    if(hash_multimap_greater_equal(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimap m1 is greater than or equal to the hash_multimap m2.\n");
    }

    //测试第一个hash_multimap_t是否小于第二个hash_multimap_t
    if(hash_multimap_less(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimap m1 is less than the hash_multimap m2.\n");
    }

    //测试第一个hash_multimap_t是否小于等于第二个hash_multimap_t
    if(hash_multimap_less_equal(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimap m1 is less than or equal to the hash_multimap m2.\n");
    }
    
    //测试两个hash_multimap_t是否不等
    if(hash_multimap_not_equal(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimaps m1 and m2 are not equal.\n");
    }

    // 返回hash_multimap_t使用的哈希函数
    if(hash_multimap_hash(phmm_hmm2) == _hash_function)
    {
        printf("The hash function of hash_multimap hs2 is _hash_function.\n");
    }
    
    range_t r_r;
    hash_multimap_clear(phmm_hmm1);
    
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);

    //返回hash_multimap_t中包含指定数据的数据区间
    r_r = hash_multimap_equal_range(phmm_hmm1, 2); //返回数据区间大于等于20的

    printf("The lower bound of the element with a key of 2 in the hash_multimap m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_begin)));//30
    printf("The upper bound of the element with a key of 2 in the hash_multimap m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_end))); //20

    r_r = hash_multimap_equal_range(phmm_hmm1, 4);
    /* If no match is found for the key, both elements of the range return end() */
    if(iterator_equal(r_r.it_begin, hash_multimap_end(phmm_hmm1)) &&
        iterator_equal(r_r.it_end, hash_multimap_end(phmm_hmm1)))
    {
        printf("The hash_multimap m1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of hash_multimap m1 with a key >= 40 is %d.\n",
            *(int*)pair_first(iterator_get_pointer(r_r.it_begin)));
    }

    hash_multimap_clear(phmm_hmm1);
    
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 5, 50);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    
    //hash_multimap_erase 删除基于哈希结构的多重映射容器中与指定数据相等的数据
    int t_count = hash_multimap_erase(phmm_hmm1, 4); // <1, 10> <2, 20> <3, 30>  <5, 50> t_count = 1

    //hash_multimap_erase_pos 删除基于哈希结构的多重映射容器中指定位置的数据
    hash_multimap_erase_pos(phmm_hmm1, iterator_next(hash_multimap_begin(phmm_hmm1))); //<1, 10> <3, 30>  <5, 50>

    //hash_multimap_erase_range 删除基于哈希结构的多重映射容器中指定数据区间的数据
    hash_multimap_erase_range(phmm_hmm1, iterator_next(hash_multimap_begin(phmm_hmm1)),
        iterator_prev(hash_multimap_end(phmm_hmm1))); // <1, 10> <5, 50>

    //在hash_multimap_t中查找指定的数据
    it_hmm = hash_multimap_find(phmm_hmm1, 1);
    printf("The element of hash_multimap m1 with a key of 1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_hmm)));
    
    /* If no match is found for the key, end() is returned */
    it_hmm = hash_multimap_find(phmm_hmm1, 4);
    if(iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1)))
    {
        printf("The hash_multimap m1 doesn't have an element with a key of 4.\n");
    }
    
    hash_multimap_clear(phmm_hmm1);
    hash_multimap_clear(phmm_hmm2);

    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_multimap_insert(phmm_hmm1, ppair_p);

    //向hash_multimap_t中插入数据,成功后返回指向该数据的迭代器，如果hash_multimap_t中包含了该数据那么插入失败，返回hash_multimap_end()
    pair_make(ppair_p, 1, 10);
    it_hmm = hash_multimap_insert(phmm_hmm1, ppair_p);
    if(!iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1)))
    {
        printf("The element 10 was inserted in m1 successfully.\n");
    }
    else
    {
        printf("The number 1 already exists in m1.\n");
    }


    pair_make(ppair_p, 10, 100);
    hash_multimap_insert(phmm_hmm2, ppair_p);
    //插入指定的数据区间
    hash_multimap_insert_range(phmm_hmm2, iterator_next(hash_multimap_begin(phmm_hmm1)),
        iterator_prev(hash_multimap_end(phmm_hmm1)));
    printf("After the insertions, the key values of m2 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm2);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm2));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hmm)),
            *(int*)pair_second(iterator_get_pointer(it_hmm)));
    }
    //<2, 20> <3, 30> <4, 40> <10, 100>
    printf("\n");

    hash_multimap_clear(phmm_hmm1);
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    

    //返回hash_multimap_t中能够保存的数据个数的最大可能值
    printf("The maximum possible length of the hash_multimap is %u.\n",
        hash_multimap_max_size(phmm_hmm1));

    //返回hash_multimap_t中保存的数据的数量
    printf("The hash_multimap length is %d.\n", hash_multimap_size(phmm_hmm1));

    //交换两个hash_multimap_t中的内容
    hash_multimap_swap(phmm_hmm1, phmm_hmm2);

    binary_function_t bfun_vc = NULL;
    binary_function_t bfun_kc = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;
    hash_multimap_iterator_t it_hmm1;  //hash_multimap_t类型的迭代器类型
    hash_multimap_iterator_t it_hmm2;  //hash_multimap_t类型的迭代器类型

    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    phmm_hmm1 = create_hash_multimap(int, int);
    phmm_hmm2 = create_hash_multimap(int, int);

    hash_multimap_init_ex(phmm_hmm1, 0, NULL, fun_less_int);
    
    //返回hash_multimap_t的键比较规则
    bfun_kc = hash_multimap_key_comp(phmm_hmm1);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m1.\n");
    }

    hash_multimap_destroy(phmm_hmm1);

    hash_multimap_init_ex(phmm_hmm2, 0, NULL, fun_greater_int);

    bfun_kc = hash_multimap_key_comp(phmm_hmm2);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m2.\n");
    }
    
    hash_multimap_destroy(phmm_hmm2);
    
    phmm_hmm1 = create_hash_multimap(int, int);
    hash_multimap_init_ex(phmm_hmm1, 0, NULL, fun_less_int);

    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 5);
    hash_multimap_insert(phmm_hmm1, ppair_p);

    it_hmm1 = hash_multimap_find(phmm_hmm1, 1);
    it_hmm2 = hash_multimap_find(phmm_hmm1, 2);
    //返回hash_multimap_t中数据的比较规则,这个规则是针对数据本身的比较规则而不是键或者值
    bfun_vc = hash_multimap_value_comp(phmm_hmm1);

    (*bfun_vc)(iterator_get_pointer(it_hmm1), iterator_get_pointer(it_hmm2), &b_result);
    if(b_result)
    {
        printf("The element (1, 10) precedes the element (2, 5).\n");
    }
    else
    {
        printf("The element (1, 10) does not precedes the element (2, 5).\n");
    }

    (*bfun_vc)(iterator_get_pointer(it_hmm2), iterator_get_pointer(it_hmm1), &b_result);
    if(b_result)
    {
        printf("The element (2, 5) precedes the element (1, 10).\n");
    }
    else
    {
        printf("The element (2, 5) does not precedes the element (1, 10).\n");
    }
    hash_multimap_destroy(phmm_hmm1);

    hash_multimap_t* phmm_hmm0 = create_hash_multimap(int, int);
    phmm_hmm1 = create_hash_multimap(int, int);
    phmm_hmm2 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm3 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm4 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm5 = create_hash_multimap(int, int);

    if(phmm_hmm0 == NULL || phmm_hmm1 == NULL || phmm_hmm2 == NULL || phmm_hmm3 == NULL || phmm_hmm4 == NULL || phmm_hmm5 == NULL)
    {
        return -1;
    }
    
    //hash_multimap_init 初始化一个空的基于哈希结构的多重映射容器。
    hash_multimap_init(phmm_hmm0);

    //hash_multimap_init_ex 使用指定的排序规则初始化一个空的基于哈希结构的多重映射容器
    hash_multimap_init_ex(phmm_hmm1, 0, _hash_function, fun_less_int);
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_multimap_insert(phmm_hmm1, ppair_p);

    //hash_multimap_init_ex 使用指定的哈希函数，比较规则，存储单元数量初始化一个空的基于哈希结构的多重映射
    hash_multimap_init_ex(phmm_hmm2, 0, _hash_function, fun_greater_int);
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm2, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm2, ppair_p);

    //hash_multimap_init_copy 使用拷贝的方式初始化一个基于哈希结构的多重映射容器，所有内容都来自于源容器。
    hash_multimap_init_copy(phmm_hmm3, phmm_hmm1); 

    //hash_multimap_init_copy_range 使用指定的数据区间初始化一个基于哈希结构的多重映射容器。
    hash_multimap_init_copy_range(phmm_hmm4, hash_multimap_begin(phmm_hmm1), iterator_advance(hash_multimap_begin(phmm_hmm1), 2)); 

    //hash_multimap_init_copy_range_ex 使用指定的数据区间，哈希函数，比较规则，存储单元数量来初始化容器。
    hash_multimap_init_copy_range_ex(phmm_hmm5, hash_multimap_begin(phmm_hmm3),
        hash_multimap_end(phmm_hmm3), 100, _hash_function, fun_less_int);

    hash_multimap_destroy(phmm_hmm0);
    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    hash_multimap_destroy(phmm_hmm3);
    hash_multimap_destroy(phmm_hmm4);
    hash_multimap_destroy(phmm_hmm5);
    pair_destroy(ppair_p);

    return 0;
}

