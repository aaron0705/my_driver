/*
 * uart.h
 *
 *  Created on: Jan 16, 2026
 *      Author: atran
 */

#ifndef UART_H_
#define UART_H_

#include "base.h"

// tx pa9 rx pa10
#define USART_SR_offset (0x00)
#define USART_SR (UART1 + USART_SR+offset)

#define USART_DR_offset (0x04)
#define USART_DR (UART1 + USART_DR+offset)

#define USART_BRR_offset (0x08)
#define USART_BRR (UART1 + USART_BRR_offset)

#define USART_CR1_offset (0x0C)
#define USART_CR1 (UART1 + USART_CR1_offset)

#define USART_CR2_offset (0x10)
#define USART_CR2 (UART1 + USART_CR2_offset)

#define USART_CR3_offset (0x14)
#define USART_CR3 (UART1 + USART_CR3_offset)

#define USART_GTPR_offset (0x18)
#define USART_GTPR (UART1 + USART_GTPR_offset)

#define UE (1u<<13)
#define eight_data_bits 0
#define nine_data_bits 1

#define USART_CR1_RST (0x0000)

void uart_init(uint8_t baudrate);

#endif /* UART_H_ */
