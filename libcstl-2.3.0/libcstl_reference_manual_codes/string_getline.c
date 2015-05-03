/*
 * string_getline.c
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

    printf("Enter a sentence:\n");
    string_getline(pstr_str1, stdin);
    printf("%s\n", string_c_str(pstr_str1));

    printf("Enter a sentence (use <space> as the delimiter):\n");
    string_getline_delimiter(pstr_str1, stdin, ' ');
    printf("%s\n", string_c_str(pstr_str1));

    string_destroy(pstr_str1);

    return 0;
}
