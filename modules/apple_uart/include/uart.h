#ifndef UART_H
#define UART_H

void uart_init(void *uartBase);
void uart_deinit();

void uart_putc(char c);


#endif //UART_H