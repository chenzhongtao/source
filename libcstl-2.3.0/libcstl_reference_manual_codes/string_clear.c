/*
 * string_clear.c
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

    printf("The original string str1 is \"%s\".\n", string_c_str(pstr_str1));

    string_clear(pstr_str1);
    printf("The modified string str1 is \"%s\".\n", string_c_str(pstr_str1));

    if(iterator_equal(string_begin(pstr_str1), string_end(pstr_str1)))
    {
        printf("The string str1 is empty.\n");
    }
    else
    {
        printf("The string str1 is not empty.\n");
    }

    string_destroy(pstr_str1);

    return 0;
}
