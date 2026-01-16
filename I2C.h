/*
 * I2C.h
 *
 *  Created on: Dec 18, 2025
 *      Author: atran
 */

#ifndef I2C_H_
#define I2C_H_
#include "base.h"
#include <stdint.h>

#define I2C_CR1_offset (0x00)
#define I2C_CR1 ((volatile uint32_t *)(I2C + I2C_CR1_offset))

#define I2C_CR2_offset (0x04)
#define I2C_CR2 ((volatile uint32_t *)(I2C + I2C_CR2_offset))

#define I2C_OAR1_offset (0x08)
#define I2C_OAR1 ((volatile uint32_t *)(I2C + I2C_OAR1_offset))

#define I2C_DR_offset (0x10)
#define I2C_DR ((volatile uint32_t *)(I2C + I2C_DR_offset))

#define I2C_SR1_offset (0x14)
#define I2C_SR1 ((volatile uint32_t *)(I2C + I2C_SR1_offset))

#define I2C_SR2_offset (0x18)
#define I2C_SR2 ((volatile uint32_t *)(I2C + I2C_SR2_offset))

#define I2C_CCR_offset (0x1c)
#define I2C_CCR ((volatile uint32_t *)(I2C + I2C_CCR_offset))

#define I2C_TRISE_offset (0x20)
#define I2C_TRISE ((volatile uint32_t *)(I2C + I2C_TRISE_offset))

#define Start_Bit_Gen 	(*I2C_SR1 & (1u<<0))
#define Start_Bit 		(1u<<8)
#define Stop_Bit 		(1u<<9)
#define Bus_Busy 		(*I2C_SR2 & (1u<<1))
#define Addr_Matched 	(*I2C_SR1 & (1u<<1))
#define TxE 			(*I2C_SR1 & (1u<<7))
#define BTF				(*I2C_SR1 & (1u<<2))
#define AF				(*I2C_SR1 & (1u<<10))
#define I2C_PE			(1u)

#define I2C_EXC_TRISE_RST (0x0000)
#define I2C_TRISE_RST (0x0002)

#define FERQ_2MHZ (0b000010)
#define FERQ_8MHZ (0b001000)

#define Standa_Mode (100000)
#define Fast_Mode (400000)

void I2C_Reset();

void I2C_Init(volatile uint32_t clock, volatile char Mode, volatile uint32_t SCL_Clock);

void lcd_init();

void I2C_Transmit_LCD(uint8_t Address, uint8_t *pData, int Size);

void I2C_Write_Byte(uint8_t data, uint8_t mode);

void Write4_Bit(uint8_t data);

#endif /* I2C_H_ */
