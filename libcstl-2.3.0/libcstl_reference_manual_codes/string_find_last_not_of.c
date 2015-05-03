/*
 * string_find_last_not_of.c
 * compile with : -lcstl
 */

#include <string.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1a = create_string();
    string_t* pstr_str1b = create_string();
    string_t* pstr_str1c = create_string();
    string_t* pstr_str2a = create_string();
    string_t* pstr_str3a = create_string();
    string_t* pstr_str4a = create_string();
    size_t t_pos = 0;

    if(pstr_str1a == NULL || pstr_str1b == NULL || pstr_str1c == NULL ||
       pstr_str2a == NULL || pstr_str3a == NULL || pstr_str4a == NULL)
    {
        return -1;
    }

    /* Searching a string for a substring as specified by a string */
    string_init_cstr(pstr_str1a, "12-ab-12-ab");
    string_init_cstr(pstr_str1b, "b-a");
    string_init_cstr(pstr_str1c, "12");

    printf("The original string str1a is \"%s\".\n", string_c_str(pstr_str1a));
    t_pos = string_find_last_not_of(pstr_str1a, pstr_str1b, 5);
    if(t_pos != NPOS)
    {
        printf("The index of the last non occurrence of an element of 'b-a' in str1a before the 5th position is %u.\n", t_pos);
    }
    else
    {
        printf("Elements other than those in the substring 'b-a' were not found in the string str1a.\n");
    }

    t_pos = string_find_last_not_of(pstr_str1a, pstr_str1c, NPOS);
    if(t_pos != NPOS)
    {
        printf("The index of the last non occurrence of an element of '12' in str1a position is %u.\n", t_pos);
    }
    else
    {
        printf("Elements other than those in the substring '12' were not found in the string str1a.\n");
    }

    string_destroy(pstr_str1a);
    string_destroy(pstr_str1b);
    string_destroy(pstr_str1c);

    /* Searching a string for a substring as specified by a c-string */
    string_init_cstr(pstr_str2a, "BBB-111");

    printf("The original string str2a is \"%s\".\n", string_c_str(pstr_str2a));
    t_pos = string_find_last_not_of_cstr(pstr_str2a, "B1", 6);
    if(t_pos != NPOS)
    {
        printf("The index of the last non occurrence of an element of 'B1' in str2a before the 6th position is %u.\n", t_pos);
    }
    else
    {
        printf("Elements other than those in the substring 'B1' were not found in the string str2a.\n");
    }

    t_pos = string_find_last_not_of_cstr(pstr_str2a, "B-1", NPOS);
    if(t_pos != NPOS)
    {
        printf("The index of the last non occurrence of an element of 'B-1' in str2a position is %u.\n", t_pos);
    }
    else
    {
        printf("Elements other than those in the substring 'B-1' were not found in the string str2a.\n");
    }

    string_destroy(pstr_str2a);

    /* Searching a string for a substring as specified by part of a c-string */
    string_init_cstr(pstr_str3a, "444-555-GGG");

    printf("The original string str3a is \"%s\".\n", string_c_str(pstr_str3a));
    t_pos = string_find_last_not_of_cstr(pstr_str3a, "45G", NPOS);
    if(t_pos != NPOS)
    {
        printf("The index of the last non occurrence of an element of '45G' in str3a is %u.\n", t_pos);
    }
    else
    {
        printf("Elements other than those in the substring '45G' were not found in the string str3a.\n");
    }

    t_pos = string_find_last_not_of_subcstr(pstr_str3a, "45G", 6, t_pos - 1);
    if(t_pos != NPOS)
    {
        printf("The index of the last non occurrence of an element of '45G' in str3a position is %u.\n", t_pos);
    }
    else
    {
        printf("Elements other than those in the substring '45G' were not found in the string str3a.\n");
    }

    string_destroy(pstr_str3a);

    /* Searching a string for a substring as specified by a single character */
    string_init_cstr(pstr_str4a, "dddd-1dd4-abdd");

    printf("The original string str4a is \"%s\".\n", string_c_str(pstr_str4a));
    t_pos = string_find_last_not_of_char(pstr_str4a, 'd', 7);
    if(t_pos != NPOS)
    {
        printf("The index of the last non occurrence of an element of 'd' in str4a is %u.\n", t_pos);
    }
    else
    {
        printf("Elements other than those in the substring 'd' were not found in the string str4a.\n");
    }

    t_pos = string_find_last_not_of_char(pstr_str4a, 'x', NPOS);
    if(t_pos != NPOS)
    {
        printf("The index of the last non occurrence of an element of 'x' in str4a position is %u.\n", t_pos);
    }
    else
    {
        printf("Elements other than those in the substring 'x' were not found in the string str4a.\n");
    }

    string_destroy(pstr_str4a);

    return 0;
}
