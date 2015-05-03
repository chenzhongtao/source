/*
 * string_max_size.c
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

    printf("The original string str1 is \"%s\".\n", string_c_str(pstr_str1));
    printf("The current size of original string str1 is %d.\n", string_size(pstr_str1));
    printf("The current length of original string str1 is %d.\n", string_length(pstr_str1));
    printf("The capacity of original string str1 is %d.\n", string_capacity(pstr_str1));
    printf("The max_size of original string str1 is %u.\n", string_max_size(pstr_str1));

    string_erase_substring(pstr_str1, 6, 5);
    printf("The modified string str1 is \"%s\".\n", string_c_str(pstr_str1));
    printf("The current size of modified string str1 is %d.\n", string_size(pstr_str1));
    printf("The current length of modified string str1 is %d.\n", string_length(pstr_str1));
    printf("The capacity of modified string str1 is %d.\n", string_capacity(pstr_str1));
    printf("The max_size of modified string str1 is %u.\n", string_max_size(pstr_str1));

    string_destroy(pstr_str1);

    return 0;
}
