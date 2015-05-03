/*
 * string3.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <ctype.h>
#include <cstl/cstring.h>
#include <cstl/calgorithm.h>

static void _to_lower(const void* cpv_input, void* pv_output)
{
    *(char*)pv_output = tolower(*(char*)cpv_input);
}

static void _to_upper(const void* cpv_input, void* pv_output)
{
    *(char*)pv_output = toupper(*(char*)cpv_input);
}

int main(int argc, char* argv[])
{
    string_t* pstr_s = create_string();

    if(pstr_s == NULL)
    {
        return -1;
    }

    string_init_cstr(pstr_s, "The tell of Office is 123456789.\n");
    printf("original: ");
    string_output(pstr_s, stdout);

    algo_transform(string_begin(pstr_s), string_end(pstr_s),
        string_begin(pstr_s), _to_lower);

    printf("lowered: ");
    string_output(pstr_s, stdout);

    algo_transform(string_begin(pstr_s), string_end(pstr_s),
        string_begin(pstr_s), _to_upper);

    printf("uppered: ");
    string_output(pstr_s, stdout);

    string_destroy(pstr_s);

    return 0;
}
