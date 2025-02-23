#include "../include/mmu.h"
#include "../../../platform/arm32/include/regdefs.h"

void resetSCTLR(){
  uint32_t val = getSCTLR();
  SCTLR_t *s = (SCTLR_t*)&val;
  s->M = 0; //disable MMU
  s->A = 0; //disable alignment enforcement
  s->C = 0; //disable cacheing

  s->CP15BEN = 1; //Enables accesses to the DMB, DSB, and ISB System instructions

  //disable ExecuteNever
  s->WXN = 0;
  s->UWXN = 0;
  setSCTLR(val);
}

void enableMMU(){
  uint32_t val = getSCTLR();
  SCTLR_t *s = (SCTLR_t*)&val;
  s->M = 1;
  setSCTLR(val);
}

void disableMMU(){
  uint32_t val = getSCTLR();
  SCTLR_t *s = (SCTLR_t*)&val;
  s->M = 0;
  setSCTLR(val);
}

uint8_t getMAIRAtIdx(int idx){
  uint32_t val = (idx >=4) ? getMAIR1() : getMAIR0();
  return MAIR_GET_VAL_AT_IDX(idx & 3, val);
}

void setMAIRAtIdx(int idx, uint8_t mair){
  int midx = idx & 3;
  uint32_t mval = 0;
  if (idx >= 4){
    mval = getMAIR1();
    mval &= ~MAIR_SET_VAL_AT_IDX(midx, 0xFF);
    mval |= MAIR_SET_VAL_AT_IDX(midx, mair);
    setMAIR1(mval);
  }else{
    mval = getMAIR0();
    mval &= ~MAIR_SET_VAL_AT_IDX(midx, 0xFF);
    mval |= MAIR_SET_VAL_AT_IDX(midx, mair);
    setMAIR0(mval);
  }
}
