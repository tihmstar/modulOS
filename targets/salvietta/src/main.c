
#include <barebone_utils_arm32.h>
#include <printf.h>
#include <uart.h>
#include <mmu.h>
#include <string.h>
#include <regdefs.h>
#include <interrupt.h>
#include <mmu_pte.h>

#define UART0_BASE ((uint32_t*)0x3a0c0000)

extern int32_t early_stack_start;
extern int32_t early_stack_end;
extern int32_t start_rw_section;
extern int32_t file_start;

__attribute__((__section__(".pagetables"))) static uint8_t pagetables[0];
void init_vmem(){
  resetSCTLR();

  memset((void*)pagetables, 0, 0x4000);

  /*
    Configure caching
  */
 setMAIR1(0x00); //everything is strongly ordered
 setMAIRAtIdx(0, MAIR_UPPER_NORMAL_MEMORY_OUTER_WRITE_BACK_NON_TRANSIENT(1,1) | MAIR_LOWER_NORMAL_MEMORY_INNER_WRITE_BACK_NON_TRANSIENT(1,1));  //idx 0, normal memory most caching
 setMAIRAtIdx(1, MAIR_UPPER_NORMAL_MEMORY_OUTER_NON_CACHEABLE | MAIR_LOWER_NORMAL_MEMORY_INNER_NON_CACHEABLE);                                  //idx 1, normal memory non-cacheable
 setMAIRAtIdx(3, MAIR_VAL_DEVICE_MEMORY);                                                                                                       //idx 3, device memory
 {
  TTBCR_long_t ttbcr = {
    .T0SZ = 2,    //1GB addressable address space with TTBR0 0x00000000-0x40000000
    .EPD0 = 0,    //TTBR0 walk is enabled
    .IRGN0 = TTBCR_RGN_WRITE_BACK_NO_WRITE_ALLOCATE_CACHEABLE,
    .ORGN0 = TTBCR_RGN_NON_CACHEABLE, //maybe outer non-cacheable, because outer mem can be modified externally?
    .SH0 = TTBCR_SH_OUTER_SHAREABLE,  //maybe outer shareable, because we share DRAM with other (external) core?

    .T1SZ = 0,    //Full 4GB address space is accessible via TTBR1. (But we're not using TTBR1)
    .A1 = 0,      //TTBR0.ASID defines the ASID.

    .EPD1 = 0,    //TTBR1 walk is disabled
    .IRGN1 = TTBCR_RGN_WRITE_BACK_NO_WRITE_ALLOCATE_CACHEABLE,
    .ORGN1 = TTBCR_RGN_NON_CACHEABLE, //maybe outer non-cacheable, because outer mem can be modified externally?
    .SH1 = TTBCR_SH_OUTER_SHAREABLE,  //maybe outer shareable, because we share DRAM with other (external) core?

    .EAE = 1,     //Use the 40-bit translation system, with the Long-descriptor translation table format
  };
  setTTBCR(*(uint32_t*)&ttbcr);
 }

  /*
    Setup mappings
  */
#define PHYS_IMAGE_BASE 0x800000000

  setTTBR0(PHYS_IMAGE_BASE + (uint64_t)pagetables);

  setPTEForVaddr(&pagetables[0], 2, 0x00000000,
    makeBlockEntry(PHYS_IMAGE_BASE, 1, PTE_AP_PRIV_READ_WRITE_UNPRIV_READ_WRITE, PTE_SH_OUTER_SHAREABLE, 0, 0)
  );


  uint64_t *dbgpt = (uint64_t*)pagetables;
  for (size_t i = 384; i < 512; i++){
    uint64_t loc = (i-384);
    loc *= 0x200000;
    dbgpt[i] = makeBlockEntry(0x200000000+loc, 3, PTE_AP_PRIV_READ_WRITE_UNPRIV_READ_WRITE, PTE_SH_OUTER_SHAREABLE, 0, 0);
  }

  clean_all_caches();
  flush_TLB_cache();
  
  {
    //enable MMU
    uint32_t val = getSCTLR();
    SCTLR_t *s = (SCTLR_t*)&val;
    s->M = 1; //enable MMU
    s->A = 1; //enable alignment enforcement
    s->C = 1; //enable cacheing  
    setSCTLR(val);
  }
}

void main(void){
  setVBAR(0);
  init_vmem();

  uart_init(UART0_BASE);
  printf("\nHello world from salvietta!\n");

  while (1){
    printf("Hello from salvietta\n");
    delay(0x500000);
  }

  printf("Goodbye, salvietta out!\n");
}