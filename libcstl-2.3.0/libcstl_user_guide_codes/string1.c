/*
 * string1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstring.h>

int main(int argc, char* argv[])
{
    string_t* pstr_filename = create_string();
    string_t* pstr_basename = create_string();
    string_t* pstr_extname = create_string();
    string_t* pstr_tmpname = create_string();
    string_t* pstr_suffix = create_string();
    size_t t_index = 0;
    int i = 0;

    if(pstr_filename == NULL || pstr_basename == NULL ||
       pstr_extname == NULL || pstr_tmpname == NULL ||
       pstr_suffix == NULL)
    {
        return -1;
    }

    string_init(pstr_filename);
    string_init(pstr_basename);
    string_init(pstr_extname);
    string_init(pstr_tmpname);
    string_init_cstr(pstr_suffix, "tmp");

    for(i = 1; i < argc; ++i)
    {
        string_assign_cstr(pstr_filename, argv[i]);

        t_index = string_find_char(pstr_filename, '.', 0);
        if(t_index == NPOS)
        {
            string_assign(pstr_tmpname, pstr_filename);
            string_connect_char(pstr_tmpname, '.');
            string_connect(pstr_tmpname, pstr_suffix);
        }
        else
        {
            string_assign_substring(pstr_basename, pstr_filename, 0, t_index);
            string_assign_substring(pstr_extname, pstr_filename, t_index + 1, NPOS);
            string_assign(pstr_tmpname, pstr_filename);
            if(string_empty(pstr_extname))
            {
                string_append(pstr_tmpname, pstr_suffix);
            }
            else if(string_equal(pstr_extname, pstr_suffix))
            {
                string_replace_cstr(pstr_tmpname, t_index + 1,
                    string_size(pstr_extname), "xxx");
            }
            else
            {
                string_replace(pstr_tmpname, t_index + 1, NPOS, pstr_suffix);
            }
        }

        printf("%s => %s\n", string_c_str(pstr_filename), string_c_str(pstr_tmpname));
    }

    string_destroy(pstr_filename);
    string_destroy(pstr_basename);
    string_destroy(pstr_extname);
    string_destroy(pstr_tmpname);
    string_destroy(pstr_suffix);

    return 0;
}
