/*
 * string_erase.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_str1 = create_string();
    string_t* pstr_str2 = create_string();
    string_t* pstr_str3 = create_string();
    string_iterator_t it_str;

    if(pstr_str1 == NULL || pstr_str2 == NULL || pstr_str3 == NULL)
    {
        return -1;
    }

    /* Erasing a character pointed to by an iterator */
    string_init_cstr(pstr_str1, "Hello World");

    printf("The original string str1 is \"%s\".\n", string_c_str(pstr_str1));
    it_str = string_erase(pstr_str1, iterator_next_n(string_begin(pstr_str1), 5));
    printf("The first element after those removed is '%c'.\n",
        *(char*)iterator_get_pointer(it_str));
    printf("The modified string str1 is \"%s\".\n", string_c_str(pstr_str1));

    string_destroy(pstr_str1);

    /* Erasing a range demarcated by iterators */
    string_init_cstr(pstr_str2, "Hello World");

    printf("The original string str2 is \"%s\".\n", string_c_str(pstr_str2));
    it_str = string_erase_range(pstr_str2,
        iterator_next_n(string_begin(pstr_str2), 3),
        iterator_prev(string_end(pstr_str2)));
    printf("The first element after those removed is '%c'.\n",
        *(char*)iterator_get_pointer(it_str));
    printf("The modified string str2 is \"%s\".\n", string_c_str(pstr_str2));

    string_destroy(pstr_str2);

    /* Erasing a number of characters after a character */
    string_init_cstr(pstr_str3, "Hello computer");

    printf("The original string str3 is \"%s\".\n", string_c_str(pstr_str3));
    string_erase_substring(pstr_str3, 6, 8);
    printf("The modified string str3 is \"%s\".\n", string_c_str(pstr_str3));

    string_destroy(pstr_str3);

    return 0;
}
