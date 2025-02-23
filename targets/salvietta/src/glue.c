#include <uart.h>
#include <platform.h>

const uint32_t gPageSize = PAGE_SIZE;

void putc(char c){
    uart_putc(c);
}