/*
file: hash_set.c

���ڹ�ϣ�ṹ�ļ���hash_set_t

���ڹ�ϣ�ṹ�ļ�������hash_set_t�ǹ�����������ʹ��ָ���Ĺ�ϣ�����������ݵĴ洢λ�ã������ݱ�����
���λ���ϡ�hash_set_t�е�����λ���Ǹ������ݱ������ģ����ұ�֤������hash_set_t�����е�Ψһ�ԣ���������
��������Ҳ������ĳ�������ԣ�����Ҳ����ͨ��ֱ�ӻ��߼�ӵķ�ʽ�޸������е����ݡ�hash_set_t�ṩ˫���������
�����µ����ݲ����ƻ�ԭ�е����ݵĵ�������ɾ��һ�����ݵ�ʱ��ֻ��ָ�����ݱ���ĵ�����ʧЧ�����ǵ���ϣ����
�¼�������λ�õ�ʱ�����еĵ�������ʧЧ��

Typedefs
    hash_set_t ���ڹ�ϣ�ṹ�ļ����������͡�
    hash_set_iterator_t ���ڹ�ϣ�ṹ�ļ����������������͡�

Operation Functions
    create_hash_set �������ڹ�ϣ�ṹ�ļ�����������
    hash_set_assign Ϊ���ڹ�ϣ�ṹ�ļ���������ֵ��
    hash_set_begin ����ָ�������е�һ�����ݵĵ�������
    hash_set_bucket_count ���ع�ϣ��洢��Ԫ��������
    hash_set_clear ɾ�������е��������ݡ�
    hash_set_count ����������ָ�����ݵ�������
    hash_set_destroy ���ٻ��ڹ�ϣ�ṹ�ļ���������
    hash_set_empty ���Ի��ڹ�ϣ�ṹ�ļ��������Ƿ�Ϊ�ա�
    hash_set_end ����ָ����ڹ�ϣ�ṹ�ļ�������ĩβ�ĵ�������
    hash_set_equal �����������ڹ�ϣ�ṹ�ļ��������Ƿ���ȡ�
    hash_set_equal_range ���������а���ָ�����ݵ��������䡣
    hash_set_erase ɾ�������е�ָ�����ݡ�
    hash_set_erase_pos ɾ��������ָ��λ�õ����ݡ�
    hash_set_erase_range ɾ��������ָ��������������ݡ�
    hash_set_find �ڻ��ڹ�ϣ�ṹ�ļ��������в���ָ�������ݡ�
    hash_set_greater ���Ե�һ�����ڹ�ϣ�ṹ�ļ��������Ƿ���ڵڶ������ڹ�ϣ�ṹ�ļ���������
    hash_set_greater_equal ���Ե�һ�����ڹ�ϣ�ṹ�ļ��������Ƿ���ڵ��ڵڶ������ڹ�ϣ�ṹ�ļ���������
    hash_set_hash ���ػ��ڹ�ϣ�ṹ�ļ�������ʹ�õĹ�ϣ������
    hash_set_init ��ʼ��һ���յĻ��ڹ�ϣ�ṹ�ļ���������
    hash_set_init_copy ʹ��һ�����ڹ�ϣ�ṹ�ļ���������ʼ����ǰ������
    hash_set_init_copy_range ʹ��ָ�������������ʼ�����ڹ�ϣ�ṹ�ļ���������
    hash_set_init_copy_range_ex ʹ��ָ�����������䣬��ϣ�����ͱȽϹ����ʼ�����ڹ�ϣ�ṹ�ļ���������
    hash_set_init_ex ʹ��ָ���Ĺ�ϣ�����ͱȽϹ����ʼ��һ���յĻ��ڹ�ϣ�ṹ�ļ���������
    hash_set_insert ����ڹ�ϣ�ṹ�ļ��������в���ָ�������ݡ�
    hash_set_insert_range ����ڹ�ϣ�ṹ�ļ��������в���ָ�����������䡣
    hash_set_key_comp ���ػ��ڹ�ϣ�ṹ�ļ�������ʹ�õļ��ȽϹ���
    hash_set_less ���Ե�һ�����ڹ�ϣ�ṹ�ļ��������Ƿ�С�ڵڶ������ڹ�ϣ�ṹ�ļ���������
    hash_set_less_equal ���Ե�һ�����ڹ�ϣ�ṹ�ļ��������Ƿ�С�ڵ��ڵڶ������ڹ�ϣ�ṹ�ļ���������
    hash_set_max_size ���ػ��ڹ�ϣ�ṹ�ļ���������������������������ֵ��
    hash_set_not_equal �����������ڹ�ϣ�ṹ�ļ��������Ƿ񲻵ȡ�
    hash_set_resize �������ù�ϣ��洢��Ԫ��������
    hash_set_size ���ػ��ڹ�ϣ�ṹ�ļ������������ݵ�������
    hash_set_swap �����������ڹ�ϣ�ṹ�ļ��������е����ݡ�
    hash_set_value_comp ���ػ��ڹ�ϣ�ṹ�ļ���������ʹ�õ����ݱȽϹ���
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
    hash_set_t* phset_hs1 = create_hash_set(int); //����hash_set_t����
    hash_set_t* phset_hs2 = create_hash_set(int);
    hash_set_iterator_t it_hs;  //hash_set_t���͵ĵ���������

    if(phset_hs1 == NULL || phset_hs2 == NULL)
    {
        return -1;
    }

    hash_set_init(phset_hs1); //��ʼ��hash_set_t����
    hash_set_init(phset_hs2);

    hash_set_insert(phset_hs1, 10);//����ڹ�ϣ�ṹ�ļ����в���һ�����ݡ�
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);
    
    hash_set_insert(phset_hs2, 40);
    hash_set_insert(phset_hs2, 50);
    hash_set_insert(phset_hs2, 60);

    //hash_set_begin: ����ָ��hash_set_t��һ�����ݵĵ�����
    //hash_set_end: ����ָ��hash_set_tĩβλ�õĵ�����
    printf("s1 =");
    for(it_hs = hash_set_begin(phset_hs1); !iterator_equal(it_hs, hash_set_end(phset_hs1)); it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    // 10 20 30
    printf("\n");
    
    //ʹ��hash_set_t����Ϊ��ǰ��hash_set_t��ֵ
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

    // ����hash_set_t�еĹ�ϣ��Ĵ洢��Ԫ����
    printf("The default bucket count of hs1 is %d.\n",
        hash_set_bucket_count(phset_hs1)); //53
    printf("The custom bucket count of hs2 is %d.\n",
        hash_set_bucket_count(phset_hs2)); // 193
    
    // ��������hash_set_t�й�ϣ��洢��Ԫ������
    hash_set_resize(phset_hs1, 100);
    
    printf("The bucket count of hash_set hs1 is now: %d.\n",
        hash_set_bucket_count(phset_hs1));  // 193

    // hs1 resize֮�󣬺����hs1 �� hs2�ıȽϺͽ�������
    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);
    phset_hs1 = create_hash_set(int);
    phset_hs2 = create_hash_set(int);
    hash_set_init(phset_hs1);
    hash_set_init(phset_hs2);

    //ɾ��hash_set_t�е��������ݡ�
    hash_set_clear(phset_hs1);
    
    hash_set_insert(phset_hs1, 1);
    hash_set_insert(phset_hs1, 1);
    
    //hash_set_count ���������а���ָ�����ݵĸ���
    printf("The number of elements in s1 with a sort key of 1 is: %d.\n",
        hash_set_count(phset_hs1, 1)); //1// 1
    printf("The number of elements in s1 with a sort key of 2 is: %d.\n",
        hash_set_count(phset_hs1, 2)); //1// 0

    // ����hash_set_t�����Ƿ�Ϊ��
    if(hash_set_empty(phset_hs1))
    {
        printf("The hash_set s1 is empty.\n");
    }

    //��������hash_set_t�Ƿ����
    if(hash_set_equal(phset_hs1, phset_hs2))
    {
        printf("The hash_sets s1 and s2 are equal.\n");
    }

    //���Ե�һ��hash_set_t�����Ƿ���ڵڶ���hash_set_t����
    if(hash_set_greater(phset_hs1, phset_hs2))
    {
        printf("The hash_set s1 is greater than the hash_set s2.\n");
    }

    //���Ե�һ��hash_set_t�Ƿ���ڵ��ڵڶ���hash_set_t
    if(hash_set_greater_equal(phset_hs1, phset_hs2))
    {
        printf("The hash_set s1 is greater than or equal to the hash_set s2.\n");
    }

    //���Ե�һ��hash_set_t�Ƿ�С�ڵڶ���hash_set_t
    if(hash_set_less(phset_hs1, phset_hs2))
    {
        printf("The hash_set s1 is less than the hash_set s2.\n");
    }

    //���Ե�һ��hash_set_t�Ƿ�С�ڵ��ڵڶ���hash_set_t
    if(hash_set_less_equal(phset_hs1, phset_hs2))
    {
        printf("The hash_set s1 is less than or equal to the hash_set s2.\n");
    }
    
    //��������hash_set_t�Ƿ񲻵�
    if(hash_set_not_equal(phset_hs1, phset_hs2))
    {
        printf("The hash_sets s1 and s2 are not equal.\n");
    }

    // ����hash_set_tʹ�õĹ�ϣ����
    if(hash_set_hash(phset_hs2) == _hash_function)
    {
        printf("The hash function of hash_set hs2 is _hash_function.\n");
    }
   
    range_t r_r1;
    hash_set_clear(phset_hs1);
    
    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);

    //����hash_set_t�а���ָ�����ݵ���������
    r_r1 = hash_set_equal_range(phset_hs1, 20); //��������������ڵ���20��

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
    
    //hash_set_erase ɾ�����ڹ�ϣ�ṹ�ļ�����������ָ��������ȵ�����
    int t_count = hash_set_erase(phset_hs1, 40); // 10 20 30 50  t_count = 1

    //hash_set_erase_pos ɾ�����ڹ�ϣ�ṹ�ļ���������ָ��λ�õ�����
    hash_set_erase_pos(phset_hs1, iterator_next(hash_set_begin(phset_hs1))); //10 30 50

    //hash_set_erase_range ɾ�����ڹ�ϣ�ṹ�ļ���������ָ���������������
    hash_set_erase_range(phset_hs1, iterator_next(hash_set_begin(phset_hs1)),
        iterator_prev(hash_set_end(phset_hs1))); // 10 50

    //��hash_set_t�в���ָ��������
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

    //��hash_set_t�в�������,�ɹ��󷵻�ָ������ݵĵ����������hash_set_t�а����˸�������ô����ʧ�ܣ�����hash_set_end()
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
    

    //����hash_set_t���ܹ���������ݸ�����������ֵ
    printf("The maximum possible length of the hash_set is %u.\n",
        hash_set_max_size(phset_hs1));

    //����hash_set_t�б�������ݵ�����
    printf("The hash_set length is %d.\n", hash_set_size(phset_hs1));

    //��������hash_set_t�е�����
    hash_set_swap(phset_hs1, phset_hs2);

    binary_function_t bfun_vl = NULL;
    binary_function_t bfun_kl = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;

    hash_set_clear(phset_hs1);
    hash_set_destroy(phset_hs2);
    phset_hs2 = create_hash_set(int);
    
    //����hash_set_t�����ݵıȽϹ���,����hash_set_t�����ݱ�����Ǽ���������������ķ���ֵ��hash_set_key_comp()��ͬ
    bfun_vl = hash_set_value_comp(phset_hs1);

    //����hash_set_t�ļ��ȽϹ���,����hash_set_t�����ݱ�����Ǽ���������������ķ���ֵ��hash_set_value_comp()��ͬ
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


    //hash_set_init ��ʼ��һ���յĻ��ڹ�ϣ�ṹ�ļ�������
    hash_set_init(phset_hs0);

    //hash_set_init_ex ʹ��ָ���Ĺ�ϣ�����ͱȽϹ����ʼ��һ���յĻ��ڹ�ϣ�ṹ�ļ���������
    hash_set_init_ex(phset_hs1, 10, _hash_function, fun_less_int);
    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);
    hash_set_insert(phset_hs1, 40);//40 10 20 30

    //hash_set_init_ex ʹ��ָ���Ĺ�ϣ�����ͱȽϹ����ʼ��һ���յĻ��ڹ�ϣ�ṹ�ļ���������
    hash_set_init_ex(phset_hs2, 100, _hash_function, fun_greater_int);
    hash_set_insert(phset_hs2, 10);
    hash_set_insert(phset_hs2, 20);//10 20

    //hash_set_init_copy ʹ��һ�����ڹ�ϣ�ṹ�ļ���������ʼ����ǰ������
    hash_set_init_copy(phset_hs3, phset_hs1); //40 10 20 30

    //hash_set_init_copy_range ʹ��ָ�������������ʼ�����ڹ�ϣ�ṹ�ļ���������
    hash_set_init_copy_range(phset_hs4, hash_set_begin(phset_hs1), iterator_advance(hash_set_begin(phset_hs1), 2)); //10 40

    //hash_set_init_copy_range_ex ʹ��ָ�����������䣬��ϣ�����ͱȽϹ����ʼ�����ڹ�ϣ�ṹ�ļ���������
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

