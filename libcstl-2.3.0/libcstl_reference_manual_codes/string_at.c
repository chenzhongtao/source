/*
 * string_at.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1 = create_string();

    if(pstr_str1 == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_str1, "Hello world");

    printf("The original string str1 is : \"%s\".\n", string_c_str(pstr_str1));

    printf("The character with an index of 6 in string str1 is %c.\n",
        *(char*)string_at(pstr_str1, 6));

    *(char*)string_at(pstr_str1, 6) = 'W';

    printf("After modifing, the string str1 is \"%s\".\n", string_c_str(pstr_str1));

    string_destroy(pstr_str1);

    return 0;
}
