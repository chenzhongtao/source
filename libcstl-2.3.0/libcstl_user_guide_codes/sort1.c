/*
 * sort1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <string.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

typedef struct _tagperson
{
    char s_firstname[21];
    char s_lastname[21];
}person_t;

static void _print(const void* cpv_input, void* pv_output)
{
    printf("%s.%s ",
        ((person_t*)cpv_input)->s_firstname,
        ((person_t*)cpv_input)->s_lastname);
}

static void _person_sort_criterion(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    person_t* pt_first = (person_t*)cpv_first;
    person_t* pt_second = (person_t*)cpv_second;
    int n_result1 = strncmp(pt_first->s_firstname, pt_second->s_firstname, 21);
    int n_result2 = strncmp(pt_first->s_lastname, pt_second->s_lastname, 21);

    if(n_result1 < 0 || (n_result1 == 0 && n_result2 < 0))
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

int main(int argc, char* argv[])
{
    deque_t* pdeq_coll = NULL;
    person_t t_person;

    type_register(person_t, NULL, NULL, NULL, NULL);
    pdeq_coll = create_deque(person_t);
    if(pdeq_coll == NULL)
    {
        return -1;
    }

    deque_init(pdeq_coll);

    memset(t_person.s_firstname, '\0', 21);
    memset(t_person.s_lastname, '\0', 21);
    strcpy(t_person.s_firstname, "Jonh");
    strcpy(t_person.s_lastname, "right");
    deque_push_back(pdeq_coll, &t_person);
    memset(t_person.s_firstname, '\0', 21);
    memset(t_person.s_lastname, '\0', 21);
    strcpy(t_person.s_firstname, "Bill");
    strcpy(t_person.s_lastname, "killer");
    deque_push_back(pdeq_coll, &t_person);
    memset(t_person.s_firstname, '\0', 21);
    memset(t_person.s_lastname, '\0', 21);
    strcpy(t_person.s_firstname, "Jonh");
    strcpy(t_person.s_lastname, "sound");
    deque_push_back(pdeq_coll, &t_person);
    memset(t_person.s_firstname, '\0', 21);
    memset(t_person.s_lastname, '\0', 21);
    strcpy(t_person.s_firstname, "Bin");
    strcpy(t_person.s_lastname, "lee");
    deque_push_back(pdeq_coll, &t_person);
    memset(t_person.s_firstname, '\0', 21);
    memset(t_person.s_lastname, '\0', 21);
    strcpy(t_person.s_firstname, "Lee");
    strcpy(t_person.s_lastname, "bird");
    deque_push_back(pdeq_coll, &t_person);

    algo_for_each(deque_begin(pdeq_coll), deque_end(pdeq_coll), _print);
    printf("\n");

    algo_sort_if(deque_begin(pdeq_coll), deque_end(pdeq_coll), _person_sort_criterion);

    algo_for_each(deque_begin(pdeq_coll), deque_end(pdeq_coll), _print);
    printf("\n");

    deque_destroy(pdeq_coll);

    return 0;
}
