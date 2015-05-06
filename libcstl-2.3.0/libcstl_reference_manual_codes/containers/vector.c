/*
file: vector.c

向量vector_t
vector_t与数组类似，以线性方式保存并管理数据，但是它可以自动生长。vector_t快速的随机访问任何数据，
在vector_t末尾插入或删除数据花费常数时间，在开头或者中间插入或者删除花费线性时间。vector_t的迭代器是随机
访问迭代器，可以通过迭代器随机访问数据，获得并修改数据。当插入或者删除数据是，在插入或删除数据位置之后
的迭代器失效。

Typedefs
vector_t 向量容器类型。
vector_iterator_t 向量容器迭代器类型。

Operation Functions
    create_vector 创建向量容器类型。
    vector_assign 使用向量容器类型为当前向量容器赋值。
    vector_assign_elem 使用指定数据为向量容器赋值。
    vector_assign_range 使用指定的数据区间为向量赋值。
    vector_at 使用下标随机访问向量中的数据。
    vector_back 访问向量容器的最后一个数据。
    vector_begin 返回指向向量容器的开始的迭代器。
    vector_capacity 返回向量容器在不重新分配内存的情况下能够保存数据的个数。
    vector_clear 删除向量容器中的所有数据。
    vector_destroy 销毁向量容器类型。
    vector_empty 测试向量容器是否为空。
    vector_end 返回指向向量容器末尾位置的迭代器。
    vector_equal 测试两个向量容器是否相等。
    vector_erase 删除向量容器中指定位置的数据。
    vector_erase_range 删除向量容器中指定数据区间中的数据。
    vector_front 访问向量容器中第一个数据。
    vector_greater 测试第一个向量容器是否大于第二个向量容器。
    vector_greater_equal 测试第一个向量容器是否大于等于第二个向量容器。
    vector_init 初始化一个空的向量容器。
    vector_init_copy 使用一个向量容器类型初始化当前向量容器。
    vector_init_copy_range 使用指定数据区间中的数据初始化向量容器。
    vector_init_elem 使用指定数据初始化向量容器。
    vector_init_n 使用多个默认数据初始化向量容器。
    vector_insert 在向量容器的指定位置插入一个数据。
    vector_insert_n 在向量容器的指定位置插入多个数据。
    vector_insert_range 在向量容器的指定位置插入数据区间中的数据。
    vector_less 测试第一个向量容器是否小于第二个向量容器。
    vector_less_equal 测试第一个向量容器是否小于等于第二个向量容器。
    vector_max_size 向量容器能够保存的数据的可能最大数量。
    vector_not_equal 测试两个向量容器是否不等。
    vector_pop_back 删除向量容器中的最后一个数据。
    vector_push_back 在向量容器的末尾添加一个数据。
    vector_reserve 设置向量容器在不分配内存的情况下能够保存数据的个数。
    vector_resize 重新设置向量容器中数据的个数。
    vector_resize_elem 重新设置向量容器中数据的个数，不足的部分使用指定数据填充。
    vector_size 获得向量容器中的数据的个数。
    vector_swap 交换两个向量容器中的内容。
*/

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cfunctional.h>

//是否是奇数
static void is_odd(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int); //创建一个向量容器类型
    vector_t* pvec_v2 = create_vector(int);
    vector_iterator_t it_v; // 向量的迭代器类型

    int* pn_i = NULL;
    int* pn_j = NULL;

    if(pvec_v1 == NULL || pvec_v2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1); //初始化一个空的向量容器。
    vector_init(pvec_v2);

    vector_push_back(pvec_v1, 10);//向vector_t末尾添加一个数据。
    vector_push_back(pvec_v1, 20);
    vector_push_back(pvec_v1, 30);
    vector_push_back(pvec_v2, 40);
    vector_push_back(pvec_v2, 50);
    vector_push_back(pvec_v2, 60);

    printf("l1 =");
    //vector_begin: 返回指向vector_t中第一个数据的迭代器。
    //vector_end: 返回指向vector_t末尾的迭代器。
    for(it_v = vector_begin(pvec_v1); !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    //10 20 30
    printf("\n");

    //将另一个向量赋值给当前的向量。
    vector_assign(pvec_v1, pvec_v2); //pvec_v1 = 40 50 60

    //使用指定数据区间为向量赋值。
    vector_assign_range(pvec_v1, iterator_next(vector_begin(pvec_v2)), vector_end(pvec_v2));
    //pvec_v1 = 50 60

    //使用指定数据为向量赋值。
    vector_assign_elem(pvec_v1, 5, 4); //pvec_v1 = 4 4 4 4 4

    //删除vector_t中的所有数据。
    vector_clear(pvec_v1);
    
    vector_push_back(pvec_v1, 10);
    vector_push_back(pvec_v1, 20);
    
    //使用下标对vector_t中的数据进行随机访问,下标从零开始
    pn_i = (int*)vector_back(pvec_v1);
    printf("The last integer of v1 is %d\n", *pn_i);//20

    //访问向量容器中最后一个数据。
    pn_i = (int*)vector_at(pvec_v1, 1);
    printf("The last integer of v1 is %d\n", *pn_i);//20

    //访问vector_t中的第一个数据。
    pn_i = (int*)vector_front(pvec_v1);
    printf("The first integer of v1 is %d\n", *pn_i);//10

    // 返回vector_t在不重新分配内存时能够保存的数据的个数。
    printf("The length of storage allocated is now %d.\n",
        vector_capacity(pvec_v1));
    
    //测试vector_t是否为空。
    if(vector_empty(pvec_v1))
    {
        printf("The vector is empty.\n");
    }
    else
    {
        printf("The vector is not empty.\n");
    }
    
    //测试两个vector_t是否相等。 
    if(vector_equal(pvec_v1, pvec_v2))
    {
        ;
    }

    //测试两个vector_t是否不等
    if(vector_not_equal(pvec_v1, pvec_v2))
    {
        ;
    }

    //测试第一个vector_t是否大于第二个vector_t
    if(vector_greater(pvec_v1, pvec_v2))
    {
        ;
    }

    // 测试第一个vector_t是否大于等于第二个vector_t。
    if(vector_greater_equal(pvec_v1, pvec_v2))
    {
        ;
    }

    //测试第一个vector_t是否小于第二个vector_t。
    if(vector_less(pvec_v1, pvec_v2))
    {
        ;
    }

    //测试第一个vector_t是否小于等于第二个vector_t
    if(vector_less_equal(pvec_v1, pvec_v2))
    {
        ;
    }

    vector_push_back(pvec_v1, 30);
    vector_push_back(pvec_v1, 40);
    vector_push_back(pvec_v1, 50); // 10 20 30 40 50 

    //删除vector_t中指定位置的数据。
    vector_erase(pvec_v1, vector_begin(pvec_v1));//20 30 40 50

    //删除vector_t中指定数据区间的数据。
    vector_erase_range(pvec_v1, iterator_next(vector_begin(pvec_v1)),
        iterator_next_n(vector_begin(pvec_v1), 3)); //20 50

    vector_clear(pvec_v1);
    vector_clear(pvec_v2);
    vector_push_back(pvec_v1, 10);
    vector_push_back(pvec_v1, 20);
    vector_push_back(pvec_v1, 30);// 10 20 30 
    vector_push_back(pvec_v2, 40);
    vector_push_back(pvec_v2, 50);
    vector_push_back(pvec_v2, 60);//40 50 60
    //vector_insert 在指定位置插入一个数据。
    //vector_insert_range 在指定位置插入一个数据区间。
    //vector_insert_n 在指定位置插入多个数据。

    //在指定位置插入一个数据。 10 100 20 30
    vector_insert(pvec_v1, iterator_next(vector_begin(pvec_v1)), 100); 
    

    //在指定位置插入多个数据。10 100 200 200 20 30
    vector_insert_n(pvec_v1, iterator_advance(vector_begin(pvec_v1), 2), 2, 200);

    //在指定位置插入一个数据区间 10 40 50 100 200 200 20 30
    vector_insert_range(pvec_v1, iterator_next(vector_begin(pvec_v1)), vector_begin(pvec_v2), iterator_prev(vector_end(pvec_v2)));

    //返回vector_t中保存数据的可能的最大数量。 这是一个与系统相关的常量。
    printf("Maximum possible length of the vector is %u\n",
        vector_max_size(pvec_v1));

    //vector_pop_back 删除最后一个数据。
    vector_pop_back(pvec_v1);//10 40 50 100 200 200 20

    //vector_push_back 在向量的末尾添加一个数据。
    vector_push_back(pvec_v1, 1);//10 40 50 100 200 200 20 1

    //重设vector_t中数据的个数，当新的数据个数比当前个数多，多处的数据使用默认数据0填充
    vector_resize(pvec_v1, 2); // 10 40 
    vector_resize(pvec_v1, 4); // 10 40 0 0

    //重设vector_t中数据的个数，当新的数据个数比当前个数多，多处的数据使用指定数据填充。
    vector_resize_elem(pvec_v1, 5, 60); // 10 40 0 0 60

    //设置vector_t在未重新分配内存时能够保存的数据的数量。
    vector_reserve(pvec_v1, 20);
    printf("Current capacity of v1 = %d\n", vector_capacity(pvec_v1)); //20

    //返回vector_t中数据的个数
    printf("vector length is %d\n", vector_size(pvec_v1)); //5
    

    // 交换两个vector_t中的内容
    vector_swap(pvec_v1, pvec_v2);

    //销毁vector_t
    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);

    
    vector_t* pvec_v0 = create_vector(int);
    pvec_v1 = create_vector(int);
    pvec_v2 = create_vector(int);
    vector_t* pvec_v3 = create_vector(int);
    vector_t* pvec_v4 = create_vector(int);

    if(pvec_v0 == NULL || pvec_v1 == NULL || pvec_v2 == NULL || pvec_v3 == NULL || pvec_v4 == NULL)
    {
        return -1;
    }

    //vector_init 初始化一个空的向量容器。
    vector_init(pvec_v0);

    //vector_init_n 使用指定个数的默认数据初始化向量。
    vector_init_n(pvec_v1, 3);//0 0 0

    //vector_init_elem 使用指定数据初始化向量。
    vector_init_elem(pvec_v2, 5, 2);// 2 2 2 2 2

    //vector_init_copy 使用另一个向量初始化当前的向量。
    vector_init_copy(pvec_v3, pvec_v2); //2 // 2 2 2 2 2 

    //vector_init_copy_range 使用指定的数据区间初始化向量。
    vector_init_copy_range(pvec_v4, iterator_advance(vector_begin(pvec_v3), 2), vector_end(pvec_v3));//2 // 2 2 2
    //销毁vector_t
    vector_destroy(pvec_v0);
    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    vector_destroy(pvec_v3);
    vector_destroy(pvec_v4);

    return 0;
}

