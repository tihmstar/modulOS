#ifndef PLATFORM_REGDEFS_H
#define PLATFORM_REGDEFS_H

#include <stdint.h>

//https://developer.arm.com/documentation/100442/0100/register-descriptions/aarch32-system-registers/sctlr--system-control-register
typedef struct {
  uint32_t M : 1; //MMU enable for EL1 and EL0 stage 1 address translation.
  uint32_t A : 1; //Alignment check enable.
  uint32_t C : 1; //Cacheability control, for data accesses at EL1 and EL0.

  /*
    1: This bit is not controllable. Load/Store Multiple to memory marked at stage1 as Device-nGRE/Device-nGnRE/Device-nGnRnE memory does not generate a stage 1 alignment fault as a result of this mechanism.
  */
  uint32_t nTLSMD : 1; //no Trap Load/Store Multiple to Device-nGRE/Device-nGnRE/Device-nGnRnE memory. 
  
  /*
    1: This bit is not controllable. The ordering and interrupt behavior of Load/Store Multiple is as defined for ARMv8.
  */
  uint32_t LSMAOE : 1; //Load/Store Multiple Atomicity and Ordering Enable.

  /*
    0: PL0 and PL1 execution of the CP15DMB, CP15DSB, and CP15ISB instructions is UNDEFINED.
    1: PL0 and PL1 execution of the CP15DMB, CP15DSB, and CP15ISB instructions is enabled.
  */
  uint32_t CP15BEN : 1; //System instruction memory barrier enable. Enables accesses to the DMB, DSB, and ISB System instructions in the (coproc==1111) encoding space from PL1 and PL0.

  uint32_t UNK : 1; //Writes to this bit are IGNORED. Reads of this bit return an UNKNOWN value.

  /*
    0: All IT instruction functionality is always implemented in PL0, PL1 and enabled at PL2.
  */
  uint32_t ITD : 1;

  /*
    0: SETEND instruction execution is enabled at PL0 and PL1.
    1: SETEND instructions are UNDEFINED at PL0 and PL1.
  */
  uint32_t SED : 1; //SETEND instruction disable. Disables SETEND instructions at PL0 and PL1:

  uint32_t __pad1 : 3;

  uint32_t I : 1; //Instruction access Cacheability control, for accesses at EL1 and EL0.
  uint32_t V : 1; //Vectors bit.

  uint32_t __pad2 : 2;

  uint32_t nTWI : 1; //Traps PL0 execution of WFI instructions to Undefined mode.

  uint32_t __pad3 : 1;

  uint32_t nTWE : 1; //Traps PL0 execution of WFE instructions to Undefined mode.
  uint32_t WXN : 1; //Write permission implies XN (Execute-never).
  uint32_t UWXN : 1; //Unprivileged write permission implies PL1 XN (Execute-never).

  uint32_t __pad4 : 2;

  uint32_t SPAN : 1;

  uint32_t __pad5 : 1;

  uint32_t EE : 1; //Exception Endianness bit.

  uint32_t __pad6 : 2;

  uint32_t TRE : 1; //TEX remap enable.
  uint32_t AFE : 1; //Access Flag Enable.
  uint32_t TE : 1; //T32 Exception enable.
}SCTLR_t;


//https://developer.arm.com/documentation/ddi0406/c/System-Level-Architecture/System-Control-Registers-in-a-VMSA-implementation/VMSA-System-control-registers-descriptions--in-register-order/TTBCR--Translation-Table-Base-Control-Register--VMSA
typedef struct {
  /*
    The value of N also determines:
    - whether TTBR0 or TTBR1 is used as the base address for translation table walks.
    - the size of the translation table pointed to by TTBR0.
   */
  uint32_t N      : 3; //Indicate the width of the base address held in TTBR0. In TTBR0, the base address field is bits[31:14-N]

  uint32_t _UNK1  : 1;  //Reserved, UNK/SBZP.

  /*
    0:    Perform translation table walks using TTBR0.
    1:    A TLB miss on an address that is translated using TTBR0 generates a Translation fault. No translation table walk is performed.
  */
  uint32_t PD0    : 1;  //Translation table walk disable for translations using TTBR0. This bit controls whether a translation table walk is performed on a TLB miss for an address that is translated using TTBR0

  /*
    0:    Perform translation table walks using TTBR1.
    1:    A TLB miss on an address that is translated using TTBR1 generates a Translation fault. No translation table walk is performed.
  */
  uint32_t PD1    : 1;  //Translation table walk disable for translations using TTBR1. This bit controls whether a translation table walk is performed on a TLB miss for an address that is translated using TTBR1

  uint32_t _UNK2  : 25;  //Reserved, UNK/SBZP.

  /*
    0:  Use the 32-bit translation system, with the Short-descriptor translation table format. In this case, the format of the TTBCR is as described in TTBCR format when using the Short-descriptor translation table format.
    1:  Use the 40-bit translation system, with the Long-descriptor translation table format. In this case, the format of the TTBCR is as described in this section.
  */
  uint32_t EAE    : 1;  //Extended Address Enable.
} TTBCR_short_t;


typedef struct {
  uint32_t T0SZ   : 3;  //The size offset of the memory region addressed by TTBR0. This field is encoded as a three-bit unsigned integer, and the region size is 2(32-T0SZ) bytes.
  uint32_t _UNK1  : 4;  //Reserved, UNK/SBZP.
  /*
    0:    Perform translation table walks using TTBR0.
    1:    A TLB miss on an address that is translated using TTBR0 generates a Translation fault. No translation table walk is performed.
  */
  uint32_t EPD0   : 1;  //Translation table walk disable for translations using TTBR0. This bit controls whether a translation table walk is performed on a TLB miss, for an address that is translated using TTBR0.

  /*
    00: Normal memory, Inner Non-cacheable
    01: Normal memory, Inner Write-Back Write-Allocate Cacheable
    10: Normal memory, Inner Write-Through Cacheable
    11: Normal memory, Inner Write-Back no Write-Allocate Cacheable
  */
  uint32_t IRGN0  : 2;  //Inner cacheability attribute for memory associated with translation table walks using TTBR0

  /*
    00: Normal memory, Outer Non-cacheable
    01: Normal memory, Outer Write-Back Write-Allocate Cacheable
    10: Normal memory, Outer Write-Through Cacheable
    11: Normal memory, Outer Write-Back no Write-Allocate Cacheable
  */
  uint32_t ORGN0  : 2;  //Outer cacheability attribute for memory associated with translation table walks using TTBR0
  uint32_t SH0    : 2;  //Shareability attribute for memory associated with translation table walks using TTBR0. Shareability, Long-descriptor format defines the encoding of this field.
  uint32_t _UNK2  : 2;  //Reserved, UNK/SBZP.

  uint32_t T1SZ   : 3;  //The size offset of the memory region addressed by TTBR1. This field is encoded as a three-bit unsigned integer, and the region size is 2(32-T1SZ) bytes.
  uint32_t _UNK3  : 3;  //Reserved, UNK/SBZP.
  /*
    0:    TTBR0.ASID defines the ASID.
    1:    TTBR1.ASID defines the ASID.
  */
  uint32_t A1     : 1;  //Selects whether TTBR0 or TTBR1 defines the ASID. The encoding of this bit is:

  /*
    0:    Perform translation table walks using TTBR1.
    1:    A TLB miss on an address that is translated using TTBR1 generates a Translation fault. No translation table walk is performed.
  */
  uint32_t EPD1   : 1;  //Translation table walk disable for translations using TTBR1. This bit controls whether a translation table walk is performed on a TLB miss, for an address that is translated using TTBR1. The encoding of this bit is: 

  /*
    00: Normal memory, Inner Non-cacheable
    01: Normal memory, Inner Write-Back Write-Allocate Cacheable
    10: Normal memory, Inner Write-Through Cacheable
    11: Normal memory, Inner Write-Back no Write-Allocate Cacheable
  */
  uint32_t IRGN1  : 2;  //Inner cacheability attribute for memory associated with translation table walks using TTBR1
  
  /*
    00: Normal memory, Outer Non-cacheable
    01: Normal memory, Outer Write-Back Write-Allocate Cacheable
    10: Normal memory, Outer Write-Through Cacheable
    11: Normal memory, Outer Write-Back no Write-Allocate Cacheable
  */
  uint32_t ORGN1  : 2;  //Outer cacheability attribute for memory associated with translation table walks using TTBR1

  uint32_t SH1    : 2;  //Shareability attribute for memory associated with translation table walks using TTBR1. This field is encoded as described in Shareability, Long-descriptor format.

  uint32_t impdef : 1;  //An implementation defined bit.

  /*
    0:  Use the 32-bit translation system, with the Short-descriptor translation table format. In this case, the format of the TTBCR is as described in TTBCR format when using the Short-descriptor translation table format.
    1:  Use the 40-bit translation system, with the Long-descriptor translation table format. In this case, the format of the TTBCR is as described in this section.
  */
  uint32_t EAE    : 1;  //Extended Address Enable.

} TTBCR_long_t;

/*
  Inner/Outer cacheability attribute for memory associated with translation table walks using TTBR0/1
*/
#define TTBCR_RGN_NON_CACHEABLE                           0b00
#define TTBCR_RGN_WRITE_BACK_WRITE_ALLOCATE_CACHEABLE     0b01
#define TTBCR_RGN_WRITE_THROUGH_CACHEABLE                 0b10
#define TTBCR_RGN_WRITE_BACK_NO_WRITE_ALLOCATE_CACHEABLE  0b11

#define TTBCR_SH_NON_SHAREABLE                            0b00
#define TTBCR_SH_UNPREDICTABLE                            0b01
#define TTBCR_SH_OUTER_SHAREABLE                          0b10
#define TTBCR_SH_INNER_SHAREABLE                          0b11

/*
  MAIR caching attributes
*/
#define MAIR_VAL_STRONGLY_ORDERED_MEMORY                                                    ((uint32_t)0x00)
#define MAIR_VAL_DEVICE_MEMORY                                                              ((uint32_t)0x04)

#define MAIR_UPPER_NORMAL_MEMORY_OUTER_WRITE_THROUGH_TRANSIENT(readAlloc, writeAlloc)       ((uint32_t)0x00 | ((readAlloc != 0) << 5) | (writeAlloc != 0) << 4) //R/W can't be 00, otherwise DEVICE_MEM
#define MAIR_UPPER_NORMAL_MEMORY_OUTER_NON_CACHEABLE                                        ((uint32_t)0x40)
#define MAIR_UPPER_NORMAL_MEMORY_OUTER_WRITE_BACK_TRANSIENT(readAlloc, writeAlloc)          ((uint32_t)0x40 | ((readAlloc != 0) << 5) | (writeAlloc != 0) << 4) //R/W can't be 00, otherwise NON_CACHEABLE
#define MAIR_UPPER_NORMAL_MEMORY_OUTER_WRITE_THROUGH_NON_TRANSIENT(readAlloc, writeAlloc)   ((uint32_t)0x80 | ((readAlloc != 0) << 5) | (writeAlloc != 0) << 4) 
#define MAIR_UPPER_NORMAL_MEMORY_OUTER_WRITE_BACK_NON_TRANSIENT(readAlloc, writeAlloc)      ((uint32_t)0xc0 | ((readAlloc != 0) << 5) | (writeAlloc != 0) << 4)

#define MAIR_LOWER_NORMAL_MEMORY_INNER_WRITE_THROUGH_TRANSIENT(readAlloc, writeAlloc)       ((uint32_t)0x00 | ((readAlloc != 0) << 1) | (writeAlloc != 0)) //R/W can't be 00, otherwise unpredictable
#define MAIR_LOWER_NORMAL_MEMORY_INNER_NON_CACHEABLE                                        ((uint32_t)0x04)
#define MAIR_LOWER_NORMAL_MEMORY_INNER_WRITE_BACK_TRANSIENT(readAlloc, writeAlloc)          ((uint32_t)0x04 | ((readAlloc != 0) << 1) | (writeAlloc != 0)) //R/W can't be 00, otherwise DEVICE_MEM
#define MAIR_LOWER_NORMAL_MEMORY_INNER_WRITE_THROUGH_NON_TRANSIENT(readAlloc, writeAlloc)   ((uint32_t)0x08 | ((readAlloc != 0) << 1) | (writeAlloc != 0))
#define MAIR_LOWER_NORMAL_MEMORY_INNER_WRITE_BACK_NON_TRANSIENT(readAlloc, writeAlloc)      ((uint32_t)0x0c | ((readAlloc != 0) << 1) | (writeAlloc != 0))

#define MAIR_SET_VAL_AT_IDX(idx, val) (((uint32_t)(val)) << 8*idx)
#define MAIR_GET_VAL_AT_IDX(idx, val) ((((uint32_t)(val)) >> 8*idx) & 0xFF)

#define PAGE_SIZE 0x1000



#pragma mark optional platform definitions
/*
  When these are needed, you need to define them in your target and set to the appropriate value
*/
extern uint32_t gPageSize; //=PAGE_SIZE

#endif //PLATFORM_REGDEFS_H