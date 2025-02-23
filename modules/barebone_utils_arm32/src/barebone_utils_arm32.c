
#include "../include/barebone_utils_arm32.h"

__attribute__((naked)) void delay(uint32_t ctr){
  __asm__(
  "cmp r0, #0\n"
  "beq .done\n"
  ".loop:\n"
  "subs r0, r0, #1\n"
  "bne .loop\n"
  ".done:\n"
  "bx lr\n"
  );
}
