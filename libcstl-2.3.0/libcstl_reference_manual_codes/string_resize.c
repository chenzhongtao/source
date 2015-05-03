/*
 * string_resize.c
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

    string_init_cstr(pstr_str1, "Hello world");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str1));
    printf("The current size of string is %u.\n", string_size(pstr_str1));
    printf("The capacity of original string is %u.\n", string_capacity(pstr_str1));

    string_resize(pstr_str1, string_size(pstr_str1) + 2, '!');
    printf("The resized string is \"%s\".\n", string_c_str(pstr_str1));
    printf("The current size of string is %u.\n", string_size(pstr_str1));
    printf("The capacity of original string is %u.\n", string_capacity(pstr_str1));

    string_resize(pstr_str1, string_size(pstr_str1) + 20, 'x');
    printf("The resized string is \"%s\".\n", string_c_str(pstr_str1));
    printf("The current size of string is %u.\n", string_size(pstr_str1));
    printf("The capacity of original string is %u.\n", string_capacity(pstr_str1));

    string_resize(pstr_str1, string_size(pstr_str1) - 28, 'o');
    printf("The resized string is \"%s\".\n", string_c_str(pstr_str1));
    printf("The current size of string is %u.\n", string_size(pstr_str1));
    printf("The capacity of original string is %u.\n", string_capacity(pstr_str1));

    string_destroy(pstr_str1);

    return 0;
}
