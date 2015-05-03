/*
 * string_copy.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1 = create_string();
    char ac_array1[20] = {'\0'};
    char ac_array2[10] = {'\0'};
    size_t t_copy = 0;

    if(pstr_str1 == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_str1, "Hello world");

    printf("The original string str1 is \"%s\".\n", string_c_str(pstr_str1));

    t_copy = string_copy(pstr_str1, ac_array1, 15, 0);
    printf("The number of copied character in array1 is %u.\n", t_copy);
    printf("The copied characters array1 is \"%s\".\n", ac_array1);

    t_copy = string_copy(pstr_str1, ac_array2, 5, 6);
    printf("The number of copied character in array2 is %u.\n", t_copy);
    printf("The copied characters array2 is \"%s\".\n", ac_array2);

    string_destroy(pstr_str1);

    return 0;
}
