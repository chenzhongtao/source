/*
 * string_find.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1a = create_string();
    string_t* pstr_str1b = create_string();
    string_t* pstr_str2a = create_string();
    string_t* pstr_str3a = create_string();
    string_t* pstr_str4a = create_string();
    size_t t_pos = 0;

    if(pstr_str1a == NULL || pstr_str1b == NULL ||
       pstr_str2a == NULL || pstr_str3a == NULL ||
       pstr_str4a == NULL)
    {
        return -1;
    }

    /* searching a string for a substring as specified by a string */
    string_init_cstr(pstr_str1a, "clearly this perfectly unclear.");
    string_init_cstr(pstr_str1b, "clear");

    printf("The original string str1a is \"%s\".\n", string_c_str(pstr_str1a));
    t_pos = string_find(pstr_str1a, pstr_str1b, 0);
    if(t_pos != NPOS)
    {
        printf("The index of the first element of \"clear\" in str1a is %u.\n", t_pos);
    }
    else
    {
        printf("the substring \"clear\" was not found in str1a.\n");
    }

    t_pos = string_find(pstr_str1a, pstr_str1b, 5);
    if(t_pos != NPOS)
    {
        printf("The index of the first element of \"clear\" after the 5th position in str1a is %u.\n", t_pos);
    }
    else
    {
        printf("the substring \"clear\" was not found in str1a.\n");
    }

    string_destroy(pstr_str1a);
    string_destroy(pstr_str1b);

    /* searching a string for a substring as specified by a c-string */
    string_init_cstr(pstr_str2a, "This is a sample string for this program.");

    printf("The original string str2a is \"%s\".\n", string_c_str(pstr_str2a));
    t_pos = string_find_cstr(pstr_str2a, "sample", 0);
    if(t_pos != NPOS)
    {
        printf("The index of the first element of \"sample\" in str2a is %u.\n", t_pos);
    }
    else
    {
        printf("the substring \"sample\" was not found in str2a.\n");
    }

    t_pos = string_find_cstr(pstr_str2a, "programming", 0);
    if(t_pos != NPOS)
    {
        printf("The index of the first element of \"programming\" in str2a is %u.\n", t_pos);
    }
    else
    {
        printf("the substring \"programming\" was not found in str2a.\n");
    }

    string_destroy(pstr_str2a);

    /* searching a string for a substring as specified by part of a c-string */
    string_init_cstr(pstr_str3a, "Let me make this perfectly clear.");

    printf("The original string str3a is \"%s\".\n", string_c_str(pstr_str3a));
    t_pos = string_find_subcstr(pstr_str3a, "this for you", 0, 4);
    if(t_pos != NPOS)
    {
        printf("The index of the first element of \"this\" in str3a is %u.\n", t_pos);
    }
    else
    {
        printf("the substring \"this\" was not found in str3a.\n");
    }

    t_pos = string_find_subcstr(pstr_str3a, "this for you", 0, NPOS);
    if(t_pos != NPOS)
    {
        printf("The index of the first element of \"this for you\" in str3a is %u.\n", t_pos);
    }
    else
    {
        printf("the substring \"this for you\" was not found in str3a.\n");
    }

    string_destroy(pstr_str3a);

    /* searching a string for a substring as specified by a single character */
    string_init_cstr(pstr_str4a, "Hello Everyone");

    printf("The original string str4a is \"%s\".\n", string_c_str(pstr_str4a));
    t_pos = string_find_char(pstr_str4a, 'e', 3);
    if(t_pos != NPOS)
    {
        printf("The index of the first element of 'e' after 3rd in str4a is %u.\n", t_pos);
    }
    else
    {
        printf("the substring 'e' was not found in str4a.\n");
    }

    t_pos = string_find_char(pstr_str4a, 'x', 0);
    if(t_pos != NPOS)
    {
        printf("The index of the first element of 'x' in str4a is %u.\n", t_pos);
    }
    else
    {
        printf("the substring 'x' was not found in str4a.\n");
    }

    string_destroy(pstr_str4a);

    return 0;
}
