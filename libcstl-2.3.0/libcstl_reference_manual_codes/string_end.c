/*
 * string_end.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1 = create_string();
    string_t* pstr_str2 = create_string();
    string_iterator_t it_str;
    char c_last;

    if(pstr_str1 == NULL || pstr_str2 == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_str1, "No way out.");
    string_init(pstr_str2);

    it_str = string_end(pstr_str1);
    it_str = iterator_prev_n(it_str, 2);
    printf("The last character of the string str1 is: '%c'.\n",
        *(char*)iterator_get_pointer(it_str));
    printf("The full original string str1 is: \"%s\".\n",
        string_c_str(pstr_str1));

    c_last = 'T';
    iterator_set_value(it_str, &c_last);
    printf("The last character of the modified string str1 is: '%c'.\n",
        *(char*)iterator_get_pointer(it_str));
    printf("The full modified string str1 is: \"%s\".\n",
        string_c_str(pstr_str1));

    if(iterator_equal(string_begin(pstr_str2), string_end(pstr_str2)))
    {
        printf("The string str2 is empty.\n");
    }
    else
    {
        printf("The string str2 is not empty.\n");
    }

    string_destroy(pstr_str1);
    string_destroy(pstr_str2);

    return 0;
}
