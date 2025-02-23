#ifndef PLATFORM_PLATFORM_H
#define PLATFORM_PLATFORM_H

#include <stdint.h>

#define PAGE_SIZE 0x1000

#pragma mark optional platform definitions
/*
  When these are needed, you need to define them in your target and set to the appropriate value
*/
extern const uint32_t gPageSize; //=PAGE_SIZE

#endif //PLATFORM_PLATFORM_H