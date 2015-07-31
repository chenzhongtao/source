#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>   
#include "bitmap.h"   
  
int32_t main()  
{  
    int32_t a[] = {5,8,7,6,3,1,10,78,56,34,23,12,43,54,65,76,87,98,89,100};  
    int32_t i;  
    bitmap_init(100, 0);  
    for(i=0; i<20; i++)  
        bitmap_set(a[i]);  
    for(i=0; i<100; i++)  
    {  
        if(bitmap_get(i) > 0 )  
            printf("%d ", bitmap_data(i));  
    }  
    printf("/n");  
    bitmap_free();  
    return 0;  
}  


#ifdef __cplusplus
}
#endif