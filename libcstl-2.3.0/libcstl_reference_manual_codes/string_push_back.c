/*
 * string_push_back.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1 = create_string();

    if(pstr_str1 == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_str1, "abc");

    printf("The original string str1 is \"%s\".\n", string_c_str(pstr_str1));

    string_push_back(pstr_str1, 'd');
    printf("The last chatacter of the modified string str1 is now '%c'.\n",
        *(char*)iterator_get_pointer(iterator_prev(string_end(pstr_str1))));

    printf("The modified string str1 is \"%s\".\n", string_c_str(pstr_str1));

    string_destroy(pstr_str1);

    return 0;
}
