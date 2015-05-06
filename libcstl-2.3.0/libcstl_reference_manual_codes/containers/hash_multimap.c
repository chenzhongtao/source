/*
file: hash_multimap.c

���ڹ�ϣ�ṹ�Ķ���ӳ��hash_multimap_t

���ڹ�ϣ�ṹ�Ķ���ӳ��hash_multimap_t�ǹ��������������б����������pair_t���͡�pair_t�ĵ�һ������
�Ǽ���hash_multimap_t�е����ݾ��Ǹ������������ģ�������ֱ�ӻ��߼���޸ļ���pair_t�ĵڶ���������ֵ��ֵ
���û��ֱ�ӵĹ�ϵ��ֵ����hash_multimap_t�е���������û��Ӱ�죬����ֱ�ӻ��߼���޸�ֵ��
hash_multimap_t�ĵ�������˫��������������µ����ݲ����ƻ�ԭ�еĵ�������ɾ��һ�����ݵ�ʱ��ֻ��ָ
������ݵĵ�����ʧЧ����hash_multimap_t�в��ң��������ɾ�����ݶ��Ǹ�Ч�ġ�
hash_multimap_t�е����ݱ����ڹ�ϣ���У��������ݺ�ָ���Ĺ�ϣ�������������ڹ�ϣ���е�λ�ã�ͬʱ��
�ݼ�����ָ�������Զ�����Ĭ�Ϲ����������ص�С�ڲ������û�Ҳ�����ڳ�ʼ��ʱָ���Զ���Ĺ���
hash_multimap_t�����ݵĲ���ɾ�����ҵȲ����������ƽ��������Ĺ����������Ч�ʸ��ߣ����Դﵽ�ӽ���������
�������ݲ�����ȫ����ġ�

Typedefs
    hash_multimap_t ���ڹ�ϣ�ṹ�Ķ���ӳ���������͡�
    hash_multimap_iterator_t ���ڹ�ϣ�ṹ�Ķ���ӳ���������������͡�
Operation Functions
    create_hash_multimap �������ڹ�ϣ�ṹ�Ķ���ӳ���������͡�
    hash_multimap_assign Ϊ���ڹ�ϣ�ṹ�Ķ���ӳ���������������͸�ֵ��
    hash_multimap_begin ����ָ����ڹ�ϣ�ṹ�Ķ���ӳ���е�һ�����ݵĵ�������
    hash_multimap_bucket_count ���ػ��ڹ�ϣ�ṹ�Ķ���ӳ��ʹ�õĹ�ϣ��Ĵ洢��Ԫ������
    hash_multimap_clear ɾ�����ڹ�ϣ�ṹ�Ķ���ӳ���а���ָ���������ݡ�
    hash_multimap_count ͳ�ƻ��ڹ�ϣ�ṹ�Ķ���ӳ���а���ָ���������ݵĸ�����
    hash_multimap_destroy ���ٻ��ڹ�ϣ�ṹ�Ķ���ӳ��������
    hash_multimap_empty ���Ի��ڹ�ϣ�ṹ�Ķ���ӳ�������Ƿ�Ϊ�ա�
    hash_multimap_end ����ָ����ڹ�ϣ�ṹ�Ķ���ӳ������ĩβλ�õĵ�������
    hash_multimap_equal �����������ڹ�ϣ�ṹ�Ķ���ӳ�������Ƿ���ȡ�
    hash_multimap_equal_range ���ػ��ڹ�ϣ�ṹ�Ķ���ӳ�������а���ָ�������������䡣
    hash_multimap_erase ɾ�����ڹ�ϣ�ṹ�Ķ���ӳ���а���ָ���������ݡ�
    hash_multimap_erase_pos ɾ�����ڹ�ϣ�ṹ�Ķ���ӳ��������ָ��λ�õ����ݡ�
    hash_multimap_erase_range ɾ�����ڹ�ϣ�ṹ�Ķ���ӳ�������е�ָ���������䡣
    hash_multimap_find ���һ��ڹ�ϣ�ṹ�Ķ���ӳ�������а���ָ���������ݡ�
    hash_multimap_greater ���Ե�һ�����ڹ�ϣ�ṹ�Ķ���ӳ���Ƿ���ڵڶ������ڹ�ϣ�ṹ�Ķ���ӳ�䡣
    hash_multimap_greater_equal ���Ե�һ�����ڹ�ϣ�ṹ�Ķ���ӳ���Ƿ���ڵ��ڵڶ���������
    hash_multimap_hash ���ػ��ڹ�ϣ�ṹ�Ķ���ӳ��ʹ�õĹ�ϣ������
    hash_multimap_init ��ʼ��һ���յĻ��ڹ�ϣ�ṹ�Ķ���ӳ�䡣
    hash_multimap_init_copy ʹ�ÿ����ķ�ʽ��ʼ��һ�����ڹ�ϣ�ṹ�Ķ���ӳ�䡣
    hash_multimap_init_copy_range ʹ��ָ�������������ʼ��һ�����ڹ�ϣ�ṹ�Ķ���ӳ�䡣
    hash_multimap_init_copy_range_ex ʹ��ָ�����������䣬��ϣ�������ȽϹ���ʹ洢��Ԫ����ʼ��������
    hash_multimap_init_ex ʹ��ָ���Ĺ�ϣ�������ȽϹ���ʹ洢��Ԫ����ʼ��һ���յ�������
    hash_multimap_insert ����ڹ�ϣ�ṹ�Ķ���ӳ�������в������ݡ�
    hash_multimap_insert_range ����ڹ�ϣ�ṹ�Ķ���ӳ�������в����������䡣
    hash_multimap_key_comp ���ػ��ڹ�ϣ�ṹ�Ķ���ӳ������ʹ�õļ��ȽϹ���
    hash_multimap_less ���Ե�һ�����ڹ�ϣ�ṹ�Ķ���ӳ���Ƿ�С�ڵڶ���������
    hash_multimap_less_equal ���Ե�һ�����ڹ�ϣ�ṹ�Ķ���ӳ���Ƿ�С�ڵ��ڵڶ���������
    hash_multimap_max_size ���ػ��ڹ�ϣ�ṹ�Ķ���ӳ���������ܹ�������������������ֵ��
    hash_multimap_not_equal �����������ڹ�ϣ�ṹ�Ķ���ӳ�������Ƿ񲻵ȡ�
    hash_multimap_resize �������û��ڹ�ϣ�ṹ�Ķ���ӳ������ʹ�õĹ�ϣ��Ĵ洢��Ԫ������
    hash_multimap_size ���ػ��ڹ�ϣ�ṹ�Ķ���ӳ�������б�������ݵĸ�����
    hash_multimap_swap �����������ڹ�ϣ�ṹ�Ķ���ӳ�������е����ݡ�
    hash_multimap_value_comp ���ػ��ڹ�ϣ�ṹ�Ķ���ӳ������ʹ�õ����ݱȽϹ���

*/


#include <stdio.h>
#include <cstl/chash_map.h>
#include <cstl/cfunctional.h>

static void _hash_function(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input + 20;
}

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int); //����hash_multimap_t����
    hash_multimap_t* phmm_hmm2 = create_hash_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int); //����pair_t����
    hash_multimap_iterator_t it_hmm;  //hash_multimap_t���͵ĵ���������

    if(phmm_hmm1 == NULL || phmm_hmm2 == NULL)
    {
        return -1;
    }
    
    pair_init(ppair_p);//��ʼ��pair_t����
    hash_multimap_init(phmm_hmm1); //��ʼ��hash_multimap_t����
    hash_multimap_init(phmm_hmm2);

    
    //����ڹ�ϣ�ṹ�Ķ���ӳ���в���һ�����ݡ�
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);

    pair_make(ppair_p, 4, 40);
    hash_multimap_insert(phmm_hmm2, ppair_p);
    pair_make(ppair_p, 5, 50);
    hash_multimap_insert(phmm_hmm2, ppair_p);
    pair_make(ppair_p, 6, 60);
    hash_multimap_insert(phmm_hmm2, ppair_p);

    //hash_multimap_begin: ����ָ��hash_multimap_t��һ�����ݵĵ�����
    //hash_multimap_end: ����ָ��hash_multimap_tĩβλ�õĵ�����
    printf("m1 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm1);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hmm)),
            *(int*)pair_second(iterator_get_pointer(it_hmm)));
    }
    // <1, 10> <2, 20> <3, 30>
    printf("\n");
    
    //ʹ��hash_multimap_t����Ϊ��ǰ��hash_multimap_t��ֵ
    hash_multimap_assign(phmm_hmm1, phmm_hmm2);
    printf("m1 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm1);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hmm)),
            *(int*)pair_second(iterator_get_pointer(it_hmm)));
    }
    // <4, 40> <5, 50> <6, 60>
    printf("\n");


    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    phmm_hmm1 = create_hash_multimap(int, int);
    phmm_hmm2 = create_hash_multimap(int, int);
    hash_multimap_init(phmm_hmm1);
    hash_multimap_init_ex(phmm_hmm2, 100, NULL, NULL);

    // ����hash_multimap_t�й�ϣ��Ĵ洢��Ԫ�ĸ�����
    printf("The default bucket count of hm1 is %d.\n",
    hash_multimap_bucket_count(phmm_hmm1)); //53
    printf("The custom bucket count of hm2 is %d.\n",
    hash_multimap_bucket_count(phmm_hmm2)); //193

    hash_multimap_destroy(phmm_hmm2);
    phmm_hmm2 = create_hash_multimap(int, int);
    hash_multimap_init(phmm_hmm2);

    //ɾ��hash_multimap_t�е��������ݡ�
    hash_multimap_clear(phmm_hmm1);
    
    pair_make(ppair_p, 1, 1);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 1);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 1, 4); //���Զ����Ǹ���
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 1);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    
    //hash_multimap_count ���������а���ָ�����ݵĸ���
    /* Keys must be unique in hash_multimap, so duplicates are ignored */
    printf("The number of elements in m1 with a sort key of 1 is: %d.\n",
        hash_multimap_count(phmm_hmm1, 1)); // 2
    printf("The number of elements in m1 with a sort key of 2 is: %d.\n",
        hash_multimap_count(phmm_hmm1, 2)); // 2
    printf("The number of elements in m1 with a sort key of 3 is: %d.\n",
        hash_multimap_count(phmm_hmm1, 3)); // 0

    printf("m1 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm1);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hmm)),
            *(int*)pair_second(iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    // ����hash_multimap_t�����Ƿ�Ϊ��
    if(hash_multimap_empty(phmm_hmm1))
    {
        printf("The hash_multimap m1 is empty.\n");
    }

    //��������hash_multimap_t�Ƿ����
    if(hash_multimap_equal(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimaps m1 and m2 are equal.\n");
    }

    //���Ե�һ��hash_multimap_t�����Ƿ���ڵڶ���hash_multimap_t����
    if(hash_multimap_greater(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimap m1 is greater than the hash_multimap m2.\n");
    }

    //���Ե�һ��hash_multimap_t�Ƿ���ڵ��ڵڶ���hash_multimap_t
    if(hash_multimap_greater_equal(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimap m1 is greater than or equal to the hash_multimap m2.\n");
    }

    //���Ե�һ��hash_multimap_t�Ƿ�С�ڵڶ���hash_multimap_t
    if(hash_multimap_less(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimap m1 is less than the hash_multimap m2.\n");
    }

    //���Ե�һ��hash_multimap_t�Ƿ�С�ڵ��ڵڶ���hash_multimap_t
    if(hash_multimap_less_equal(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimap m1 is less than or equal to the hash_multimap m2.\n");
    }
    
    //��������hash_multimap_t�Ƿ񲻵�
    if(hash_multimap_not_equal(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimaps m1 and m2 are not equal.\n");
    }

    // ����hash_multimap_tʹ�õĹ�ϣ����
    if(hash_multimap_hash(phmm_hmm2) == _hash_function)
    {
        printf("The hash function of hash_multimap hs2 is _hash_function.\n");
    }
    
    range_t r_r;
    hash_multimap_clear(phmm_hmm1);
    
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);

    //����hash_multimap_t�а���ָ�����ݵ���������
    r_r = hash_multimap_equal_range(phmm_hmm1, 2); //��������������ڵ���20��

    printf("The lower bound of the element with a key of 2 in the hash_multimap m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_begin)));//30
    printf("The upper bound of the element with a key of 2 in the hash_multimap m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_end))); //20

    r_r = hash_multimap_equal_range(phmm_hmm1, 4);
    /* If no match is found for the key, both elements of the range return end() */
    if(iterator_equal(r_r.it_begin, hash_multimap_end(phmm_hmm1)) &&
        iterator_equal(r_r.it_end, hash_multimap_end(phmm_hmm1)))
    {
        printf("The hash_multimap m1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of hash_multimap m1 with a key >= 40 is %d.\n",
            *(int*)pair_first(iterator_get_pointer(r_r.it_begin)));
    }

    hash_multimap_clear(phmm_hmm1);
    
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 5, 50);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    
    //hash_multimap_erase ɾ�����ڹ�ϣ�ṹ�Ķ���ӳ����������ָ��������ȵ�����
    int t_count = hash_multimap_erase(phmm_hmm1, 4); // <1, 10> <2, 20> <3, 30>  <5, 50> t_count = 1

    //hash_multimap_erase_pos ɾ�����ڹ�ϣ�ṹ�Ķ���ӳ��������ָ��λ�õ�����
    hash_multimap_erase_pos(phmm_hmm1, iterator_next(hash_multimap_begin(phmm_hmm1))); //<1, 10> <3, 30>  <5, 50>

    //hash_multimap_erase_range ɾ�����ڹ�ϣ�ṹ�Ķ���ӳ��������ָ���������������
    hash_multimap_erase_range(phmm_hmm1, iterator_next(hash_multimap_begin(phmm_hmm1)),
        iterator_prev(hash_multimap_end(phmm_hmm1))); // <1, 10> <5, 50>

    //��hash_multimap_t�в���ָ��������
    it_hmm = hash_multimap_find(phmm_hmm1, 1);
    printf("The element of hash_multimap m1 with a key of 1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_hmm)));
    
    /* If no match is found for the key, end() is returned */
    it_hmm = hash_multimap_find(phmm_hmm1, 4);
    if(iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1)))
    {
        printf("The hash_multimap m1 doesn't have an element with a key of 4.\n");
    }
    
    hash_multimap_clear(phmm_hmm1);
    hash_multimap_clear(phmm_hmm2);

    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_multimap_insert(phmm_hmm1, ppair_p);

    //��hash_multimap_t�в�������,�ɹ��󷵻�ָ������ݵĵ����������hash_multimap_t�а����˸�������ô����ʧ�ܣ�����hash_multimap_end()
    pair_make(ppair_p, 1, 10);
    it_hmm = hash_multimap_insert(phmm_hmm1, ppair_p);
    if(!iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1)))
    {
        printf("The element 10 was inserted in m1 successfully.\n");
    }
    else
    {
        printf("The number 1 already exists in m1.\n");
    }


    pair_make(ppair_p, 10, 100);
    hash_multimap_insert(phmm_hmm2, ppair_p);
    //����ָ������������
    hash_multimap_insert_range(phmm_hmm2, iterator_next(hash_multimap_begin(phmm_hmm1)),
        iterator_prev(hash_multimap_end(phmm_hmm1)));
    printf("After the insertions, the key values of m2 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm2);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm2));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hmm)),
            *(int*)pair_second(iterator_get_pointer(it_hmm)));
    }
    //<2, 20> <3, 30> <4, 40> <10, 100>
    printf("\n");

    hash_multimap_clear(phmm_hmm1);
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    

    //����hash_multimap_t���ܹ���������ݸ�����������ֵ
    printf("The maximum possible length of the hash_multimap is %u.\n",
        hash_multimap_max_size(phmm_hmm1));

    //����hash_multimap_t�б�������ݵ�����
    printf("The hash_multimap length is %d.\n", hash_multimap_size(phmm_hmm1));

    //��������hash_multimap_t�е�����
    hash_multimap_swap(phmm_hmm1, phmm_hmm2);

    binary_function_t bfun_vc = NULL;
    binary_function_t bfun_kc = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;
    hash_multimap_iterator_t it_hmm1;  //hash_multimap_t���͵ĵ���������
    hash_multimap_iterator_t it_hmm2;  //hash_multimap_t���͵ĵ���������

    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    phmm_hmm1 = create_hash_multimap(int, int);
    phmm_hmm2 = create_hash_multimap(int, int);

    hash_multimap_init_ex(phmm_hmm1, 0, NULL, fun_less_int);
    
    //����hash_multimap_t�ļ��ȽϹ���
    bfun_kc = hash_multimap_key_comp(phmm_hmm1);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m1.\n");
    }

    hash_multimap_destroy(phmm_hmm1);

    hash_multimap_init_ex(phmm_hmm2, 0, NULL, fun_greater_int);

    bfun_kc = hash_multimap_key_comp(phmm_hmm2);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m2.\n");
    }
    
    hash_multimap_destroy(phmm_hmm2);
    
    phmm_hmm1 = create_hash_multimap(int, int);
    hash_multimap_init_ex(phmm_hmm1, 0, NULL, fun_less_int);

    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 5);
    hash_multimap_insert(phmm_hmm1, ppair_p);

    it_hmm1 = hash_multimap_find(phmm_hmm1, 1);
    it_hmm2 = hash_multimap_find(phmm_hmm1, 2);
    //����hash_multimap_t�����ݵıȽϹ���,���������������ݱ���ıȽϹ�������Ǽ�����ֵ
    bfun_vc = hash_multimap_value_comp(phmm_hmm1);

    (*bfun_vc)(iterator_get_pointer(it_hmm1), iterator_get_pointer(it_hmm2), &b_result);
    if(b_result)
    {
        printf("The element (1, 10) precedes the element (2, 5).\n");
    }
    else
    {
        printf("The element (1, 10) does not precedes the element (2, 5).\n");
    }

    (*bfun_vc)(iterator_get_pointer(it_hmm2), iterator_get_pointer(it_hmm1), &b_result);
    if(b_result)
    {
        printf("The element (2, 5) precedes the element (1, 10).\n");
    }
    else
    {
        printf("The element (2, 5) does not precedes the element (1, 10).\n");
    }
    hash_multimap_destroy(phmm_hmm1);

    hash_multimap_t* phmm_hmm0 = create_hash_multimap(int, int);
    phmm_hmm1 = create_hash_multimap(int, int);
    phmm_hmm2 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm3 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm4 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm5 = create_hash_multimap(int, int);

    if(phmm_hmm0 == NULL || phmm_hmm1 == NULL || phmm_hmm2 == NULL || phmm_hmm3 == NULL || phmm_hmm4 == NULL || phmm_hmm5 == NULL)
    {
        return -1;
    }
    
    //hash_multimap_init ��ʼ��һ���յĻ��ڹ�ϣ�ṹ�Ķ���ӳ��������
    hash_multimap_init(phmm_hmm0);

    //hash_multimap_init_ex ʹ��ָ������������ʼ��һ���յĻ��ڹ�ϣ�ṹ�Ķ���ӳ������
    hash_multimap_init_ex(phmm_hmm1, 0, _hash_function, fun_less_int);
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_multimap_insert(phmm_hmm1, ppair_p);

    //hash_multimap_init_ex ʹ��ָ���Ĺ�ϣ�������ȽϹ��򣬴洢��Ԫ������ʼ��һ���յĻ��ڹ�ϣ�ṹ�Ķ���ӳ��
    hash_multimap_init_ex(phmm_hmm2, 0, _hash_function, fun_greater_int);
    pair_make(ppair_p, 1, 10);
    hash_multimap_insert(phmm_hmm2, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_multimap_insert(phmm_hmm2, ppair_p);

    //hash_multimap_init_copy ʹ�ÿ����ķ�ʽ��ʼ��һ�����ڹ�ϣ�ṹ�Ķ���ӳ���������������ݶ�������Դ������
    hash_multimap_init_copy(phmm_hmm3, phmm_hmm1); 

    //hash_multimap_init_copy_range ʹ��ָ�������������ʼ��һ�����ڹ�ϣ�ṹ�Ķ���ӳ��������
    hash_multimap_init_copy_range(phmm_hmm4, hash_multimap_begin(phmm_hmm1), iterator_advance(hash_multimap_begin(phmm_hmm1), 2)); 

    //hash_multimap_init_copy_range_ex ʹ��ָ�����������䣬��ϣ�������ȽϹ��򣬴洢��Ԫ��������ʼ��������
    hash_multimap_init_copy_range_ex(phmm_hmm5, hash_multimap_begin(phmm_hmm3),
        hash_multimap_end(phmm_hmm3), 100, _hash_function, fun_less_int);

    hash_multimap_destroy(phmm_hmm0);
    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    hash_multimap_destroy(phmm_hmm3);
    hash_multimap_destroy(phmm_hmm4);
    hash_multimap_destroy(phmm_hmm5);
    pair_destroy(ppair_p);

    return 0;
}

