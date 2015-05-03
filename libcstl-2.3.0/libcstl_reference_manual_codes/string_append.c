/*
 * string_append.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1a = create_string();
    string_t* pstr_str1b = create_string();
    string_t* pstr_str2a = create_string();
    string_t* pstr_str2b = create_string();
    string_t* pstr_str3a = create_string();
    string_t* pstr_str4a = create_string();
    string_t* pstr_str5a = create_string();
    string_t* pstr_str6a = create_string();
    string_t* pstr_str6b = create_string();

    if(pstr_str1a == NULL || pstr_str1b == NULL ||
       pstr_str2a == NULL || pstr_str2b == NULL ||
       pstr_str3a == NULL || pstr_str4a == NULL ||
       pstr_str5a == NULL || pstr_str6a == NULL ||
       pstr_str6b == NULL)
    {
        return -1;
    }

    /* Appending one string to another */
    string_init_cstr(pstr_str1a, "Hello ");
    string_init_cstr(pstr_str1b, "World.");

    string_append(pstr_str1a, pstr_str1b);
    printf("The appended string str1a is \"%s\".\n", string_c_str(pstr_str1a));

    string_destroy(pstr_str1a);
    string_destroy(pstr_str1b);

    /* Appending part of one string to another */
    string_init_cstr(pstr_str2a, "Hello ");
    string_init_cstr(pstr_str2b, "Wide World.");

    string_append_substring(pstr_str2a, pstr_str2b, 5, 5);
    printf("The appended string str2a is \"%s\".\n", string_c_str(pstr_str2a));

    string_destroy(pstr_str2a);
    string_destroy(pstr_str2b);

    /* Appending a c-string to a string */
    string_init_cstr(pstr_str3a, "Hello ");

    string_append_cstr(pstr_str3a, "World.");
    printf("The appended string str3a is \"%s\".\n", string_c_str(pstr_str3a));

    string_destroy(pstr_str3a);

    /* Appending part of a c-string to a string */
    string_init_cstr(pstr_str4a, "Hello ");

    string_append_subcstr(pstr_str4a, "Out There", 3);
    printf("The appended string str4a is \"%s\".\n", string_c_str(pstr_str4a));

    string_destroy(pstr_str4a);

    /* Appending characters to a string */
    string_init_cstr(pstr_str5a, "Hello ");

    string_append_char(pstr_str5a, 4, '!');
    printf("The appended string str5a is \"%s\".\n", string_c_str(pstr_str5a));

    string_destroy(pstr_str5a);

    /* Appending a range of one string to another */
    string_init_cstr(pstr_str6a, "Hello ");
    string_init_cstr(pstr_str6b, "Wide World ");

    string_append_range(pstr_str6a, iterator_next_n(string_begin(pstr_str6b), 5),
        iterator_prev(string_end(pstr_str6b)));
    printf("The appended string str6a is \"%s\".\n", string_c_str(pstr_str6a));

    string_destroy(pstr_str6a);
    string_destroy(pstr_str6b);

    return 0;
}
