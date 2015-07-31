#ifdef __cplusplus
extern "C"{
#endif
/*
������ʵ����

1)��֪ĳ���ļ��ڰ���һЩ�绰���룬ÿ������Ϊ8λ���֣�ͳ�Ʋ�ͬ����ĸ�����

8λ���99 999 999�������Ҫ99m��bit�����10��m�ֽڵ��ڴ漴�ɡ� 
���������Ϊ��0-99 999 999�����֣�ÿ�����ֶ�Ӧһ��Bitλ������ֻ��Ҫ99M��
Bit==1.2MBytes��������������СС��1.2M���ҵ��ڴ��ʾ�����е�8λ���ĵ绰��

2)2.5�ڸ��������ҳ����ظ��������ĸ������ڴ�ռ䲻����������2.5�ڸ�������

��bit-map��չһ�£���2bit��ʾһ�������ɣ�0��ʾδ���֣�1��ʾ����һ�Σ�2
��ʾ����2�μ����ϣ��ڱ�����Щ����ʱ�������Ӧλ�õ�ֵ��0��������Ϊ1��
�����1��������Ϊ2�������2���򱣳ֲ��䡣�������ǲ���2bit�����б�ʾ������
������bit-map����ģ��ʵ����� 2bit-map������һ���ĵ���

1��������־���ݣ���ȡ��ĳ�շ��ʰٶȴ��������Ǹ�IP��
���⣬����֮ǰ��һƪ���£�����ͷ��β���׽���Hash���㷨��ͷ�����ᵽ��
��ʱ�����ķ����ǣ�IP����Ŀ�������޵ģ����2^32�������Կ��Կ���ʹ��hash
��ipֱ�Ӵ����ڴ棬Ȼ�����ͳ�ơ�����ϸ�����´˷�������������һ�죬����
�Ƿ��ʰٶȵ���־�е�IPȡ���������д�뵽һ�����ļ��С�ע�⵽IP��32λ�ģ�
����и�2^32��IP��ͬ�����Բ���ӳ��ķ���������ģ1000�����������ļ�ӳ��Ϊ
1000��С�ļ������ҳ�ÿ��С���г���Ƶ������IP�����Բ���hash_map����Ƶ��
ͳ�ƣ�Ȼ�����ҳ�Ƶ�����ļ���������Ӧ��Ƶ�ʡ�Ȼ��������1000������IP�У�
�ҳ��Ǹ�Ƶ������IP����Ϊ����
    

6����2.5�ڸ��������ҳ����ظ���������ע���ڴ治����������2.5�ڸ�������

����1������2-Bitmap��ÿ��������2bit��00��ʾ�����ڣ�01��ʾ����һ�Σ�
10��ʾ��Σ�11�����壩���У������ڴ��ڴ棬�����Խ��ܡ�Ȼ��ɨ����2.5
�ڸ��������鿴Bitmap�����Ӧλ�������00��01��01��10��10���ֲ��䡣
�������º󣬲鿴bitmap���Ѷ�Ӧλ��01������������ɡ�
����2��Ҳ�ɲ������1�����Ƶķ��������л���С�ļ��ķ�����Ȼ����С��
�����ҳ����ظ���������������Ȼ���ٽ��й鲢��ע��ȥ���ظ���Ԫ�ء�
*/


#include <stdint.h> /*������ uint64_t��*/
#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>   
#include "bitmap.h"   
  
unsigned char *g_bitmap = NULL;  
int32_t g_size = 0;  
int32_t g_base = 0;  

 /* 
 *���ܣ���ʼ��bitmap 
 *������ 
 *size��bitmap�Ĵ�С����bitλ�ĸ��� 
 *start����ʼֵ 
 *����ֵ��0��ʾʧ�ܣ�1��ʾ�ɹ� 
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
 *���ܣ���ֵindex�Ķ�Ӧλ��Ϊ1 
 *index:Ҫ���ֵ 
 *����ֵ��0��ʾʧ�ܣ�1��ʾ�ɹ� 
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