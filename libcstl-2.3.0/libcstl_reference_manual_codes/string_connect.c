/*
 * string_connect.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1a = create_string();
    string_t* pstr_str1b = create_string();
    string_t* pstr_str2a = create_string();
    string_t* pstr_str3a = create_string();

    if(pstr_str1a == NULL || pstr_str1b == NULL ||
       pstr_str2a == NULL || pstr_str3a == NULL)
    {
        return -1;
    }

    /* Appending one string to another */
    string_init_cstr(pstr_str1a, "Hello ");
    string_init_cstr(pstr_str1b, "World");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str1a));
    string_connect(pstr_str1a, pstr_str1b);
    printf("The appended string is \"%s\".\n", string_c_str(pstr_str1a));

    string_destroy(pstr_str1a);
    string_destroy(pstr_str1b);

    /* Appending c-string to a string */
    string_init_cstr(pstr_str2a, "Hello ");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str2a));
    string_connect_cstr(pstr_str2a, "Out There");
    printf("The appended string is \"%s\".\n", string_c_str(pstr_str2a));

    string_destroy(pstr_str2a);

    /* Appending a single character to a string */
    string_init_cstr(pstr_str3a, "Hello");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str3a));
    string_connect_char(pstr_str3a, '!');
    printf("The appended string is \"%s\".\n", string_c_str(pstr_str3a));

    string_destroy(pstr_str3a);

    return 0;
}
