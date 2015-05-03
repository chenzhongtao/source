/*
 * string2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_delims = create_string();
    string_t* pstr_line = create_string();

    if(pstr_delims == NULL || pstr_line == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_delims, " \t,.;");
    string_init(pstr_line);

    while(string_getline(pstr_line, stdin))
    {
        size_t t_begin = 0;
        size_t t_end = 0;
        int i = 0;

        t_begin = string_find_first_not_of(pstr_line, pstr_delims, 0);
        while(t_begin != NPOS)
        {
            t_end = string_find_first_of(pstr_line, pstr_delims, t_begin);
            if(t_end == NPOS)
            {
                t_end = string_length(pstr_line);
            }

            for(i = t_end - 1; i >= (int)t_begin; --i)
            {
                printf("%c", *string_at(pstr_line, i));
            }
            printf(" ");

            t_begin = string_find_first_not_of(pstr_line, pstr_delims, t_end);
        }
        printf("\n");
    }

    string_destroy(pstr_delims);
    string_destroy(pstr_line);

    return 0;
}
