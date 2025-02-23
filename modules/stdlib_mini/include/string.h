#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

void * memset ( void * ptr, int value, size_t num );
int memcmp(const void *mem1, const void *mem2, size_t len);
void *memcpy(void *dst, const void * src, size_t n);


int isMemset(void *buf, size_t bufSize, uint8_t val);

#endif // STRING_H