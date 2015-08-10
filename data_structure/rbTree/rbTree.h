#ifdef __cplusplus
extern "C"{
#endif

/* 
 *bitmap��c����ʵ�� 
 */  
 
#ifndef _BITMAP_H_   
#define _BITMAP_H_ 

#include <stdint.h>
  
/* 
 *���ܣ���ʼ��bitmap 
 *������ 
 *size��bitmap�Ĵ�С����bitλ�ĸ��� 
 *start����ʼֵ 
 *����ֵ��0��ʾʧ�ܣ�1��ʾ�ɹ� 
 */  
int32_t bitmap_init(int32_t size, int32_t start);  
  
/* 
 *���ܣ���ֵindex�Ķ�Ӧλ��Ϊ1 
 *index:Ҫ���ֵ 
 *����ֵ��0��ʾʧ�ܣ�1��ʾ�ɹ� 
 */  
int32_t bitmap_set(int32_t index);  
  
/* 
 *���ܣ�ȡbitmap��iλ��ֵ 
 *i����ȡλ 
 *����ֵ��-1��ʾʧ�ܣ����򷵻ض�Ӧλ��ֵ 
 */  
int32_t bitmap_get(int32_t i);  
  
/* 
 *���ܣ�����indexλ��Ӧ��ֵ 
 */  
int32_t bitmap_data(int32_t index);  
  
/*�ͷ��ڴ�*/  
int32_t bitmap_free();  


#endif

#ifdef __cplusplus
}
#endif

