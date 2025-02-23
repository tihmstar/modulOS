
#include <barebone_utils_arm32.h>
#include <printf.h>

void putc(char c){
  *((uint32_t*)(0x2a040000)) = c;
  delay(0x2000);
  if (c == '\n'){
    delay(0x8000);
  }
}

void _target_entry(void){
  printf("\nHello world from megapint code!\n");
    
  printf("Payload done!\n");
}