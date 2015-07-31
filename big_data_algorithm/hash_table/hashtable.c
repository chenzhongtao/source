#ifdef __cplusplus
extern "C"{
#endif

// http://blog.csdn.net/zmxiangde_88/article/details/8025541 �����վ���Կ�һ��


#include <stdint.h> /*������ uint64_t��*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hashfn.h"

#define TRUE 1
#define FALSE 0
#define true 1
#define false 0

/*��ʼ��hashtable*/
Hashtable* hashtable_init(int32_t size){
    Hashtable* hashtable = (Hashtable*)calloc(1, sizeof(Hashtable));
    hashtable->size = size;
    hashtable->item_size = 0;
    HashNode* head = (HashNode *)calloc(size, sizeof(HashNode));
    hashtable->head = head;
    return hashtable;
}

/*���һ��*/
void hashtable_put(Hashtable *hashtable, char* key, char* value){

    int32_t len = strlen(key); 
    int32_t index = hashfn(key, len) % hashtable->size;
    HashNode *hashNode = hashtable->head + index;

    while (true)
    {
        if (hashNode->key == NULL || *key == *(hashNode->key))
        {
            if (hashNode->key == NULL)
            {
                hashtable->item_size = hashtable->item_size + 1;
            }
            hashNode->key = key;
            hashNode->value = value; //������ھ�ֵ���滻
            return;
        }
        if (hashNode->next != NULL){
            hashNode = hashNode->next;
        }
        else{
            HashNode *newNode = (HashNode*)calloc(1, sizeof(HashNode));
            newNode->key = key;
            newNode->value = value;
            hashNode->next = newNode;
            hashtable->item_size = hashtable->item_size + 1;
            return;
        }
    }
}

/*��ȡһ��*/
char* hashtable_get(Hashtable *hashtable, char* key){

    int32_t len = strlen(key); 
    int32_t index = hashfn(key, len) % hashtable->size;
    HashNode *hashNode = hashtable->head + index;
    while (hashNode != NULL)
    {
        if (hashNode->key != NULL&&*key == *(hashNode->key))
        {
            return hashNode->value;
        }
        hashNode = hashNode->next;
    }
    return NULL;
}

/*ɾ��һ��*/
void hashtable_remove(Hashtable *hashtable, char* key){

    int32_t len = strlen(key); 
    int32_t index = hashfn(key, len) % hashtable->size;
    HashNode *hashNode = hashtable->head + index;
    HashNode *temp = hashNode;
    while (hashNode != NULL)
    {
        if (*key == *(hashNode->key))
        {
            if ((hashtable->head + index) == hashNode)
            {
                hashNode->key = NULL;
                hashNode->value = NULL;
            }
            else
            {
                temp->next = hashNode->next;
                free(hashNode);
            }
            hashtable->item_size = hashtable->item_size - 1;
            return;
        }
        temp = hashNode;
        hashNode = hashNode->next;
    }
    return;
}


/*����*/
void hashtable_destroy(Hashtable *hashtable){
    HashNode *head = hashtable->head;
    int32_t index;
    for (index = 0; index < hashtable->size; index++)
    {
        HashNode *next = head->next;
        while (next != NULL)
        {
            HashNode *temp = next;
            next = next->next;
            free(temp);
        }
        head++;
    }
    free(hashtable->head);
    free(hashtable);
}

/*��ӡ*/
void hashtable_print(Hashtable *hashtable){
    HashNode *head = hashtable->head;
    int32_t index;
    for (index = 0; index < hashtable->size; index++)
    {
        printf("index:%d\t", index);
        if (head->key!=NULL)
        {
            printf("%s:%s\t", head->key, head->value);
        }

        HashNode *next = head->next;
        while (next != NULL)
        {
            if (next->key != NULL)
            {
                printf("%s:%s\t", next->key, next->value);
            }
            next = next->next;
        }
        printf("\n");
        head++;
    }
}

#ifdef __cplusplus
}
#endif