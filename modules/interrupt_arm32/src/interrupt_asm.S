

.section .text

.globl getVBAR //uint32_t getVBAR();
.globl setVBAR //void setVBAR(uint64_t vbar);

.thumb
getVBAR:
  mrc p15,0x0,r0,cr12,cr0,0x0
  bx lr

setVBAR:
  mcr p15,0x0,r0,cr12,cr0,0x0
  bx lr
