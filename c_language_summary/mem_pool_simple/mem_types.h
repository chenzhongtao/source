#ifdef __cplusplus
extern "C"{
#endif

#ifndef __MEM_TYPES_H__
#define __MEM_TYPES_H__


enum gf_common_mem_types_ {
        gf_common_mt_mem_pool = 0,
        gf_common_mt_long,
        gf_common_mt_strdup,
        gf_common_mt_asprintf,
        gf_common_mt_end
};

#endif

#ifdef __cplusplus
}
#endif