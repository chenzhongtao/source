#ifdef __cplusplus
extern "C"{
#endif
/*
【问题实例】

1)已知某个文件内包含一些电话号码，每个号码为8位数字，统计不同号码的个数。

8位最多99 999 999，大概需要99m个bit，大概10几m字节的内存即可。 
（可以理解为从0-99 999 999的数字，每个数字对应一个Bit位，所以只需要99M个
Bit==1.2MBytes，这样，就用了小小的1.2M左右的内存表示了所有的8位数的电话）

2)2.5亿个整数中找出不重复的整数的个数，内存空间不足以容纳这2.5亿个整数。

将bit-map扩展一下，用2bit表示一个数即可，0表示未出现，1表示出现一次，2
表示出现2次及以上，在遍历这些数的时候，如果对应位置的值是0，则将其置为1；
如果是1，将其置为2；如果是2，则保持不变。或者我们不用2bit来进行表示，我们
用两个bit-map即可模拟实现这个 2bit-map，都是一样的道理。

1、海量日志数据，提取出某日访问百度次数最多的那个IP。
此题，在我之前的一篇文章：“从头到尾彻底解析Hash表”算法里头有所提到，
当时给出的方案是：IP的数目还是有限的，最多2^32个，所以可以考虑使用hash
将ip直接存入内存，然后进行统计。再详细介绍下此方案：首先是这一天，并且
是访问百度的日志中的IP取出来，逐个写入到一个大文件中。注意到IP是32位的，
最多有个2^32个IP。同样可以采用映射的方法，比如模1000，把整个大文件映射为
1000个小文件，再找出每个小文中出现频率最大的IP（可以采用hash_map进行频率
统计，然后再找出频率最大的几个）及相应的频率。然后再在这1000个最大的IP中，
找出那个频率最大的IP，即为所求。
    

6、在2.5亿个整数中找出不重复的整数，注，内存不足以容纳这2.5亿个整数。

方案1：采用2-Bitmap（每个数分配2bit，00表示不存在，01表示出现一次，
10表示多次，11无意义）进行，共需内存内存，还可以接受。然后扫描这2.5
亿个整数，查看Bitmap中相对应位，如果是00变01，01变10，10保持不变。
所描完事后，查看bitmap，把对应位是01的整数输出即可。
方案2：也可采用与第1题类似的方法，进行划分小文件的方法。然后在小文
件中找出不重复的整数，并排序。然后再进行归并，注意去除重复的元素。
*/


#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>   
#include "bitmap.h"   
  
unsigned char *g_bitmap = NULL;  
int32_t g_size = 0;  
int32_t g_base = 0;  

 /* 
 *功能：初始化bitmap 
 *参数： 
 *size：bitmap的大小，即bit位的个数 
 *start：起始值 
 *返回值：0表示失败，1表示成功 
 */
int32_t bitmap_init(int32_t size, int32_t start)  
{  
    g_bitmap = (char *)malloc((size/8+1)*sizeof(char));  
    if(g_bitmap == NULL)  
        return 0;  
    g_base = start;  
    g_size = size/8+1;  
    memset(g_bitmap, 0x0, g_size);  
    return 1;  
}  


 /* 
 *功能：将值index的对应位设为1 
 *index:要设的值 
 *返回值：0表示失败，1表示成功 
 */
int32_t bitmap_set(int32_t index)  
{  
    int32_t quo = (index-g_base)/8 ;  
    int32_t remainder = (index-g_base)%8;  
    unsigned char x = (0x1<<remainder);  
    if( quo > g_size)  
        return 0;  
    g_bitmap[quo] |= x;  
    return 1;   
}  
  
int32_t bitmap_get(int32_t i)  
{  
    int32_t quo = (i)/8 ;  
    int32_t remainder = (i)%8;  
    unsigned char x = (0x1<<remainder);  
    unsigned char res;  
    if( quo > g_size)  
        return -1;  
    res = g_bitmap[quo] & x;  
    return res > 0 ? 1 : 0;   
}  
  
int32_t bitmap_data(int32_t index)  
{  
    return (index + g_base);  
}  
  
int32_t bitmap_free()  
{  
    free(g_bitmap);  
} 


#ifdef __cplusplus
}
#endif