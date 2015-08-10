#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdlib.h>

#include "hashfn.h"

#define get16bits(d) (*((const uint16_t *) (d)))

#define DM_DELTA 0x9E3779B9
#define DM_FULLROUNDS 10        /* 32 is overkill, 16 is strong crypto */
#define DM_PARTROUNDS 6         /* 6 gets complete mixing */


uint32_t
ReallySimpleHash (char *s, int32_t len)
{
        uint32_t        hash = 0;
        for (;len > 0; len--)
                hash ^= (char)s[len];

        return hash;
}

/*
  This is apparently the "fastest hash function for strings".
  Written by Paul Hsieh <http://www.azillionmonkeys.com/qed/hash.html>
*/

/* In any case make sure, you return 1 */

uint32_t SuperFastHash (const char * s, int32_t len) {
        uint32_t hash = len, tmp;
        int32_t rem;

        if (len <= 1 || s == NULL) return 1;

        rem = len & 3;
        len >>= 2;

        /* Main loop */
        for (;len > 0; len--) {
                hash  += get16bits (s);
                tmp    = (get16bits (s+2) << 11) ^ hash;
                hash   = (hash << 16) ^ tmp;
                s  += 2*sizeof (uint16_t);
                hash  += hash >> 11;
        }

        /* Handle end cases */
        switch (rem) {
        case 3: hash += get16bits (s);
                hash ^= hash << 16;
                hash ^= s[sizeof (uint16_t)] << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (s);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += *s;
                hash ^= hash << 10;
                hash += hash >> 1;
        }

        /* Force "avalanching" of final 127 bits */
        hash ^= hash << 3;
        hash += hash >> 5;
        hash ^= hash << 4;
        hash += hash >> 17;
        hash ^= hash << 25;
        hash += hash >> 6;

        return hash;
}


uint32_t ELFHash(const char *s, int32_t len)
{  
    const unsigned char *name = (const unsigned char *)s;  
    unsigned long h = 0, g;  
    int i;  
  
    for(i=0;i<len;i++)  
    {  
        h = (h << 4) + (unsigned long)(name[i]); //hash左移4位，当前字符ASCII存入hash    
        if ((g = (h & 0xF0000000UL))!=0)       
            h ^= (g >> 24);  
        h &= ~g;  //清空28-31位。   
    }  
  
    return (int)h;  
} 

/****************\
| Hash Functions |
\****************/

unsigned int RSHash(unsigned char *str, unsigned int len)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}

unsigned int JSHash(unsigned char *str, unsigned int len)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}

unsigned int PJWHash(unsigned char *str, unsigned int len)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash              = 0;
   unsigned int test              = 0;
   unsigned int i                 = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (hash << OneEighth) + (*str);

      if((test = hash & HighBits)  != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}

unsigned int SDBMHash(unsigned char *str, unsigned int len)
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}

unsigned int DJBHash(unsigned char *str, unsigned int len)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}

unsigned int DEKHash(unsigned char *str, unsigned int len)
{
   unsigned int hash = len;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
   }
   return hash;
}

unsigned int FNVHash(unsigned char *str, unsigned int len)
{
   const unsigned int fnv_prime = 0x811C9DC5;
   unsigned int hash      = 0;
   unsigned int i         = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash *= fnv_prime;
      hash ^= (*str);
   }

   return hash;
}

#ifdef __cplusplus
}
#endif