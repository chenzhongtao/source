#ifdef __cplusplus
extern "C"{
#endif

#ifndef __HASHFN_H__
#define __HASHFN_H__


#include <sys/types.h>
#include <stdint.h>

uint32_t SuperFastHash (const char * s, int32_t len);

uint32_t ReallySimpleHash (char *s, int32_t len);

uint32_t ELFHash(const char *s, int32_t len);

/* hash functions */
unsigned int RSHash  (unsigned char *, unsigned int);
unsigned int DJBHash (unsigned char *, unsigned int);
unsigned int FNVHash (unsigned char *, unsigned int);
unsigned int JSHash  (unsigned char *, unsigned int);
unsigned int PJWHash (unsigned char *, unsigned int);
unsigned int SDBMHash(unsigned char *, unsigned int);
unsigned int DEKHash (unsigned char *, unsigned int);

#define hashfn ELFHash

#endif /* __HASHFN_H__ */


#ifdef __cplusplus
}
#endif

