#ifdef __cplusplus
extern "C"{
#endif

/* 
 *bitmap的c语言实现 
 */  
 
#ifndef _BITMAP_H_   
#define _BITMAP_H_ 

#include <stdint.h>
  
/* 
 *功能：初始化bitmap 
 *参数： 
 *size：bitmap的大小，即bit位的个数 
 *start：起始值 
 *返回值：0表示失败，1表示成功 
 */  
int32_t bitmap_init(int32_t size, int32_t start);  
  
/* 
 *功能：将值index的对应位设为1 
 *index:要设的值 
 *返回值：0表示失败，1表示成功 
 */  
int32_t bitmap_set(int32_t index);  
  
/* 
 *功能：取bitmap第i位的值 
 *i：待取位 
 *返回值：-1表示失败，否则返回对应位的值 
 */  
int32_t bitmap_get(int32_t i);  
  
/* 
 *功能：返回index位对应的值 
 */  
int32_t bitmap_data(int32_t index);  
  
/*释放内存*/  
int32_t bitmap_free();  


#endif

#ifdef __cplusplus
}
#endif

