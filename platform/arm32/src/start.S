
.section .text.boot
.globl _entrypoint
.arm
_entrypoint:
  b entry         //Reset
  b deadloop_arm  //UndefinedInstruction
  b deadloop_arm  //SupervisorCall
  b deadloop_arm  //PrefetchAbort
  b deadloop_arm  //DataAbort
  b deadloop_arm  //NotUsed
  b deadloop_arm  //IRQ
  b deadloop_arm  //FIQ

entry:
  adr r8, start+1
  bx r8

deadloop_arm:
  b .

.thumb
start:
  adr r8, _entrypoint
  ldr r7, =early_stack_end_offset
  add r8, r8, r7
  mov sp, r8
#  push {r0,r1,r2,r3,r4,r5,r6}
#  bl core_boot
#  pop  {r0,r1,r2,r3,r4,r5,r6}
  bl _target_entry

deadloop:
  b .
