/*
 * priority_queue_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cqueue.h>
#include <cstl/cvector.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v5 = create_vector(int);
    priority_queue_t* ppq_pq1 = create_priority_queue(int);
    priority_queue_t* ppq_pq2 = create_priority_queue(int);
    priority_queue_t* ppq_pq3 = create_priority_queue(int);
    priority_queue_t* ppq_pq4 = create_priority_queue(int);
    priority_queue_t* ppq_pq5 = create_priority_queue(int);
    priority_queue_t* ppq_pq6 = create_priority_queue(int);
    vector_iterator_t it_v5;

    if(ppq_pq1 == NULL || ppq_pq2 == NULL || ppq_pq3 == NULL ||
       ppq_pq4 == NULL || ppq_pq5 == NULL || ppq_pq6 == NULL ||
       pvec_v5 == NULL)
    {
        return -1;
    }

    /* Create an empty priority_queue */
    priority_queue_init(ppq_pq1);
    printf("pq1 = ( ");
    while(!priority_queue_empty(ppq_pq1))
    {
        printf("%d ", *(int*)priority_queue_top(ppq_pq1));
        priority_queue_pop(ppq_pq1);
    }
    printf(")\n");

    /* Create an empty priority_queue and push 3 elements */
    priority_queue_init(ppq_pq2);
    priority_queue_push(ppq_pq2, 5);
    priority_queue_push(ppq_pq2, 15);
    priority_queue_push(ppq_pq2, 10);
    printf("pq2 = ( ");
    while(!priority_queue_empty(ppq_pq2))
    {
        printf("%d ", *(int*)priority_queue_top(ppq_pq2));
        priority_queue_pop(ppq_pq2);
    }
    printf(")\n");
    printf("After printing, pq2 has %d elements.\n", priority_queue_size(ppq_pq2));

    /* 
     * Create an empty priority_queue with specific comparison function
     * and push 3 elements.
     */
    priority_queue_init_ex(ppq_pq3, fun_greater_int);
    priority_queue_push(ppq_pq3, 2);
    priority_queue_push(ppq_pq3, 1);
    priority_queue_push(ppq_pq3, 3);
    printf("pq3 = ( ");
    while(!priority_queue_empty(ppq_pq3))
    {
        printf("%d ", *(int*)priority_queue_top(ppq_pq3));
        priority_queue_pop(ppq_pq3);
    }
    printf(")\n");

    /* Create an copy priority_queue form pq1 */
    priority_queue_push(ppq_pq1, 100);
    priority_queue_push(ppq_pq1, 200);
    priority_queue_init_copy(ppq_pq4, ppq_pq1);
    printf("pq4 = ( ");
    while(!priority_queue_empty(ppq_pq4))
    {
        printf("%d ", *(int*)priority_queue_top(ppq_pq4));
        priority_queue_pop(ppq_pq4);
    }
    printf(")\n");

    /* Create an auxiliary vector v5 to be used to initialize pq5 */
    vector_init(pvec_v5);
    vector_push_back(pvec_v5, 10);
    vector_push_back(pvec_v5, 30);
    vector_push_back(pvec_v5, 20);
    printf("v5 = ( ");
    for(it_v5 = vector_begin(pvec_v5);
        !iterator_equal(it_v5, vector_end(pvec_v5));
        it_v5 = iterator_next(it_v5))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v5));
    }
    printf(")\n");

    /* Create a priority_queue pq5 by copying the range v5[first, last) */
    priority_queue_init_copy_range(ppq_pq5, vector_begin(pvec_v5), vector_end(pvec_v5));
    printf("pq5 = ( ");
    while(!priority_queue_empty(ppq_pq5))
    {
        printf("%d ", *(int*)priority_queue_top(ppq_pq5));
        priority_queue_pop(ppq_pq5);
    }
    printf(")\n");

    /* 
     * Create a priority_queue pq6 by copying the range v5 [first, last) and
     * initialize with a comparison function greater.
     */
    priority_queue_init_copy_range_ex(ppq_pq6, vector_begin(pvec_v5),
        vector_end(pvec_v5), fun_greater_int);
    printf("pq6 = ( ");
    while(!priority_queue_empty(ppq_pq6))
    {
        printf("%d ", *(int*)priority_queue_top(ppq_pq6));
        priority_queue_pop(ppq_pq6);
    }
    printf(")\n");

    vector_destroy(pvec_v5);
    priority_queue_destroy(ppq_pq1);
    priority_queue_destroy(ppq_pq2);
    priority_queue_destroy(ppq_pq3);
    priority_queue_destroy(ppq_pq4);
    priority_queue_destroy(ppq_pq5);
    priority_queue_destroy(ppq_pq6);

    return 0;
}
