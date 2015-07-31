#ifdef __cplusplus
extern "C"{
#endif

#ifndef __HASHFN_H__
#define __HASHFN_H__


#include <sys/types.h>
#include <stdint.h>

void prepareCryptTable();

unsigned long HashString( char *s, unsigned long HashType );


#endif /* __HASHFN_H__ */


#ifdef __cplusplus
}
#endif

