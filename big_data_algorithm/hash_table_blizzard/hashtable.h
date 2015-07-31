#ifdef __cplusplus
extern "C"{
#endif

#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdint.h>

typedef struct HashNode{
    int nHashA;  
    int nHashB;  
    char bExists;
    char *key;
    char *value;
} HashNode;


typedef struct Hashtable{
    int32_t size;
    int32_t item_size;
    HashNode* head;
} Hashtable;


/*初始化*/
Hashtable* hashtable_init(uint32_t size);

/*添加一个*/
void hashtable_put(Hashtable *hashtable, char* key, char* value);

/*获取一个*/
HashNode * hashtable_get(Hashtable *hashtable, char* key);


/*销毁*/
void hashtable_destroy(Hashtable *hashtable);

/*打印*/
void hashtable_print(Hashtable *hashtable);

#endif

#ifdef __cplusplus
}
#endif

