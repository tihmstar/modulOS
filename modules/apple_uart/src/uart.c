#include "../include/uart.h"

#include <stdint.h>
#include <stddef.h>

#define rULCON0     (*(volatile uint32_t*)(gUartBase + 0x00))  //UART 0 Line control
#define rUCON0      (*(volatile uint32_t*)(gUartBase + 0x04))  //UART 0 Control
#define rUFCON0     (*(volatile uint32_t*)(gUartBase + 0x08))  //UART 0 FIFO control
#define rUMCON0     (*(volatile uint32_t*)(gUartBase + 0x0c))  //UART 0 Modem control
#define rUTRSTAT0   (*(volatile uint32_t*)(gUartBase + 0x10))  //UART 0 Tx/Rx status
#define rUERSTAT0   (*(volatile uint32_t*)(gUartBase + 0x14))  //UART 0 Rx error status
#define rUFSTAT0    (*(volatile uint32_t*)(gUartBase + 0x18))  //UART 0 FIFO status
#define rUMSTAT0    (*(volatile uint32_t*)(gUartBase + 0x1c))  //UART 0 Modem status
#define rUTXH0      (*(volatile uint32_t*)(gUartBase + 0x20))  //UART 0 Transmission Hold
#define rURXH0      (*(volatile uint32_t*)(gUartBase + 0x24))  //UART 0 Receive buffer
#define rUBRDIV0    (*(volatile uint32_t*)(gUartBase + 0x28))  //UART 0 Baud rate divisor
#define rUDIVSLOT0  (*(volatile uint32_t*)(gUartBase + 0x2C))  //UART 0 Baud rate divisor
#define rUINTM0     (*(volatile uint32_t*)(gUartBase + 0x38))  //UART 0 Baud rate divisor

static uint8_t *gUartBase = NULL;

#pragma mark public 
void uart_init(void *uartBase){
  gUartBase = (uint8_t*)uartBase;

  rULCON0 = 3;
  rUCON0 = 0x405;
  rUFCON0 = 0;
  rUMCON0 = 0;
}

void uart_deinit(){
  gUartBase = NULL;
}

void uart_putc(char c){
  if (!gUartBase) return;
  if (c == '\n') uart_putc('\r');
  while (!(rUTRSTAT0 & 0x04)) {}
  rUTXH0 = (unsigned)(c);
  return;
}
