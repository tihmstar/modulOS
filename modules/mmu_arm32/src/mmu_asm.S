

.section .text

.globl getTTBR0 //uint64_t getTTBR0();
.globl setTTBR0 //void setTTBR0(uint64_t ttbr0);
.globl getTTBR1 //uint64_t getTTBR1();
.globl setTTBR1 //void setTTBR1(uint64_t ttbr0);
.globl getSCTLR //uint32_t getSCTLR();
.globl setSCTLR //void setSCTLR(uint32_t sctlr);
.globl getMAIR0 //uint32_t getMAIR0();
.globl setMAIR0 //void setMAIR0(uint32_t mair0);
.globl getMAIR1 //uint32_t getMAIR1();
.globl setMAIR1 //void setMAIR1(uint32_t mair1);
.globl getTTBCR //uint32_t getTTBCR();
.globl setTTBCR //void setTTBCR(uint32_t ttbcr);
.global MMUTranslateVaToPa //uint64_t MMUTranslateVaToPa(uint32_t va)

.globl clean_all_caches //void clean_all_caches();
.globl flush_TLB_cache //void flush_TLB_cache();


.thumb
getTTBR0:
  mrrc  p15,0x0,r0,r1,cr2
  bx lr

setTTBR0:
  mcrr  p15,0x0,r0,r1,cr2
  bx lr

getTTBR1:
  mcrr  p15,0x1,r0,r1,cr2
  bx lr

setTTBR1:
  mcrr  p15,0x1,r0,r1,cr2
  bx lr

getSCTLR:
  isb
  mrc p15,0x0,r0,cr1,cr0,0x0
  isb
  bx lr

setSCTLR:
  dsb
  isb
  mcr p15,0x0,r0,cr1,cr0,0x0
  dsb
  isb
  bx lr

getMAIR0:
  mrc p15,0x0,r0,cr10,cr2,0x0
  bx lr

setMAIR0:
  mcr p15,0x0,r0,cr10,cr2,0x0
  bx lr

getMAIR1:
  mrc p15,0x0,r0,cr10,cr2,0x1
  bx lr

setMAIR1:
  mcr p15,0x0,r0,cr10,cr2,0x1
  bx lr

getTTBCR:
  mrc p15,0x0,r0,cr2,cr0,0x2
  bx lr

setTTBCR:
  mcr p15,0x0,r0,cr2,cr0,0x2
  bx lr

MMUTranslateVaToPa:
  mcr p15,0x0,r0,c7,c8,0x0
  mrrc p15,0x0,r0,r1,cr7
  bx lr

clean_all_caches:
  movs       r0,#0x0
  movs       r1,#0x40
  dsb        SY
.loop:
  mcr        p15,0x0,r0,cr7,cr14,0x2
  add        r0,r0,r1
  mcr        p15,0x0,r0,cr7,cr14,0x2
  add        r0,r0,r1
  mcr        p15,0x0,r0,cr7,cr14,0x2
  add        r0,r0,r1
  mcr        p15,0x0,r0,cr7,cr14,0x2
  add        r0,r0,r1
  tst        r0,#0x2000
  beq        .loop
  bic        r0,r0,#0x2000
  adds       r0,r0,#0x40000000
  bcc        .loop
  dsb        SY
  bx         lr

flush_TLB_cache:
  dsb        SY
  mcr        p15,0x0,r0,cr8,cr7,0x0
  dsb        SY
  isb        SY
  bx         lr
