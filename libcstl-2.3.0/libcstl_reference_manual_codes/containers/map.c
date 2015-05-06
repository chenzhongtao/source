/*
file: map.c

ӳ��map_t

ӳ��map_t�ǹ��������������б����������pair_t���͡�pair_t�ĵ�һ�������Ǽ���map_t�е����ݾ��Ǹ���
���������ģ���map_t�м��������ظ���Ҳ������ֱ�ӻ��߼���޸ļ���pair_t�ĵڶ���������ֵ��ֵ���û��ֱ
�ӵĹ�ϵ��map_t�ж���ֵ��Ψһ��û��Ҫ��ֵ����map_t�е���������û��Ӱ�죬����ֱ�ӻ��߼���޸�ֵ��
map_t�ĵ�������˫��������������µ����ݲ����ƻ�ԭ�еĵ�������ɾ��һ�����ݵ�ʱ��ֻ��ָ������ݵ�
������ʧЧ����map_t�в��ң��������ɾ�����ݶ��Ǹ�Ч�ģ�ͬʱ������ʹ�ü���Ϊ�±�ֱ�ӷ�����Ӧ��ֵ��
map_t�е����ݸ��ݼ�����ָ�������Զ�����Ĭ�Ϲ����������ص�С�ڲ������û�Ҳ�����ڳ�ʼ��ʱָ��
�Զ���Ĺ���

Typedefs
    map_t ӳ���������͡�
    map_iterator_t ӳ���������������͡�

Operation Functions
    create_map ����ӳ���������͡�
    map_assign Ϊӳ��������ֵ��
    map_at ͨ���¼�ֱ�ӷ���ֵ��
    map_begin ����ָ��ӳ���е�һ�����ݵĵ�������
    map_clear ɾ��ӳ���е��������ݡ�
    map_count ͳ��ӳ����ӵ��ָ���������ݵĸ�����
    map_destroy ����ӳ��������
    map_empty ����ӳ�������Ƿ�Ϊ�ա�
    map_end ����ָ������ĩβ�ĵ�������
    map_equal ��������ӳ�������Ƿ���ȡ�
    map_equal_range ������ָ������ȵ��������䡣
    map_erase ɾ��ӳ������ָ����ֵ��ȵ����ݡ�
    map_erase_pos ɾ��ӳ����ָ��λ�õ����ݡ�
    map_erase_range ɾ��ӳ����ָ�����������䡣
    map_find ����������ӵ��ָ���������ݡ�
    map_greater ���Ե�һ��ӳ���Ƿ���ڵڶ���ӳ�䡣
    map_greater_equal ���Ե�һ��ӳ���Ƿ���ڵ��ڵڶ���ӳ�䡣
    map_init ��ʼ��һ����ӳ�䡣
    map_init_copy ʹ����һ��ӳ���ʼ����ǰӳ��������
    map_init_copy_range ʹ��ָ�������������ʼ��ӳ��������
    map_init_copy_range_ex ʹ��ָ�������������ָ������������ʼ��ӳ��������
    map_init_ex ʹ��ָ������������ʼ��һ���յ�ӳ��������
    map_insert ��ӳ�������в������ݡ�
    map_insert_hint ��ӳ�������в������ݣ�ͬʱ����λ����ʾ��
    map_insert_range ��ӳ�������в����������䡣
    map_key_comp ����ӳ������ʹ�õļ��ȽϹ���
    map_less ���Ե�һ��ӳ�������Ƿ�С�ڵڶ���ӳ��������
    map_less_equal ���Ե�һ��ӳ�������Ƿ�С�ڵ��ڵڶ���ӳ��������
    map_lower_bound ������ָ������ȵĵ�һ�����ݵĵ�������
    map_max_size ����ӳ���������ܹ��������ݵ���������Ŀ���ֵ��
    map_not_equal ��������ӳ�������Ƿ񲻵ȡ�
    map_size ����ӳ�����������ݵ�������
    map_swap ��������ӳ�����������ݡ�
    map_upper_bound ���ش���ָ�����ĵ�һ�����ݵĵ�������
    map_value_comp ����ӳ������ʹ�õ����ݱȽϹ���

*/


#include <stdio.h>
#include <cstl/cmap.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int); //����map_t����
    map_t* pmap_m2 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int); //����pair_t����
    map_iterator_t it_m;  //map_t���͵ĵ���������

    if(pmap_m1 == NULL || pmap_m2 == NULL)
    {
        return -1;
    }
    
    pair_init(ppair_p);//��ʼ��pair_t����
    map_init(pmap_m1); //��ʼ��map_t����
    map_init(pmap_m2);

    
    //��ӳ���в���һ�����ݡ�
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);

    pair_make(ppair_p, 4, 40);
    map_insert(pmap_m2, ppair_p);
    pair_make(ppair_p, 5, 50);
    map_insert(pmap_m2, ppair_p);
    pair_make(ppair_p, 6, 60);
    map_insert(pmap_m2, ppair_p);

    //map_begin: ����ָ��map_t��һ�����ݵĵ�����
    //map_end: ����ָ��map_tĩβλ�õĵ�����
    printf("m1 =");
    for(it_m = map_begin(pmap_m1);
        !iterator_equal(it_m, map_end(pmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    // <1, 10> <2, 20> <3, 30>
    printf("\n");
    
    //ʹ��map_t����Ϊ��ǰ��map_t��ֵ
    map_assign(pmap_m1, pmap_m2);
    printf("m1 =");
    for(it_m = map_begin(pmap_m1);
        !iterator_equal(it_m, map_end(pmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    // <4, 40> <5, 50> <6, 60>
    printf("\n");

    //ͨ������Ϊ�±�ֱ�ӷ���map_t����Ӧ���ݵ�ֵ
    //�����������ͨ��ָ���ļ�������map_t����Ӧ���ݵ�ֵ�����map_t�а������������ô�ͷ���ָ����Ӧ��
    //�ݵ�ֵ��ָ�룬���map_t�в��������������ô������map_t�в���һ�����ݣ����������ָ���ļ�Ϊ������ֵ��
    //Ĭ������Ϊֵ��Ȼ�󷵻�ָ��������ݵ�ֵ��ָ�롣
    *(int*)map_at(pmap_m1, 4) = 45; // <4, 45> <5, 50> <6, 60>
    map_at(pmap_m1, 7); // <4, 45> <5, 50> <6, 60> <7, 0>
    printf("m1 =");
    for(it_m = map_begin(pmap_m1);
        !iterator_equal(it_m, map_end(pmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    //ɾ��map_t�е��������ݡ�
    map_clear(pmap_m1);
    
    pair_make(ppair_p, 1, 1);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 1, 4); //���Զ����Ǹ���
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1);
    map_insert(pmap_m1, ppair_p);
    
    //map_count ���������а���ָ�����ݵĸ���
    /* Keys must be unique in map, so duplicates are ignored */
    printf("The number of elements in m1 with a sort key of 1 is: %d.\n",
        map_count(pmap_m1, 1)); // 1
    printf("The number of elements in m1 with a sort key of 2 is: %d.\n",
        map_count(pmap_m1, 2)); // 1
    printf("The number of elements in m1 with a sort key of 3 is: %d.\n",
        map_count(pmap_m1, 3)); // 0

    printf("m1 =");
    for(it_m = map_begin(pmap_m1);
        !iterator_equal(it_m, map_end(pmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    // ����map_t�����Ƿ�Ϊ��
    if(map_empty(pmap_m1))
    {
        printf("The map m1 is empty.\n");
    }

    //��������map_t�Ƿ����
    if(map_equal(pmap_m1, pmap_m2))
    {
        printf("The maps m1 and m2 are equal.\n");
    }

    //���Ե�һ��map_t�����Ƿ���ڵڶ���map_t����
    if(map_greater(pmap_m1, pmap_m2))
    {
        printf("The map m1 is greater than the map m2.\n");
    }

    //���Ե�һ��map_t�Ƿ���ڵ��ڵڶ���map_t
    if(map_greater_equal(pmap_m1, pmap_m2))
    {
        printf("The map m1 is greater than or equal to the map m2.\n");
    }

    //���Ե�һ��map_t�Ƿ�С�ڵڶ���map_t
    if(map_less(pmap_m1, pmap_m2))
    {
        printf("The map m1 is less than the map m2.\n");
    }

    //���Ե�һ��map_t�Ƿ�С�ڵ��ڵڶ���map_t
    if(map_less_equal(pmap_m1, pmap_m2))
    {
        printf("The map m1 is less than or equal to the map m2.\n");
    }
    
    //��������map_t�Ƿ񲻵�
    if(map_not_equal(pmap_m1, pmap_m2))
    {
        printf("The maps m1 and m2 are not equal.\n");
    }
    
    range_t r_r;
    map_clear(pmap_m1);
    
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);

    //����map_t�а���ָ�����ݵ���������
    r_r = map_equal_range(pmap_m1, 2); //��������������ڵ���20��

    printf("The lower bound of the element with a key of 2 in the map m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_begin)));//30
    printf("The upper bound of the element with a key of 2 in the map m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(r_r.it_end))); //20

    //����map_t�д���ָ�����ݵĵ�һ�����ݵĵ�����
    it_m = map_upper_bound(pmap_m1, 2);
    printf("A direct call of upper_bound(2) gives %d, matching "
        "the second element of the range returned by equal_range(2).\n",
        *(int*)pair_second(iterator_get_pointer(it_m))); //30

    r_r = map_equal_range(pmap_m1, 4);
    /* If no match is found for the key, both elements of the range return end() */
    if(iterator_equal(r_r.it_begin, map_end(pmap_m1)) &&
        iterator_equal(r_r.it_end, map_end(pmap_m1)))
    {
        printf("The map m1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of map m1 with a key >= 40 is %d.\n",
            *(int*)pair_first(iterator_get_pointer(r_r.it_begin)));
    }

    map_clear(pmap_m1);
    
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 5, 50);
    map_insert(pmap_m1, ppair_p);
    
    //map_erase ɾ��ӳ����������ָ��������ȵ�����
    int t_count = map_erase(pmap_m1, 4); // <1, 10> <2, 20> <3, 30>  <5, 50> t_count = 1

    //map_erase_pos ɾ��ӳ��������ָ��λ�õ�����
    map_erase_pos(pmap_m1, iterator_next(map_begin(pmap_m1))); //<1, 10> <3, 30>  <5, 50>

    //map_erase_range ɾ��ӳ��������ָ���������������
    map_erase_range(pmap_m1, iterator_next(map_begin(pmap_m1)),
        iterator_prev(map_end(pmap_m1))); // <1, 10> <5, 50>

    //��map_t�в���ָ��������
    it_m = map_find(pmap_m1, 1);
    printf("The element of map m1 with a key of 1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));
    
    /* If no match is found for the key, end() is returned */
    it_m = map_find(pmap_m1, 4);
    if(iterator_equal(it_m, map_end(pmap_m1)))
    {
        printf("The map m1 doesn't have an element with a key of 4.\n");
    }
    
    map_clear(pmap_m1);
    map_clear(pmap_m2);

    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    map_insert(pmap_m1, ppair_p);

    //��map_t�в�������,�ɹ��󷵻�ָ������ݵĵ����������map_t�а����˸�������ô����ʧ�ܣ�����map_end()
    pair_make(ppair_p, 1, 10);
    it_m = map_insert(pmap_m1, ppair_p);
    if(!iterator_equal(it_m, map_end(pmap_m1)))
    {
        printf("The element 10 was inserted in m1 successfully.\n");
    }
    else
    {
        printf("The number 1 already exists in m1.\n");
    }

    // ��map_t�в���һ��ָ�������ݣ�ͬʱ����һ�������ݱ���������ʾλ�õ�������������λ��
    //����map_t���������Ͱ�������ݷ�����ʾλ���гɹ��󷵻�ָ������ݵĵ������������ʾλ�ò���ȷ�������
    //ʾλ�ã�(�ǲ���Ϊ�˼���)�����ݲ���ɹ��󷵻����ݵ�ʵ��λ�õ����������map_t�а����˸�������ô����ʧ�ܣ�����map_end()
    pair_make(ppair_p, 5, 50);
    map_insert_hint(pmap_m1, iterator_prev(map_end(pmap_m1)), ppair_p);
    printf("After the insertions, the key values of m1 =");
    for(it_m = map_begin(pmap_m1);
        !iterator_equal(it_m, map_end(pmap_m1));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
      //  <1, 10> <2, 20> <3, 30> <4, 40> <5, 50>
    printf("\n");

    pair_make(ppair_p, 10, 100);
    map_insert(pmap_m2, ppair_p);
    //����ָ������������
    map_insert_range(pmap_m2, iterator_next(map_begin(pmap_m1)),
        iterator_prev(map_end(pmap_m1)));
    printf("After the insertions, the key values of m2 =");
    for(it_m = map_begin(pmap_m2);
        !iterator_equal(it_m, map_end(pmap_m2));
        it_m = iterator_next(it_m))
    {
        printf(" <%d, %d>",
            *(int*)pair_first(iterator_get_pointer(it_m)),
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    //<2, 20> <3, 30> <4, 40> <10, 100>
    printf("\n");

    map_clear(pmap_m1);
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);
    
     //���map_t�е��ڻ��ߴ���ָ�����ݵĵ�һ�����ݵĵ�����
    it_m = map_lower_bound(pmap_m1, 2);
    printf("The first element of map m1 with a key of 2 is: %d.\n",// 20
        *(int*)pair_second(iterator_get_pointer(it_m)));

    //����map_t�д���ָ�����ݵĵ�һ�����ݵĵ�����
    it_m = map_upper_bound(pmap_m1, 2);
    printf("The first element of map m1 with a key greater than 2 is: %d.\n", // 30
        *(int*)pair_second(iterator_get_pointer(it_m)));
    
    /* If no match is found for this key, end() is returned */
    it_m = map_lower_bound(pmap_m1, 4);
    if(iterator_equal(it_m, map_end(pmap_m1)))
    {
        printf("The map m1 doesn't have an element with a key of 4.\n");
    }
    else
    {
        printf("The element of map m1 with key of 4 is: %d.\n",
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }

    //����map_t���ܹ���������ݸ�����������ֵ
    printf("The maximum possible length of the map is %u.\n",
        map_max_size(pmap_m1));

    //����map_t�б�������ݵ�����
    printf("The map length is %d.\n", map_size(pmap_m1));

    //��������map_t�е�����
    map_swap(pmap_m1, pmap_m2);

    binary_function_t bfun_vc = NULL;
    binary_function_t bfun_kc = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;
    map_iterator_t it_m1;  //map_t���͵ĵ���������
    map_iterator_t it_m2;  //map_t���͵ĵ���������

    map_destroy(pmap_m1);
    map_destroy(pmap_m2);
    pmap_m1 = create_map(int, int);
    pmap_m2 = create_map(int, int);

    map_init_ex(pmap_m1, fun_less_int);
    
    //����map_t�ļ��ȽϹ���
    bfun_kc = map_key_comp(pmap_m1);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m1.\n");
    }

    map_destroy(pmap_m1);

    map_init_ex(pmap_m2, fun_greater_int);

    bfun_kc = map_key_comp(pmap_m2);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m2.\n");
    }
    
    map_destroy(pmap_m2);
    
    pmap_m1 = create_map(int, int);
    map_init_ex(pmap_m1, fun_less_int);

    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 5);
    map_insert(pmap_m1, ppair_p);

    it_m1 = map_find(pmap_m1, 1);
    it_m2 = map_find(pmap_m1, 2);
    //����map_t�����ݵıȽϹ���,���������������ݱ���ıȽϹ�������Ǽ�����ֵ
    bfun_vc = map_value_comp(pmap_m1);

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
    map_destroy(pmap_m1);

    map_t* pmap_m0 = create_map(int, int);
    pmap_m1 = create_map(int, int);
    pmap_m2 = create_map(int, int);
    map_t* pmap_m3 = create_map(int, int);
    map_t* pmap_m4 = create_map(int, int);
    map_t* pmap_m5 = create_map(int, int);

    if(pmap_m0 == NULL || pmap_m1 == NULL || pmap_m2 == NULL || pmap_m3 == NULL || pmap_m4 == NULL || pmap_m5 == NULL)
    {
        return -1;
    }
    
    //map_init ��ʼ��һ���յ�ӳ������
    map_init(pmap_m0);

    //map_init_ex ʹ��ָ������������ʼ��һ���յ�ӳ������
    map_init_ex(pmap_m1, fun_less_int);
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    map_insert(pmap_m1, ppair_p);//10 20 30 40

    //map_init_ex ʹ��ָ������������ʼ��һ���յ�ӳ������
    map_init_ex(pmap_m2, fun_greater_int);
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m2, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m2, ppair_p);// 20 10

    //map_init_copy ʹ��һ��ӳ����������������ʼ����ǰӳ��������
    map_init_copy(pmap_m3, pmap_m1); //10 20 30 40 

    //map_init_copy_range ʹ��ָ�������������ʼ��ӳ��������
    map_init_copy_range(pmap_m4, map_begin(pmap_m1), iterator_advance(map_begin(pmap_m1), 2)); //10 20

    //map_init_copy_range_ex ʹ��ָ�������������ָ������������ʼ��ӳ��������
    map_init_copy_range_ex(pmap_m5, map_begin(pmap_m3), iterator_next(map_begin(pmap_m3)), fun_less_int);//10 

    map_destroy(pmap_m0);
    map_destroy(pmap_m1);
    map_destroy(pmap_m2);
    map_destroy(pmap_m3);
    map_destroy(pmap_m4);
    map_destroy(pmap_m5);
    pair_destroy(ppair_p);

    return 0;
}

