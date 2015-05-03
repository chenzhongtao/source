/*
 * string_data.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1 = create_string();
    const char* s_str = NULL;

    if(pstr_str1 == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_str1, "Hello world");

    printf("The original string str1 is \"%s\".\n",
        string_data(pstr_str1));
    printf("The length of the string str1 is %d.\n",
        string_length(pstr_str1));

    s_str = string_data(pstr_str1);
    printf("The c-style string s_str is \"%s\".\n", s_str);
    printf("The length of c-style string s_str is %d.\n", strlen(s_str));

    string_destroy(pstr_str1);

    return 0;
}
