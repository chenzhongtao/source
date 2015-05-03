/*
 * string_insert.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1a = create_string();
    string_t* pstr_str2a = create_string();
    string_t* pstr_str3a = create_string();
    string_t* pstr_str3b = create_string();
    string_t* pstr_str4a = create_string();
    string_t* pstr_str4b = create_string();
    string_t* pstr_str5a = create_string();
    string_t* pstr_str6a = create_string();
    string_t* pstr_str7a = create_string();
    string_t* pstr_str8a = create_string();
    string_t* pstr_str8b = create_string();
    string_iterator_t it_str;

    if(pstr_str1a == NULL || pstr_str2a == NULL ||
       pstr_str3a == NULL || pstr_str3b == NULL ||
       pstr_str4a == NULL || pstr_str4b == NULL ||
       pstr_str5a == NULL || pstr_str6a == NULL ||
       pstr_str7a == NULL || pstr_str8a == NULL ||
       pstr_str8b == NULL)
    {
        return -1;
    }

    /* Inserting a character at aspecified position in the string */
    string_init_cstr(pstr_str1a, "ABCDEF");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str1a));
    string_insert(pstr_str1a, iterator_next_n(string_begin(pstr_str1a), 4), 'e');
    printf("The string with a character inserted is \"%s\".\n", string_c_str(pstr_str1a));

    string_destroy(pstr_str1a);

    /* Inserting a number of characters at aspecified position in the string */
    string_init_cstr(pstr_str2a, "ABCDHIJ");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str2a));
    string_insert_n(pstr_str2a, iterator_next_n(string_begin(pstr_str2a), 4), 3, 'e');
    printf("The string with a number of characters inserted is \"%s\".\n", string_c_str(pstr_str2a));

    string_destroy(pstr_str2a);

    /* Inserting a string at a given position */
    string_init_cstr(pstr_str3a, "Bye");
    string_init_cstr(pstr_str3b, "Good");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str3a));
    string_insert_string(pstr_str3a, 0, pstr_str3b);
    printf("The string with a string inserted at position 0 is \"%s\".\n", string_c_str(pstr_str3a));

    string_destroy(pstr_str3a);
    string_destroy(pstr_str3b);

    /* Inserting part of a string at a given position */
    string_init_cstr(pstr_str4a, "Good ");
    string_init_cstr(pstr_str4b, "Bye Bye Baby");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str4a));
    string_insert_substring(pstr_str4a, 5, pstr_str4b, 8, 4);
    printf("The string with part of a string inserted at position 5 is \"%s\".\n", string_c_str(pstr_str4a));

    string_destroy(pstr_str4a);
    string_destroy(pstr_str4b);

    /* Inserting a c-string at a given position */
    string_init_cstr(pstr_str5a, "way");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str5a));
    string_insert_cstr(pstr_str5a, 0, "a");
    printf("The string with a c-string inserted at position 0 is \"%s\".\n", string_c_str(pstr_str5a));

    string_destroy(pstr_str5a);

    /* Inserting part of a c-string at a given position */
    string_init_cstr(pstr_str6a, "Good");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str6a));
    string_insert_subcstr(pstr_str6a, 4, "Bye Bye Baby", 3);
    printf("The string with part of a c-string inserted at position 4 is \"%s\".\n", string_c_str(pstr_str6a));

    string_destroy(pstr_str6a);

    /* Inserting a number of characters at a given position */
    string_init_cstr(pstr_str7a, "The number is: .");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str7a));
    string_insert_char(pstr_str7a, 15, 3, '3');
    printf("The string with a number of characters inserted at position 15 is \"%s\".\n", string_c_str(pstr_str7a));

    string_destroy(pstr_str7a);

    /* Inserting a range at a specified position in the string */
    string_init_cstr(pstr_str8a, "ABCDHIJ");
    string_init_cstr(pstr_str8b, "abcdefgh");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str8a));
    string_insert_range(pstr_str8a, iterator_next_n(string_begin(pstr_str8a), 4),
        iterator_next_n(string_begin(pstr_str8b), 4), iterator_prev(string_end(pstr_str8b)));
    printf("The string with a range inserted at specified position is \"%s\".\n", string_c_str(pstr_str8a));

    string_destroy(pstr_str8a);
    string_destroy(pstr_str8b);

    return 0;
}
