/*
 * string_substr.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1 = create_string();
    string_t* pstr_sub1 = NULL;
    string_t* pstr_sub2 = NULL;

    if(pstr_str1 == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_str1, "Heterological paradoxes are persistent.");

    printf("The original string str1 is \"%s\".\n", string_c_str(pstr_str1));

    pstr_sub1 = string_substr(pstr_str1, 6, 7);
    printf("The substring1 copied is \"%s\".\n", string_c_str(pstr_sub1));

    pstr_sub2 = string_substr(pstr_str1, 0, NPOS);
    printf("The substring2 copied is \"%s\".\n", string_c_str(pstr_sub2));

    string_destroy(pstr_str1);
    string_destroy(pstr_sub1);
    string_destroy(pstr_sub2);

    return 0;
}
