/*
 * string_swap.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1 = create_string();
    string_t* pstr_str2 = create_string();

    if(pstr_str1 == NULL || pstr_str2 == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_str1, "Tweedledee");
    string_init_cstr(pstr_str2, "Tweedledum");

    printf("Before swapping string str1 and str2:\n");
    printf("The str1 = \"%s\".\n", string_c_str(pstr_str1));
    printf("The str2 = \"%s\".\n", string_c_str(pstr_str2));

    string_swap(pstr_str1, pstr_str2);

    printf("After swapping string str1 and str2:\n");
    printf("The str1 = \"%s\".\n", string_c_str(pstr_str1));
    printf("The str2 = \"%s\".\n", string_c_str(pstr_str2));

    string_destroy(pstr_str1);
    string_destroy(pstr_str2);

    return 0;
}
