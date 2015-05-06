/*
file: multiset.c

���ؼ���multiset_t

���ؼ�������multiset_t�ǹ���������multiset_t�е������ǰ��ռ���ָ���Ĺ����Զ���������������ͬ��
�����ڣ�multiset_t�еļ��������ݱ���multiset_t�е����ݲ�����ֱ�ӻ���ͨ���������޸ģ���Ϊ�������ƻ�
multiset_t�����ݵ������ԣ�Ҫ���޸�һ������ֻ����ɾ����Ȼ������µ����ݡ�multiset_t֧��˫���������������
�����ǲ����ƻ�ԭ�еĵ�������ɾ��������ֻ��ָ��ɾ�������ݵĵ�����ʧЧ��multiset_t�������ݵĲ��ң������
ɾ�����Ǹ�Ч�ġ�multiset_t�е����ݸ���ָ���Ĺ����Զ�����Ĭ�ϵ����������ʹ�����ݵ�С�ڲ��������û�����
�ڳ�ʼ��ʱָ���Զ�����������

Typedefs
    multiset_t ���ؼ����������͡�
    multiset_iterator_t ���ؼ����������������͡�
Operation Functions
    create_multiset �������ؼ����������͡�
multiset_assign Ϊ���ؼ���������ֵ��
multiset_begin ����ָ����ؼ��������е�һ�����ݵĵ�������
multiset_clear ɾ�����ؼ����е��������ݡ�
multiset_count ���ض��ؼ��������а���ָ�����ݵĸ�����
multiset_destroy ���ٶ��ؼ���������
multiset_empty ���Զ��ؼ��������Ƿ�Ϊ�ա�
multiset_end ����ָ����ؼ�������ĩβ�ĵ�������
multiset_equal �����������ؼ��������Ƿ���ȡ�
multiset_equal_range ��ö��ؼ��������а���ָ�����ݵ��������䡣
multiset_erase ɾ��ָ�����ݡ�
multiset_erase_pos ɾ��ָ��λ�õ����ݡ�
multiset_erase_range ɾ��ָ��������������ݡ�
multiset_find �ڶ��ؼ��������в���ָ�������ݡ�
multiset_greater ���Ե�һ�����ؼ��������Ƿ���ڵڶ������ؼ���������
multiset_greater_equal ���Ե�һ�����ؼ��������Ƿ���ڵ��ڵڶ������ؼ���������
multiset_init ��ʼ��һ���յĶ��ؼ���������
multiset_init_copy ʹ��һ���Ѿ����ڵĶ��ؼ�����������ʼ����ǰ�Ķ��ؼ���������
multiset_init_copy_range ʹ��ָ�������е����ݳ�ʼ�����ؼ���������
multiset_init_copy_range_ex ʹ��ָ�������������ָ������������ʼ�����ؼ���������
multiset_init_ex ʹ��ָ������������ʼ��һ���յĶ��ؼ���������
multiset_insert ����ؼ��������в���һ��ָ�������ݡ�
multiset_insert_hint ����ؼ��������в���һ��ָ�������ݣ�������λ����ʾ��
multiset_insert_range ����ؼ��������в���һ��ָ�����������䡣
multiset_key_comp ���ض��ؼ�������ʹ�õļ��ȽϹ���
multiset_less ���Ե�һ�����ؼ��������Ƿ�С�ڵڶ������ؼ���������
multiset_less_equal ���Ե�һ�����ؼ��������Ƿ�С�ڵ��ڵڶ������ؼ���������
multiset_lower_bound ���ض��ؼ��������е���ָ�����ݵĵ�һ�����ݵĵ�������
multiset_max_size ���ض��ؼ��������ܹ����������������������ֵ��
multiset_not_equal �����������ؼ��������Ƿ񲻵ȡ�
multiset_size ���ض��ؼ������������ݵ�������
multiset_swap �����������ؼ������������ݡ�
multiset_upper_bound ���ض��ؼ��������д���ָ�����ݵĵ�һ�����ݵĵ�������
multiset_value_comp ���ض��ؼ�������ʹ�õ����ݱȽϹ���

*/


#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int); //����multiset_t����
    multiset_t* pmset_s2 = create_multiset(int);
    multiset_iterator_t it_s;  //multiset_t���͵ĵ���������

    if(pmset_s1 == NULL || pmset_s2 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1); //��ʼ��multiset_t����
    multiset_init(pmset_s2);

    multiset_insert(pmset_s1, 10);//����ؼ����в���һ�����ݡ�
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    
    multiset_insert(pmset_s2, 40);
    multiset_insert(pmset_s2, 50);
    multiset_insert(pmset_s2, 60);

    //multiset_begin: ����ָ��multiset_t��һ�����ݵĵ�����
    //multiset_end: ����ָ��multiset_tĩβλ�õĵ�����
    printf("s1 =");
    for(it_s = multiset_begin(pmset_s1); !iterator_equal(it_s, multiset_end(pmset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    // 10 20 30
    printf("\n");
    
    //ʹ��multiset_t����Ϊ��ǰ��multiset_t��ֵ
    multiset_assign(pmset_s1, pmset_s2);
    printf("s1 =");
    for(it_s = multiset_begin(pmset_s1); !iterator_equal(it_s, multiset_end(pmset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    // 40 50 60
    printf("\n");

    //ɾ��multiset_t�е��������ݡ�
    multiset_clear(pmset_s1);
    
    multiset_insert(pmset_s1, 1);
    multiset_insert(pmset_s1, 1);
    
    //multiset_count ���������а���ָ�����ݵĸ���
    printf("The number of elements in s1 with a sort key of 1 is: %d.\n",
        multiset_count(pmset_s1, 1)); //1// 2
    printf("The number of elements in s1 with a sort key of 2 is: %d.\n",
        multiset_count(pmset_s1, 2)); //1// 0

    // ����multiset_t�����Ƿ�Ϊ��
    if(multiset_empty(pmset_s1))
    {
        printf("The multiset s1 is empty.\n");
    }

    //��������multiset_t�Ƿ����
    if(multiset_equal(pmset_s1, pmset_s2))
    {
        printf("The multisets s1 and s2 are equal.\n");
    }

    //���Ե�һ��multiset_t�����Ƿ���ڵڶ���multiset_t����
    if(multiset_greater(pmset_s1, pmset_s2))
    {
        printf("The multiset s1 is greater than the multiset s2.\n");
    }

    //���Ե�һ��multiset_t�Ƿ���ڵ��ڵڶ���multiset_t
    if(multiset_greater_equal(pmset_s1, pmset_s2))
    {
        printf("The multiset s1 is greater than or equal to the multiset s2.\n");
    }

    //���Ե�һ��multiset_t�Ƿ�С�ڵڶ���multiset_t
    if(multiset_less(pmset_s1, pmset_s2))
    {
        printf("The multiset s1 is less than the multiset s2.\n");
    }

    //���Ե�һ��multiset_t�Ƿ�С�ڵ��ڵڶ���multiset_t
    if(multiset_less_equal(pmset_s1, pmset_s2))
    {
        printf("The multiset s1 is less than or equal to the multiset s2.\n");
    }
    
    //��������multiset_t�Ƿ񲻵�
    if(multiset_not_equal(pmset_s1, pmset_s2))
    {
        printf("The multisets s1 and s2 are not equal.\n");
    }
    
    range_t r_r1;
    multiset_clear(pmset_s1);
    
    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);

    //����multiset_t�а���ָ�����ݵ���������
    r_r1 = multiset_equal_range(pmset_s1, 20); //��������������ڵ���20��

    printf("The upper bound of the element with a key of 20 in the multiset s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_end)); //30
    printf("The lower bound of the element with a key of 20 in the multiset s1 is: %d.\n", 
            *(int*)iterator_get_pointer(r_r1.it_begin)); //20

    //����multiset_t�д���ָ�����ݵĵ�һ�����ݵĵ�����
    it_s = multiset_upper_bound(pmset_s1, 20);
    printf("A direct call of upper_bound(20), gives %d,\n", *(int*)iterator_get_pointer(it_s));//30
    printf("matching the 2nd element of the range returned by equal_range(20).\n");

    r_r1 = multiset_equal_range(pmset_s1, 40);
    /* If no match is found for the key. both elements of the range return end() */
    if(iterator_equal(r_r1.it_begin, multiset_end(pmset_s1)) && iterator_equal(r_r1.it_end, multiset_end(pmset_s1)))
    {
        printf("The multiset s1 doesn't have and element with a key less than 40.\n");
    }
    else
    {
        printf("The element of multiset s1 with a key >= 40 is: %d.\n", *(int*)iterator_get_pointer(r_r1.it_begin));
    }

    multiset_clear(pmset_s1);
    
    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    multiset_insert(pmset_s1, 40);
    multiset_insert(pmset_s1, 50);
    
    //multiset_erase ɾ�����ؼ�����������ָ��������ȵ�����
    int t_count = multiset_erase(pmset_s1, 40); // 10 20 30 50  t_count = 1

    //multiset_erase_pos ɾ�����ؼ���������ָ��λ�õ�����
    multiset_erase_pos(pmset_s1, iterator_next(multiset_begin(pmset_s1))); //10 30 50

    //multiset_erase_range ɾ�����ؼ���������ָ���������������
    multiset_erase_range(pmset_s1, iterator_next(multiset_begin(pmset_s1)),
        iterator_prev(multiset_end(pmset_s1))); // 10 50

    //��multiset_t�в���ָ��������
    it_s = multiset_find(pmset_s1, 10);
    printf("The element of multiset s1 with a key of 20 is: %d.\n",
        *(int*)iterator_get_pointer(it_s));
    
    it_s = multiset_find(pmset_s1, 40);
    /* If no match is found for the key, end() is returned */
    if(iterator_equal(it_s, multiset_end(pmset_s1)))
    {
        printf("The multiset s1 doesn't have an element with a key of 40.\n");
    }
    
    multiset_clear(pmset_s1);
    multiset_clear(pmset_s2);

    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    multiset_insert(pmset_s1, 40);

    //��multiset_t�в���һ��ָ�������ݣ��ɹ��󷵻�ָ������ݵĵ��������������ʧ�ܣ�����multiset_end()��
    it_s = multiset_insert(pmset_s1, 10);  // 10 10 20 30 40
    if(iterator_equal(it_s, multiset_end(pmset_s1)))
    {
        printf("Insert value error.\n");
    }

    // ��multiset_t�в���һ��ָ�������ݣ�ͬʱ����һ�������ݱ���������ʾλ�õ�������������λ��
    //����multiset_t���������Ͱ�������ݷ�����ʾλ���гɹ��󷵻�ָ������ݵĵ������������ʾλ�ò���ȷ�������
    //ʾλ�ã�(�ǲ���Ϊ�˼���)�����ݲ���ɹ��󷵻����ݵ�ʵ��λ�õ����������multiset_t�а����˸�������ô����ʧ�ܣ�����multiset_end()
    multiset_insert_hint(pmset_s1, iterator_prev(multiset_end(pmset_s1)), 50);  //10 10 20 30 40 50
    printf("After the insertions, s1 =");
    for(it_s = multiset_begin(pmset_s1); !iterator_equal(it_s, multiset_end(pmset_s1)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    printf("\n");

    multiset_insert(pmset_s2, 100);
    multiset_insert_range(pmset_s2, iterator_next(multiset_begin(pmset_s1)), iterator_prev(multiset_end(pmset_s1)));
    printf("s2 =");
    for(it_s = multiset_begin(pmset_s2); !iterator_equal(it_s, multiset_end(pmset_s2)); it_s = iterator_next(it_s))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_s));
    }
    //10 20 30 40 100
    printf("\n");

    multiset_clear(pmset_s1);
    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    
     //���multiset_t�е��ڻ��ߴ���ָ�����ݵĵ�һ�����ݵĵ�����
    it_s = multiset_lower_bound(pmset_s1, 20);
    printf("The element of multiset s1 with a key of 20 is: %d.\n", //20
        *(int*)iterator_get_pointer(it_s));

    //����multiset_t�д���ָ�����ݵĵ�һ�����ݵĵ�����
    it_s = multiset_upper_bound(pmset_s1, 20);
    printf("A direct call of upper_bound(20), gives %d,\n", *(int*)iterator_get_pointer(it_s));//30
    printf("matching the 2nd element of the range returned by equal_range(20).\n");
    
    it_s = multiset_lower_bound(pmset_s1, 40);
    /* If no match is found for the key, end() is is returend */
    if(iterator_equal(it_s, multiset_end(pmset_s1)))
    {
        printf("The multiset s1 doesn't have an element with a key of 40.\n");
    }
    else
    {
        printf("The element of multiset s1 with a key of 40 is: %d.\n",
            *(int*)iterator_get_pointer(it_s));
    }

    //����multiset_t���ܹ���������ݸ�����������ֵ
    printf("The maximum possible length of the multiset is %u.\n",
        multiset_max_size(pmset_s1));

    //����multiset_t�б�������ݵ�����
    printf("The multiset length is %d.\n", multiset_size(pmset_s1));

    //��������multiset_t�е�����
    multiset_swap(pmset_s1, pmset_s2);

    binary_function_t bfun_vl = NULL;
    binary_function_t bfun_kl = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;

    multiset_clear(pmset_s1);
    multiset_destroy(pmset_s2);
    pmset_s2 = create_multiset(int);
    
    //����multiset_t�����ݵıȽϹ���,����multiset_t�����ݱ�����Ǽ���������������ķ���ֵ��multiset_key_comp()��ͬ
    bfun_vl = multiset_value_comp(pmset_s1);

    //����multiset_t�ļ��ȽϹ���,����multiset_t�����ݱ�����Ǽ���������������ķ���ֵ��multiset_value_comp()��ͬ
    bfun_kl = multiset_key_comp(pmset_s1);
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
    
    multiset_init_ex(pmset_s2, fun_greater_int);

    bfun_vl = multiset_value_comp(pmset_s2);
    bfun_kl = multiset_key_comp(pmset_s1);
    (*bfun_vl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_vl)(2, 3) returns value of true, where bfun_vl is the function of s2.\n");
    }
    else
    {
        printf("(*bfun_vl)(2, 3) returns value of false, where bfun_vl is the function of s2.\n");
    }

    
    multiset_destroy(pmset_s1);
    multiset_destroy(pmset_s2);

    multiset_t* pmset_s0 = create_multiset(int);
    pmset_s1 = create_multiset(int);
    pmset_s2 = create_multiset(int);
    multiset_t* pmset_s3 = create_multiset(int);
    multiset_t* pmset_s4 = create_multiset(int);
    multiset_t* pmset_s5 = create_multiset(int);

    if(pmset_s0 == NULL || pmset_s1 == NULL || pmset_s2 == NULL || pmset_s3 == NULL || pmset_s4 == NULL || pmset_s5 == NULL)
    {
        return -1;
    }
    
    //multiset_init ��ʼ��һ���յĶ��ؼ�������
    multiset_init(pmset_s0);

    //multiset_init_ex ʹ��ָ������������ʼ��һ���յĶ��ؼ�������
    multiset_init_ex(pmset_s1, fun_less_int);
    multiset_insert(pmset_s1, 10);
    multiset_insert(pmset_s1, 20);
    multiset_insert(pmset_s1, 30);
    multiset_insert(pmset_s1, 40); // 10 20 30 40

    //multiset_init_ex ʹ��ָ������������ʼ��һ���յĶ��ؼ�������
    multiset_init_ex(pmset_s2, fun_greater_int);
    multiset_insert(pmset_s2, 10);
    multiset_insert(pmset_s2, 20); //20 10

    //multiset_init_copy ʹ��һ�����ؼ�����������������ʼ����ǰ���ؼ���������
    multiset_init_copy(pmset_s3, pmset_s1); //10 20 30 40 

    //multiset_init_copy_range ʹ��ָ�������������ʼ�����ؼ���������
    multiset_init_copy_range(pmset_s4, multiset_begin(pmset_s1), iterator_advance(multiset_begin(pmset_s1), 2)); //10 20

    //multiset_init_copy_range_ex ʹ��ָ�������������ָ������������ʼ�����ؼ���������
    multiset_init_copy_range_ex(pmset_s5, multiset_begin(pmset_s3), iterator_next(multiset_begin(pmset_s3)), fun_less_int);//10 20

    multiset_destroy(pmset_s0);
    multiset_destroy(pmset_s1);
    multiset_destroy(pmset_s2);
    multiset_destroy(pmset_s3);
    multiset_destroy(pmset_s4);
    multiset_destroy(pmset_s5);

    return 0;
}

