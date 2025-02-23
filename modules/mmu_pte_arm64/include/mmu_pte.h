#ifndef MMU_PTE_ARM64_H
#define MMU_PTE_ARM64_H

#include <stdint.h>

typedef struct {
  uint64_t isValid : 1;                                   //0
  uint64_t isTableEntry : 1;                              //1
  uint64_t Indx : 3; //index into MAIR_ELn                //2
  uint64_t NS : 1; //security bit (EL3/secure EL1 only)   //5
  uint64_t AP : 2; //access permission                    //6
  uint64_t SH : 2; //shareable attribute                  //8
  uint64_t AF : 1; //access flag                          //10
  uint64_t outblockaddress : 42;                          //11
  uint64_t PXN : 1; //privileged execute never            //53
  uint64_t UXN : 1; //un-privileged execute never         //54
  uint64_t reserved : 4;                                  //55
  uint64_t pad : 5;                                       //59
} pte_block_entry;


typedef struct {
  uint64_t isValid : 1;                                   //0
  uint64_t isTableEntry : 1;                              //1
  uint64_t nextTableAddress : 53;                         //2
  uint64_t reserved : 4;                                  //55
  uint64_t pad : 5;                                       //59
} pte_table_entry;

typedef pte_block_entry pte_table_descriptor;

struct pte{
  union {
      struct {
          uint64_t isValid : 1;
          uint64_t isTableEntry : 1;
      };
      pte_table_descriptor td;
      pte_block_entry be;
      pte_table_entry te;
  };
};

#define PTE_AP_PRIV_READ_WRITE_UNPRIV_NONE            0b00
#define PTE_AP_PRIV_READ_WRITE_UNPRIV_READ_WRITE      0b01
#define PTE_AP_PRIV_READ_UNPRIV_NONE                  0b10
#define PTE_AP_PRIV_READ_UNPRIV_READ                  0b11

#define PTE_SH_NON_SHAREABLE      0b00
#define PTE_SH_UNPREDICTABLE      0b01
#define PTE_SH_OUTER_SHAREABLE    0b10
#define PTE_SH_INNER_SHAREABLE    0b11


uint64_t makeBlockEntry(uint64_t physaddr, uint8_t IdxMAIR, uint8_t AP, uint8_t SH, uint8_t PXN, uint8_t UXN);
uint64_t makeTableEntry(uint64_t physaddr);

int getPTEForVaddr(uint64_t *pagetable, uint8_t level, uint64_t vaddr, uint64_t *entry);
int setPTEForVaddr(uint64_t *pagetable, uint8_t level, uint64_t vaddr, uint64_t entry);

int mapMem(uint64_t *pagetable, uint8_t level, uint64_t vaddr, uint64_t physaddr, uint64_t size, uint8_t IdxMAIR, uint8_t AP, uint8_t SH, uint8_t PXN, uint8_t UXN);

#endif //MMU_PTE_ARM64_H