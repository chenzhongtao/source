/*
 * string_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1 = create_string();
    string_t* pstr_str2 = create_string();
    string_t* pstr_str3 = create_string();
    string_t* pstr_str4 = create_string();
    string_t* pstr_str5 = create_string();
    string_t* pstr_str6 = create_string();
    string_t* pstr_str7 = create_string();

    if(pstr_str1 == NULL || pstr_str2 == NULL || pstr_str3 == NULL ||
       pstr_str4 == NULL || pstr_str5 == NULL || pstr_str6 == NULL ||
       pstr_str7 == NULL);

    /* Create an empty string */
    string_init(pstr_str1);
    printf("The string str1 is \"%s\".\n", string_c_str(pstr_str1));

    /* Initialize string with const c string */
    string_init_cstr(pstr_str2, "libcstl");
    printf("The string str2 is \"%s\".\n", string_c_str(pstr_str2));

    /* Initialize string with sub const c string */
    string_init_subcstr(pstr_str3, "Hello Out There.", 5);
    printf("The string str3 is \"%s\".\n", string_c_str(pstr_str3));

    /* Initialize string with a number of characters of a specific value */
    string_init_char(pstr_str4, 5, '9');
    printf("The string str4 is \"%s\".\n", string_c_str(pstr_str4));

    /* Initialize string with another initialized string */
    string_init_copy(pstr_str5, pstr_str2);
    printf("The string str5 is \"%s\".\n", string_c_str(pstr_str5));

    /* Initialize string with sub string */
    string_init_copy_substring(pstr_str6, pstr_str2, 3, 4);
    printf("The string str6 is \"%s\".\n", string_c_str(pstr_str6));

    /* Initialize string with string range */
    string_init_copy_range(pstr_str7,
        iterator_next_n(string_begin(pstr_str2), 3), string_end(pstr_str2));
    printf("The string str7 is \"%s\".\n", string_c_str(pstr_str7));

    string_destroy(pstr_str1);
    string_destroy(pstr_str2);
    string_destroy(pstr_str3);
    string_destroy(pstr_str4);
    string_destroy(pstr_str5);
    string_destroy(pstr_str6);
    string_destroy(pstr_str7);

    return 0;
}
