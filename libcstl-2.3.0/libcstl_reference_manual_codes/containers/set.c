/*
file: set.c

����set_t
��������set_t�ǹ���������set_t�е����ݰ��ռ���ָ���Ĺ����Զ������ұ�֤����Ψһ�ģ�set_t�еļ���
�����ݱ���set_t�е����ݲ�����ֱ�ӻ���ͨ���������޸ģ���Ϊ�������ƻ�set_t�����ݵ������ԣ�Ҫ���޸�һ��
����ֻ����ɾ����Ȼ������µ����ݡ�set_t֧��˫��������������������ǲ����ƻ�ԭ�еĵ�������ɾ��������ֻ��
ָ��ɾ�������ݵĵ�����ʧЧ��set_t�������ݵĲ��ң������ɾ�����Ǹ�Ч�ġ�set_t�е����ݸ���ָ���Ĺ����Զ�
����Ĭ�ϵ����������ʹ�����ݵ�С�ڲ��������û������ڳ�ʼ��ʱָ���Զ�����������

Typedefs
    set_t �����������͡�
    set_iterator_t ������������������

Operation Functions
    create_set ����������������
    set_assign Ϊ����������ֵ��
    set_begin ����ָ�򼯺��е�һ�����ݵĵ�������
    set_clear ɾ�����������е��������ݡ�
    set_count ���ؼ��������а���ָ�����ݵĸ�����
    set_destroy ���ټ���������
    set_empty ���Լ��������Ƿ�Ϊ�ա�
    set_end ����ָ�򼯺�����ĩβλ�õĵ�������
    set_equal �����������������Ƿ���ȡ�
    set_equal_range ����һ�����������а���ָ�����ݵ��������䡣
    set_erase ɾ��������������ָ��������ȵ����ݡ�
    set_erase_pos ɾ������������ָ��λ�õ����ݡ�
    set_erase_range ɾ������������ָ��������������ݡ�
    set_find �ڼ��������в���ָ�������ݡ�
    set_greater ���Ե�һ�������Ƿ���ڵڶ������ϡ�
    set_greater_equal ���Ե�һ�������Ƿ���ڵ��ڵڶ������ϡ�
    set_init ��ʼ��һ���յļ���������
    set_init_copy ʹ��һ��������������������ʼ����ǰ����������
    set_init_copy_range ʹ��ָ�������������ʼ������������
    set_init_copy_range_ex ʹ��ָ�������������ָ������������ʼ������������
    set_init_ex ʹ��ָ������������ʼ��һ���յļ���������
    set_insert �򼯺��в���һ�����ݡ�
    set_insert_hint �򼯺��в���һ������ͬʱ����λ����ʾ��
    set_insert_range �򼯺��в���ָ��������������ݡ�
    set_key_comp ���ؼ��������ļ��ȽϹ���
    set_less ���Ե�һ�����������Ƿ�С�ڵڶ�������������
    set_less_equal ���Ե�һ�����������Ƿ�С�ڵ��ڵڶ�������������
    set_lower_bound ���ؼ�������ָ��������ȵĵ�һ�����ݵĵ�������
    set_max_size ���ؼ������ܹ���������ݸ�����������ֵ��
    set_not_equal �������������Ƿ񲻵ȡ�
    set_size ���ؼ����б�������ݵ�������
    set_swap �����������ϵ����ݡ�
    set_upper_bound ���ؼ����д���ָ�����ݵĵ�һ�����ݵĵ�������
    set_value_comp ��ü����е����ݱȽϹ���

*/


#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    set_t* pset_s1 = create_set(int); //����set_t����
    set_t* pset_s2 = create_set(int);
    set_iterator_t it_s;  //set_t���͵ĵ���������

    if(pset_s1 == NULL || pset_s2 == NULL)
    {
        return -1;
    }

    set_init(pset_s1); //��ʼ��set_t����
    set_init(pset_s2);

    set_insert(pset_s1, 10);//�򼯺��в���һ�����ݡ�
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    
    set_insert(pset_s2, 40);
    set_insert(pset_s2, 50);
    set_insert(pset_s2, 60);

    //set_begin: ����ָ��set_t��һ�����ݵĵ�����
    //set_end: ����ָ��set_tĩβλ�õĵ�����
    printf("s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    // 10 20 30
    printf("\n");
    
    //ʹ��set_t����Ϊ��ǰ��set_t��ֵ
    set_assign(pset_s1, pset_s2);
    printf("s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    // 40 50 60
    printf("\n");

    //ɾ��set_t�е��������ݡ�
    set_clear(pset_s1);
    
    set_insert(pset_s1, 1);
    set_insert(pset_s1, 1);
    
    //set_count ���������а���ָ�����ݵĸ���
    printf("The number of elements in s1 with a sort key of 1 is: %d.\n",
        set_count(pset_s1, 1)); //1// 1
    printf("The number of elements in s1 with a sort key of 2 is: %d.\n",
        set_count(pset_s1, 2)); //1// 0

    // ����set_t�����Ƿ�Ϊ��
    if(set_empty(pset_s1))
    {
        printf("The set s1 is empty.\n");
    }

    //��������set_t�Ƿ����
    if(set_equal(pset_s1, pset_s2))
    {
        printf("The sets s1 and s2 are equal.\n");
    }

    //���Ե�һ��set_t�����Ƿ���ڵڶ���set_t����
    if(set_greater(pset_s1, pset_s2))
    {
        printf("The set s1 is greater than the set s2.\n");
    }

    //���Ե�һ��set_t�Ƿ���ڵ��ڵڶ���set_t
    if(set_greater_equal(pset_s1, pset_s2))
    {
        printf("The set s1 is greater than or equal to the set s2.\n");
    }

    //���Ե�һ��set_t�Ƿ�С�ڵڶ���set_t
    if(set_less(pset_s1, pset_s2))
    {
        printf("The set s1 is less than the set s2.\n");
    }

    //���Ե�һ��set_t�Ƿ�С�ڵ��ڵڶ���set_t
    if(set_less_equal(pset_s1, pset_s2))
    {
        printf("The set s1 is less than or equal to the set s2.\n");
    }
    
    //��������set_t�Ƿ񲻵�
    if(set_not_equal(pset_s1, pset_s2))
    {
        printf("The sets s1 and s2 are not equal.\n");
    }
    
    range_t r_r1;
    set_clear(pset_s1);
    
    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);

    //����set_t�а���ָ�����ݵ���������
    r_r1 = set_equal_range(pset_s1, 20); //��������������ڵ���20��

    printf("The upper bound of the element with a key of 20 in the set s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_end)); //30
    printf("The lower bound of the element with a key of 20 in the set s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_begin)); //20

    //����set_t�д���ָ�����ݵĵ�һ�����ݵĵ�����
    it_s = set_upper_bound(pset_s1, 20);
    printf("A direct call of upper_bound(20), gives %d,\n", *(int*)iterator_get_pointer(it_s));//30
    printf("matching the 2nd element of the range returned by equal_range(20).\n");

    r_r1 = set_equal_range(pset_s1, 40);
    /* If no match is found for the key. both elements of the range return end() */
    if(iterator_equal(r_r1.it_begin, set_end(pset_s1)) && iterator_equal(r_r1.it_end, set_end(pset_s1)))
    {
        printf("The set s1 doesn't have and element with a key less than 40.\n");
    }
    else
    {
        printf("The element of set s1 with a key >= 40 is: %d.\n", *(int*)iterator_get_pointer(r_r1.it_begin));
    }

    set_clear(pset_s1);
    
    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    set_insert(pset_s1, 40);
    set_insert(pset_s1, 50);
    
    //set_erase ɾ��������������ָ��������ȵ�����
    int t_count = set_erase(pset_s1, 40); // 10 20 30 50  t_count = 1

    //set_erase_pos ɾ������������ָ��λ�õ�����
    set_erase_pos(pset_s1, iterator_next(set_begin(pset_s1))); //10 30 50

    //set_erase_range ɾ������������ָ���������������
    set_erase_range(pset_s1, iterator_next(set_begin(pset_s1)),
        iterator_prev(set_end(pset_s1))); // 10 50

    //��set_t�в���ָ��������
    it_s = set_find(pset_s1, 10);
    printf("The element of set s1 with a key of 20 is: %d.\n",
        *(int*)iterator_get_pointer(it_s));
    
    it_s = set_find(pset_s1, 40);
    /* If no match is found for the key, end() is returned */
    if(iterator_equal(it_s, set_end(pset_s1)))
    {
        printf("The set s1 doesn't have an element with a key of 40.\n");
    }
    
    set_clear(pset_s1);
    set_clear(pset_s2);

    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    set_insert(pset_s1, 40);

    //��set_t�в�������,�ɹ��󷵻�ָ������ݵĵ����������set_t�а����˸�������ô����ʧ�ܣ�����set_end()
    it_s = set_insert(pset_s1, 10);
    if(iterator_equal(it_s, set_end(pset_s1)))
    {
        printf("The element 10 already exists in s1.\n");
    }
    else
    {
        printf("The element 10 was inserted in s1 successfully.\n");
    }

    // ��set_t�в���һ��ָ�������ݣ�ͬʱ����һ�������ݱ���������ʾλ�õ�������������λ��
    //����set_t���������Ͱ�������ݷ�����ʾλ���гɹ��󷵻�ָ������ݵĵ������������ʾλ�ò���ȷ�������
    //ʾλ�ã�(�ǲ���Ϊ�˼���)�����ݲ���ɹ��󷵻����ݵ�ʵ��λ�õ����������set_t�а����˸�������ô����ʧ�ܣ�����set_end()
    set_insert_hint(pset_s1, iterator_prev(set_end(pset_s1)), 50);  //10 20 30 40 50
    printf("After the insertions, s1 =");
    for(it_s = set_begin(pset_s1); !iterator_equal(it_s, set_end(pset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    set_insert(pset_s2, 100);
    set_insert_range(pset_s2, iterator_next(set_begin(pset_s1)), iterator_prev(set_end(pset_s1)));
    printf("s2 =");
    for(it_s = set_begin(pset_s2); !iterator_equal(it_s, set_end(pset_s2)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    //20 30 40 100
    printf("\n");

    set_clear(pset_s1);
    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    
     //���set_t�е��ڻ��ߴ���ָ�����ݵĵ�һ�����ݵĵ�����
    it_s = set_lower_bound(pset_s1, 20);
    printf("The element of set s1 with a key of 20 is: %d.\n", //20
        *(int*)iterator_get_pointer(it_s));

    //����set_t�д���ָ�����ݵĵ�һ�����ݵĵ�����
    it_s = set_upper_bound(pset_s1, 20);
    printf("A direct call of upper_bound(20), gives %d,\n", *(int*)iterator_get_pointer(it_s));//30
    printf("matching the 2nd element of the range returned by equal_range(20).\n");
    
    it_s = set_lower_bound(pset_s1, 40);
    /* If no match is found for the key, end() is is returend */
    if(iterator_equal(it_s, set_end(pset_s1)))
    {
        printf("The set s1 doesn't have an element with a key of 40.\n");
    }
    else
    {
        printf("The element of set s1 with a key of 40 is: %d.\n",
            *(int*)iterator_get_pointer(it_s));
    }

    //����set_t���ܹ���������ݸ�����������ֵ
    printf("The maximum possible length of the set is %u.\n",
        set_max_size(pset_s1));

    //����set_t�б�������ݵ�����
    printf("The set length is %d.\n", set_size(pset_s1));

    //��������set_t�е�����
    set_swap(pset_s1, pset_s2);

    binary_function_t bfun_vl = NULL;
    binary_function_t bfun_kl = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;

    set_clear(pset_s1);
    set_destroy(pset_s2);
    pset_s2 = create_set(int);
    
    //����set_t�����ݵıȽϹ���,����set_t�����ݱ�����Ǽ���������������ķ���ֵ��set_key_comp()��ͬ
    bfun_vl = set_value_comp(pset_s1);

    //����set_t�ļ��ȽϹ���,����set_t�����ݱ�����Ǽ���������������ķ���ֵ��set_value_comp()��ͬ
    bfun_kl = set_key_comp(pset_s1);
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
    
    set_init_ex(pset_s2, fun_greater_int);

    bfun_vl = set_value_comp(pset_s2);
    bfun_kl = set_key_comp(pset_s1);
    (*bfun_vl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_vl)(2, 3) returns value of true, where bfun_vl is the function of s2.\n");
    }
    else
    {
        printf("(*bfun_vl)(2, 3) returns value of false, where bfun_vl is the function of s2.\n");
    }

    
    set_destroy(pset_s1);
    set_destroy(pset_s2);

    set_t* pset_s0 = create_set(int);
    pset_s1 = create_set(int);
    pset_s2 = create_set(int);
    set_t* pset_s3 = create_set(int);
    set_t* pset_s4 = create_set(int);
    set_t* pset_s5 = create_set(int);

    if(pset_s0 == NULL || pset_s1 == NULL || pset_s2 == NULL || pset_s3 == NULL || pset_s4 == NULL || pset_s5 == NULL)
    {
        return -1;
    }
    
    //set_init ��ʼ��һ���յļ�������
    set_init(pset_s0);

    //set_init_ex ʹ��ָ������������ʼ��һ���յļ�������
    set_init_ex(pset_s1, fun_less_int);
    set_insert(pset_s1, 10);
    set_insert(pset_s1, 20);
    set_insert(pset_s1, 30);
    set_insert(pset_s1, 40); // 10 20 30 40

    //set_init_ex ʹ��ָ������������ʼ��һ���յļ�������
    set_init_ex(pset_s2, fun_greater_int);
    set_insert(pset_s2, 10);
    set_insert(pset_s2, 20); //20 10

    //set_init_copy ʹ��һ��������������������ʼ����ǰ����������
    set_init_copy(pset_s3, pset_s1); //10 20 30 40 

    //set_init_copy_range ʹ��ָ�������������ʼ������������
    set_init_copy_range(pset_s4, set_begin(pset_s1), iterator_advance(set_begin(pset_s1), 2)); //10 20

    //set_init_copy_range_ex ʹ��ָ�������������ָ������������ʼ������������
    set_init_copy_range_ex(pset_s5, set_begin(pset_s3), iterator_next(set_begin(pset_s3)), fun_less_int);//10 20

    set_destroy(pset_s0);
    set_destroy(pset_s1);
    set_destroy(pset_s2);
    set_destroy(pset_s3);
    set_destroy(pset_s4);
    set_destroy(pset_s5);

    return 0;
}

