#ifndef __STRING_H
#define __STRING_H 1

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/// compare first n bytes of mem2 with mem1
int memcmp(const void* mem1, const void* mem2, size_t n);

/// copy first n bytes of src into dest
int memcpy(void* __restrict dest, const void* __restrict src, size_t n);

/// move first n bytes of src into dest
int memmove(void* dest, const void* src, size_t n);

/// 


#ifdef __cplusplus
/* extern "C" {*/ }
#endif

#endif//__STRING_H