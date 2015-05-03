/*
 * string_empty.c
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

    string_init_cstr(pstr_str1, "Hello world");
    string_init(pstr_str2);

    printf("The original string str1 is \"%s\".\n", string_c_str(pstr_str1));
    if(string_empty(pstr_str1))
    {
        printf("The string str1 is empty.\n");
    }
    else
    {
        printf("The string str1 is not empty.\n");
    }

    if(string_empty(pstr_str2))
    {
        printf("The string str2 is empty.\n");
    }
    else
    {
        printf("The string str2 is not empty.\n");
    }

    string_destroy(pstr_str1);
    string_destroy(pstr_str2);

    return 0;
}
