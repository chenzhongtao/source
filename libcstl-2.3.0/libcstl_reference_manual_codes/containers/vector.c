/*
file: vector.c

����vector_t
vector_t���������ƣ������Է�ʽ���沢�������ݣ������������Զ�������vector_t���ٵ���������κ����ݣ�
��vector_tĩβ�����ɾ�����ݻ��ѳ���ʱ�䣬�ڿ�ͷ�����м�������ɾ����������ʱ�䡣vector_t�ĵ����������
���ʵ�����������ͨ������������������ݣ���ò��޸����ݡ����������ɾ�������ǣ��ڲ����ɾ������λ��֮��
�ĵ�����ʧЧ��

Typedefs
vector_t �����������͡�
vector_iterator_t �����������������͡�

Operation Functions
    create_vector ���������������͡�
    vector_assign ʹ��������������Ϊ��ǰ����������ֵ��
    vector_assign_elem ʹ��ָ������Ϊ����������ֵ��
    vector_assign_range ʹ��ָ������������Ϊ������ֵ��
    vector_at ʹ���±�������������е����ݡ�
    vector_back �����������������һ�����ݡ�
    vector_begin ����ָ�����������Ŀ�ʼ�ĵ�������
    vector_capacity �������������ڲ����·����ڴ��������ܹ��������ݵĸ�����
    vector_clear ɾ�����������е��������ݡ�
    vector_destroy ���������������͡�
    vector_empty �������������Ƿ�Ϊ�ա�
    vector_end ����ָ����������ĩβλ�õĵ�������
    vector_equal �����������������Ƿ���ȡ�
    vector_erase ɾ������������ָ��λ�õ����ݡ�
    vector_erase_range ɾ������������ָ�����������е����ݡ�
    vector_front �������������е�һ�����ݡ�
    vector_greater ���Ե�һ�����������Ƿ���ڵڶ�������������
    vector_greater_equal ���Ե�һ�����������Ƿ���ڵ��ڵڶ�������������
    vector_init ��ʼ��һ���յ�����������
    vector_init_copy ʹ��һ�������������ͳ�ʼ����ǰ����������
    vector_init_copy_range ʹ��ָ�����������е����ݳ�ʼ������������
    vector_init_elem ʹ��ָ�����ݳ�ʼ������������
    vector_init_n ʹ�ö��Ĭ�����ݳ�ʼ������������
    vector_insert ������������ָ��λ�ò���һ�����ݡ�
    vector_insert_n ������������ָ��λ�ò��������ݡ�
    vector_insert_range ������������ָ��λ�ò������������е����ݡ�
    vector_less ���Ե�һ�����������Ƿ�С�ڵڶ�������������
    vector_less_equal ���Ե�һ�����������Ƿ�С�ڵ��ڵڶ�������������
    vector_max_size ���������ܹ���������ݵĿ������������
    vector_not_equal �����������������Ƿ񲻵ȡ�
    vector_pop_back ɾ�����������е����һ�����ݡ�
    vector_push_back ������������ĩβ���һ�����ݡ�
    vector_reserve �������������ڲ������ڴ��������ܹ��������ݵĸ�����
    vector_resize ���������������������ݵĸ�����
    vector_resize_elem ���������������������ݵĸ���������Ĳ���ʹ��ָ��������䡣
    vector_size ������������е����ݵĸ�����
    vector_swap �����������������е����ݡ�
*/

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cfunctional.h>

//�Ƿ�������
static void is_odd(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int); //����һ��������������
    vector_t* pvec_v2 = create_vector(int);
    vector_iterator_t it_v; // �����ĵ���������

    int* pn_i = NULL;
    int* pn_j = NULL;

    if(pvec_v1 == NULL || pvec_v2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1); //��ʼ��һ���յ�����������
    vector_init(pvec_v2);

    vector_push_back(pvec_v1, 10);//��vector_tĩβ���һ�����ݡ�
    vector_push_back(pvec_v1, 20);
    vector_push_back(pvec_v1, 30);
    vector_push_back(pvec_v2, 40);
    vector_push_back(pvec_v2, 50);
    vector_push_back(pvec_v2, 60);

    printf("l1 =");
    //vector_begin: ����ָ��vector_t�е�һ�����ݵĵ�������
    //vector_end: ����ָ��vector_tĩβ�ĵ�������
    for(it_v = vector_begin(pvec_v1); !iterator_equal(it_v, vector_end(pvec_v1)); it_v = iterator_next(it_v))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_v));
    }
    //10 20 30
    printf("\n");

    //����һ��������ֵ����ǰ��������
    vector_assign(pvec_v1, pvec_v2); //pvec_v1 = 40 50 60

    //ʹ��ָ����������Ϊ������ֵ��
    vector_assign_range(pvec_v1, iterator_next(vector_begin(pvec_v2)), vector_end(pvec_v2));
    //pvec_v1 = 50 60

    //ʹ��ָ������Ϊ������ֵ��
    vector_assign_elem(pvec_v1, 5, 4); //pvec_v1 = 4 4 4 4 4

    //ɾ��vector_t�е��������ݡ�
    vector_clear(pvec_v1);
    
    vector_push_back(pvec_v1, 10);
    vector_push_back(pvec_v1, 20);
    
    //ʹ���±��vector_t�е����ݽ����������,�±���㿪ʼ
    pn_i = (int*)vector_back(pvec_v1);
    printf("The last integer of v1 is %d\n", *pn_i);//20

    //�����������������һ�����ݡ�
    pn_i = (int*)vector_at(pvec_v1, 1);
    printf("The last integer of v1 is %d\n", *pn_i);//20

    //����vector_t�еĵ�һ�����ݡ�
    pn_i = (int*)vector_front(pvec_v1);
    printf("The first integer of v1 is %d\n", *pn_i);//10

    // ����vector_t�ڲ����·����ڴ�ʱ�ܹ���������ݵĸ�����
    printf("The length of storage allocated is now %d.\n",
        vector_capacity(pvec_v1));
    
    //����vector_t�Ƿ�Ϊ�ա�
    if(vector_empty(pvec_v1))
    {
        printf("The vector is empty.\n");
    }
    else
    {
        printf("The vector is not empty.\n");
    }
    
    //��������vector_t�Ƿ���ȡ� 
    if(vector_equal(pvec_v1, pvec_v2))
    {
        ;
    }

    //��������vector_t�Ƿ񲻵�
    if(vector_not_equal(pvec_v1, pvec_v2))
    {
        ;
    }

    //���Ե�һ��vector_t�Ƿ���ڵڶ���vector_t
    if(vector_greater(pvec_v1, pvec_v2))
    {
        ;
    }

    // ���Ե�һ��vector_t�Ƿ���ڵ��ڵڶ���vector_t��
    if(vector_greater_equal(pvec_v1, pvec_v2))
    {
        ;
    }

    //���Ե�һ��vector_t�Ƿ�С�ڵڶ���vector_t��
    if(vector_less(pvec_v1, pvec_v2))
    {
        ;
    }

    //���Ե�һ��vector_t�Ƿ�С�ڵ��ڵڶ���vector_t
    if(vector_less_equal(pvec_v1, pvec_v2))
    {
        ;
    }

    vector_push_back(pvec_v1, 30);
    vector_push_back(pvec_v1, 40);
    vector_push_back(pvec_v1, 50); // 10 20 30 40 50 

    //ɾ��vector_t��ָ��λ�õ����ݡ�
    vector_erase(pvec_v1, vector_begin(pvec_v1));//20 30 40 50

    //ɾ��vector_t��ָ��������������ݡ�
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
    //vector_insert ��ָ��λ�ò���һ�����ݡ�
    //vector_insert_range ��ָ��λ�ò���һ���������䡣
    //vector_insert_n ��ָ��λ�ò��������ݡ�

    //��ָ��λ�ò���һ�����ݡ� 10 100 20 30
    vector_insert(pvec_v1, iterator_next(vector_begin(pvec_v1)), 100); 
    

    //��ָ��λ�ò��������ݡ�10 100 200 200 20 30
    vector_insert_n(pvec_v1, iterator_advance(vector_begin(pvec_v1), 2), 2, 200);

    //��ָ��λ�ò���һ���������� 10 40 50 100 200 200 20 30
    vector_insert_range(pvec_v1, iterator_next(vector_begin(pvec_v1)), vector_begin(pvec_v2), iterator_prev(vector_end(pvec_v2)));

    //����vector_t�б������ݵĿ��ܵ���������� ����һ����ϵͳ��صĳ�����
    printf("Maximum possible length of the vector is %u\n",
        vector_max_size(pvec_v1));

    //vector_pop_back ɾ�����һ�����ݡ�
    vector_pop_back(pvec_v1);//10 40 50 100 200 200 20

    //vector_push_back ��������ĩβ���һ�����ݡ�
    vector_push_back(pvec_v1, 1);//10 40 50 100 200 200 20 1

    //����vector_t�����ݵĸ��������µ����ݸ����ȵ�ǰ�����࣬�ദ������ʹ��Ĭ������0���
    vector_resize(pvec_v1, 2); // 10 40 
    vector_resize(pvec_v1, 4); // 10 40 0 0

    //����vector_t�����ݵĸ��������µ����ݸ����ȵ�ǰ�����࣬�ദ������ʹ��ָ��������䡣
    vector_resize_elem(pvec_v1, 5, 60); // 10 40 0 0 60

    //����vector_t��δ���·����ڴ�ʱ�ܹ���������ݵ�������
    vector_reserve(pvec_v1, 20);
    printf("Current capacity of v1 = %d\n", vector_capacity(pvec_v1)); //20

    //����vector_t�����ݵĸ���
    printf("vector length is %d\n", vector_size(pvec_v1)); //5
    

    // ��������vector_t�е�����
    vector_swap(pvec_v1, pvec_v2);

    //����vector_t
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

    //vector_init ��ʼ��һ���յ�����������
    vector_init(pvec_v0);

    //vector_init_n ʹ��ָ��������Ĭ�����ݳ�ʼ��������
    vector_init_n(pvec_v1, 3);//0 0 0

    //vector_init_elem ʹ��ָ�����ݳ�ʼ��������
    vector_init_elem(pvec_v2, 5, 2);// 2 2 2 2 2

    //vector_init_copy ʹ����һ��������ʼ����ǰ��������
    vector_init_copy(pvec_v3, pvec_v2); //2 // 2 2 2 2 2 

    //vector_init_copy_range ʹ��ָ�������������ʼ��������
    vector_init_copy_range(pvec_v4, iterator_advance(vector_begin(pvec_v3), 2), vector_end(pvec_v3));//2 // 2 2 2
    //����vector_t
    vector_destroy(pvec_v0);
    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    vector_destroy(pvec_v3);
    vector_destroy(pvec_v4);

    return 0;
}

