/*
file: deque.c

双端队列 deque_t
双端队列使用线性的方式保存数据，像向量(vector_t)一样，它允许随机的访问数据，以及在末尾高效的插入
和删除数据，与vector_t不同的是deque_t也允许在队列的开头高效的插入和删除数据。当添加或者删除实际时，
deque_t的迭代器会失效。


Typedefs
    deque_t 双端队列容器。
    deque_iterator_t 双端队列容器的迭代器。

Operation Functions
    create_deque 创建一个双端队列。
    deque_assign 将原始的数据删除并将新的双端队列中的数据拷贝到原来的双端队列中。
    deque_assign_elem 将原始的数据删除并将指定个数的数据拷贝到原来的双端队列中。
    deque_assign_range 将原始的数据删除并将指定范围内的数据拷贝到原来的双端队列中。
    deque_at 访问双端队列中指定位置的数据。
    deque_back 访问双端队列中最后一个数据。
    deque_begin 返回指向双端队列中第一个数据的迭代器。
    deque_clear 删除双端队列中的所有数据。
    deque_destroy 销毁双端队列。
    deque_empty 测试双端队列是否为空。
    deque_end 返回指向双端队列末尾的迭代器。
    deque_equal 测试两个双端队列是否相等。
    deque_erase 删除双端队列中指定位置的数据。
    deque_erase_range 删除双端队列中指定范围的数据。
    deque_front 访问双端队列的第一个数据。
    deque_greater 测试第一个双端队列是否大于第二个双端队列。
    deque_greater_equal 测试第一个双端队列是否大于等于第二个双端队列。
    deque_init 初始化一个空的双端队列。
    deque_init_copy 使用一个双端队列初始化另一个双端队列。
    deque_init_copy_range 使用指定范围内的数据初始化双端队列。
    deque_init_elem 使用指定数据初始化双端队列。
    deque_init_n 使用指定个数的默认数据初始化双端队列。
    deque_insert 在指定位置插入数据。
    deque_insert_range 在指定位置插入一个指定数据区间的数据。
    deque_insert_n 在指定位置插入多个数据。
    deque_less 测试第一个双端队列是否小于第二个双端队列。
    deque_less_equal 测试第一个双端队列是否小于等于第二个双端队列。
    deque_max_size 返回双端队列的最大可能长度。
    deque_not_equal 测试两个双端队列是否不等。
    deque_pop_back 删除双端队列的最后一个数据。
    deque_pop_front 删除双端队列的第一个数据。
    deque_push_back 在双端队列的末尾添加一个数据。
    deque_push_front 在双端队列的开头添加一个数据。
    deque_resize 指定双端队列的新的长度。
    deque_resize_elem 指定双端队列的新的长度，并用指定数据填充。
    deque_size 返回双端队列的数据个数。
    deque_swap 交换两个双端队列中的数据。

*/

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdq_q1 = create_deque(int); //创建一个双端队列
    deque_t* pdq_q2 = create_deque(int); //创建一个双端队列
    deque_iterator_t it_q;  //双端队列的迭代器类型
    int* pn_i = NULL;
    int n_j = 0;
    
if(pdq_q1 == NULL || pdq_q2 == NULL)
{
    return -1;
}
    deque_init(pdq_q1);   //初始化deque_t容器
    deque_init(pdq_q2);   //初始化deque_t容器
    
    deque_push_back(pdq_q1, 10); //向deque_t容器的末尾添加一个数据
    deque_push_back(pdq_q1, 20);
    deque_push_back(pdq_q1, 30);
    
    deque_push_back(pdq_q2, 40);
    deque_push_back(pdq_q2, 50);
    deque_push_back(pdq_q2, 60);

    printf("q1 =");
    //deque_begin: 返回指向deque_t中第一个数据的迭代器
    //deque_end: 返回指向deque_t末尾的迭代器
    //iterator_equal: 测试两个迭代器是否相等
    //iterator_next: 获得指向下一个数据的迭代器
    //iterator_get_pointer: 返回迭代器指向的数据的指针
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_q));
    }
    // q1 = 10 20 30
    printf("\n"); 
    //将原始的数据删除并将新的双端队列中的数据拷贝到原来的双端队列中。pdq_q2拷贝到pdq_q1
    deque_assign(pdq_q1, pdq_q2);
    printf("q1 =");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_q));
    }
    // q1 = 40 50 60
    printf("\n");

    //将原始的数据删除并将指定范围内的数据拷贝到原来的双端队列中。
    deque_assign_range(pdq_q1, iterator_next(deque_begin(pdq_q2)), deque_end(pdq_q2));
    printf("q1 =");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_q));
    }
    //q1 = 50 60
    printf("\n");
    //将原始的数据删除并将指定个数的数据拷贝到原来的双端队列中。
    deque_assign_elem(pdq_q1, 7, 4);
    printf("q1 =");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_q));
    }
    //q1 = 4 4 4 4 4 4 4
    printf("\n");
    
    //删除deque_t中的所有数据。
    deque_clear(pdq_q1);

    deque_push_back(pdq_q1, 10);
    deque_push_back(pdq_q1, 20);

    //deque_at: 返回指向deque_t中指定位置的数据的指针。
    pn_i = (int*)deque_at(pdq_q1, 0);
    n_j = *(int*)deque_at(pdq_q1, 1);
    printf("The first element is %d\n", *pn_i); // 10
    printf("The second element is %d\n", n_j);  // 20
    //返回指向deque_t中最后一个数据的指针。
    pn_i = (int*)deque_back(pdq_q1);
    printf("The last integer of q1 is %d\n", *pn_i); // 20

    //测试deque_t是否为空。
    if(deque_empty(pdq_q1))
    {
        printf("The deque is emtpy.\n");
    }
    else
    {
        printf("The deque is not empty.\n");
    }

    //测试两个deque_t是否相等。
    if(deque_equal(pdq_q1, pdq_q2))
    {
        printf("The deques are equal.\n");
    }
    else
    {
        printf("The deques are not equal.\n");
    }

    deque_clear(pdq_q1);
    deque_push_back(pdq_q1, 10);
    deque_push_back(pdq_q1, 20);
    deque_push_back(pdq_q1, 30);
    deque_push_back(pdq_q1, 40);
    deque_push_back(pdq_q1, 50);

    //删除指定位置的数据
    deque_erase(pdq_q1, deque_begin(pdq_q1));
    printf("After erasing the first element, the deque becomes: ");
    for(it_q = deque_begin(pdq_q1);
        !iterator_equal(it_q, deque_end(pdq_q1));
        it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    //20 30 40 50
    printf("\n");

    //删除指定数据区间中的数据。
    deque_erase_range(pdq_q1,
        iterator_next(deque_begin(pdq_q1)),
        deque_end(pdq_q1));
    printf("After erasing all elements but the first, the deque becomes: ");
    for(it_q = deque_begin(pdq_q1);
        !iterator_equal(it_q, deque_end(pdq_q1));
        it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    //20
    printf("\n");

    //返回指向第一个数据的指针。
    pn_i = (int*)deque_front(pdq_q1);
    printf("The first integer of q1 is %d\n", *pn_i); //2//20

    deque_clear(pdq_q1);
    deque_clear(pdq_q2);
    
    deque_push_back(pdq_q1, 1);
    deque_push_back(pdq_q1, 3);
    deque_push_back(pdq_q1, 1);
    
    deque_push_back(pdq_q2, 1);
    deque_push_back(pdq_q2, 2);
    deque_push_back(pdq_q2, 2);
    
    if(deque_greater(pdq_q1, pdq_q2))
    {
        printf("Deque q1 is greater than deque q2.\n");
    }
    else
    {
        printf("Deque q1 is not greater than deque q2.\n");
    }
    
    // 测试第一个deque_t是否大于等于第二个deque_t
    if(deque_greater_equal(pdq_q1, pdq_q2))
    {
        printf("Deque q1 is greater than or equal to deque q2.\n");
    }
    else
    {
        printf("Deque q1 is less than deque q2.\n");
    }

    //测试第一个deque_t类型是否小于第二个deque_t类型。
    if(deque_less(pdq_q1, pdq_q2))
    {
        printf("Deque q1 is less than deque q2.\n");
    }
    else
    {
        printf("Deque q1 is not less than deque q2.\n");
    }

    //测试第一个deque_t类型是否小于等于第二个deque_t类型。
    if(deque_less_equal(pdq_q1, pdq_q2))
    {
        printf("Deque q1 is less than or equal to deque q2.\n");
    }
    else
    {
        printf("Deque q1 is greater than deque q2.\n");
    }

    //测试两个deque_t类型是否不等。
    if(deque_not_equal(pdq_q1, pdq_q2))
    {
        printf("The deques are not equal.\n");
    }
    else
    {
        printf("The deques are equal.\n");
    }

    //返回deque_t类型保存数据可能的最大数量。
    printf("The maxmum possible length of the deque is %u 0x%x\n",
    deque_max_size(pdq_q1), deque_max_size(pdq_q1));  //4294967295  0xffffffff

    deque_clear(pdq_q1);
    //向deque_t容器的末尾添加一个数据。
    deque_push_back(pdq_q1, 1); // 1
    deque_push_back(pdq_q1, 2); // 1 2

    //删除deque_t中的第一个数据。
    deque_pop_back(pdq_q1);// 1
    
    deque_push_back(pdq_q1, 2); // 1 2

    //删除deque_t中的第一个数据。
    deque_pop_front(pdq_q1);//2//2

    // 向deque_t的开始位置添加数据。
    deque_push_front(pdq_q1, 1);//3     //1 2

    deque_push_back(pdq_q1, 3); 
    deque_push_back(pdq_q1, 4);// 1 2 3 4

    deque_clear(pdq_q2);
    deque_push_back(pdq_q2, 5); 
    deque_push_back(pdq_q2, 6); 
    deque_push_back(pdq_q2, 7); // 5 6 7

    deque_insert(pdq_q1, iterator_next(deque_begin(pdq_q1)), 10);
    printf("q1 = ");
    for(it_q = deque_begin(pdq_q1);
        !iterator_equal(it_q, deque_end(pdq_q1));
        it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    // 1 10 2 3 4
    printf("\n");

    //iterator_advance: 一次迭代多步
    //deque_insert_n: 在指定位置插入多个数据
    deque_insert_n(pdq_q1, iterator_advance(deque_begin(pdq_q1), 2), 2, 20);
    printf("q1 = ");
    for(it_q = deque_begin(pdq_q1);
        !iterator_equal(it_q, deque_end(pdq_q1));
        it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    // 1 10 20 20 2 3 4
    printf("\n");

    //在指定位置插入一个指定数据区间的数据。
    deque_insert_range(pdq_q1, iterator_next(deque_begin(pdq_q1)),
            deque_begin(pdq_q2), iterator_prev(deque_end(pdq_q2)));
    for(it_q = deque_begin(pdq_q1);
        !iterator_equal(it_q, deque_end(pdq_q1));
        it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    // 1 10 20 20 2 3 4
    printf("\n");
    // 重新指定deque_t中数据的个数，扩充的部分使用默认数据0
    deque_resize(pdq_q1, 2); // 1 10
    deque_resize(pdq_q1, 4); // 1 10 0 0

    //重新指定deque_t中数据的个数，扩充的部分使用指定的数据填充
    deque_resize_elem(pdq_q1, 5, 40);// 1 10 0 0 40

    //返回容器中数据的个数。
    printf("The deque length is %d\n", deque_size(pdq_q1)); //5

    //交换两个deque_t的内容。
    deque_swap(pdq_q1, pdq_q2);
    
    // 销毁deque_t，释放申请的资源。
    deque_destroy(pdq_q1);
    deque_destroy(pdq_q2);

    deque_t* pdq_q0 = create_deque(int);
    pdq_q1 = create_deque(int);
    pdq_q2 = create_deque(int);
    deque_t* pdq_q3 = create_deque(int);
    deque_t* pdq_q4 = create_deque(int);
    if(pdq_q0 == NULL || pdq_q1 == NULL || pdq_q2 == NULL ||
        pdq_q3 == NULL || pdq_q4 == NULL)
    {
        return -1;
    }

    // 初始化一个空的双端队列。
    deque_init(pdq_q0);
    // 使用指定个数的默认数据初始化双端队列。
    deque_init_n(pdq_q1, 3); // 0 0 0
    // 使用指定数据初始化双端队列。
    deque_init_elem(pdq_q2, 5, 2); // 2 2 2 2 2
    // 使用一个双端队列初始化另一个双端队列。
    deque_init_copy(pdq_q3, pdq_q2);// 2 2 2 2 2
    //使用指定范围内的数据初始化双端队列。
    deque_init_copy_range(pdq_q4, deque_begin(pdq_q3),
        iterator_advance(deque_begin(pdq_q3), 2)); // 2 2
        
    deque_destroy(pdq_q0);
    deque_destroy(pdq_q1);
    deque_destroy(pdq_q2);
    deque_destroy(pdq_q3);
    deque_destroy(pdq_q4);
    return 0;
}

