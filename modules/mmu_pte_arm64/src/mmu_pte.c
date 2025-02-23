#include "../include/mmu_pte.h"

#include <platform.h>

uint64_t makeBlockEntry(uint64_t physaddr, uint8_t IdxMAIR, uint8_t AP, uint8_t SH, uint8_t PXN, uint8_t UXN){
  pte_block_entry ret = {
    .isValid = 1,
    .isTableEntry = 0,
    .Indx = IdxMAIR,
    .NS = 0, //Secure. Ignored when accessing from non-secure memory
    .AP = AP,
    .SH = SH,
    .AF = 1, //Entry should not generate fault
    .outblockaddress = (physaddr >> 11),
    .PXN = PXN != 0,
    .UXN = UXN != 0,
  };
  return *(uint64_t*)&ret;
}

uint64_t makeTableEntry(uint64_t physaddr){
  pte_table_entry ret = {
    .isValid = 1,
    .isTableEntry = 1,
    .nextTableAddress = physaddr >> 2,
  };
  return *(uint64_t*)&ret;
}

int getPTEForVaddr(uint64_t *pagetable, uint8_t level, uint64_t vaddr, uint64_t *entry){
  uint32_t entriesPerPage = gPageSize/sizeof(uint64_t);
  uint8_t idx = 0;
  switch (level){
    case 2:
      idx = (vaddr >> 21) & (entriesPerPage-1);
      break;
    case 3:
      idx = (vaddr >> 12) & (entriesPerPage-1);
      break;
    default:
      return -1;
  }
  *entry = pagetable[idx];
  return 0;
}

int setPTEForVaddr(uint64_t *pagetable, uint8_t level, uint64_t vaddr, uint64_t entry){
  uint32_t entriesPerPage = gPageSize/sizeof(uint64_t);
  uint8_t idx = 0;
  switch (level){
    case 2:
      idx = (vaddr >> 21) & (entriesPerPage-1);
      break;
    case 3:
      idx = (vaddr >> 12) & (entriesPerPage-1);
      break;
    default:
      return -1;
  }
  pagetable[idx] = entry;
  return 0;
}

int mapMem(uint64_t *pagetable, uint8_t level, uint64_t vaddr, uint64_t physaddr, uint64_t size, uint8_t IdxMAIR, uint8_t AP, uint8_t SH, uint8_t PXN, uint8_t UXN){
  uint64_t mapSize = 0;
  switch (level){
    case 2:
      mapSize = 1<<21;
      break;
    case 3:
      mapSize = 1<<12;
      break;
    default:
      return -1;
  }
  //TODO
  return -1;
}
