#ifdef __cplusplus
extern "C"{
#endif

#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdint.h>

typedef struct HashNode{
    char* key;
    char* value;
    struct HashNode* next; //这里少了struct会报错 
} HashNode;


typedef struct Hashtable{
    int32_t size;
    int32_t item_size;
    HashNode* head;
} Hashtable;


/*初始化*/
Hashtable* hashtable_init(int32_t size);

/*添加一个*/
void hashtable_put(Hashtable *hashtable, char* key, char* value);

/*获取一个*/
char* hashtable_get(Hashtable *hashtable, char* key);

/*删除一个*/
void hashtable_remove(Hashtable *hashtable, char* key);

/*销毁*/
void hashtable_destroy(Hashtable *hashtable);

/*打印*/
void hashtable_print(Hashtable *hashtable);

#endif

#ifdef __cplusplus
}
#endif

