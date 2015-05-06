/*
file: hash_map.c

���ڹ�ϣ�ṹ��ӳ��hash_map_t

���ڹ�ϣ�ṹ��ӳ��hash_map_t�ǹ��������������б����������pair_t���͡�pair_t�ĵ�һ�������Ǽ���
hash_map_t�е����ݾ��Ǹ������������ģ���hash_map_t�м��������ظ���Ҳ������ֱ�ӻ��߼���޸ļ���pair_t
�ĵڶ���������ֵ��ֵ���û��ֱ�ӵĹ�ϵ��hash_map_t�ж���ֵ��Ψһ��û��Ҫ��ֵ����hash_map_t�е�����
����û��Ӱ�죬����ֱ�ӻ��߼���޸�ֵ��
hash_map_t�ĵ�������˫��������������µ����ݲ����ƻ�ԭ�еĵ�������ɾ��һ�����ݵ�ʱ��ֻ��ָ���
���ݵĵ�����ʧЧ����hash_map_t�в��ң��������ɾ�����ݶ��Ǹ�Ч�ģ�ͬʱ������ʹ�ü���Ϊ�±�ֱ�ӷ�����Ӧ
��ֵ��
hash_map_t�е����ݱ����ڹ�ϣ���У��������ݺ�ָ���Ĺ�ϣ�������������ڹ�ϣ���е�λ�ã�ͬʱ���ݼ�
����ָ�������Զ�����Ĭ�Ϲ����������ص�С�ڲ������û�Ҳ�����ڳ�ʼ��ʱָ���Զ���Ĺ���hash_map_t��
���ݵĲ���ɾ�����ҵȲ����������ƽ��������Ĺ����������Ч�ʸ��ߣ����Դﵽ�ӽ��������𣬵������ݲ�����
ȫ����ġ�

Typedefs
    hash_map_t ���ڹ�ϣ�ṹ��ӳ���������͡�
    hash_map_iterator_t ���ڹ�ϣ�ṹ��ӳ���������������͡�

Operation Functions
    create_hash_map �������ڹ�ϣ�ṹ��ӳ���������͡�
    hash_map_assign Ϊ���ڹ�ϣ�ṹ��ӳ���������������͸�ֵ��
    hash_map_at ʹ�ü�Ϊ�±�������ʻ��ڹ�ϣ�ṹ��ӳ����������Ӧ���ݵ�ֵ��
    hash_map_begin ����ָ����ڹ�ϣ�ṹ��ӳ�������еĵ�һ�����ݵĵ�������
    hash_map_bucket_count ���ػ��ڹ�ϣ�ṹ��ӳ������ʹ�õĹ�ϣ��Ĵ洢��Ԫ������
    hash_map_clear ɾ�����ڹ�ϣ�ṹ��ӳ�������е��������ݡ�
    hash_map_count ͳ�ƻ��ڹ�ϣ�ṹ��ӳ�������а���ָ�����ݵĸ�����
    hash_map_destroy ���ٻ��ڹ�ϣ�ṹ��ӳ��������
    hash_map_empty ���Ի��ڹ�ϣ�ṹ��ӳ�������Ƿ�Ϊ�ա�
    hash_map_end ����ָ����ڹ�ϣ�ṹ��ӳ������ĩβ�ĵ�������
    hash_map_equal �����������ڹ�ϣ�ṹ��ӳ�������Ƿ���ȡ�
    hash_map_equal_range ���ػ��ڹ�ϣ�ṹ��ӳ�������а���ָ�������������䡣
    hash_map_erase ɾ�����ڹ�ϣ�ṹ��ӳ�������а���ָ���������ݡ�
    hash_map_erase_pos ɾ�����ڹ�ϣ�ṹ��ӳ��������ָ��λ�õ����ݡ�
    hash_map_erase_range ɾ�����ڹ�ϣ�ṹ��ӳ��������ָ�����������䡣
    hash_map_find �ڻ��ڹ�ϣ�ṹ��ӳ�������в��Ұ���ָ���������ݡ�
    hash_map_greater ���Ե�һ�����ڹ�ϣ�ṹ��ӳ���Ƿ���ڵڶ������ڹ�ϣ�ṹ��ӳ�䡣
    hash_map_greater_equal ���Ե�һ�����ڹ�ϣ�ṹ��ӳ���Ƿ���ڵ��ڵڶ������ڹ�ϣ�ṹ��ӳ�䡣
    hash_map_hash ���ػ��ڹ�ϣ�ṹ��ӳ������ʹ�õĹ�ϣ������
    hash_map_init ��ʼ��һ���յĻ��ڹ�ϣ�ṹ��ӳ��������
    hash_map_init_copy ʹ�ÿ����ķ�ʽ��ʼ��һ�����ڹ�ϣ�ṹ��ӳ���������������ݶ�������Դ������
    hash_map_init_copy_range ʹ��ָ�������������ʼ��һ�����ڹ�ϣ�ṹ��ӳ��������
    hash_map_init_copy_range_ex ʹ��ָ�����������䣬��ϣ�������ȽϹ��򣬴洢��Ԫ��������ʼ��������
    hash_map_init_ex ʹ��ָ���Ĺ�ϣ�������ȽϹ��򣬴洢��Ԫ������ʼ��һ���յĻ��ڹ�ϣ�ṹ��ӳ�䡣
    hash_map_insert ����ڹ�ϣ�ṹ��ӳ���в���һ�����ݡ�
    hash_map_insert_range ����ڹ�ϣ�ṹ��ӳ���в���һ���������䡣
    hash_map_key_comp ���ػ��ڹ�ϣ�ṹ��ӳ������ʹ�õļ��ȽϹ���
    hash_map_less ���Ե�һ�����ڹ�ϣ�ṹ��ӳ���Ƿ�С�ڵڶ������ڹ�ϣ�ṹ��ӳ�䡣
    hash_map_less_equal ���Ե�һ�����ڹ�ϣ�ṹ��ӳ���Ƿ�С�ڵ��ڵڶ������ڹ�ϣ�ṹ��ӳ�䡣
    hash_map_max_size ���ػ��ڹ�ϣ�ṹ��ӳ���������ܹ������������������ֵ��
    hash_map_not_equal �����������ڹ�ϣ�ṹ��ӳ�������Ƿ񲻵ȡ�
    hash_map_resize �������û��ڹ�ϣ�ṹ��ӳ�������Ĺ�ϣ��洢��Ԫ������
    hash_map_size ���ػ��ڹ�ϣ�ṹ��ӳ�������б������ݵĸ�����
    hash_map_swap �����������ڹ�ϣ�ṹ��ӳ�����������ݡ�
    hash_map_value_comp ���ػ��ڹ�ϣ�ṹ��ӳ������ʹ�õ����ݱȽϹ���

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
    hash_map_t* phm_hm1 = create_hash_map(int, int); //����hash_map_t����
    hash_map_t* phm_hm2 = create_hash_map(int, int);
    pair_t* ppair_p = create_pair(int, int); //����pair_t����
    hash_map_iterator_t it_hm;  //hash_map_t���͵ĵ���������

    if(phm_hm1 == NULL || phm_hm2 == NULL)
    {
        return -1;
    }
    
    pair_init(ppair_p);//��ʼ��pair_t����
    hash_map_init(phm_hm1); //��ʼ��hash_map_t����
    hash_map_init(phm_hm2);

    
    //����ڹ�ϣ�ṹ��ӳ���в���һ�����ݡ�
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);

    pair_make(ppair_p, 4, 40);
    hash_map_insert(phm_hm2, ppair_p);
    pair_make(ppair_p, 5, 50);
    hash_map_insert(phm_hm2, ppair_p);
    pair_make(ppair_p, 6, 60);
    hash_map_insert(phm_hm2, ppair_p);

    //hash_map_begin: ����ָ��hash_map_t��һ�����ݵĵ�����
    //hash_map_end: ����ָ��hash_map_tĩβλ�õĵ�����
    printf("m1 =");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hm)),
            *(int*)pair_second(iterator_get_pointer(it_hm)));
    }
    // <1, 10> <2, 20> <3, 30>
    printf("\n");
    
    //ʹ��hash_map_t����Ϊ��ǰ��hash_map_t��ֵ
    hash_map_assign(phm_hm1, phm_hm2);
    printf("m1 =");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hm)),
            *(int*)pair_second(iterator_get_pointer(it_hm)));
    }
    // <4, 40> <5, 50> <6, 60>
    printf("\n");

    //ͨ������Ϊ�±�ֱ�ӷ���hash_map_t����Ӧ���ݵ�ֵ
    //�����������ͨ��ָ���ļ�������hash_map_t����Ӧ���ݵ�ֵ�����hash_map_t�а������������ô�ͷ���ָ����Ӧ��
    //�ݵ�ֵ��ָ�룬���hash_map_t�в��������������ô������hash_map_t�в���һ�����ݣ����������ָ���ļ�Ϊ������ֵ��
    //Ĭ������Ϊֵ��Ȼ�󷵻�ָ��������ݵ�ֵ��ָ�롣
    *(int*)hash_map_at(phm_hm1, 4) = 45; // <4, 45> <5, 50> <6, 60>
    hash_map_at(phm_hm1, 7); // <4, 45> <5, 50> <6, 60> <7, 0>
    printf("m1 =");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hm)),
            *(int*)pair_second(iterator_get_pointer(it_hm)));
    }
    printf("\n");

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    phm_hm1 = create_hash_map(int, int);
    phm_hm2 = create_hash_map(int, int);
    hash_map_init(phm_hm1);
    hash_map_init_ex(phm_hm2, 100, NULL, NULL);

    // ����hash_map_t�й�ϣ��Ĵ洢��Ԫ�ĸ�����
    printf("The default bucket count of hm1 is %d.\n",
    hash_map_bucket_count(phm_hm1)); //53
    printf("The custom bucket count of hm2 is %d.\n",
    hash_map_bucket_count(phm_hm2)); //193

    hash_map_destroy(phm_hm2);
    phm_hm2 = create_hash_map(int, int);
    hash_map_init(phm_hm2);

    //ɾ��hash_map_t�е��������ݡ�
    hash_map_clear(phm_hm1);
    
    pair_make(ppair_p, 1, 1);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 1);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 1, 4); //���Զ����Ǹ���
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 1);
    hash_map_insert(phm_hm1, ppair_p);
    
    //hash_map_count ���������а���ָ�����ݵĸ���
    /* Keys must be unique in hash_map, so duplicates are ignored */
    printf("The number of elements in m1 with a sort key of 1 is: %d.\n",
        hash_map_count(phm_hm1, 1)); // 1
    printf("The number of elements in m1 with a sort key of 2 is: %d.\n",
        hash_map_count(phm_hm1, 2)); // 1
    printf("The number of elements in m1 with a sort key of 3 is: %d.\n",
        hash_map_count(phm_hm1, 3)); // 0

    printf("m1 =");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hm)),
            *(int*)pair_second(iterator_get_pointer(it_hm)));
    }
    printf("\n");

    // ����hash_map_t�����Ƿ�Ϊ��
    if(hash_map_empty(phm_hm1))
    {
        printf("The hash_map m1 is empty.\n");
    }

    //��������hash_map_t�Ƿ����
    if(hash_map_equal(phm_hm1, phm_hm2))
    {
        printf("The hash_maps m1 and m2 are equal.\n");
    }

    //���Ե�һ��hash_map_t�����Ƿ���ڵڶ���hash_map_t����
    if(hash_map_greater(phm_hm1, phm_hm2))
    {
        printf("The hash_map m1 is greater than the hash_map m2.\n");
    }

    //���Ե�һ��hash_map_t�Ƿ���ڵ��ڵڶ���hash_map_t
    if(hash_map_greater_equal(phm_hm1, phm_hm2))
    {
        printf("The hash_map m1 is greater than or equal to the hash_map m2.\n");
    }

    //���Ե�һ��hash_map_t�Ƿ�С�ڵڶ���hash_map_t
    if(hash_map_less(phm_hm1, phm_hm2))
    {
        printf("The hash_map m1 is less than the hash_map m2.\n");
    }

    //���Ե�һ��hash_map_t�Ƿ�С�ڵ��ڵڶ���hash_map_t
    if(hash_map_less_equal(phm_hm1, phm_hm2))
    {
        printf("The hash_map m1 is less than or equal to the hash_map m2.\n");
    }
    
    //��������hash_map_t�Ƿ񲻵�
    if(hash_map_not_equal(phm_hm1, phm_hm2))
    {
        printf("The hash_maps m1 and m2 are not equal.\n");
    }

    // ����hash_map_tʹ�õĹ�ϣ����
    if(hash_map_hash(phm_hm2) == _hash_function)
    {
        printf("The hash function of hash_map hs2 is _hash_function.\n");
    }
    
    range_t r_r;
    hash_map_clear(phm_hm1);
    
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);

    //����hash_map_t�а���ָ�����ݵ���������
    r_r = hash_map_equal_range(phm_hm1, 2); //��������������ڵ���20��

    printf("The lower bound of the element with a key of 2 in the hash_map m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_begin)));//30
    printf("The upper bound of the element with a key of 2 in the hash_map m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_end))); //20

    r_r = hash_map_equal_range(phm_hm1, 4);
    /* If no match is found for the key, both elements of the range return end() */
    if(iterator_equal(r_r.it_begin, hash_map_end(phm_hm1)) &&
        iterator_equal(r_r.it_end, hash_map_end(phm_hm1)))
    {
        printf("The hash_map m1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of hash_map m1 with a key >= 40 is %d.\n",
            *(int*)pair_first(iterator_get_pointer(r_r.it_begin)));
    }

    hash_map_clear(phm_hm1);
    
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 5, 50);
    hash_map_insert(phm_hm1, ppair_p);
    
    //hash_map_erase ɾ�����ڹ�ϣ�ṹ��ӳ����������ָ��������ȵ�����
    int t_count = hash_map_erase(phm_hm1, 4); // <1, 10> <2, 20> <3, 30>  <5, 50> t_count = 1

    //hash_map_erase_pos ɾ�����ڹ�ϣ�ṹ��ӳ��������ָ��λ�õ�����
    hash_map_erase_pos(phm_hm1, iterator_next(hash_map_begin(phm_hm1))); //<1, 10> <3, 30>  <5, 50>

    //hash_map_erase_range ɾ�����ڹ�ϣ�ṹ��ӳ��������ָ���������������
    hash_map_erase_range(phm_hm1, iterator_next(hash_map_begin(phm_hm1)),
        iterator_prev(hash_map_end(phm_hm1))); // <1, 10> <5, 50>

    //��hash_map_t�в���ָ��������
    it_hm = hash_map_find(phm_hm1, 1);
    printf("The element of hash_map m1 with a key of 1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_hm)));
    
    /* If no match is found for the key, end() is returned */
    it_hm = hash_map_find(phm_hm1, 4);
    if(iterator_equal(it_hm, hash_map_end(phm_hm1)))
    {
        printf("The hash_map m1 doesn't have an element with a key of 4.\n");
    }
    
    hash_map_clear(phm_hm1);
    hash_map_clear(phm_hm2);

    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_map_insert(phm_hm1, ppair_p);

    //��hash_map_t�в�������,�ɹ��󷵻�ָ������ݵĵ����������hash_map_t�а����˸�������ô����ʧ�ܣ�����hash_map_end()
    pair_make(ppair_p, 1, 10);
    it_hm = hash_map_insert(phm_hm1, ppair_p);
    if(!iterator_equal(it_hm, hash_map_end(phm_hm1)))
    {
        printf("The element 10 was inserted in m1 successfully.\n");
    }
    else
    {
        printf("The number 1 already exists in m1.\n");
    }


    pair_make(ppair_p, 10, 100);
    hash_map_insert(phm_hm2, ppair_p);
    //����ָ������������
    hash_map_insert_range(phm_hm2, iterator_next(hash_map_begin(phm_hm1)),
        iterator_prev(hash_map_end(phm_hm1)));
    printf("After the insertions, the key values of m2 =");
    for(it_hm = hash_map_begin(phm_hm2);
        !iterator_equal(it_hm, hash_map_end(phm_hm2));
        it_hm = iterator_next(it_hm))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_hm)),
            *(int*)pair_second(iterator_get_pointer(it_hm)));
    }
    //<2, 20> <3, 30> <4, 40> <10, 100>
    printf("\n");

    hash_map_clear(phm_hm1);
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);
    

    //����hash_map_t���ܹ���������ݸ�����������ֵ
    printf("The maximum possible length of the hash_map is %u.\n",
        hash_map_max_size(phm_hm1));

    //����hash_map_t�б�������ݵ�����
    printf("The hash_map length is %d.\n", hash_map_size(phm_hm1));

    //��������hash_map_t�е�����
    hash_map_swap(phm_hm1, phm_hm2);

    binary_function_t bfun_vc = NULL;
    binary_function_t bfun_kc = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;
    hash_map_iterator_t it_hm1;  //hash_map_t���͵ĵ���������
    hash_map_iterator_t it_hm2;  //hash_map_t���͵ĵ���������

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    phm_hm1 = create_hash_map(int, int);
    phm_hm2 = create_hash_map(int, int);

    hash_map_init_ex(phm_hm1, 0, NULL, fun_less_int);
    
    //����hash_map_t�ļ��ȽϹ���
    bfun_kc = hash_map_key_comp(phm_hm1);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m1.\n");
    }

    hash_map_destroy(phm_hm1);

    hash_map_init_ex(phm_hm2, 0, NULL, fun_greater_int);

    bfun_kc = hash_map_key_comp(phm_hm2);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m2.\n");
    }
    
    hash_map_destroy(phm_hm2);
    
    phm_hm1 = create_hash_map(int, int);
    hash_map_init_ex(phm_hm1, 0, NULL, fun_less_int);

    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 5);
    hash_map_insert(phm_hm1, ppair_p);

    it_hm1 = hash_map_find(phm_hm1, 1);
    it_hm2 = hash_map_find(phm_hm1, 2);
    //����hash_map_t�����ݵıȽϹ���,���������������ݱ���ıȽϹ�������Ǽ�����ֵ
    bfun_vc = hash_map_value_comp(phm_hm1);

    (*bfun_vc)(iterator_get_pointer(it_hm1), iterator_get_pointer(it_hm2), &b_result);
    if(b_result)
    {
        printf("The element (1, 10) precedes the element (2, 5).\n");
    }
    else
    {
        printf("The element (1, 10) does not precedes the element (2, 5).\n");
    }

    (*bfun_vc)(iterator_get_pointer(it_hm2), iterator_get_pointer(it_hm1), &b_result);
    if(b_result)
    {
        printf("The element (2, 5) precedes the element (1, 10).\n");
    }
    else
    {
        printf("The element (2, 5) does not precedes the element (1, 10).\n");
    }
    hash_map_destroy(phm_hm1);

    hash_map_t* phm_hm0 = create_hash_map(int, int);
    phm_hm1 = create_hash_map(int, int);
    phm_hm2 = create_hash_map(int, int);
    hash_map_t* phm_hm3 = create_hash_map(int, int);
    hash_map_t* phm_hm4 = create_hash_map(int, int);
    hash_map_t* phm_hm5 = create_hash_map(int, int);

    if(phm_hm0 == NULL || phm_hm1 == NULL || phm_hm2 == NULL || phm_hm3 == NULL || phm_hm4 == NULL || phm_hm5 == NULL)
    {
        return -1;
    }
    
    //hash_map_init ��ʼ��һ���յĻ��ڹ�ϣ�ṹ��ӳ��������
    hash_map_init(phm_hm0);

    //hash_map_init_ex ʹ��ָ������������ʼ��һ���յĻ��ڹ�ϣ�ṹ��ӳ������
    hash_map_init_ex(phm_hm1, 0, _hash_function, fun_less_int);
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 3, 30);
    hash_map_insert(phm_hm1, ppair_p);
    pair_make(ppair_p, 4, 40);
    hash_map_insert(phm_hm1, ppair_p);

    //hash_map_init_ex ʹ��ָ���Ĺ�ϣ�������ȽϹ��򣬴洢��Ԫ������ʼ��һ���յĻ��ڹ�ϣ�ṹ��ӳ��
    hash_map_init_ex(phm_hm2, 0, _hash_function, fun_greater_int);
    pair_make(ppair_p, 1, 10);
    hash_map_insert(phm_hm2, ppair_p);
    pair_make(ppair_p, 2, 20);
    hash_map_insert(phm_hm2, ppair_p);

    //hash_map_init_copy ʹ�ÿ����ķ�ʽ��ʼ��һ�����ڹ�ϣ�ṹ��ӳ���������������ݶ�������Դ������
    hash_map_init_copy(phm_hm3, phm_hm1); 

    //hash_map_init_copy_range ʹ��ָ�������������ʼ��һ�����ڹ�ϣ�ṹ��ӳ��������
    hash_map_init_copy_range(phm_hm4, hash_map_begin(phm_hm1), iterator_advance(hash_map_begin(phm_hm1), 2)); 

    //hash_map_init_copy_range_ex ʹ��ָ�����������䣬��ϣ�������ȽϹ��򣬴洢��Ԫ��������ʼ��������
    hash_map_init_copy_range_ex(phm_hm5, hash_map_begin(phm_hm3),
        hash_map_end(phm_hm3), 100, _hash_function, fun_less_int);

    hash_map_destroy(phm_hm0);
    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    hash_map_destroy(phm_hm3);
    hash_map_destroy(phm_hm4);
    hash_map_destroy(phm_hm5);
    pair_destroy(ppair_p);

    return 0;
}

