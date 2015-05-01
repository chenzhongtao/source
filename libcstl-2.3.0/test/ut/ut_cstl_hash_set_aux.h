#ifndef _UT_CSTL_HASH_SET_AUX_H_
#define _UT_CSTL_HASH_SET_AUX_H_

UT_SUIT_DECLARATION(cstl_hash_set_aux)

/*
 * test _hash_set_get_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_hash_set_get_varg_value_auxiliary)
void test__hash_set_get_varg_value_auxiliary__null_hash_set_container(void** state);
void test__hash_set_get_varg_value_auxiliary__null_node(void** state);
/*void test__hash_set_get_varg_value_auxiliary__non_created_hash_set_containter(void** state);*/
void test__hash_set_get_varg_value_auxiliary__c_builtin(void** state);
void test__hash_set_get_varg_value_auxiliary__cstr(void** state);
void test__hash_set_get_varg_value_auxiliary__libcstl_builtin(void** state);
void test__hash_set_get_varg_value_auxiliary__user_define(void** state);
/*
 * test _hash_set_destroy_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_hash_set_destroy_varg_value_auxiliary)
void test__hash_set_destroy_varg_value_auxiliary__null_hash_set_container(void** state);
void test__hash_set_destroy_varg_value_auxiliary__null_varg(void** state);
/*void test__hash_set_destroy_varg_value_auxiliary__non_created(void** state);*/
void test__hash_set_destroy_varg_value_auxiliary__successfully(void** state);

#define UT_CSTL_HASH_SET_AUX_CASE\
    UT_SUIT_BEGIN(cstl_hash_set_aux, test__hash_set_get_varg_value_auxiliary__null_hash_set_container),\
    UT_CASE(test__hash_set_get_varg_value_auxiliary__null_node),\
    UT_CASE(test__hash_set_get_varg_value_auxiliary__c_builtin),\
    UT_CASE(test__hash_set_get_varg_value_auxiliary__cstr),\
    UT_CASE(test__hash_set_get_varg_value_auxiliary__libcstl_builtin),\
    UT_CASE(test__hash_set_get_varg_value_auxiliary__user_define),\
    UT_CASE_BEGIN(_hash_set_destroy_varg_value_auxiliary, test__hash_set_destroy_varg_value_auxiliary__null_hash_set_container),\
    UT_CASE(test__hash_set_destroy_varg_value_auxiliary__null_varg),\
    UT_CASE(test__hash_set_destroy_varg_value_auxiliary__successfully)

#endif /* _UT_CSTL_HASH_SET_AUX_H_ */

