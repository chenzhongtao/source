/*
file: slist.c

��������slist_t

slist_t������һ�ֵ�������֧����ǰ�������ǲ�֧�������������κ�λ�ú�������ɾ�����ݻ��ѳ���ʱ
�䣬��ǰ������ɾ�����ݻ�������ʱ�䡣��slist_t�в����ɾ�����ݲ���ʹ������ʧЧ��slist_t��list_t��һ��������
����֧������������ݣ���˫�������������slist_t��ɾ������ʱ��ָ��ɾ�������ݵĵ�����ʧЧ��

Typedefs
    slist_t ���������������͡�
    slist_iterator_t ����������������͡�

Operation Functions
    create_slist �������������������͡�
    slist_assign ʹ�õ�������Ϊ��ǰ�ĵ����������͸�ֵ��
    slist_assign_elem ʹ��ָ��������Ϊ��������ֵ��
    slist_assign_range ʹ��ָ�����������е�����Ϊ��������ֵ��
    slist_begin ����ָ���������һ�����ݵĵ�������
    slist_clear ɾ�������������������ݡ�
    slist_destroy ���ٵ�������
    slist_empty ���Ե��������Ƿ�Ϊ�ա�
    slist_end ���ص�������ĩβλ�õĵ�������
    slist_equal �����������������Ƿ���ȡ�
    slist_erase ɾ������������ָ��λ�õ����ݡ�
    slist_erase_after ɾ������������ָ��λ�ú�����Ǹ����ݡ�
    slist_erase_after_range ɾ������������ָ�������������������������ݡ�
    slist_erase_range ɾ������������ָ��������������ݡ�
    slist_front ���ʵ��������е�һ�����ݡ�
    slist_greater ���Ե�һ�����������Ƿ���ڵڶ�����������
    slist_greater_equal ���Ե�һ�����������Ƿ���ڵ��ڵڶ�����������
    slist_init ��ʼ��һ���յĵ�������
    slist_init_copy ʹ��һ�����������ʼ����ǰ��������
    slist_init_copy_range ʹ��һ��ָ�������������е����ݳ�ʼ����������
    slist_init_elem ʹ��ָ�������ݳ�ʼ����������
    slist_init_n ʹ�ö��Ĭ�����ݳ�ʼ����������
    slist_insert ���������ָ��λ�ò���һ�����ݡ�
    slist_insert_after ���������ָ��λ�õ���һ��λ�ò���һ�����ݡ�
    slist_insert_after_n ���������ָ��λ�õ���һ��λ�ò��������ݡ�
    slist_insert_after_range ���������ָ��λ�õ���һ��λ�ò������������е����ݡ�
    slist_insert_n ���������ָ��λ�ò��������ݡ�
    slist_insert_range ���������ָ��λ�ò������������е����ݡ�
    slist_less ���Ե�һ�����������Ƿ�С�ڵڶ�����������
    slist_less_equal ���Ե�һ�����������Ƿ�С�ڵ��ڵڶ�����������
    slist_max_size ���ص����������ܹ��������ݵ����������
    slist_merge �ϲ�������������
    slist_merge_if ����ָ������ϲ���������
    slist_not_equal �����������������Ƿ񲻵ȡ�
    slist_pop_front ɾ�����������еĵ�һ�����ݡ�
    slist_previous ���ָ��λ�õ�ǰһ��λ�õĵ�������
    slist_push_front �ڵ�������Ŀ�ͷ���һ�����ݡ�
    slist_remove ɾ��������������ָ��������ȵ����ݡ�
    slist_remove_if ɾ������������������ָ����������ݡ�
    slist_resize �����µ����ݸ�����
    slist_resize_elem �����µ����ݸ���������µ����ݸ���������ǰ���ݸ�����ʹ��ָ��������䡣
    slist_reverse �����������е���������
    slist_size ���ص������������ݵĸ�����
    slist_sort �����������е���������
    slist_sort_if �����������е����ݰ���ָ����������
    slist_splice ��Դ���������е�����ת�Ƶ�Ŀ�ĵ��������е�ָ��λ�á�
    slist_splice_after_pos ��Դ����������ָ��λ�ú�����Ǹ�����ת�Ƶ�Ŀ�ĵ�������ָ��λ�ú��档
    slist_splice_after_range ��Դ����������ָ�������������������е�����ת�Ƶ�Ŀ�ĵ�������ָ��λ�ú��档
    slist_splice_pos ��Դ����������ָ��λ�õ�����ת�Ƶ�Ŀ�굥�������ָ��λ�á�
    slist_splice_range ��Դ����������ָ������������ת�Ƶ�Ŀ�ĵ��������ָ��λ�á�
    slist_swap ��������������������ݡ�
    slist_unique ɾ���������������ڵ��ظ����ݡ�
    slist_unique_if ɾ���������������ڵ�����ָ����������ݡ�
*/

#include <stdio.h>
#include <cstl/cslist.h>
#include <cstl/cfunctional.h>

//�Ƿ�������
static void is_odd(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    slist_t* pslist_l1 = create_slist(int); //�������������������͡�
    slist_t* pslist_l2 = create_slist(int);
    slist_iterator_t it_l; // ����������������͡�

    int* pn_i = NULL;
    int* pn_j = NULL;

    if(pslist_l1 == NULL || pslist_l2 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1); //��ʼ��һ���յĵ�������������
    slist_init(pslist_l2);

    slist_push_front(pslist_l1, 10);//��slist_t��ͷ���һ�����ݡ�
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 30);
    slist_push_front(pslist_l2, 40);
    slist_push_front(pslist_l2, 50);
    slist_push_front(pslist_l2, 60);

    printf("l1 =");
    //slist_begin: ����ָ��slist_t�е�һ�����ݵĵ�������
    //slist_end: ����ָ��slist_tĩβ�ĵ�������
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    //30 20 10
    printf("\n");

    //����һ����������ֵ����ǰ�ĵ�������
    slist_assign(pslist_l1, pslist_l2); //pslist_l1 = 60 50 40

    //ʹ��ָ����������Ϊ��������ֵ��
    slist_assign_range(pslist_l1, iterator_next(slist_begin(pslist_l2)), slist_end(pslist_l2));
    //pslist_l1 = 50 40

    //ʹ��ָ������Ϊ��������ֵ��
    slist_assign_elem(pslist_l1, 5, 4); //pslist_l1 = 4 4 4 4 4

    //ɾ��slist_t�е��������ݡ�
    slist_clear(pslist_l1);
    
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    
    //����slist_t�еĵ�һ�����ݡ�
    pn_i = (int*)slist_front(pslist_l1);
    printf("The first integer of l1 is %d\n", *pn_i);//20

    //����slist_t�Ƿ�Ϊ�ա�
    if(slist_empty(pslist_l1))
    {
        printf("The slist is empty.\n");
    }
    else
    {
        printf("The slist is not empty.\n");
    }
    
    //��������slist_t�Ƿ���ȡ� 
    if(slist_equal(pslist_l1, pslist_l2))
    {
        ;
    }

    //��������slist_t�Ƿ񲻵�
    if(slist_not_equal(pslist_l1, pslist_l2))
    {
        ;
    }

    //���Ե�һ��slist_t�Ƿ���ڵڶ���slist_t
    if(slist_greater(pslist_l1, pslist_l2))
    {
        ;
    }

    // ���Ե�һ��slist_t�Ƿ���ڵ��ڵڶ���slist_t��
    if(slist_greater_equal(pslist_l1, pslist_l2))
    {
        ;
    }

    //���Ե�һ��slist_t�Ƿ�С�ڵڶ���slist_t��
    if(slist_less(pslist_l1, pslist_l2))
    {
        ;
    }

    //���Ե�һ��slist_t�Ƿ�С�ڵ��ڵڶ���slist_t
    if(slist_less_equal(pslist_l1, pslist_l2))
    {
        ;
    }

    slist_push_front(pslist_l1, 30);
    slist_push_front(pslist_l1, 40);
    slist_push_front(pslist_l1, 50); //50 40 30 20 10

    //ɾ��slist_t��ָ��λ�õ����ݡ�
    slist_erase(pslist_l1, slist_begin(pslist_l1));//40 30 20 10

    //ɾ��slist_t��ָ��������������ݡ�
    slist_erase_range(pslist_l1, iterator_next(slist_begin(pslist_l1)),
        slist_end(pslist_l1)); //40

    slist_clear(pslist_l1);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 30);
    slist_push_front(pslist_l1, 40);
    slist_push_front(pslist_l1, 50);

    //slist_erase_after ɾ������������ָ��λ�ú�����Ǹ����ݡ�
    slist_erase_after(pslist_l1, slist_begin(pslist_l1));//50 30 20 10

    //slist_erase_after_range ɾ������������ָ�������������������������ݡ�
    slist_erase_after_range(pslist_l1, slist_begin(pslist_l1),
        slist_end(pslist_l1));//50
    
    slist_clear(pslist_l1);
    slist_clear(pslist_l2);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 30);// 30 20 10
    slist_push_front(pslist_l2, 40);
    slist_push_front(pslist_l2, 50);
    slist_push_front(pslist_l2, 60);//60 50 40

    //slist_insert ���������ָ��λ�ò���һ�����ݡ� 30 100 20 10
    slist_insert(pslist_l1, iterator_next(slist_begin(pslist_l1)), 100);

    //slist_insert_n ���������ָ��λ�ò��������ݡ�30 100 200 200 20 10
    slist_insert_n(pslist_l1, iterator_advance(slist_begin(pslist_l1), 2), 2, 200);

    //slist_insert_range ���������ָ��λ�ò������������е����ݡ�30 60 50 40 100 200 200 20 10
    slist_insert_range(pslist_l1, iterator_next(slist_begin(pslist_l1)), slist_begin(pslist_l2), slist_end(pslist_l2));

    //slist_insert_after ���������ָ��λ�õ���һ��λ�ò���һ�����ݡ�30 -100 60 50 40 100 200 200 20 10
    slist_insert_after(pslist_l1, slist_begin(pslist_l1), -100);
 
    //slist_insert_after_n ���������ָ��λ�õ���һ��λ�ò��������ݡ�30 -200 -200 -100 60 50 40 100 200 200 20 10
    slist_insert_after_n(pslist_l1, slist_begin(pslist_l1), 2, -200); 

    //slist_insert_after_range ���������ָ��λ�õ���һ��λ�ò������������е����ݡ�
    //30 60 50 40 -200 -200 -100 60 50 40 100 200 200 20 10
    slist_insert_after_range(pslist_l1, slist_begin(pslist_l1), slist_begin(pslist_l2), slist_end(pslist_l2));



    //����slist_t�б������ݵĿ��ܵ���������� ����һ����ϵͳ��صĳ�����
    printf("Maximum possible length of the slist is %u\n",
        slist_max_size(pslist_l1));

    //slist_pop_front ɾ����һ�����ݡ�
    slist_pop_front(pslist_l1);

    it_l = slist_end(pslist_l1);
    
    // ����ǰһ�����ݵĵ�������
    it_l = slist_previous(pslist_l1, it_l);
    printf("The last element of list is %d\n",
        *(int*)iterator_get_pointer(it_l)); //20
    
    //slist_push_front �ڵ�������Ŀ�ͷ���һ�����ݡ�
    slist_push_front(pslist_l1, 2);//2 

    slist_clear(pslist_l1);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 21);
    slist_push_front(pslist_l1, 25);
    slist_push_front(pslist_l1, 30);// 30 25 21 10
    //ɾ��slist_t����ָ��������ȵ����ݡ�
    slist_remove(pslist_l1, 21); // 30 25 10

    //ɾ�����������з����ض���������ݡ�
    slist_remove_if(pslist_l1, is_odd); //2 // 30  10

    //����slist_t�����ݵĸ��������µ����ݸ����ȵ�ǰ�����࣬�ദ������ʹ��Ĭ������0���
   
    slist_resize(pslist_l1, 4); // 30 10 0 0
    slist_resize(pslist_l1, 2); // 30 10

    //����slist_t�����ݵĸ��������µ����ݸ����ȵ�ǰ�����࣬�ദ������ʹ��ָ��������䡣
    slist_resize_elem(pslist_l1, 4, 60); // 30 10 60 60

    //��slist_t�е���������
    slist_reverse(pslist_l1);// 60 60 10 30

    //����slist_t�����ݵĸ���
    printf("slist length is %d\n", slist_size(pslist_l1)); // 4
    

    //ʹ��Ĭ�ϵĹ���������������ݵ�˳���С����
    slist_sort(pslist_l1); // 10 30 60 60

    //ʹ��ָ������bfun_op����
    slist_sort_if(pslist_l1, fun_greater_int); // 60 60 30 10

    slist_clear(pslist_l1);
    slist_clear(pslist_l2);
    
    slist_push_front(pslist_l1, 6);
    slist_push_front(pslist_l1, 3); // 3 6
    slist_push_front(pslist_l2, 4);
    slist_push_front(pslist_l2, 2); // 2 4
    
    //slist_merge �ϲ���������ĵ�������
    slist_merge(pslist_l2, pslist_l1);
    // pslist_l2 = 2 3 4 6
    // pslist_l = []
    
    slist_push_front(pslist_l1, 1);
    slist_push_front(pslist_l1, 5); // 5 1
    slist_sort_if(pslist_l2, fun_greater_int);
    
    //slist_merge_if �����ض�����ϲ���������ĵ�������
    slist_merge_if(pslist_l2, pslist_l1, fun_greater_int);
    for(it_l = slist_begin(pslist_l2);
        !iterator_equal(it_l, slist_end(pslist_l2));
    it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");
    // pslist_l2 = 6 5 4 3 2 1
    // pslist_l = []
  
   
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 11);
    //slist_splice �����������е�����ת�Ƶ���һ�����������С�
    slist_splice(pslist_l2, iterator_next(slist_begin(pslist_l2)), pslist_l1);
    // pslist_l2 = 6 11 5 4 3 2 1
    // pslist_l = []
    slist_push_front(pslist_l1, 12);
    slist_push_front(pslist_l1, 13); // 13 12
    
    //slist_splice_pos ���ƶ�λ�õ�����ת�Ƶ���һ�����������С�
    slist_splice_pos(pslist_l2, iterator_next(slist_begin(pslist_l2)),
        pslist_l1, slist_begin(pslist_l1));
    // pslist_l2 = 6 13 10 11 5 4 3 2 1
    // pslist_l = 12

    slist_push_front(pslist_l1, 14); 
    slist_push_front(pslist_l1, 15); // 15 14 12

    //slist_splice_range ���ƶ����������ת�Ƶ���һ�����������С�
    slist_splice_range(pslist_l2, iterator_next(slist_begin(pslist_l2)),
        pslist_l1, slist_begin(pslist_l1), slist_end(pslist_l1));
    // pslist_l2 =  6 15 14 12 13 10 11 5 4 3 2 1
    // pslist_l = 0

    //slist_splice_after_pos ��Դ����������ָ��λ�ú�����Ǹ�����ת�Ƶ�Ŀ�ĵ�������ָ��λ�ú��档
    slist_push_front(pslist_l1, 16); 
    slist_push_front(pslist_l1, 17); 
    slist_push_front(pslist_l1, 18);  
    slist_push_front(pslist_l1, 19); //19 18 17 16
    slist_splice_after_pos(pslist_l2, slist_begin(pslist_l2),
        pslist_l1, slist_begin(pslist_l1));
    // pslist_l2 = 6 18 15 14 12 13 10 11 5 4 3 2 1  //Ϊʲô����19
    // pslist_l = 19 17 16
    for(it_l = slist_begin(pslist_l2);
        !iterator_equal(it_l, slist_end(pslist_l2));
    it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");    
    //slist_splice_after_range ��Դ����������ָ�������������������е�����ת�Ƶ�Ŀ�ĵ�������ָ��λ�ú��档
    slist_splice_after_range(pslist_l2, slist_begin(pslist_l2),
        pslist_l1, slist_begin(pslist_l1),
        iterator_advance(slist_begin(pslist_l1), 2));
    // pslist_l2 = 6 17 16 18 15 14 12 13 10 11 5 4 3 2 1
    // pslist_l = 19
    
    for(it_l = slist_begin(pslist_l2);
    !iterator_equal(it_l, slist_end(pslist_l2));
    it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");
    
    // ��������slist_t�е�����
    slist_swap(pslist_l1, pslist_l2);

    slist_clear(pslist_l1);
    slist_clear(pslist_l2);
    slist_push_front(pslist_l1, -10);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, -10);
    
    //slist_unique ɾ�����ڵ��ظ����ݡ�
    slist_assign(pslist_l2, pslist_l1); //-10 20 10 -10
        
    //slist_unique_if ɾ�����ڵ������������ݡ�
    slist_unique(pslist_l1); // -10 -10

    //����slist_t
    slist_destroy(pslist_l1);
    slist_destroy(pslist_l2);

    
    slist_t* pslist_l0 = create_slist(int);
    pslist_l1 = create_slist(int);
    pslist_l2 = create_slist(int);
    slist_t* pslist_l3 = create_slist(int);
    slist_t* pslist_l4 = create_slist(int);

    if(pslist_l0 == NULL || pslist_l1 == NULL || pslist_l2 == NULL || pslist_l3 == NULL || pslist_l4 == NULL)
    {
        return -1;
    }

    //slist_init ��ʼ��һ���յĵ�������������
    slist_init(pslist_l0);

    //slist_init_n ʹ��ָ��������Ĭ�����ݳ�ʼ����������
    slist_init_n(pslist_l1, 3);//0 0 0

    //slist_init_elem ʹ��ָ�����ݳ�ʼ����������
    slist_init_elem(pslist_l2, 5, 2);// 2 2 2 2 2

    //slist_init_copy ʹ����һ�����������ʼ����ǰ�ĵ�������
    slist_init_copy(pslist_l3, pslist_l2); //2 // 2 2 2 2 2 

    //slist_init_copy_range ʹ��ָ�������������ʼ����������
    slist_init_copy_range(pslist_l4, iterator_advance(slist_begin(pslist_l3), 2), slist_end(pslist_l3));//2 // 2 2 2

    //����slist_t
    slist_destroy(pslist_l0);
    slist_destroy(pslist_l1);
    slist_destroy(pslist_l2);
    slist_destroy(pslist_l3);
    slist_destroy(pslist_l4);

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
