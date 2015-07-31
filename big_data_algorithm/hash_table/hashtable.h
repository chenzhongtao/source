#ifdef __cplusplus
extern "C"{
#endif

#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdint.h>

typedef struct HashNode{
    char* key;
    char* value;
    struct HashNode* next; //��������struct�ᱨ�� 
} HashNode;


typedef struct Hashtable{
    int32_t size;
    int32_t item_size;
    HashNode* head;
} Hashtable;


/*��ʼ��*/
Hashtable* hashtable_init(int32_t size);

/*���һ��*/
void hashtable_put(Hashtable *hashtable, char* key, char* value);

/*��ȡһ��*/
char* hashtable_get(Hashtable *hashtable, char* key);

/*ɾ��һ��*/
void hashtable_remove(Hashtable *hashtable, char* key);

/*����*/
void hashtable_destroy(Hashtable *hashtable);

/*��ӡ*/
void hashtable_print(Hashtable *hashtable);

#endif

#ifdef __cplusplus
}
#endif

