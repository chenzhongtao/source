/*
file: deque.c

˫�˶��� deque_t
˫�˶���ʹ�����Եķ�ʽ�������ݣ�������(vector_t)һ��������������ķ������ݣ��Լ���ĩβ��Ч�Ĳ���
��ɾ�����ݣ���vector_t��ͬ����deque_tҲ�����ڶ��еĿ�ͷ��Ч�Ĳ����ɾ�����ݡ�����ӻ���ɾ��ʵ��ʱ��
deque_t�ĵ�������ʧЧ��


Typedefs
    deque_t ˫�˶���������
    deque_iterator_t ˫�˶��������ĵ�������

Operation Functions
    create_deque ����һ��˫�˶��С�
    deque_assign ��ԭʼ������ɾ�������µ�˫�˶����е����ݿ�����ԭ����˫�˶����С�
    deque_assign_elem ��ԭʼ������ɾ������ָ�����������ݿ�����ԭ����˫�˶����С�
    deque_assign_range ��ԭʼ������ɾ������ָ����Χ�ڵ����ݿ�����ԭ����˫�˶����С�
    deque_at ����˫�˶�����ָ��λ�õ����ݡ�
    deque_back ����˫�˶��������һ�����ݡ�
    deque_begin ����ָ��˫�˶����е�һ�����ݵĵ�������
    deque_clear ɾ��˫�˶����е��������ݡ�
    deque_destroy ����˫�˶��С�
    deque_empty ����˫�˶����Ƿ�Ϊ�ա�
    deque_end ����ָ��˫�˶���ĩβ�ĵ�������
    deque_equal ��������˫�˶����Ƿ���ȡ�
    deque_erase ɾ��˫�˶�����ָ��λ�õ����ݡ�
    deque_erase_range ɾ��˫�˶�����ָ����Χ�����ݡ�
    deque_front ����˫�˶��еĵ�һ�����ݡ�
    deque_greater ���Ե�һ��˫�˶����Ƿ���ڵڶ���˫�˶��С�
    deque_greater_equal ���Ե�һ��˫�˶����Ƿ���ڵ��ڵڶ���˫�˶��С�
    deque_init ��ʼ��һ���յ�˫�˶��С�
    deque_init_copy ʹ��һ��˫�˶��г�ʼ����һ��˫�˶��С�
    deque_init_copy_range ʹ��ָ����Χ�ڵ����ݳ�ʼ��˫�˶��С�
    deque_init_elem ʹ��ָ�����ݳ�ʼ��˫�˶��С�
    deque_init_n ʹ��ָ��������Ĭ�����ݳ�ʼ��˫�˶��С�
    deque_insert ��ָ��λ�ò������ݡ�
    deque_insert_range ��ָ��λ�ò���һ��ָ��������������ݡ�
    deque_insert_n ��ָ��λ�ò��������ݡ�
    deque_less ���Ե�һ��˫�˶����Ƿ�С�ڵڶ���˫�˶��С�
    deque_less_equal ���Ե�һ��˫�˶����Ƿ�С�ڵ��ڵڶ���˫�˶��С�
    deque_max_size ����˫�˶��е������ܳ��ȡ�
    deque_not_equal ��������˫�˶����Ƿ񲻵ȡ�
    deque_pop_back ɾ��˫�˶��е����һ�����ݡ�
    deque_pop_front ɾ��˫�˶��еĵ�һ�����ݡ�
    deque_push_back ��˫�˶��е�ĩβ���һ�����ݡ�
    deque_push_front ��˫�˶��еĿ�ͷ���һ�����ݡ�
    deque_resize ָ��˫�˶��е��µĳ��ȡ�
    deque_resize_elem ָ��˫�˶��е��µĳ��ȣ�����ָ��������䡣
    deque_size ����˫�˶��е����ݸ�����
    deque_swap ��������˫�˶����е����ݡ�

*/

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdq_q1 = create_deque(int); //����һ��˫�˶���
    deque_t* pdq_q2 = create_deque(int); //����һ��˫�˶���
    deque_iterator_t it_q;  //˫�˶��еĵ���������
    int* pn_i = NULL;
    int n_j = 0;
    
if(pdq_q1 == NULL || pdq_q2 == NULL)
{
    return -1;
}
    deque_init(pdq_q1);   //��ʼ��deque_t����
    deque_init(pdq_q2);   //��ʼ��deque_t����
    
    deque_push_back(pdq_q1, 10); //��deque_t������ĩβ���һ������
    deque_push_back(pdq_q1, 20);
    deque_push_back(pdq_q1, 30);
    
    deque_push_back(pdq_q2, 40);
    deque_push_back(pdq_q2, 50);
    deque_push_back(pdq_q2, 60);

    printf("q1 =");
    //deque_begin: ����ָ��deque_t�е�һ�����ݵĵ�����
    //deque_end: ����ָ��deque_tĩβ�ĵ�����
    //iterator_equal: ���������������Ƿ����
    //iterator_next: ���ָ����һ�����ݵĵ�����
    //iterator_get_pointer: ���ص�����ָ������ݵ�ָ��
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_q));
    }
    // q1 = 10 20 30
    printf("\n"); 
    //��ԭʼ������ɾ�������µ�˫�˶����е����ݿ�����ԭ����˫�˶����С�pdq_q2������pdq_q1
    deque_assign(pdq_q1, pdq_q2);
    printf("q1 =");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_q));
    }
    // q1 = 40 50 60
    printf("\n");

    //��ԭʼ������ɾ������ָ����Χ�ڵ����ݿ�����ԭ����˫�˶����С�
    deque_assign_range(pdq_q1, iterator_next(deque_begin(pdq_q2)), deque_end(pdq_q2));
    printf("q1 =");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_q));
    }
    //q1 = 50 60
    printf("\n");
    //��ԭʼ������ɾ������ָ�����������ݿ�����ԭ����˫�˶����С�
    deque_assign_elem(pdq_q1, 7, 4);
    printf("q1 =");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_q));
    }
    //q1 = 4 4 4 4 4 4 4
    printf("\n");
    
    //ɾ��deque_t�е��������ݡ�
    deque_clear(pdq_q1);

    deque_push_back(pdq_q1, 10);
    deque_push_back(pdq_q1, 20);

    //deque_at: ����ָ��deque_t��ָ��λ�õ����ݵ�ָ�롣
    pn_i = (int*)deque_at(pdq_q1, 0);
    n_j = *(int*)deque_at(pdq_q1, 1);
    printf("The first element is %d\n", *pn_i); // 10
    printf("The second element is %d\n", n_j);  // 20
    //����ָ��deque_t�����һ�����ݵ�ָ�롣
    pn_i = (int*)deque_back(pdq_q1);
    printf("The last integer of q1 is %d\n", *pn_i); // 20

    //����deque_t�Ƿ�Ϊ�ա�
    if(deque_empty(pdq_q1))
    {
        printf("The deque is emtpy.\n");
    }
    else
    {
        printf("The deque is not empty.\n");
    }

    //��������deque_t�Ƿ���ȡ�
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

    //ɾ��ָ��λ�õ�����
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

    //ɾ��ָ�����������е����ݡ�
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

    //����ָ���һ�����ݵ�ָ�롣
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
    
    // ���Ե�һ��deque_t�Ƿ���ڵ��ڵڶ���deque_t
    if(deque_greater_equal(pdq_q1, pdq_q2))
    {
        printf("Deque q1 is greater than or equal to deque q2.\n");
    }
    else
    {
        printf("Deque q1 is less than deque q2.\n");
    }

    //���Ե�һ��deque_t�����Ƿ�С�ڵڶ���deque_t���͡�
    if(deque_less(pdq_q1, pdq_q2))
    {
        printf("Deque q1 is less than deque q2.\n");
    }
    else
    {
        printf("Deque q1 is not less than deque q2.\n");
    }

    //���Ե�һ��deque_t�����Ƿ�С�ڵ��ڵڶ���deque_t���͡�
    if(deque_less_equal(pdq_q1, pdq_q2))
    {
        printf("Deque q1 is less than or equal to deque q2.\n");
    }
    else
    {
        printf("Deque q1 is greater than deque q2.\n");
    }

    //��������deque_t�����Ƿ񲻵ȡ�
    if(deque_not_equal(pdq_q1, pdq_q2))
    {
        printf("The deques are not equal.\n");
    }
    else
    {
        printf("The deques are equal.\n");
    }

    //����deque_t���ͱ������ݿ��ܵ����������
    printf("The maxmum possible length of the deque is %u 0x%x\n",
    deque_max_size(pdq_q1), deque_max_size(pdq_q1));  //4294967295  0xffffffff

    deque_clear(pdq_q1);
    //��deque_t������ĩβ���һ�����ݡ�
    deque_push_back(pdq_q1, 1); // 1
    deque_push_back(pdq_q1, 2); // 1 2

    //ɾ��deque_t�еĵ�һ�����ݡ�
    deque_pop_back(pdq_q1);// 1
    
    deque_push_back(pdq_q1, 2); // 1 2

    //ɾ��deque_t�еĵ�һ�����ݡ�
    deque_pop_front(pdq_q1);//2//2

    // ��deque_t�Ŀ�ʼλ��������ݡ�
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

    //iterator_advance: һ�ε����ಽ
    //deque_insert_n: ��ָ��λ�ò���������
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

    //��ָ��λ�ò���һ��ָ��������������ݡ�
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
    // ����ָ��deque_t�����ݵĸ���������Ĳ���ʹ��Ĭ������0
    deque_resize(pdq_q1, 2); // 1 10
    deque_resize(pdq_q1, 4); // 1 10 0 0

    //����ָ��deque_t�����ݵĸ���������Ĳ���ʹ��ָ�����������
    deque_resize_elem(pdq_q1, 5, 40);// 1 10 0 0 40

    //�������������ݵĸ�����
    printf("The deque length is %d\n", deque_size(pdq_q1)); //5

    //��������deque_t�����ݡ�
    deque_swap(pdq_q1, pdq_q2);
    
    // ����deque_t���ͷ��������Դ��
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

    // ��ʼ��һ���յ�˫�˶��С�
    deque_init(pdq_q0);
    // ʹ��ָ��������Ĭ�����ݳ�ʼ��˫�˶��С�
    deque_init_n(pdq_q1, 3); // 0 0 0
    // ʹ��ָ�����ݳ�ʼ��˫�˶��С�
    deque_init_elem(pdq_q2, 5, 2); // 2 2 2 2 2
    // ʹ��һ��˫�˶��г�ʼ����һ��˫�˶��С�
    deque_init_copy(pdq_q3, pdq_q2);// 2 2 2 2 2
    //ʹ��ָ����Χ�ڵ����ݳ�ʼ��˫�˶��С�
    deque_init_copy_range(pdq_q4, deque_begin(pdq_q3),
        iterator_advance(deque_begin(pdq_q3), 2)); // 2 2
        
    deque_destroy(pdq_q0);
    deque_destroy(pdq_q1);
    deque_destroy(pdq_q2);
    deque_destroy(pdq_q3);
    deque_destroy(pdq_q4);
    return 0;
}

