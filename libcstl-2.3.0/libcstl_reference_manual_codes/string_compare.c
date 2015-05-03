/*
 * string_compare.c
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
    string_t* pstr_str3b = create_string();
    string_t* pstr_str4a = create_string();
    string_t* pstr_str5a = create_string();
    string_t* pstr_str6a = create_string();
    int n_result = 0;

    if(pstr_str1a == NULL || pstr_str1b == NULL ||
       pstr_str2a == NULL || pstr_str2b == NULL ||
       pstr_str3a == NULL || pstr_str3b == NULL ||
       pstr_str4a == NULL || pstr_str5a == NULL ||
       pstr_str6a == NULL)
    {
        return -1;
    }

    /* Compares a string to a string */
    string_init_cstr(pstr_str1a, "CAB");
    string_init_cstr(pstr_str1b, "CAB");

    printf("The first string is \"%s\".\n", string_c_str(pstr_str1a));
    printf("The second string is \"%s\".\n", string_c_str(pstr_str1b));
    n_result = string_compare(pstr_str1a, pstr_str1b);
    if(n_result < 0)
    {
        printf("The first string is less than the second string.\n");
    }
    else if(n_result == 0)
    {
        printf("The first string is equal to the second string.\n");
    }
    else
    {
        printf("The first string is greater the second string.\n");
    }

    string_destroy(pstr_str1a);
    string_destroy(pstr_str1b);

    /* Compares part of a string to a string */
    string_init_cstr(pstr_str2a, "AACAB");
    string_init_cstr(pstr_str2b, "CAB");

    printf("The first string is \"%s\".\n", string_c_str(pstr_str2a));
    printf("The second string is \"%s\".\n", string_c_str(pstr_str2b));
    n_result = string_compare_substring_string(pstr_str2a, 2, 3, pstr_str2b);
    if(n_result < 0)
    {
        printf("The first string is less than the second string.\n");
    }
    else if(n_result == 0)
    {
        printf("The first string is equal to the second string.\n");
    }
    else
    {
        printf("The first string is greater the second string.\n");
    }

    string_destroy(pstr_str2a);
    string_destroy(pstr_str2b);

    /* Compares part of a string to part of a string */
    string_init_cstr(pstr_str3a, "AACAB");
    string_init_cstr(pstr_str3b, "DCABD");

    printf("The first string is \"%s\".\n", string_c_str(pstr_str3a));
    printf("The second string is \"%s\".\n", string_c_str(pstr_str3b));
    n_result = string_compare_substring_substring(pstr_str3a, 2, 3, pstr_str3b, 1, 3);
    if(n_result < 0)
    {
        printf("The first string is less than the second string.\n");
    }
    else if(n_result == 0)
    {
        printf("The first string is equal to the second string.\n");
    }
    else
    {
        printf("The first string is greater the second string.\n");
    }

    string_destroy(pstr_str3a);
    string_destroy(pstr_str3b);

    /* Compares a string to a c-string */
    string_init_cstr(pstr_str4a, "ABC");

    printf("The first string is \"%s\".\n", string_c_str(pstr_str4a));
    printf("The second string is \"%s\".\n", "DEF");
    n_result = string_compare_cstr(pstr_str4a, "DEF");
    if(n_result < 0)
    {
        printf("The first string is less than the second string.\n");
    }
    else if(n_result == 0)
    {
        printf("The first string is equal to the second string.\n");
    }
    else
    {
        printf("The first string is greater the second string.\n");
    }

    string_destroy(pstr_str4a);

    /* Compares part of a string to a c-string */
    string_init_cstr(pstr_str5a, "AACAB");

    printf("The first string is \"%s\".\n", string_c_str(pstr_str5a));
    printf("The second string is \"%s\".\n", "CAB");
    n_result = string_compare_substring_cstr(pstr_str5a, 2, 3, "CAB");
    if(n_result < 0)
    {
        printf("The first string is less than the second string.\n");
    }
    else if(n_result == 0)
    {
        printf("The first string is equal to the second string.\n");
    }
    else
    {
        printf("The first string is greater the second string.\n");
    }

    string_destroy(pstr_str5a);

    /* Compares part of a string to part of a c-string */
    string_init_cstr(pstr_str6a, "AACAB");

    printf("The first string is \"%s\".\n", string_c_str(pstr_str6a));
    printf("The second string is \"%s\".\n", "ACAB");
    n_result = string_compare_substring_subcstr(pstr_str6a, 1, 3, "ACAB", 3);
    if(n_result < 0)
    {
        printf("The first string is less than the second string.\n");
    }
    else if(n_result == 0)
    {
        printf("The first string is equal to the second string.\n");
    }
    else
    {
        printf("The first string is greater the second string.\n");
    }

    string_destroy(pstr_str6a);

    return 0;
}
