/*
 * string_reserve.c
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
    printf("The current size of original string is %u.\n", string_size(pstr_str1));
    printf("The capacity of original string is %u.\n", string_capacity(pstr_str1));

    string_reserve(pstr_str1, 40);
    printf("The string is \"%s\".\n", string_c_str(pstr_str1));
    printf("The current size of original string is %u.\n", string_size(pstr_str1));
    printf("The new capacity of original string is %u.\n", string_capacity(pstr_str1));

    string_reserve(pstr_str1, 0);
    printf("The string is \"%s\".\n", string_c_str(pstr_str1));
    printf("The current size of original string is %u.\n", string_size(pstr_str1));
    printf("The new capacity of original string is %u.\n", string_capacity(pstr_str1));

    string_destroy(pstr_str1);

    return 0;
}
