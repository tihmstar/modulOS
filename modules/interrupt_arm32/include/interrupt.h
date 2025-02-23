#ifndef INTERRUPT_ARM32_H
#define INTERRUPT_ARM32_H

#include <stdint.h>


uint32_t getVBAR();
void setVBAR(uint64_t vbar);


#endif //INTERRUPT_ARM32_H