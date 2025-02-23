

.section .text.target_entry
.globl _target_entry
.thumb
_target_entry:
    b main

deadloop:
    b .