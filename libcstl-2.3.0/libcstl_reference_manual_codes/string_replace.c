/*
 * string_replace.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1a = create_string();
    string_t* pstr_str1b = create_string();
    string_t* pstr_str2a = create_string();
    string_t* pstr_str2b = create_string();
    string_t* pstr_str3a = create_string();
    string_t* pstr_str4a = create_string();
    string_t* pstr_str5a = create_string();
    string_t* pstr_str6a = create_string();
    string_t* pstr_str6b = create_string();
    string_t* pstr_str7a = create_string();
    string_t* pstr_str7b = create_string();
    string_t* pstr_str8a = create_string();
    string_t* pstr_str9a = create_string();
    string_t* pstr_str10a = create_string();
    string_t* pstr_str11a = create_string();
    string_t* pstr_str11b = create_string();

    if(pstr_str1a == NULL || pstr_str1b == NULL ||
       pstr_str2a == NULL || pstr_str2b == NULL ||
       pstr_str3a == NULL || pstr_str4a == NULL ||
       pstr_str5a == NULL || pstr_str6a == NULL ||
       pstr_str6b == NULL || pstr_str7a == NULL ||
       pstr_str7b == NULL || pstr_str8a == NULL ||
       pstr_str9a == NULL || pstr_str10a == NULL ||
       pstr_str11a == NULL || pstr_str11b == NULL)
    {
        return -1;
    }

    /* Replace part of the string with characters from a string */
    string_init_cstr(pstr_str1a, "AAAAAAAA");
    string_init_cstr(pstr_str1b, "BBB");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str1a));
    printf("The replace string is \"%s\".\n", string_c_str(pstr_str1b));
    string_replace(pstr_str1a, 1, 3, pstr_str1b);
    printf("The result string is \"%s\".\n", string_c_str(pstr_str1a));

    string_destroy(pstr_str1a);
    string_destroy(pstr_str1b);

    /* Replace part of the string with characters from part of a string */
    string_init_cstr(pstr_str2a, "AAAAAAAA");
    string_init_cstr(pstr_str2b, "BBB");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str2a));
    printf("The replace string is \"%s\".\n", string_c_str(pstr_str2b));
    string_replace_substring(pstr_str2a, 1, 3, pstr_str2b, 1, 2);
    printf("The result string is \"%s\".\n", string_c_str(pstr_str2a));

    string_destroy(pstr_str2a);
    string_destroy(pstr_str2b);

    /* Replace part of the string with characters from a c-string */
    string_init_cstr(pstr_str3a, "AAAAAAAA");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str3a));
    printf("The replace string is \"%s\".\n", "CCC");
    string_replace_cstr(pstr_str3a, 5, 3, "CCC");
    printf("The result string is \"%s\".\n", string_c_str(pstr_str3a));

    string_destroy(pstr_str3a);

    /* Replace part of the string with characters from part of a c-string */
    string_init_cstr(pstr_str4a, "AAAAAAAA");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str4a));
    printf("The replace string is \"%s\".\n", "CCC");
    string_replace_subcstr(pstr_str4a, 4, 3, "CCC", 1);
    printf("The result string is \"%s\".\n", string_c_str(pstr_str4a));

    string_destroy(pstr_str4a);

    /* Replace part of the string with characters */
    string_init_cstr(pstr_str5a, "AAAAAAAA");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str5a));
    printf("The replace character is '%c'.\n", 'C');
    string_replace_char(pstr_str5a, 1, 3, 4, 'C');
    printf("The result string is \"%s\".\n", string_c_str(pstr_str5a));

    string_destroy(pstr_str5a);

    /* Replace part of the string, delineated with iterator, with characters from a string */
    string_init_cstr(pstr_str6a, "AAAAAAAA");
    string_init_cstr(pstr_str6b, "BBB");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str6a));
    printf("The replace string is \"%s\".\n", string_c_str(pstr_str6b));
    string_range_replace(pstr_str6a, string_begin(pstr_str6a),
        iterator_next_n(string_begin(pstr_str6a), 3), pstr_str6b);
    printf("The result string is \"%s\".\n", string_c_str(pstr_str6a));

    string_destroy(pstr_str6a);
    string_destroy(pstr_str6b);

    /* Replace part of the string, delineated with iterator, with characters from part of a string */
    string_init_cstr(pstr_str7a, "AAAAAAAA");
    string_init_cstr(pstr_str7b, "BBB");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str7a));
    printf("The replace string is \"%s\".\n", string_c_str(pstr_str7b));
    string_range_replace_substring(pstr_str7a, string_begin(pstr_str7a),
        iterator_next_n(string_begin(pstr_str7a), 3), pstr_str7b, 1, 2);
    printf("The result string is \"%s\".\n", string_c_str(pstr_str7a));

    string_destroy(pstr_str7a);
    string_destroy(pstr_str7b);

    /* Replace part of the string, delineated with iterator, with characters from a c-string */
    string_init_cstr(pstr_str8a, "AAAAAAAA");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str8a));
    printf("The replace string is \"%s\".\n", "CCC");
    string_range_replace_cstr(pstr_str8a, iterator_next_n(string_begin(pstr_str8a), 5),
        string_end(pstr_str8a), "CCC");
    printf("The result string is \"%s\".\n", string_c_str(pstr_str8a));

    string_destroy(pstr_str8a);

    /* Replace part of the string, delineated with iterator, with characters from part of a c-string */
    string_init_cstr(pstr_str9a, "AAAAAAAA");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str9a));
    printf("The replace string is \"%s\".\n", "CCC");
    string_range_replace_subcstr(pstr_str9a, iterator_next_n(string_begin(pstr_str9a),4),
        iterator_next_n(string_begin(pstr_str9a), 7), "CCC", 1);
    printf("The result string is \"%s\".\n", string_c_str(pstr_str9a));

    string_destroy(pstr_str9a);

    /* Replace part of the string, delineated with iterator, with characters */
    string_init_cstr(pstr_str10a, "AAAAAAAA");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str10a));
    printf("The replace character is '%c'.\n", 'C');
    string_range_replace_char(pstr_str10a, iterator_next(string_begin(pstr_str10a)),
        iterator_next_n(string_begin(pstr_str10a), 4), 4, 'C');
    printf("The result string is \"%s\".\n", string_c_str(pstr_str10a));

    string_destroy(pstr_str10a);

    /* 
     * Replace part of the string, delineated with iterators,
     * with characters from a string delineated with iterators.
     */
    string_init_cstr(pstr_str11a, "OOOOOOOO");
    string_init_cstr(pstr_str11b, "PPPP");

    printf("The original string is \"%s\".\n", string_c_str(pstr_str11a));
    printf("The replace string is \"%s\".\n", string_c_str(pstr_str11b));
    string_replace_range(pstr_str11a, iterator_next(string_begin(pstr_str11a)),
        iterator_next_n(string_begin(pstr_str11a), 3), string_begin(pstr_str11b),
        iterator_next_n(string_begin(pstr_str11b), 2));
    printf("The result string is \"%s\".\n", string_c_str(pstr_str11a));

    string_destroy(pstr_str11a);
    string_destroy(pstr_str11b);

    return 0;
}
