/*
 * string_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1a = create_string();
    string_t* pstr_str1b = create_string();
    string_t* pstr_str2a = create_string();

    if(pstr_str1a == NULL || pstr_str1b == NULL || pstr_str2a == NULL)
    {
        return -1;
    }

    /* Comparsion between string and string */
    string_init_cstr(pstr_str1a, "pluck");
    string_init_cstr(pstr_str1b, "strum");

    printf("The string str1a = \"%s\".\n", string_c_str(pstr_str1a));
    printf("The string str1b = \"%s\".\n", string_c_str(pstr_str1b));
    if(string_equal(pstr_str1a, pstr_str1b))
    {
        printf("The strings str1a and str1b are equal.\n");
    }
    else
    {
        printf("The strings str1a and str1b are not equal.\n");
    }

    string_destroy(pstr_str1a);
    string_destroy(pstr_str1b);

    /* Comparsion between string and c-string */
    string_init_cstr(pstr_str2a, "pluck");

    printf("The string str2a = \"%s\".\n", string_c_str(pstr_str2a));
    printf("The c-string = \"%s\".\n", "pluck");
    if(string_equal_cstr(pstr_str2a, "pluck"))
    {
        printf("The strings str2a and c-string are equal.\n");
    }
    else
    {
        printf("The strings str2a and c-string are not equal.\n");
    }

    string_destroy(pstr_str2a);

    return 0;
}
