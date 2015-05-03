/*
 * string_less.c
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
    string_init_cstr(pstr_str1a, "strict");
    string_init_cstr(pstr_str1b, "strum");

    printf("The string str1a = \"%s\".\n", string_c_str(pstr_str1a));
    printf("The string str1b = \"%s\".\n", string_c_str(pstr_str1b));
    if(string_less(pstr_str1a, pstr_str1b))
    {
        printf("The string str1a is less than the string str1b.\n");
    }
    else
    {
        printf("The string str1a is not less than the string str1b.\n");
    }

    string_destroy(pstr_str1a);
    string_destroy(pstr_str1b);

    /* Comparsion between string and c-string */
    string_init_cstr(pstr_str2a, "strict");

    printf("The string str2a = \"%s\".\n", string_c_str(pstr_str2a));
    printf("The c-string = \"%s\".\n", "strict");
    if(string_less_cstr(pstr_str2a, "strict"))
    {
        printf("The string str2a is less than the c-string.\n");
    }
    else
    {
        printf("The string str2a is not less than the c-string.\n");
    }

    string_destroy(pstr_str2a);

    return 0;
}
