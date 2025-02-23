#ifndef MMU_ARM32_H
#define MMU_ARM32_H

#include <stdint.h>

uint64_t getTTBR0();
void setTTBR0(uint64_t ttbr0);

uint64_t getTTBR1();
void setTTBR1(uint64_t ttbr0);

uint32_t getSCTLR();
void setSCTLR(uint32_t sctlr);

uint32_t getMAIR0();
void setMAIR0(uint32_t mair0);
uint32_t getMAIR1();
void setMAIR1(uint32_t mair1);

uint32_t getTTBCR();
void setTTBCR(uint32_t ttbcr);

uint64_t MMUTranslateVaToPa(uint32_t va);

void resetSCTLR();
void enableMMU();
void disableMMU();

#pragma mark cache
void clean_all_caches();
void flush_TLB_cache();

uint8_t getMAIRAtIdx(int idx);
void setMAIRAtIdx(int idx, uint8_t mair);

#endif //MMU_ARM32_H