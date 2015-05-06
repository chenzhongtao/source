/*
file: multimap.c

����ӳ��multimap_t

����ӳ��multimap_t�ǹ��������������б����������pair_t���͡�pair_t�ĵ�һ�������Ǽ���multimap_t��
�����ݾ��Ǹ������������ģ���multimap_t�м������ظ���������ֱ�ӻ��߼���޸ļ���pair_t�ĵڶ���������ֵ��
ֵ���û��ֱ�ӵĹ�ϵ��ֵ����multimap_t�е���������û��Ӱ�죬����ֱ�ӻ��߼���޸�ֵ��
multimap_t�ĵ�������˫��������������µ����ݲ����ƻ�ԭ�еĵ�������ɾ��һ�����ݵ�ʱ��ֻ��ָ�����
�ݵĵ�����ʧЧ����multimap_t�в��ң��������ɾ�����ݶ��Ǹ�Ч�ġ�
multimap_t�е����ݸ��ݼ�����ָ�������Զ�����Ĭ�Ϲ����������ص�С�ڲ������û�Ҳ�����ڳ�ʼ��ʱ
ָ���Զ���Ĺ���

Typedefs
    multimap_t ����ӳ���������͡�
    multimap_iterator_t ����ӳ���������������͡�

Operation Functions
    create_multimap ��������ӳ���������͡�
    multimap_assign Ϊ����ӳ���������͸�ֵ��
    multimap_begin ����ָ�����ӳ�������еĵ�һ�����ݵĵ�������
    multimap_clear ɾ������ӳ�����������е����ݡ�
    multimap_count ���ض���ӳ�������а���ָ���������ݵĸ�����
    multimap_destroy ���ٶ���ӳ��������
    multimap_empty ���Զ���ӳ�������Ƿ�Ϊ�ա�
    multimap_end ����ָ�����ӳ������ĩβ�ĵ�������
    multimap_equal ������������ӳ�������Ƿ���ȡ�
    multimap_equal_range ���ض���ӳ�������а���ӵ��ָ���������ݵ��������䡣
    multimap_erase ɾ������ӳ�������а���ָ���������ݡ�
    multimap_erase_pos ɾ������ӳ��������ָ��λ�õ����ݡ�
    multimap_erase_range ɾ������ӳ��������ָ��������������ݡ�
    multimap_find �ڶ���ӳ�������в��Ұ���ָ���������ݡ�
    multimap_greater ���Ե�һ������ӳ�������Ƿ���ڵڶ�������ӳ��������
    multimap_greater_equal ���Ե�һ������ӳ�������Ƿ���ڵ��ڵڶ�������ӳ��������
    multimap_init ��ʼ��һ���յĶ���ӳ��������
    multimap_init_copy ʹ�ö���ӳ��������ʼ����ǰ����ӳ��������
    multimap_init_copy_range ʹ��ָ�������������ʼ������ӳ��������
    multimap_init_copy_range_ex ʹ��ָ�������������ָ������������ʼ������ӳ��������
    multimap_init_ex ʹ��ָ������������ʼ��һ���յĶ���ӳ��������
    multimap_insert �����ӳ�������в���һ��ָ�������ݡ�
    multimap_insert_hint �����ӳ�������в���һ��ָ�������ݣ�ͬʱ����λ����ʾ��
    multimap_insert_range �����ӳ�������в���ָ�����������䡣
    multimap_key_comp ���ض���ӳ������ʹ�õļ��ȽϹ���
    multimap_less ���Ե�һ������ӳ�������Ƿ�С�ڵڶ�������ӳ��������
    multimap_less_equal ���Ե�һ������ӳ�������Ƿ�С�ڵ��ڵڶ�������ӳ��������
    multimap_lower_bound ���ض���ӳ�������а���ָ�����ĵ�һ�����ݵĵ�������
    multimap_max_size ���ض���ӳ���������ܹ����������������������ֵ��
    multimap_not_equal ������������ӳ�������Ƿ񲻵ȡ�
    multimap_size ���ض���ӳ�����������ݵ�������
    multimap_swap ������������ӳ�����������ݡ�
    multimap_upper_bound ���ض���ӳ�������а�������ָ�����ĵ�һ�����ݵĵ�������
    multimap_value_comp ���ض���ӳ�����������ݵıȽϹ���

*/


#include <stdio.h>
#include <cstl/cmap.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int); //����multimap_t����
    multimap_t* pmmap_m2 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int); //����pair_t����
    multimap_iterator_t it_m;  //multimap_t���͵ĵ���������

    if(pmmap_m1 == NULL || pmmap_m2 == NULL)
    {
        return -1;
    }
    
    pair_init(ppair_p);//��ʼ��pair_t����
    multimap_init(pmmap_m1); //��ʼ��multimap_t����
    multimap_init(pmmap_m2);

    
    //�����ӳ���в���һ�����ݡ�
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);

    pair_make(ppair_p, 4, 40);
    multimap_insert(pmmap_m2, ppair_p);
    pair_make(ppair_p, 5, 50);
    multimap_insert(pmmap_m2, ppair_p);
    pair_make(ppair_p, 6, 60);
    multimap_insert(pmmap_m2, ppair_p);

    //multimap_begin: ����ָ��multimap_t��һ�����ݵĵ�����
    //multimap_end: ����ָ��multimap_tĩβλ�õĵ�����
    printf("m1 =");
    for(it_m = multimap_begin(pmmap_m1);
        !iterator_equal(it_m, multimap_end(pmmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    // <1, 10> <2, 20> <3, 30>
    printf("\n");
    
    //ʹ��multimap_t����Ϊ��ǰ��multimap_t��ֵ
    multimap_assign(pmmap_m1, pmmap_m2);
    printf("m1 =");
    for(it_m = multimap_begin(pmmap_m1);
        !iterator_equal(it_m, multimap_end(pmmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    // <4, 40> <5, 50> <6, 60>
    printf("\n");


    //ɾ��multimap_t�е��������ݡ�
    multimap_clear(pmmap_m1);
    
    pair_make(ppair_p, 1, 1);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 1, 4); 
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1); // ���Ḳ�ǻ���ԣ�������1
    multimap_insert(pmmap_m1, ppair_p);
    
    //multimap_count ���������а���ָ�����ݵĸ���
    /* Keys must be unique in multimap, so duplicates are ignored */
    printf("The number of elements in m1 with a sort key of 1 is: %d.\n",
        multimap_count(pmmap_m1, 1)); // 2
    printf("The number of elements in m1 with a sort key of 2 is: %d.\n",
        multimap_count(pmmap_m1, 2)); // 2
    printf("The number of elements in m1 with a sort key of 3 is: %d.\n",
        multimap_count(pmmap_m1, 3)); // 0

    printf("m1 =");
    for(it_m = multimap_begin(pmmap_m1);
        !iterator_equal(it_m, multimap_end(pmmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    // ����multimap_t�����Ƿ�Ϊ��
    if(multimap_empty(pmmap_m1))
    {
        printf("The multimap m1 is empty.\n");
    }

    //��������multimap_t�Ƿ����
    if(multimap_equal(pmmap_m1, pmmap_m2))
    {
        printf("The multimaps m1 and m2 are equal.\n");
    }

    //���Ե�һ��multimap_t�����Ƿ���ڵڶ���multimap_t����
    if(multimap_greater(pmmap_m1, pmmap_m2))
    {
        printf("The multimap m1 is greater than the multimap m2.\n");
    }

    //���Ե�һ��multimap_t�Ƿ���ڵ��ڵڶ���multimap_t
    if(multimap_greater_equal(pmmap_m1, pmmap_m2))
    {
        printf("The multimap m1 is greater than or equal to the multimap m2.\n");
    }

    //���Ե�һ��multimap_t�Ƿ�С�ڵڶ���multimap_t
    if(multimap_less(pmmap_m1, pmmap_m2))
    {
        printf("The multimap m1 is less than the multimap m2.\n");
    }

    //���Ե�һ��multimap_t�Ƿ�С�ڵ��ڵڶ���multimap_t
    if(multimap_less_equal(pmmap_m1, pmmap_m2))
    {
        printf("The multimap m1 is less than or equal to the multimap m2.\n");
    }
    
    //��������multimap_t�Ƿ񲻵�
    if(multimap_not_equal(pmmap_m1, pmmap_m2))
    {
        printf("The multimaps m1 and m2 are not equal.\n");
    }
    
    range_t r_r;
    multimap_clear(pmmap_m1);
    
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);

    //����multimap_t�а���ָ�����ݵ���������
    r_r = multimap_equal_range(pmmap_m1, 2); //��������������ڵ���20��

    printf("The lower bound of the element with a key of 2 in the multimap m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_begin)));//30
    printf("The upper bound of the element with a key of 2 in the multimap m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_end))); //20

    //����multimap_t�д���ָ�����ݵĵ�һ�����ݵĵ�����
    it_m = multimap_upper_bound(pmmap_m1, 2);
    printf("A direct call of upper_bound(2) gives %d, matching "
        "the second element of the range returned by equal_range(2).\n",
        *(int*)pair_second(iterator_get_pointer(it_m))); //30

    r_r = multimap_equal_range(pmmap_m1, 4);
    /* If no match is found for the key, both elements of the range return end() */
    if(iterator_equal(r_r.it_begin, multimap_end(pmmap_m1)) &&
        iterator_equal(r_r.it_end, multimap_end(pmmap_m1)))
    {
        printf("The multimap m1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of multimap m1 with a key >= 40 is %d.\n",
            *(int*)pair_first(iterator_get_pointer(r_r.it_begin)));
    }

    multimap_clear(pmmap_m1);
    
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 5, 50);
    multimap_insert(pmmap_m1, ppair_p);
    
    //multimap_erase ɾ������ӳ����������ָ��������ȵ�����
    int t_count = multimap_erase(pmmap_m1, 4); // <1, 10> <2, 20> <3, 30>  <5, 50> t_count = 1

    //multimap_erase_pos ɾ������ӳ��������ָ��λ�õ�����
    multimap_erase_pos(pmmap_m1, iterator_next(multimap_begin(pmmap_m1))); //<1, 10> <3, 30>  <5, 50>

    //multimap_erase_range ɾ������ӳ��������ָ���������������
    multimap_erase_range(pmmap_m1, iterator_next(multimap_begin(pmmap_m1)),
        iterator_prev(multimap_end(pmmap_m1))); // <1, 10> <5, 50>

    //��multimap_t�в���ָ��������
    it_m = multimap_find(pmmap_m1, 1);
    printf("The element of multimap m1 with a key of 1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));
    
    /* If no match is found for the key, end() is returned */
    it_m = multimap_find(pmmap_m1, 4);
    if(iterator_equal(it_m, multimap_end(pmmap_m1)))
    {
        printf("The multimap m1 doesn't have an element with a key of 4.\n");
    }
    
    multimap_clear(pmmap_m1);
    multimap_clear(pmmap_m2);

    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    multimap_insert(pmmap_m1, ppair_p);

    //��multimap_t�в�������,�ɹ��󷵻�ָ������ݵĵ����������multimap_t�а����˸�������ô����ʧ�ܣ�����multimap_end()
    pair_make(ppair_p, 1, 10);
    it_m = multimap_insert(pmmap_m1, ppair_p);
    if(!iterator_equal(it_m, multimap_end(pmmap_m1)))
    {
        printf("The element 10 was inserted in m1 successfully.\n");
    }
    else
    {
        printf("The number 1 already exists in m1.\n");
    }

    // ��multimap_t�в���һ��ָ�������ݣ�ͬʱ����һ�������ݱ���������ʾλ�õ�������������λ��
    //����multimap_t���������Ͱ�������ݷ�����ʾλ���гɹ��󷵻�ָ������ݵĵ������������ʾλ�ò���ȷ�������
    //ʾλ�ã�(�ǲ���Ϊ�˼���)�����ݲ���ɹ��󷵻����ݵ�ʵ��λ�õ����������multimap_t�а����˸�������ô����ʧ�ܣ�����multimap_end()
    pair_make(ppair_p, 5, 50);
    multimap_insert_hint(pmmap_m1, iterator_prev(multimap_end(pmmap_m1)), ppair_p);
    printf("After the insertions, the key values of m1 =");
    for(it_m = multimap_begin(pmmap_m1);
        !iterator_equal(it_m, multimap_end(pmmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
      //  <1, 10> <2, 20> <3, 30> <4, 40> <5, 50>
    printf("\n");

    pair_make(ppair_p, 10, 100);
    multimap_insert(pmmap_m2, ppair_p);
    //����ָ������������
    multimap_insert_range(pmmap_m2, iterator_next(multimap_begin(pmmap_m1)),
        iterator_prev(multimap_end(pmmap_m1)));
    printf("After the insertions, the key values of m2 =");
    for(it_m = multimap_begin(pmmap_m2);
        !iterator_equal(it_m, multimap_end(pmmap_m2));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    //<2, 20> <3, 30> <4, 40> <10, 100>
    printf("\n");

    multimap_clear(pmmap_m1);
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);
    
     //���multimap_t�е��ڻ��ߴ���ָ�����ݵĵ�һ�����ݵĵ�����
    it_m = multimap_lower_bound(pmmap_m1, 2);
    printf("The first element of multimap m1 with a key of 2 is: %d.\n",// 20
        *(int*)pair_second(iterator_get_pointer(it_m)));

    //����multimap_t�д���ָ�����ݵĵ�һ�����ݵĵ�����
    it_m = multimap_upper_bound(pmmap_m1, 2);
    printf("The first element of multimap m1 with a key greater than 2 is: %d.\n", // 30
        *(int*)pair_second(iterator_get_pointer(it_m)));
    
    /* If no match is found for this key, end() is returned */
    it_m = multimap_lower_bound(pmmap_m1, 4);
    if(iterator_equal(it_m, multimap_end(pmmap_m1)))
    {
        printf("The multimap m1 doesn't have an element with a key of 4.\n");
    }
    else
    {
        printf("The element of multimap m1 with key of 4 is: %d.\n",
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }

    //����multimap_t���ܹ���������ݸ�����������ֵ
    printf("The maximum possible length of the multimap is %u.\n",
        multimap_max_size(pmmap_m1));

    //����multimap_t�б�������ݵ�����
    printf("The multimap length is %d.\n", multimap_size(pmmap_m1));

    //��������multimap_t�е�����
    multimap_swap(pmmap_m1, pmmap_m2);

    binary_function_t bfun_vc = NULL;
    binary_function_t bfun_kc = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;
    multimap_iterator_t it_m1;  //multimap_t���͵ĵ���������
    multimap_iterator_t it_m2;  //multimap_t���͵ĵ���������

    multimap_destroy(pmmap_m1);
    multimap_destroy(pmmap_m2);
    pmmap_m1 = create_multimap(int, int);
    pmmap_m2 = create_multimap(int, int);

    multimap_init_ex(pmmap_m1, fun_less_int);
    
    //����multimap_t�ļ��ȽϹ���
    bfun_kc = multimap_key_comp(pmmap_m1);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m1.\n");
    }

    multimap_destroy(pmmap_m1);

    multimap_init_ex(pmmap_m2, fun_greater_int);

    bfun_kc = multimap_key_comp(pmmap_m2);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m2.\n");
    }
    
    multimap_destroy(pmmap_m2);
    
    pmmap_m1 = create_multimap(int, int);
    multimap_init_ex(pmmap_m1, fun_less_int);

    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 5);
    multimap_insert(pmmap_m1, ppair_p);

    it_m1 = multimap_find(pmmap_m1, 1);
    it_m2 = multimap_find(pmmap_m1, 2);
    //����multimap_t�����ݵıȽϹ���,���������������ݱ���ıȽϹ�������Ǽ�����ֵ
    bfun_vc = multimap_value_comp(pmmap_m1);

    (*bfun_vc)(iterator_get_pointer(it_m1), iterator_get_pointer(it_m2), &b_result);
    if(b_result)
    {
        printf("The element (1, 10) precedes the element (2, 5).\n");
    }
    else
    {
        printf("The element (1, 10) does not precedes the element (2, 5).\n");
    }

    (*bfun_vc)(iterator_get_pointer(it_m2), iterator_get_pointer(it_m1), &b_result);
    if(b_result)
    {
        printf("The element (2, 5) precedes the element (1, 10).\n");
    }
    else
    {
        printf("The element (2, 5) does not precedes the element (1, 10).\n");
    }
    multimap_destroy(pmmap_m1);

    multimap_t* pmmap_m0 = create_multimap(int, int);
    pmmap_m1 = create_multimap(int, int);
    pmmap_m2 = create_multimap(int, int);
    multimap_t* pmmap_m3 = create_multimap(int, int);
    multimap_t* pmmap_m4 = create_multimap(int, int);
    multimap_t* pmmap_m5 = create_multimap(int, int);

    if(pmmap_m0 == NULL || pmmap_m1 == NULL || pmmap_m2 == NULL || pmmap_m3 == NULL || pmmap_m4 == NULL || pmmap_m5 == NULL)
    {
        return -1;
    }
    
    //multimap_init ��ʼ��һ���յĶ���ӳ������
    multimap_init(pmmap_m0);

    //multimap_init_ex ʹ��ָ������������ʼ��һ���յĶ���ӳ������
    multimap_init_ex(pmmap_m1, fun_less_int);
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    multimap_insert(pmmap_m1, ppair_p);//10 20 30 40

    //multimap_init_ex ʹ��ָ������������ʼ��һ���յĶ���ӳ������
    multimap_init_ex(pmmap_m2, fun_greater_int);
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m2, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m2, ppair_p);// 20 10

    //multimap_init_copy ʹ��һ������ӳ����������������ʼ����ǰ����ӳ��������
    multimap_init_copy(pmmap_m3, pmmap_m1); //10 20 30 40 

    //multimap_init_copy_range ʹ��ָ�������������ʼ������ӳ��������
    multimap_init_copy_range(pmmap_m4, multimap_begin(pmmap_m1), iterator_advance(multimap_begin(pmmap_m1), 2)); //10 20

    //multimap_init_copy_range_ex ʹ��ָ�������������ָ������������ʼ������ӳ��������
    multimap_init_copy_range_ex(pmmap_m5, multimap_begin(pmmap_m3), iterator_next(multimap_begin(pmmap_m3)), fun_less_int);//10 

    multimap_destroy(pmmap_m0);
    multimap_destroy(pmmap_m1);
    multimap_destroy(pmmap_m2);
    multimap_destroy(pmmap_m3);
    multimap_destroy(pmmap_m4);
    multimap_destroy(pmmap_m5);
    pair_destroy(ppair_p);

    return 0;
}

