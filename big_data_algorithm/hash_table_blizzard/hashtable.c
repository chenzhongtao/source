#ifdef __cplusplus
extern "C"{
#endif

//http://sfsrealm.hopto.org/inside_mopaq/chapter2.htm

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hashfn.h"

#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
extern uint32_t initcryptTable;

/*初始化hashtable*/
Hashtable* hashtable_init(uint32_t size){
    if (initcryptTable == 0)
    {
        prepareCryptTable();
        initcryptTable = 1;
    }
    Hashtable* hashtable = (Hashtable*)calloc(1, sizeof(Hashtable));
    hashtable->size = size;
    hashtable->item_size = 0;
    HashNode* head = (HashNode *)calloc(size, sizeof(HashNode));
    hashtable->head = head;
    return hashtable;
}

/*添加一个*/
void hashtable_put(Hashtable *hashtable, char* key, char* value){

    const uint32_t HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
    uint32_t nHash = HashString(key, HASH_OFFSET);
    uint32_t nHashA = HashString(key, HASH_A);
    uint32_t nHashB = HashString(key, HASH_B);
    uint32_t nHashStart = nHash % hashtable->size; 
    uint32_t nHashPos = nHashStart;

    HashNode *hashNode = hashtable->head + nHashPos;
    while (hashNode->bExists)
    {
        if (hashNode->nHashA == nHashA && hashNode->nHashB == nHashB)
            break;
        else
        {
            nHashPos = (nHashPos + 1) % nHash % hashtable->size;
            hashNode = hashtable->head + nHashPos;
        }
         
        if (nHashPos == nHashStart)
        {
            printf("The hash table is out\n");
            return;
        }
    }
    hashNode->bExists = 1;
    hashNode->nHashA = nHashA;
    hashNode->nHashB = nHashB;
    hashNode->key = key;
    hashNode->value = value;
    hashtable->item_size = hashtable->item_size + 1;
    return;
        
}

/*获取一个*/
HashNode * hashtable_get(Hashtable *hashtable, char* key){

    const uint32_t HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
    uint32_t nHash = HashString(key, HASH_OFFSET);
    uint32_t nHashA = HashString(key, HASH_A);
    uint32_t nHashB = HashString(key, HASH_B);
    uint32_t nHashStart = nHash % hashtable->size; 
    uint32_t nHashPos = nHashStart;

    HashNode *hashNode = hashtable->head + nHashPos;
    while (hashNode->bExists)
    {
        if (hashNode->nHashA == nHashA && hashNode->nHashB == nHashB)
            return hashNode;
        else
        {
            nHashPos = (nHashPos + 1) % nHash % hashtable->size;
            hashNode = hashtable->head + nHashPos;
        }
         
        if (nHashPos == nHashStart)
            break;
    }

    return NULL; //Error value
}



/*销毁*/
void hashtable_destroy(Hashtable *hashtable){
    free(hashtable->head);
    free(hashtable);
}

/*打印*/
void hashtable_print(Hashtable *hashtable){
    HashNode *head = hashtable->head;
    uint32_t index;
    for (index = 0; index < hashtable->size; index++)
    {
        printf("index:%d\t", index);
        if (head->key!=NULL)
        {
            printf("%s:%s\n", head->key, head->value);
        }
        head++;
    }
}

#ifdef __cplusplus
}
#endif