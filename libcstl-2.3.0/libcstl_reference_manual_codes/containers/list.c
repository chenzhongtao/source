/*
file: list.c

˫������list_t
˫������������������һ�֣��������Եķ�ʽ�������ݣ�ͬʱ����������λ�ø�Ч�Ĳ������ɾ�����ݣ���
�ǲ��ܹ�����ķ��������е����ݡ�����list_t��ɾ�����ݵ�ʱ��ָ��ɾ�����ݵĵ�����ʧЧ��

Typedefs
    list_t ˫�������������͡�
    list_iterator_t ˫��������������͡

Operation Functions
    create_list ����˫������������
    list_assign ����һ��˫������ֵ����ǰ��˫������
    list_assign_elem ʹ��ָ������Ϊ˫������ֵ��
    list_assign_range ʹ��ָ����������Ϊ˫������ֵ��
    list_back �������һ�����ݡ�
    list_begin ����ָ���һ�����ݵĵ�������
    list_clear ɾ���������ݡ�
    list_destroy ����˫������������
    list_empty ���������Ƿ�Ϊ�ա�
    list_end ��������ĩβ�ĵ�������
    list_equal ��������˫�������Ƿ���ȡ�
    list_erase ɾ��ָ��λ�õ����ݡ�
    list_erase_range ɾ��ָ��������������ݡ�
    list_front ���������еĵ�һ�����ݡ�
    list_greater ���Ե�һ��˫�������Ƿ���ڵڶ���˫������
    list_greater_equal ���Ե�һ��˫�������Ƿ���ڵ��ڵڶ���˫������
    list_init ��ʼ��һ���յ�˫������������
    list_init_copy ʹ����һ��˫�������ʼ����ǰ��˫������
    list_init_copy_range ʹ��ָ�������������ʼ��˫������
    list_init_elem ʹ��ָ�����ݳ�ʼ��˫������
    list_init_n ʹ��ָ��������Ĭ�����ݳ�ʼ��˫������
    list_insert ��ָ��λ�ò���һ�����ݡ�
    list_insert_range ��ָ��λ�ò���һ���������䡣
    list_insert_n ��ָ��λ�ò��������ݡ�
    list_less ���Ե�һ��˫�������Ƿ�С�ڵڶ���˫������
    list_less_equal ���Ե�һ��˫�������Ƿ�С�ڵ��ڵڶ���˫������
    list_max_size ����˫�������ܹ������������ݸ�����
    list_merge �ϲ����������˫������
    list_merge_if �����ض�����ϲ����������˫������
    list_not_equal ��������˫�������Ƿ񲻵ȡ�
    list_pop_back ɾ�����һ�����ݡ�
    list_pop_front ɾ����һ�����ݡ�
    list_push_back ��˫�������ĩβ���һ�����ݡ�
    list_push_front ��˫������Ŀ�ͷ���һ�����ݡ�
    list_remove ɾ��˫����������ָ����������ȵ����ݡ�
    list_remove_if ɾ��˫�������з����ض���������ݡ�
    list_resize ��������˫�������е����ݸ���������Ĳ��ֲ���Ĭ���������
    list_resize_elem ��������˫�������е����ݸ���������Ĳ��ֲ���ָ��������䡣
    list_reverse ��˫�������е���������
    list_size ����˫�����������ݵĸ�����
    list_sort ����˫�������е����ݡ�
    list_sort_if ���չ�������˫�������е����ݡ�
    list_splice ��˫�������е�����ת�Ƶ���һ��˫�������С�
    list_splice_pos ���ƶ�λ�õ�����ת�Ƶ���һ��˫�������С�
    list_splice_range ���ƶ����������ת�Ƶ���һ��˫�������С�
    list_swap ��������˫����������ݡ�
    list_unique ɾ�����ڵ��ظ����ݡ�
    list_unique_if ɾ�����ڵ������������ݡ�
*/

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cfunctional.h>

//�Ƿ�������
static void is_odd(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int); //����һ��˫��������������
    list_t* plist_l2 = create_list(int);
    list_iterator_t it_l; // ˫������ĵ���������

    int* pn_i = NULL;
    int* pn_j = NULL;

    if(plist_l1 == NULL || plist_l2 == NULL)
    {
        return -1;
    }

    list_init(plist_l1); //��ʼ��һ���յ�˫������������
    list_init(plist_l2);

    list_push_back(plist_l1, 10);//��list_tĩβ���һ�����ݡ�
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 30);
    list_push_back(plist_l2, 40);
    list_push_back(plist_l2, 50);
    list_push_back(plist_l2, 60);
/*
list_assign ����һ��˫������ֵ����ǰ��˫������
list_assign_elem ʹ��ָ������Ϊ˫������ֵ��
list_assign_range ʹ��ָ����������Ϊ˫������ֵ��
*/
    printf("l1 =");
    //list_begin: ����ָ��list_t�е�һ�����ݵĵ�������
    //list_end: ����ָ��list_tĩβ�ĵ�������
    for(it_l = list_begin(plist_l1); !iterator_equal(it_l, list_end(plist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    //10 20 30
    printf("\n");

    //����һ��˫������ֵ����ǰ��˫������
    list_assign(plist_l1, plist_l2); //plist_l1 = 40 50 60

    //ʹ��ָ����������Ϊ˫������ֵ��
    list_assign_range(plist_l1, iterator_next(list_begin(plist_l2)), list_end(plist_l2));
    //plist_l1 = 50 60

    //ʹ��ָ������Ϊ˫������ֵ��
    list_assign_elem(plist_l1, 5, 4); //plist_l1 = 4 4 4 4 4

    //ɾ��list_t�е��������ݡ�
    list_clear(plist_l1);
    
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    
    //����˫���������������һ�����ݡ�
    pn_i = (int*)list_back(plist_l1);
    printf("The last integer of l1 is %d\n", *pn_i);//20

    //����list_t�еĵ�һ�����ݡ�
    pn_i = (int*)list_front(plist_l1);
    printf("The first integer of l1 is %d\n", *pn_i);//10

    //����list_t�Ƿ�Ϊ�ա�
    if(list_empty(plist_l1))
    {
        printf("The list is empty.\n");
    }
    else
    {
        printf("The list is not empty.\n");
    }
    
    //��������list_t�Ƿ���ȡ� 
    if(list_equal(plist_l1, plist_l2))
    {
        ;
    }

    //��������list_t�Ƿ񲻵�
    if(list_not_equal(plist_l1, plist_l2))
    {
        ;
    }

    //���Ե�һ��list_t�Ƿ���ڵڶ���list_t
    if(list_greater(plist_l1, plist_l2))
    {
        ;
    }

    // ���Ե�һ��list_t�Ƿ���ڵ��ڵڶ���list_t��
    if(list_greater_equal(plist_l1, plist_l2))
    {
        ;
    }

    //���Ե�һ��list_t�Ƿ�С�ڵڶ���list_t��
    if(list_less(plist_l1, plist_l2))
    {
        ;
    }

    //���Ե�һ��list_t�Ƿ�С�ڵ��ڵڶ���list_t
    if(list_less_equal(plist_l1, plist_l2))
    {
        ;
    }

    list_push_back(plist_l1, 30);
    list_push_back(plist_l1, 40);
    list_push_back(plist_l1, 50); // 10 20 30 40 50 

    //ɾ��list_t��ָ��λ�õ����ݡ�
    list_erase(plist_l1, list_begin(plist_l1));//20 30 40 50

    //ɾ��list_t��ָ��������������ݡ�
    list_erase_range(plist_l1, iterator_next(list_begin(plist_l1)),
        list_end(plist_l1)); //20

    list_clear(plist_l1);
    list_clear(plist_l2);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 30);// 10 20 30 
    list_push_back(plist_l2, 40);
    list_push_back(plist_l2, 50);
    list_push_back(plist_l2, 60);//40 50 60
    //list_insert ��ָ��λ�ò���һ�����ݡ�
    //list_insert_range ��ָ��λ�ò���һ���������䡣
    //list_insert_n ��ָ��λ�ò��������ݡ�

    //��ָ��λ�ò���һ�����ݡ� 10 100 20 30
    list_insert(plist_l1, iterator_next(list_begin(plist_l1)), 100); 
    

    //��ָ��λ�ò��������ݡ�10 100 200 200 20 30
    list_insert_n(plist_l1, iterator_advance(list_begin(plist_l1), 2), 2, 200);

    //��ָ��λ�ò���һ���������� 10 40 50 100 200 200 20 30
    list_insert_range(plist_l1, iterator_next(list_begin(plist_l1)), list_begin(plist_l2), iterator_prev(list_end(plist_l2)));

    //����list_t�б������ݵĿ��ܵ���������� ����һ����ϵͳ��صĳ�����
    printf("Maximum possible length of the list is %u\n",
        list_max_size(plist_l1));

    //list_pop_back ɾ�����һ�����ݡ�
    list_pop_back(plist_l1);//10 40 50 100 200 200 20

    //list_pop_front ɾ����һ�����ݡ�
    list_pop_front(plist_l1);//40 50 100 200 200 20
    
    //list_push_back ��˫�������ĩβ���һ�����ݡ�
    list_push_back(plist_l1, 1);//40 50 100 200 200 20 1

    //list_push_front ��˫������Ŀ�ͷ���һ�����ݡ�
    list_push_front(plist_l1, 2);//2 //2 40 50 100 200 200 20 1

    //ɾ��list_t����ָ��������ȵ����ݡ�
    list_remove(plist_l1, 200); // 2 40 50 100 20 1

    //ɾ��˫�������з����ض���������ݡ�
    list_remove_if(plist_l1, is_odd); //2 //40 50 100 20

    //����list_t�����ݵĸ��������µ����ݸ����ȵ�ǰ�����࣬�ദ������ʹ��Ĭ������0���
    list_resize(plist_l1, 2); // 40 50
    list_resize(plist_l1, 4); // 40 50 0 0

    //����list_t�����ݵĸ��������µ����ݸ����ȵ�ǰ�����࣬�ദ������ʹ��ָ��������䡣
    list_resize_elem(plist_l1, 5, 60); // 40 50 0 0 60

    //��list_t�е���������
    list_reverse(plist_l1);// 60 0 0 50 40

    //����list_t�����ݵĸ���
    printf("List length is %d\n", list_size(plist_l1)); //5
    

    //ʹ��Ĭ�ϵĹ���������������ݵ�˳���С����
    list_sort(plist_l1); // 0 0 40 50 60

    //ʹ��ָ������bfun_op����
    list_sort_if(plist_l1, fun_greater_int); // 60 50 40 0 0

    list_clear(plist_l1);
    list_clear(plist_l2);
    
    list_push_back(plist_l1, 3);
    list_push_back(plist_l1, 6); // 3 6
    list_push_back(plist_l2, 2);
    list_push_back(plist_l2, 4); // 2 4
    
    //list_merge �ϲ����������˫������
    list_merge(plist_l2, plist_l1);
    // plist_l2 = 2 3 4 6
    // plist_l = []
    
    list_push_back(plist_l1, 5);
    list_push_back(plist_l1, 1); // 5 1
    list_sort_if(plist_l2, fun_greater_int);
    
    //list_merge_if �����ض�����ϲ����������˫������
    list_merge_if(plist_l2, plist_l1, fun_greater_int);
    for(it_l = list_begin(plist_l2);
        !iterator_equal(it_l, list_end(plist_l2));
    it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");
    // plist_l2 = 6 5 4 3 2 1
    // plist_l = []
  
    //list_splice ��˫�������е�����ת�Ƶ���һ��˫�������С�
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 11);
    list_splice(plist_l2, iterator_next(list_begin(plist_l2)), plist_l1);
    // plist_l2 = 6 10 11 5 4 3 2 1
    // plist_l = []
    list_push_back(plist_l1, 12);
    list_push_back(plist_l1, 13); // 12 13
    
    //list_splice_pos ���ƶ�λ�õ�����ת�Ƶ���һ��˫�������С�
    list_splice_pos(plist_l2, iterator_next(list_begin(plist_l2)),
        plist_l1, list_begin(plist_l1));
    // plist_l2 = 6 12 10 11 5 4 3 2 1
    // plist_l = 13

    list_push_back(plist_l1, 14); 
    list_push_back(plist_l1, 15); // 13 14 15

    //list_splice_range ���ƶ����������ת�Ƶ���һ��˫�������С�
    list_splice_range(plist_l2, iterator_next(list_begin(plist_l2)),
        plist_l1, list_begin(plist_l1), iterator_prev(list_end(plist_l1)));
    // plist_l2 = 6 13 14 12 10 11 5 4 3 2 1
    // plist_l = 15

    // ��������list_t�е�����
    list_swap(plist_l1, plist_l2);

    list_clear(plist_l1);
    list_clear(plist_l2);
    list_push_back(plist_l1, -10);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, -10);
    
    //list_unique ɾ�����ڵ��ظ����ݡ�
    list_assign(plist_l2, plist_l1); //-10 10 20 -10
        
    //list_unique_if ɾ�����ڵ������������ݡ�
    list_unique(plist_l1); // -10 -10

    //����list_t
    list_destroy(plist_l1);
    list_destroy(plist_l2);

    
    list_t* plist_l0 = create_list(int);
    plist_l1 = create_list(int);
    plist_l2 = create_list(int);
    list_t* plist_l3 = create_list(int);
    list_t* plist_l4 = create_list(int);

    if(plist_l0 == NULL || plist_l1 == NULL || plist_l2 == NULL || plist_l3 == NULL || plist_l4 == NULL)
    {
        return -1;
    }

    //list_init ��ʼ��һ���յ�˫������������
    list_init(plist_l0);

    //list_init_n ʹ��ָ��������Ĭ�����ݳ�ʼ��˫������
    list_init_n(plist_l1, 3);//0 0 0

    //list_init_elem ʹ��ָ�����ݳ�ʼ��˫������
    list_init_elem(plist_l2, 5, 2);// 2 2 2 2 2

    //list_init_copy ʹ����һ��˫�������ʼ����ǰ��˫������
    list_init_copy(plist_l3, plist_l2); //2 // 2 2 2 2 2 

    //list_init_copy_range ʹ��ָ�������������ʼ��˫������
    list_init_copy_range(plist_l4, iterator_advance(list_begin(plist_l3), 2), list_end(plist_l3));//2 // 2 2 2

    //����list_t
    list_destroy(plist_l0);
    list_destroy(plist_l1);
    list_destroy(plist_l2);
    list_destroy(plist_l3);
    list_destroy(plist_l4);

    return 0;
}

static void is_odd(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    if(*(int*)cpv_input % 2 == 1)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
