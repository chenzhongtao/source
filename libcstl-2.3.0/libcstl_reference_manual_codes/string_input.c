/*
 * string_input.c
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

    string_init(pstr_str1);

    printf("The original string is: \"%s\".\n", string_c_str(pstr_str1));
    printf("Input a string (try input:\n\"Hello world\nMy world!\n\"\nand enter the end of input):\n");
    string_input(pstr_str1, stdin);
    printf("The input string is:\n\"%s\".\n", string_c_str(pstr_str1));

    string_destroy(pstr_str1);

    return 0;
}
