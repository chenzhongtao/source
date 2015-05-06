/*
file: hash_multiset.c

���ڹ�ϣ�ṹ�Ķ��ؼ���hash_multiset_t

���ڹ�ϣ�ṹ�Ķ��ؼ�������hash_multiset_t�ǹ�����������ʹ��ָ���Ĺ�ϣ�����������ݵĴ洢λ�ã�����
�ݱ��������λ���ϡ�hash_multiset_t�е�����λ���Ǹ������ݱ������ģ�������hash_multiset_t��������������
���ģ�����������Ҳ������ĳ�������ԣ�����Ҳ����ͨ��ֱ�ӻ��߼�ӵķ�ʽ�޸������е����ݡ�hash_multiset_t��
��˫��������������µ����ݲ����ƻ�ԭ�е����ݵĵ�������ɾ��һ�����ݵ�ʱ��ֻ��ָ�����ݱ���ĵ�����ʧЧ��
���ǵ���ϣ�����¼�������λ�õ�ʱ�����еĵ�������ʧЧ��

Typedefs
    hash_multiset_t ���ڹ�ϣ�ṹ�Ķ��ؼ����������͡�
    hash_multiset_iterator_t ���ڹ�ϣ�ṹ�Ķ��ؼ����������������͡�

Operation Functions
    create_hash_multiset �������ڹ�ϣ�ṹ�Ķ��ؼ����������͡�
    hash_multiset_assign Ϊ���ڹ�ϣ�ṹ�Ķ��ؼ���������ֵ��
    hash_multiset_begin ���ػ��ڹ�ϣ�ṹ�Ķ��ؼ�����ָ���һ�����ݵĵ�������
    hash_multiset_bucket_count ���ػ��ڹ�ϣ�ṹ�Ķ��ؼ���ʹ�õĹ�ϣ��Ĵ洢��Ԫ������
    hash_multiset_clear ɾ�����ڹ�ϣ�ṹ�Ķ��ؼ��������е����ݡ�
    hash_multiset_count ͳ�ƻ��ڹ�ϣ�ṹ�Ķ��ؼ��ϰ�����ָ�����ݵĸ�����
    hash_multiset_destroy ���ٻ��ڹ�ϣ�ṹ�Ķ��ؼ����������͡�
    hash_multiset_empty ���Ի��ڹ�ϣ�ṹ�Ķ��ؼ����Ƿ�Ϊ�ա�
    hash_multiset_end ���ػ��ڹ�ϣ�ṹ�Ķ��ؼ��ϵ�ĩβλ�õĵ�������
    hash_multiset_equal �����������ڹ�ϣ�ṹ�Ķ��ؼ����Ƿ���ȡ�
    hash_multiset_equal_range ���ػ��ڹ�ϣ�ṹ�Ķ��ؼ����а���ָ�����ݵ��������䡣
    hash_multiset_erase ɾ�����ڹ�ϣ�ṹ�Ķ��ؼ����а�����ָ�����ݡ�
    hash_multiset_erase_pos ɾ�����ڹ�ϣ�ṹ�Ķ��ؼ�����ָ��λ�õ����ݡ�
    hash_multiset_erase_range ɾ�����ڹ�ϣ�ṹ�Ķ��ؼ�����ָ��������������ݡ�
    hash_multiset_find �ڻ��ڹ�ϣ�ṹ�Ķ��ؼ����в���ָ�������ݡ�
    hash_multiset_greater ���Ե�һ�����ڹ�ϣ�ṹ�Ķ��ؼ����Ƿ���ڵڶ������ڹ�ϣ�ṹ�Ķ��ؼ��ϡ�
    hash_multiset_greater_equal ���Ե�һ�����ڹ�ϣ�ṹ�Ķ��ؼ����Ƿ���ڵ��ڵڶ�����
    hash_multiset_hash ���ػ��ڹ�ϣ�ṹ�Ķ��ؼ���ʹ�õĹ�ϣ������
    hash_multiset_init ��ʼ��һ���յĻ��ڹ�ϣ�ṹ�Ķ��ؼ��ϡ�
    hash_multiset_init_copy ͨ�������ķ�ʽ��ʼ�����ڹ�ϣ�ṹ�Ķ��ؼ��ϡ�
    hash_multiset_init_copy_range ʹ��ָ�������������ʼ�����ڹ�ϣ�ṹ�Ķ��ؼ��ϡ�
    hash_multiset_init_copy_range_ex ʹ��ָ�����������䣬��ϣ�������������ʹ洢��Ԫ�������г�ʼ����
    hash_multiset_init_ex ʹ��ָ���Ĺ�ϣ�������������ʹ洢��Ԫ�������г�ʼ����
    hash_multiset_insert ����ڹ�ϣ�ṹ�Ķ��ؼ����в������ݡ�
    hash_multiset_insert_range ����ڹ�ϣ�ṹ�Ķ��ؼ����в���ָ�����������䡣
    hash_multiset_key_comp ���ػ��ڹ�ϣ�ṹ�Ķ��ؼ���ʹ�õļ��ȽϹ���
    hash_multiset_less ���Ե�һ�����ڹ�ϣ�ṹ�Ķ��ؼ����Ƿ�С�ڵڶ������ڹ�ϣ�ṹ�Ķ��ؼ��ϡ�
    hash_multiset_less_equal ���Ե�һ�����ڹ�ϣ�ṹ�Ķ��ؼ����Ƿ�С�ڵ��ڵڶ�����
    hash_multiset_max_size ���ػ��ڹ�ϣ�ṹ�Ķ��ؼ����ܹ��������ݵ����������
    hash_multiset_not_equal �����������ڹ�ϣ�ṹ�Ķ��ؼ����Ƿ񲻵ȡ�
    hash_multiset_resize �������û��ڹ�ϣ�ṹ�Ķ��ؼ���ʹ�õĹ�ϣ��Ĵ洢��Ԫ������
    hash_multiset_size ���ػ��ڹ�ϣ�ṹ�Ķ��ؼ��������ݵ�������
    hash_multiset_swap �����������ڹ�ϣ�ṹ�Ķ��ؼ��ϵ����ݡ�
    hash_multiset_value_comp ���ػ��ڹ�ϣ�ṹ�Ķ��ؼ���ʹ�õ�ֵ�ȽϹ���
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
    hash_multiset_t* phmset_hms1 = create_hash_multiset(int); //����hash_multiset_t����
    hash_multiset_t* phmset_hms2 = create_hash_multiset(int);
    hash_multiset_iterator_t it_hms;  //hash_multiset_t���͵ĵ���������

    if(phmset_hms1 == NULL || phmset_hms2 == NULL)
    {
        return -1;
    }

    hash_multiset_init(phmset_hms1); //��ʼ��hash_multiset_t����
    hash_multiset_init(phmset_hms2);

    hash_multiset_insert(phmset_hms1, 10);//����ڹ�ϣ�ṹ�Ķ��ؼ����в���һ�����ݡ�
    hash_multiset_insert(phmset_hms1, 20);
    hash_multiset_insert(phmset_hms1, 30);
    
    hash_multiset_insert(phmset_hms2, 40);
    hash_multiset_insert(phmset_hms2, 50);
    hash_multiset_insert(phmset_hms2, 60);

    //hash_multiset_begin: ����ָ��hash_multiset_t��һ�����ݵĵ�����
    //hash_multiset_end: ����ָ��hash_multiset_tĩβλ�õĵ�����
    printf("s1 =");
    for(it_hms = hash_multiset_begin(phmset_hms1); !iterator_equal(it_hms, hash_multiset_end(phmset_hms1)); it_hms = iterator_next(it_hms))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hms));
    }
    // 10 20 30
    printf("\n");
    
    //ʹ��hash_multiset_t����Ϊ��ǰ��hash_multiset_t��ֵ
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

    // ����hash_multiset_t�еĹ�ϣ��Ĵ洢��Ԫ����
    printf("The default bucket count of hs1 is %d.\n",
        hash_multiset_bucket_count(phmset_hms1)); //53
    printf("The custom bucket count of hs2 is %d.\n",
        hash_multiset_bucket_count(phmset_hms2)); // 193
    
    // ��������hash_multiset_t�й�ϣ��洢��Ԫ������
    hash_multiset_resize(phmset_hms1, 100);
    
    printf("The bucket count of hash_multiset hs1 is now: %d.\n",
        hash_multiset_bucket_count(phmset_hms1));  // 193

    // hs1 resize֮�󣬺����hs1 �� hs2�ıȽϺͽ�������
    hash_multiset_destroy(phmset_hms1);
    hash_multiset_destroy(phmset_hms2);
    phmset_hms1 = create_hash_multiset(int);
    phmset_hms2 = create_hash_multiset(int);
    hash_multiset_init(phmset_hms1);
    hash_multiset_init(phmset_hms2);

    //ɾ��hash_multiset_t�е��������ݡ�
    hash_multiset_clear(phmset_hms1);
    
    hash_multiset_insert(phmset_hms1, 1);
    hash_multiset_insert(phmset_hms1, 1);
    
    //hash_multiset_count ���������а���ָ�����ݵĸ���
    printf("The number of elements in s1 with a sort key of 1 is: %d.\n",
        hash_multiset_count(phmset_hms1, 1)); //1// 2
    printf("The number of elements in s1 with a sort key of 2 is: %d.\n",
        hash_multiset_count(phmset_hms1, 2)); //1// 0

    // ����hash_multiset_t�����Ƿ�Ϊ��
    if(hash_multiset_empty(phmset_hms1))
    {
        printf("The hash_multiset s1 is empty.\n");
    }

    //��������hash_multiset_t�Ƿ����
    if(hash_multiset_equal(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multisets s1 and s2 are equal.\n");
    }

    //���Ե�һ��hash_multiset_t�����Ƿ���ڵڶ���hash_multiset_t����
    if(hash_multiset_greater(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multiset s1 is greater than the hash_multiset s2.\n");
    }

    //���Ե�һ��hash_multiset_t�Ƿ���ڵ��ڵڶ���hash_multiset_t
    if(hash_multiset_greater_equal(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multiset s1 is greater than or equal to the hash_multiset s2.\n");
    }

    //���Ե�һ��hash_multiset_t�Ƿ�С�ڵڶ���hash_multiset_t
    if(hash_multiset_less(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multiset s1 is less than the hash_multiset s2.\n");
    }

    //���Ե�һ��hash_multiset_t�Ƿ�С�ڵ��ڵڶ���hash_multiset_t
    if(hash_multiset_less_equal(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multiset s1 is less than or equal to the hash_multiset s2.\n");
    }
    
    //��������hash_multiset_t�Ƿ񲻵�
    if(hash_multiset_not_equal(phmset_hms1, phmset_hms2))
    {
        printf("The hash_multisets s1 and s2 are not equal.\n");
    }

    // ����hash_multiset_tʹ�õĹ�ϣ����
    if(hash_multiset_hash(phmset_hms2) == _hash_function)
    {
        printf("The hash function of hash_multiset hs2 is _hash_function.\n");
    }
   
    range_t r_r1;
    hash_multiset_clear(phmset_hms1);
    
    hash_multiset_insert(phmset_hms1, 10);
    hash_multiset_insert(phmset_hms1, 20);
    hash_multiset_insert(phmset_hms1, 30);

    //����hash_multiset_t�а���ָ�����ݵ���������
    r_r1 = hash_multiset_equal_range(phmset_hms1, 20); //��������������ڵ���20��

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
    
    //hash_multiset_erase ɾ�����ڹ�ϣ�ṹ�Ķ��ؼ�����������ָ��������ȵ�����
    int t_count = hash_multiset_erase(phmset_hms1, 40); // 10 20 30 50  t_count = 1

    //hash_multiset_erase_pos ɾ�����ڹ�ϣ�ṹ�Ķ��ؼ���������ָ��λ�õ�����
    hash_multiset_erase_pos(phmset_hms1, iterator_next(hash_multiset_begin(phmset_hms1))); //10 30 50

    //hash_multiset_erase_range ɾ�����ڹ�ϣ�ṹ�Ķ��ؼ���������ָ���������������
    hash_multiset_erase_range(phmset_hms1, iterator_next(hash_multiset_begin(phmset_hms1)),
        iterator_prev(hash_multiset_end(phmset_hms1))); // 10 50

    //��hash_multiset_t�в���ָ��������
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

    //��hash_multiset_t�в�������,�ɹ��󷵻�ָ������ݵĵ����������hash_multiset_t�а����˸�������ô����ʧ�ܣ�����hash_multiset_end()
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
    

    //����hash_multiset_t���ܹ���������ݸ�����������ֵ
    printf("The maximum possible length of the hash_multiset is %u.\n",
        hash_multiset_max_size(phmset_hms1));

    //����hash_multiset_t�б�������ݵ�����
    printf("The hash_multiset length is %d.\n", hash_multiset_size(phmset_hms1));

    //��������hash_multiset_t�е�����
    hash_multiset_swap(phmset_hms1, phmset_hms2);

    binary_function_t bfun_vl = NULL;
    binary_function_t bfun_kl = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;

    hash_multiset_clear(phmset_hms1);
    hash_multiset_destroy(phmset_hms2);
    phmset_hms2 = create_hash_multiset(int);
    
    //����hash_multiset_t�����ݵıȽϹ���,����hash_multiset_t�����ݱ�����Ǽ���������������ķ���ֵ��hash_multiset_key_comp()��ͬ
    bfun_vl = hash_multiset_value_comp(phmset_hms1);

    //����hash_multiset_t�ļ��ȽϹ���,����hash_multiset_t�����ݱ�����Ǽ���������������ķ���ֵ��hash_multiset_value_comp()��ͬ
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


    //hash_multiset_init ��ʼ��һ���յĻ��ڹ�ϣ�ṹ�Ķ��ؼ�������
    hash_multiset_init(phmset_hms0);

    //hash_multiset_init_ex ʹ��ָ���Ĺ�ϣ�����ͱȽϹ����ʼ��һ���յĻ��ڹ�ϣ�ṹ�Ķ��ؼ���������
    hash_multiset_init_ex(phmset_hms1, 10, _hash_function, fun_less_int);
    hash_multiset_insert(phmset_hms1, 10);
    hash_multiset_insert(phmset_hms1, 20);
    hash_multiset_insert(phmset_hms1, 30);
    hash_multiset_insert(phmset_hms1, 40);//40 10 20 30

    //hash_multiset_init_ex ʹ��ָ���Ĺ�ϣ�����ͱȽϹ����ʼ��һ���յĻ��ڹ�ϣ�ṹ�Ķ��ؼ���������
    hash_multiset_init_ex(phmset_hms2, 100, _hash_function, fun_greater_int);
    hash_multiset_insert(phmset_hms2, 10);
    hash_multiset_insert(phmset_hms2, 20);//10 20

    //hash_multiset_init_copy ʹ��һ�����ڹ�ϣ�ṹ�Ķ��ؼ���������ʼ����ǰ������
    hash_multiset_init_copy(phmset_hms3, phmset_hms1); //40 10 20 30

    //hash_multiset_init_copy_range ʹ��ָ�������������ʼ�����ڹ�ϣ�ṹ�Ķ��ؼ���������
    hash_multiset_init_copy_range(phmset_hms4, hash_multiset_begin(phmset_hms1), iterator_advance(hash_multiset_begin(phmset_hms1), 2)); //10 40

    //hash_multiset_init_copy_range_ex ʹ��ָ�����������䣬��ϣ�����ͱȽϹ����ʼ�����ڹ�ϣ�ṹ�Ķ��ؼ���������
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

