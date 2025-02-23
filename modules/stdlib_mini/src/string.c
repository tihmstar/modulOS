
#include "../include/string.h"
#include <stdint.h>

void * memset ( void * ptr, int value, size_t num ){
  uint8_t *p =(uint8_t*)ptr;
  while (num--){
    *p++ = value;
  }
  return ptr;
}

int memcmp(const void *mem1, const void *mem2, size_t len){
  int ret = 0;

  uint8_t *m1 = (uint8_t*)mem1;
  uint8_t *m2 = (uint8_t*)mem2;

  while (!ret && len--){
    ret = *m2++ - *m1++;
  }

  return ret;
}

void *memcpy(void *dst, const void * src, size_t n){
  uint8_t *d =(uint8_t*)dst;
  const uint8_t *s =(const uint8_t*)src;
  while (n-->0){
    *d++ = *s++;
  }
  return dst;  
}

int isMemset(void *buf, size_t bufSize, uint8_t val){
  for (uint8_t *p = (uint8_t*)buf; bufSize>0; bufSize--){
    if (*p++ != val) return 0;
  }
  return 1;
}
