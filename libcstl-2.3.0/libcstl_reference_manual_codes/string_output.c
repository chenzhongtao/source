/*
 * string_output.c
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

    string_init_cstr(pstr_str1, "Hello! This is the insertion operator.");

    string_output(pstr_str1, stdout);
    printf("\n");

    string_destroy(pstr_str1);

    return 0;
}
