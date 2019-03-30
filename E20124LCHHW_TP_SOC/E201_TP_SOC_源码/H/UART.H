#ifndef _UART_H_
#define _UART_H_

#define	Fsys		12000000

#define	BaudRate	9600

void uart_init(void);
void UART_TX_byte(unsigned char DATA);


#endif