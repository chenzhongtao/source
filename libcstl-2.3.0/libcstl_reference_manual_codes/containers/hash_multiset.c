/*
file: hash_multiset.c

基于哈希结构的多重集合hash_multiset_t

基于哈希结构的多重集合容器hash_multiset_t是关联容器，它使用指定的哈希函数计算数据的存储位置，将数
据保存在这个位置上。hash_multiset_t中的数据位置是根据数据本身计算的，数据在hash_multiset_t容器中是允许重
复的，容器中数据也存在着某种有序性，所以也不能通过直接或者间接的方式修改容器中的数据。hash_multiset_t提
供双向迭代器，插入新的数据不会破坏原有的数据的迭代器，删除一个数据的时候只有指向数据本身的迭代器失效，
但是当哈希表重新计算数据位置的时候所有的迭代器都失效。

Typedefs
    hash_multiset_t 基于哈希结构的多重集合容器类型。
    hash_multiset_iterator_t 基于哈希结构的多重集合容器迭代器类型。

Operation Functions
    create_hash_multiset 创建基于哈希结构的多重集合容器类型。
    hash_multiset_assign 为基于哈希结构的多重集合容器赋值。
    hash_multiset_begin 返回基于哈希结构的多重集合中指向第一个数据的迭代器。
    hash_multiset_bucket_count 返回基于哈希结构的多重集合使用的哈希表的存储单元个数。
    hash_multiset_clear 删除基于哈希结构的多重集合中所有的数据。
    hash_multiset_count 统计基于哈希结构的多重集合包含的指定数据的个数。
    hash_multiset_destroy 销毁基于哈希结构的多重集合容器类型。
    hash_multiset_empty 测试基于哈希结构的多重集合是否为空。
    hash_multiset_end 返回基于哈希结构的多重集合的末尾位置的迭代器。
    hash_multiset_equal 测试两个基于哈希结构的多重集合是否相等。
    hash_multiset_equal_range 返回基于哈希结构的多重集合中包含指定数据的数据区间。
    hash_multiset_erase 删除基于哈希结构的多重集合中包含的指定数据。
    hash_multiset_erase_pos 删除基于哈希结构的多重集合中指定位置的数据。
    hash_multiset_erase_range 删除基于哈希结构的多重集合中指定数据区间的数据。
    hash_multiset_find 在基于哈希结构的多重集合中查找指定的数据。
    hash_multiset_greater 测试第一个基于哈希结构的多重集合是否大于第二个基于哈希结构的多重集合。
    hash_multiset_greater_equal 测试第一个基于哈希结构的多重集合是否大于等于第二个。
    hash_multiset_hash 返回基于哈希结构的多重集合使用的哈希函数。
    hash_multiset_init 初始化一个空的基于哈希结构的多重集合。
    hash_multiset_init_copy 通过拷贝的方式初始化基于哈希结构的多重集合。
    hash_multiset_init_copy_range 使用指定的数据区间初始化基于哈希结构的多重集合。
    hash_multiset_init_copy_range_ex 使用指定的数据区间，哈希函数，排序规则和存储单元个数进行初始化。
    hash_multiset_init_ex 使用指定的哈希函数，排序规则和存储单元个数进行初始化。
    hash_multiset_insert 向基于哈希结构的多重集合中插入数据。
    hash_multiset_insert_range 向基于哈希结构的多重集合中插入指定的数据区间。
    hash_multiset_key_comp 返回基于哈希结构的多重集合使用的键比较规则。
    hash_multiset_less 测试第一个基于哈希结构的多重集合是否小于第二个基于哈希结构的多重集合。
    hash_multiset_less_equal 测试第一个基于哈希结构的多重集合是否小于等于第二个。
    hash_multiset_max_size 返回基于哈希结构的多重集合能够保存数据的最大数量。
    hash_multiset_not_equal 测试两个基于哈希结构的多重集合是否不等。
    hash_multiset_resize 重新设置基于哈希结构的多重集合使用的哈希表的存储单元个数。
    hash_multiset_size 返回基于哈希结构的多重集合中数据的数量。
    hash_multiset_swap 交换两个基于哈希结构的多重集合的内容。
    hash_multiset_value_comp 返回基于哈希结构的多重集合使用的值比较规则。
*/

#include <stdio.h>
#include <cstl/chash_set.h>
#include <cstl/cfunctional.h>

static void _hash_function(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input + 20;
}

int main(int argc, char* argv[])
{
    hash_multiset_t* phmset_hms1 = create_hash_multiset(int); //创建hash_multiset_t类型
    hash_multiset_t* phmset_hms2 = create_hash_multiset(int);
    hash_multiset_iterator_t it_hms;  //hash_multiset_t类型的迭代器类型

    if(phmset_hms1 == NULL || phmset_hms2 == NULL)
    {
        return -1;
    }

    hash_multiset_init(phmset_hms1); //初始化hash_multiset_t类型
    hash_multiset_init(phmset_hms2);

    hash_multiset_insert(phmset_hms1, 10);//向基于哈希结构的多重集合中插入一个数据。
    hash_multiset_insert(phmset_hms1, 20);
    hash_multiset_insert(phmset_hms1, 30);
    
    hash_multiset_insert(phmset_hms2, 40);
    hash_multiset_insert(phmset_hms2, 50);
    hash_multiset_insert(phmset_hms2, 60);

    //hash_multiset_begin: 返回指向hash_multiset_t第一个数据的迭代器
    //hash_multiset_end: 返回指向hash_multiset_t末尾位置的迭代器
    printf("s1 =");
    for(it_hms = hash_multiset_begin(phmset_hms1); !iterator_equal(it_hms, hash_multiset_end(phmset_hms1)); it_hms = iterator_next(it_hms))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hms));
    }
    // 10 20 30
    printf("\n");
    
    //使用hash_multiset_t类型为当前的hash_multiset_t赋值
    hash_multiset_assign(phmset_hms1, phmset_hms2);
    printf("s1 =");
    for(it_hms = hash_multiset_begin(phmset_hms1); !iterator_equal(it_hms, hash_multiset_end(phmset_hms1)); it_hms = iterator_next(it_hms))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hms));
    }
    // 60 40 50
    printf("\n");

    hash_multiset_destroy(phmset_hms1);
    hash_multiset_destroy(phmset_hms2);
    phmset_hms1 = create_hash_multiset(int);
    phmset_hms2 = create_hash_multiset(int);
    
    if(phmset_hms1 == NULL || phmset_hms2 == NULL)
    {
        return -1;
    }
    
    hash_multiset_init(phmset_hms1);
    hash_multiset_init_ex(phmset_hms2, 100, NULL, NULL);

    // 返回hash_multiset_t中的哈希表的存储单元个数
    printf("The default bucket count of hs1 is %d.\n",
        hash_multiset_bucket_count(phmset_hms1)); //53
    printf("The custom bucket count of hs2 is %d.\n",
        hash_multiset_bucket_count(phmset_hms2)); // 193
    
    // 重新设置hash_multiset_t中哈希表存储单元的数量
    hash_multiset_resize(phmset_hms1, 100);
    
    printf("The bucket count of hash_multiset hs1 is now: %d.\n",
        hash_multiset_bucket_count(phmset_hms1));  // 193

    // hs1 resize之后，后面的hs1 和 hs2的比较和交换出错
    hash_multiset_destroy(phmset_hms1);
    hash_multiset_destroy(phmset_hms2);
    phmset_hms1 = create_hash_multiset(int);
    phmset_hms2 = create_hash_multiset(int);
    hash_multiset_init(phmset_hms1);
    hash_multiset_init(phmset_hms2);

    //删除hash_multiset_t中的所有数据。
    hash_multiset_clear(phmset_hms1);
    
    hash_multiset_insert(phmset_hms1, 1);
    hash_multiset_insert(phmset_hms1, 1);
    
    //hash_multiset_count 返回容器中包含指定数据的个数
    printf("The number of elements in s1 with a sort key of 1 is: %d.\n",
        hash_multiset_count(phmset_hms1, 1)); //1// 2
    printf("The number of elements in s1 with a sort key of 2 is: %d.\n",
        hash_multiset_count(phmset_hms1, 2)); //1// 0

    // 测试hash_multiset_t容器是否为空
    if(hash_multiset_empty(phmset_hms1))
    {
        printf("The hash_multiset s1 is empty.\n");
    }

    //测试两个hash_multiset_t是否相等
    if(hash_multiset_equal(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multisets s1 and s2 are equal.\n");
    }

    //测试第一个hash_multiset_t容器是否大于第二个hash_multiset_t容器
    if(hash_multiset_greater(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multiset s1 is greater than the hash_multiset s2.\n");
    }

    //测试第一个hash_multiset_t是否大于等于第二个hash_multiset_t
    if(hash_multiset_greater_equal(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multiset s1 is greater than or equal to the hash_multiset s2.\n");
    }

    //测试第一个hash_multiset_t是否小于第二个hash_multiset_t
    if(hash_multiset_less(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multiset s1 is less than the hash_multiset s2.\n");
    }

    //测试第一个hash_multiset_t是否小于等于第二个hash_multiset_t
    if(hash_multiset_less_equal(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multiset s1 is less than or equal to the hash_multiset s2.\n");
    }
    
    //测试两个hash_multiset_t是否不等
    if(hash_multiset_not_equal(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multisets s1 and s2 are not equal.\n");
    }

    // 返回hash_multiset_t使用的哈希函数
    if(hash_multiset_hash(phmset_hms2) == _hash_function)
    {
        printf("The hash function of hash_multiset hs2 is _hash_function.\n");
    }
   
    range_t r_r1;
    hash_multiset_clear(phmset_hms1);
    
    hash_multiset_insert(phmset_hms1, 10);
    hash_multiset_insert(phmset_hms1, 20);
    hash_multiset_insert(phmset_hms1, 30);

    //返回hash_multiset_t中包含指定数据的数据区间
    r_r1 = hash_multiset_equal_range(phmset_hms1, 20); //返回数据区间大于等于20的

    printf("The upper bound of the element with a key of 20 in the hash_multiset s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_end)); //30
    printf("The lower bound of the element with a key of 20 in the hash_multiset s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_begin)); //20


    r_r1 = hash_multiset_equal_range(phmset_hms1, 40);
    /* If no match is found for the key. both elements of the range return end() */
    if(iterator_equal(r_r1.it_begin, hash_multiset_end(phmset_hms1)) && iterator_equal(r_r1.it_end, hash_multiset_end(phmset_hms1)))
    {
        printf("The hash_multiset s1 doesn't have and element with a key less than 40.\n");
    }
    else
    {
        printf("The element of hash_multiset s1 with a key >= 40 is: %d.\n", *(int*)iterator_get_pointer(r_r1.it_begin));
    }

    hash_multiset_clear(phmset_hms1);
    
    hash_multiset_insert(phmset_hms1, 10);
    hash_multiset_insert(phmset_hms1, 20);
    hash_multiset_insert(phmset_hms1, 30);
    hash_multiset_insert(phmset_hms1, 40);
    hash_multiset_insert(phmset_hms1, 50);
    
    //hash_multiset_erase 删除基于哈希结构的多重集合容器中与指定数据相等的数据
    int t_count = hash_multiset_erase(phmset_hms1, 40); // 10 20 30 50  t_count = 1

    //hash_multiset_erase_pos 删除基于哈希结构的多重集合容器中指定位置的数据
    hash_multiset_erase_pos(phmset_hms1, iterator_next(hash_multiset_begin(phmset_hms1))); //10 30 50

    //hash_multiset_erase_range 删除基于哈希结构的多重集合容器中指定数据区间的数据
    hash_multiset_erase_range(phmset_hms1, iterator_next(hash_multiset_begin(phmset_hms1)),
        iterator_prev(hash_multiset_end(phmset_hms1))); // 10 50

    //在hash_multiset_t中查找指定的数据
    it_hms = hash_multiset_find(phmset_hms1, 10);
    printf("The element of hash_multiset s1 with a key of 20 is: %d.\n",
        *(int*)iterator_get_pointer(it_hms));
    
    it_hms = hash_multiset_find(phmset_hms1, 40);
    /* If no match is found for the key, end() is returned */
    if(iterator_equal(it_hms, hash_multiset_end(phmset_hms1)))
    {
        printf("The hash_multiset s1 doesn't have an element with a key of 40.\n");
    }
    
    hash_multiset_clear(phmset_hms1);
    hash_multiset_clear(phmset_hms2);

    hash_multiset_insert(phmset_hms1, 10);
    hash_multiset_insert(phmset_hms1, 20);
    hash_multiset_insert(phmset_hms1, 30);
    hash_multiset_insert(phmset_hms1, 40);

    //向hash_multiset_t中插入数据,成功后返回指向该数据的迭代器，如果hash_multiset_t中包含了该数据那么插入失败，返回hash_multiset_end()
    it_hms = hash_multiset_insert(phmset_hms1, 10);
    if(iterator_equal(it_hms, hash_multiset_end(phmset_hms1)))
    {
        printf("The element 10 already exists in s1.\n");
    }
    else
    {
        printf("The element 10 was inserted in s1 successfully.\n");
    }


    hash_multiset_insert(phmset_hms2, 100);
    hash_multiset_insert_range(phmset_hms2, iterator_next(hash_multiset_begin(phmset_hms1)), iterator_prev(hash_multiset_end(phmset_hms1)));
    printf("s2 =");
    for(it_hms = hash_multiset_begin(phmset_hms2); !iterator_equal(it_hms, hash_multiset_end(phmset_hms2)); it_hms = iterator_next(it_hms))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hms));
    }
    //20 30 100
    printf("\n");

    hash_multiset_clear(phmset_hms1);
    hash_multiset_insert(phmset_hms1, 10);
    hash_multiset_insert(phmset_hms1, 20);
    hash_multiset_insert(phmset_hms1, 30);
    

    //返回hash_multiset_t中能够保存的数据个数的最大可能值
    printf("The maximum possible length of the hash_multiset is %u.\n",
        hash_multiset_max_size(phmset_hms1));

    //返回hash_multiset_t中保存的数据的数量
    printf("The hash_multiset length is %d.\n", hash_multiset_size(phmset_hms1));

    //交换两个hash_multiset_t中的内容
    hash_multiset_swap(phmset_hms1, phmset_hms2);

    binary_function_t bfun_vl = NULL;
    binary_function_t bfun_kl = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;

    hash_multiset_clear(phmset_hms1);
    hash_multiset_destroy(phmset_hms2);
    phmset_hms2 = create_hash_multiset(int);
    
    //返回hash_multiset_t中数据的比较规则,由于hash_multiset_t中数据本身就是键，所以这个函数的返回值与hash_multiset_key_comp()相同
    bfun_vl = hash_multiset_value_comp(phmset_hms1);

    //返回hash_multiset_t的键比较规则,由于hash_multiset_t中数据本身就是键，所以这个函数的返回值与hash_multiset_value_comp()相同
    bfun_kl = hash_multiset_key_comp(phmset_hms1);
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
    
    hash_multiset_init_ex(phmset_hms2, 0, NULL, fun_greater_int);

    bfun_vl = hash_multiset_value_comp(phmset_hms2);
    bfun_kl = hash_multiset_key_comp(phmset_hms1);
    (*bfun_vl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_vl)(2, 3) returns value of true, where bfun_vl is the function of s2.\n");
    }
    else
    {
        printf("(*bfun_vl)(2, 3) returns value of false, where bfun_vl is the function of s2.\n");
    }

    
    hash_multiset_destroy(phmset_hms1);
    hash_multiset_destroy(phmset_hms2);

    hash_multiset_t* phmset_hms0 = create_hash_multiset(int);
    phmset_hms1 = create_hash_multiset(int);
    phmset_hms2 = create_hash_multiset(int);
    hash_multiset_t* phmset_hms3 = create_hash_multiset(int);
    hash_multiset_t* phmset_hms4 = create_hash_multiset(int);
    hash_multiset_t* phmset_hms5 = create_hash_multiset(int);

    if(phmset_hms0 == NULL || phmset_hms1 == NULL || phmset_hms2 == NULL || phmset_hms3 == NULL || phmset_hms4 == NULL || phmset_hms5 == NULL)
    {
        return -1;
    }


    //hash_multiset_init 初始化一个空的基于哈希结构的多重集合容器
    hash_multiset_init(phmset_hms0);

    //hash_multiset_init_ex 使用指定的哈希函数和比较规则初始化一个空的基于哈希结构的多重集合容器。
    hash_multiset_init_ex(phmset_hms1, 10, _hash_function, fun_less_int);
    hash_multiset_insert(phmset_hms1, 10);
    hash_multiset_insert(phmset_hms1, 20);
    hash_multiset_insert(phmset_hms1, 30);
    hash_multiset_insert(phmset_hms1, 40);//40 10 20 30

    //hash_multiset_init_ex 使用指定的哈希函数和比较规则初始化一个空的基于哈希结构的多重集合容器。
    hash_multiset_init_ex(phmset_hms2, 100, _hash_function, fun_greater_int);
    hash_multiset_insert(phmset_hms2, 10);
    hash_multiset_insert(phmset_hms2, 20);//10 20

    //hash_multiset_init_copy 使用一个基于哈希结构的多重集合容器初始化当前容器。
    hash_multiset_init_copy(phmset_hms3, phmset_hms1); //40 10 20 30

    //hash_multiset_init_copy_range 使用指定的数据区间初始化基于哈希结构的多重集合容器。
    hash_multiset_init_copy_range(phmset_hms4, hash_multiset_begin(phmset_hms1), iterator_advance(hash_multiset_begin(phmset_hms1), 2)); //10 40

    //hash_multiset_init_copy_range_ex 使用指定的数据区间，哈希函数和比较规则初始化基于哈希结构的多重集合容器。
    hash_multiset_init_copy_range_ex(phmset_hms5, hash_multiset_begin(phmset_hms3),
        iterator_next(hash_multiset_begin(phmset_hms3)), 100,
        _hash_function, fun_less_int);//40

    hash_multiset_destroy(phmset_hms0);
    hash_multiset_destroy(phmset_hms1);
    hash_multiset_destroy(phmset_hms2);
    hash_multiset_destroy(phmset_hms3);
    hash_multiset_destroy(phmset_hms4);
    hash_multiset_destroy(phmset_hms5);

    return 0;
}

