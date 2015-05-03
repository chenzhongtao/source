/*
 * string5.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    string_t* pstr_hello = create_string();
    string_t* pstr_s = create_string();
    string_iterator_t it_pos;

    if(pstr_hello == NULL || pstr_s == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_hello, "Hello, how are you?");
    string_init_copy_range(pstr_s,
        string_begin(pstr_hello), string_end(pstr_hello));

    for(it_pos = string_begin(pstr_s);
        !iterator_equal(it_pos, string_end(pstr_s));
        it_pos = iterator_next(it_pos))
    {
        printf("%c", *(char*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_reverse(string_begin(pstr_s), string_end(pstr_s));
    printf("reverse: %s\n", string_c_str(pstr_s));

    algo_sort(string_begin(pstr_s), string_end(pstr_s));
    printf("ordered: %s\n", string_c_str(pstr_s));

    string_erase_range(pstr_s,
        algo_unique(string_begin(pstr_s), string_end(pstr_s)),
        string_end(pstr_s));
    printf("uniqued: %s\n", string_c_str(pstr_s));

    string_destroy(pstr_hello);
    string_destroy(pstr_s);

    return 0;
}
