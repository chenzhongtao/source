/*
file: hash_set.c

基于哈希结构的集合hash_set_t

基于哈希结构的集合容器hash_set_t是关联容器，它使用指定的哈希函数计算数据的存储位置，将数据保存在
这个位置上。hash_set_t中的数据位置是根据数据本身计算的，并且保证数据在hash_set_t容器中的唯一性，所以在容
器中数据也存在着某种有序性，所以也不能通过直接或者间接的方式修改容器中的数据。hash_set_t提供双向迭代器，
插入新的数据不会破坏原有的数据的迭代器，删除一个数据的时候只有指向数据本身的迭代器失效，但是当哈希表重
新计算数据位置的时候所有的迭代器都失效。

Typedefs
    hash_set_t 基于哈希结构的集合容器类型。
    hash_set_iterator_t 基于哈希结构的集合容器迭代器类型。

Operation Functions
    create_hash_set 创建基于哈希结构的集合容器类型
    hash_set_assign 为基于哈希结构的集合容器赋值。
    hash_set_begin 返回指向容器中第一个数据的迭代器。
    hash_set_bucket_count 返回哈希表存储单元的数量。
    hash_set_clear 删除容器中的所有数据。
    hash_set_count 返回容器中指定数据的数量。
    hash_set_destroy 销毁基于哈希结构的集合容器。
    hash_set_empty 测试基于哈希结构的集合容器是否为空。
    hash_set_end 返回指向基于哈希结构的集合容器末尾的迭代器。
    hash_set_equal 测试两个基于哈希结构的集合容器是否相等。
    hash_set_equal_range 返回容器中包含指定数据的数据区间。
    hash_set_erase 删除容器中的指定数据。
    hash_set_erase_pos 删除容器中指定位置的数据。
    hash_set_erase_range 删除容器中指定数据区间的数据。
    hash_set_find 在基于哈希结构的集合容器中查找指定的数据。
    hash_set_greater 测试第一个基于哈希结构的集合容器是否大于第二个基于哈希结构的集合容器。
    hash_set_greater_equal 测试第一个基于哈希结构的集合容器是否大于等于第二个基于哈希结构的集合容器。
    hash_set_hash 返回基于哈希结构的集合容器使用的哈希函数。
    hash_set_init 初始化一个空的基于哈希结构的集合容器。
    hash_set_init_copy 使用一个基于哈希结构的集合容器初始化当前容器。
    hash_set_init_copy_range 使用指定的数据区间初始化基于哈希结构的集合容器。
    hash_set_init_copy_range_ex 使用指定的数据区间，哈希函数和比较规则初始化基于哈希结构的集合容器。
    hash_set_init_ex 使用指定的哈希函数和比较规则初始化一个空的基于哈希结构的集合容器。
    hash_set_insert 向基于哈希结构的集合容器中插入指定的数据。
    hash_set_insert_range 向基于哈希结构的集合容器中插入指定的数据区间。
    hash_set_key_comp 返回基于哈希结构的集合容器使用的键比较规则。
    hash_set_less 测试第一个基于哈希结构的集合容器是否小于第二个基于哈希结构的集合容器。
    hash_set_less_equal 测试第一个基于哈希结构的集合容器是否小于等于第二个基于哈希结构的集合容器。
    hash_set_max_size 返回基于哈希结构的集合容器保存数据数量的最大可能值。
    hash_set_not_equal 测试两个基于哈希结构的集合容器是否不等。
    hash_set_resize 重新设置哈希表存储单元的数量。
    hash_set_size 返回基于哈希结构的集合容器中数据的数量。
    hash_set_swap 交换两个基于哈希结构的集合容器中的内容。
    hash_set_value_comp 返回基于哈希结构的集合容器中使用的数据比较规则。
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
    hash_set_t* phset_hs1 = create_hash_set(int); //创建hash_set_t类型
    hash_set_t* phset_hs2 = create_hash_set(int);
    hash_set_iterator_t it_hs;  //hash_set_t类型的迭代器类型

    if(phset_hs1 == NULL || phset_hs2 == NULL)
    {
        return -1;
    }

    hash_set_init(phset_hs1); //初始化hash_set_t类型
    hash_set_init(phset_hs2);

    hash_set_insert(phset_hs1, 10);//向基于哈希结构的集合中插入一个数据。
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);
    
    hash_set_insert(phset_hs2, 40);
    hash_set_insert(phset_hs2, 50);
    hash_set_insert(phset_hs2, 60);

    //hash_set_begin: 返回指向hash_set_t第一个数据的迭代器
    //hash_set_end: 返回指向hash_set_t末尾位置的迭代器
    printf("s1 =");
    for(it_hs = hash_set_begin(phset_hs1); !iterator_equal(it_hs, hash_set_end(phset_hs1)); it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    // 10 20 30
    printf("\n");
    
    //使用hash_set_t类型为当前的hash_set_t赋值
    hash_set_assign(phset_hs1, phset_hs2);
    printf("s1 =");
    for(it_hs = hash_set_begin(phset_hs1); !iterator_equal(it_hs, hash_set_end(phset_hs1)); it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    // 60 40 50
    printf("\n");

    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);
    phset_hs1 = create_hash_set(int);
    phset_hs2 = create_hash_set(int);
    
    if(phset_hs1 == NULL || phset_hs2 == NULL)
    {
        return -1;
    }
    
    hash_set_init(phset_hs1);
    hash_set_init_ex(phset_hs2, 100, NULL, NULL);

    // 返回hash_set_t中的哈希表的存储单元个数
    printf("The default bucket count of hs1 is %d.\n",
        hash_set_bucket_count(phset_hs1)); //53
    printf("The custom bucket count of hs2 is %d.\n",
        hash_set_bucket_count(phset_hs2)); // 193
    
    // 重新设置hash_set_t中哈希表存储单元的数量
    hash_set_resize(phset_hs1, 100);
    
    printf("The bucket count of hash_set hs1 is now: %d.\n",
        hash_set_bucket_count(phset_hs1));  // 193

    // hs1 resize之后，后面的hs1 和 hs2的比较和交换出错
    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);
    phset_hs1 = create_hash_set(int);
    phset_hs2 = create_hash_set(int);
    hash_set_init(phset_hs1);
    hash_set_init(phset_hs2);

    //删除hash_set_t中的所有数据。
    hash_set_clear(phset_hs1);
    
    hash_set_insert(phset_hs1, 1);
    hash_set_insert(phset_hs1, 1);
    
    //hash_set_count 返回容器中包含指定数据的个数
    printf("The number of elements in s1 with a sort key of 1 is: %d.\n",
        hash_set_count(phset_hs1, 1)); //1// 1
    printf("The number of elements in s1 with a sort key of 2 is: %d.\n",
        hash_set_count(phset_hs1, 2)); //1// 0

    // 测试hash_set_t容器是否为空
    if(hash_set_empty(phset_hs1))
    {
        printf("The hash_set s1 is empty.\n");
    }

    //测试两个hash_set_t是否相等
    if(hash_set_equal(phset_hs1, phset_hs2))
    {
        printf("The hash_sets s1 and s2 are equal.\n");
    }

    //测试第一个hash_set_t容器是否大于第二个hash_set_t容器
    if(hash_set_greater(phset_hs1, phset_hs2))
    {
        printf("The hash_set s1 is greater than the hash_set s2.\n");
    }

    //测试第一个hash_set_t是否大于等于第二个hash_set_t
    if(hash_set_greater_equal(phset_hs1, phset_hs2))
    {
        printf("The hash_set s1 is greater than or equal to the hash_set s2.\n");
    }

    //测试第一个hash_set_t是否小于第二个hash_set_t
    if(hash_set_less(phset_hs1, phset_hs2))
    {
        printf("The hash_set s1 is less than the hash_set s2.\n");
    }

    //测试第一个hash_set_t是否小于等于第二个hash_set_t
    if(hash_set_less_equal(phset_hs1, phset_hs2))
    {
        printf("The hash_set s1 is less than or equal to the hash_set s2.\n");
    }
    
    //测试两个hash_set_t是否不等
    if(hash_set_not_equal(phset_hs1, phset_hs2))
    {
        printf("The hash_sets s1 and s2 are not equal.\n");
    }

    // 返回hash_set_t使用的哈希函数
    if(hash_set_hash(phset_hs2) == _hash_function)
    {
        printf("The hash function of hash_set hs2 is _hash_function.\n");
    }
   
    range_t r_r1;
    hash_set_clear(phset_hs1);
    
    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);

    //返回hash_set_t中包含指定数据的数据区间
    r_r1 = hash_set_equal_range(phset_hs1, 20); //返回数据区间大于等于20的

    printf("The upper bound of the element with a key of 20 in the hash_set s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_end)); //30
    printf("The lower bound of the element with a key of 20 in the hash_set s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_begin)); //20


    r_r1 = hash_set_equal_range(phset_hs1, 40);
    /* If no match is found for the key. both elements of the range return end() */
    if(iterator_equal(r_r1.it_begin, hash_set_end(phset_hs1)) && iterator_equal(r_r1.it_end, hash_set_end(phset_hs1)))
    {
        printf("The hash_set s1 doesn't have and element with a key less than 40.\n");
    }
    else
    {
        printf("The element of hash_set s1 with a key >= 40 is: %d.\n", *(int*)iterator_get_pointer(r_r1.it_begin));
    }

    hash_set_clear(phset_hs1);
    
    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);
    hash_set_insert(phset_hs1, 40);
    hash_set_insert(phset_hs1, 50);
    
    //hash_set_erase 删除基于哈希结构的集合容器中与指定数据相等的数据
    int t_count = hash_set_erase(phset_hs1, 40); // 10 20 30 50  t_count = 1

    //hash_set_erase_pos 删除基于哈希结构的集合容器中指定位置的数据
    hash_set_erase_pos(phset_hs1, iterator_next(hash_set_begin(phset_hs1))); //10 30 50

    //hash_set_erase_range 删除基于哈希结构的集合容器中指定数据区间的数据
    hash_set_erase_range(phset_hs1, iterator_next(hash_set_begin(phset_hs1)),
        iterator_prev(hash_set_end(phset_hs1))); // 10 50

    //在hash_set_t中查找指定的数据
    it_hs = hash_set_find(phset_hs1, 10);
    printf("The element of hash_set s1 with a key of 20 is: %d.\n",
        *(int*)iterator_get_pointer(it_hs));
    
    it_hs = hash_set_find(phset_hs1, 40);
    /* If no match is found for the key, end() is returned */
    if(iterator_equal(it_hs, hash_set_end(phset_hs1)))
    {
        printf("The hash_set s1 doesn't have an element with a key of 40.\n");
    }
    
    hash_set_clear(phset_hs1);
    hash_set_clear(phset_hs2);

    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);
    hash_set_insert(phset_hs1, 40);

    //向hash_set_t中插入数据,成功后返回指向该数据的迭代器，如果hash_set_t中包含了该数据那么插入失败，返回hash_set_end()
    it_hs = hash_set_insert(phset_hs1, 10);
    if(iterator_equal(it_hs, hash_set_end(phset_hs1)))
    {
        printf("The element 10 already exists in s1.\n");
    }
    else
    {
        printf("The element 10 was inserted in s1 successfully.\n");
    }


    hash_set_insert(phset_hs2, 100);
    hash_set_insert_range(phset_hs2, iterator_next(hash_set_begin(phset_hs1)), iterator_prev(hash_set_end(phset_hs1)));
    printf("s2 =");
    for(it_hs = hash_set_begin(phset_hs2); !iterator_equal(it_hs, hash_set_end(phset_hs2)); it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    //20 30 100
    printf("\n");

    hash_set_clear(phset_hs1);
    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);
    

    //返回hash_set_t中能够保存的数据个数的最大可能值
    printf("The maximum possible length of the hash_set is %u.\n",
        hash_set_max_size(phset_hs1));

    //返回hash_set_t中保存的数据的数量
    printf("The hash_set length is %d.\n", hash_set_size(phset_hs1));

    //交换两个hash_set_t中的内容
    hash_set_swap(phset_hs1, phset_hs2);

    binary_function_t bfun_vl = NULL;
    binary_function_t bfun_kl = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;

    hash_set_clear(phset_hs1);
    hash_set_destroy(phset_hs2);
    phset_hs2 = create_hash_set(int);
    
    //返回hash_set_t中数据的比较规则,由于hash_set_t中数据本身就是键，所以这个函数的返回值与hash_set_key_comp()相同
    bfun_vl = hash_set_value_comp(phset_hs1);

    //返回hash_set_t的键比较规则,由于hash_set_t中数据本身就是键，所以这个函数的返回值与hash_set_value_comp()相同
    bfun_kl = hash_set_key_comp(phset_hs1);
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
    
    hash_set_init_ex(phset_hs2, 0, NULL, fun_greater_int);

    bfun_vl = hash_set_value_comp(phset_hs2);
    bfun_kl = hash_set_key_comp(phset_hs1);
    (*bfun_vl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_vl)(2, 3) returns value of true, where bfun_vl is the function of s2.\n");
    }
    else
    {
        printf("(*bfun_vl)(2, 3) returns value of false, where bfun_vl is the function of s2.\n");
    }

    
    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);

    hash_set_t* phset_hs0 = create_hash_set(int);
    phset_hs1 = create_hash_set(int);
    phset_hs2 = create_hash_set(int);
    hash_set_t* phset_hs3 = create_hash_set(int);
    hash_set_t* phset_hs4 = create_hash_set(int);
    hash_set_t* phset_hs5 = create_hash_set(int);

    if(phset_hs0 == NULL || phset_hs1 == NULL || phset_hs2 == NULL || phset_hs3 == NULL || phset_hs4 == NULL || phset_hs5 == NULL)
    {
        return -1;
    }


    //hash_set_init 初始化一个空的基于哈希结构的集合容器
    hash_set_init(phset_hs0);

    //hash_set_init_ex 使用指定的哈希函数和比较规则初始化一个空的基于哈希结构的集合容器。
    hash_set_init_ex(phset_hs1, 10, _hash_function, fun_less_int);
    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);
    hash_set_insert(phset_hs1, 40);//40 10 20 30

    //hash_set_init_ex 使用指定的哈希函数和比较规则初始化一个空的基于哈希结构的集合容器。
    hash_set_init_ex(phset_hs2, 100, _hash_function, fun_greater_int);
    hash_set_insert(phset_hs2, 10);
    hash_set_insert(phset_hs2, 20);//10 20

    //hash_set_init_copy 使用一个基于哈希结构的集合容器初始化当前容器。
    hash_set_init_copy(phset_hs3, phset_hs1); //40 10 20 30

    //hash_set_init_copy_range 使用指定的数据区间初始化基于哈希结构的集合容器。
    hash_set_init_copy_range(phset_hs4, hash_set_begin(phset_hs1), iterator_advance(hash_set_begin(phset_hs1), 2)); //10 40

    //hash_set_init_copy_range_ex 使用指定的数据区间，哈希函数和比较规则初始化基于哈希结构的集合容器。
    hash_set_init_copy_range_ex(phset_hs5, hash_set_begin(phset_hs3),
        iterator_next(hash_set_begin(phset_hs3)), 100,
        _hash_function, fun_less_int);//40

    hash_set_destroy(phset_hs0);
    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);
    hash_set_destroy(phset_hs3);
    hash_set_destroy(phset_hs4);
    hash_set_destroy(phset_hs5);

    return 0;
}

