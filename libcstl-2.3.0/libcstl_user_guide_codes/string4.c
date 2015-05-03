/*
 * string4.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <ctype.h>
#include <cstl/cstring.h>
#include <cstl/calgorithm.h>

static void _nocase_compare(const void* cpv_first,
    const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output =
        toupper(*(char*)cpv_first) == toupper(*(char*)cpv_second) ?
        true : false;
}

int main(int argc, char* argv[])
{
    string_t* pstr_s1 = create_string();
    string_t* pstr_s2 = create_string();
    string_iterator_t it_pos;

    if(pstr_s1 == NULL || pstr_s2 == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_s1, "This is a string");
    string_init_cstr(pstr_s2, "STRING");

    if(string_size(pstr_s1) == string_size(pstr_s2) &&
       algo_equal_if(string_begin(pstr_s1), string_end(pstr_s1),
            string_begin(pstr_s2), _nocase_compare))
    {
        printf("the strings are equal.\n");
    }
    else
    {
        printf("the strings are not equal.\n");
    }

    it_pos = algo_search_if(string_begin(pstr_s1), string_end(pstr_s1),
        string_begin(pstr_s2), string_end(pstr_s2), _nocase_compare);
    if(iterator_equal(it_pos, string_end(pstr_s1)))
    {
        printf("s2 is not a substring of s1.\n");
    }
    else
    {
        printf("\"%s\" is a substring of \"%s\" (at index %d).\n",
            string_c_str(pstr_s2), string_c_str(pstr_s1),
            iterator_distance(string_begin(pstr_s1), it_pos));
    }

    string_destroy(pstr_s1);
    string_destroy(pstr_s2);

    return 0;
}
