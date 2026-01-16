/*
 * I2C.c
 *
 *  Created on: Dec 18, 2025
 *      Author: atran
 */
#include "I2C.h"
#include <stdint.h>
#include "iperipheral.h"

#define E 		(1 << 2)
#define BL 	(1 << 3)
#define RS 	(1 << 0)

void I2C_Reset()
{
	*I2C_CR1 = I2C_EXC_TRISE_RST;
	*I2C_CR2 = I2C_EXC_TRISE_RST;
	*I2C_DR = I2C_EXC_TRISE_RST;
	*I2C_SR1 = I2C_EXC_TRISE_RST;
	*I2C_SR2 = I2C_EXC_TRISE_RST;
	*I2C_CCR = I2C_EXC_TRISE_RST;
	*I2C_TRISE = I2C_TRISE_RST;
}

void I2C_Init(volatile uint32_t clock, volatile char Mode, volatile uint32_t SCL_Clock)
{
	I2C_Reset();
	if (clock > 50 || clock < 2)
	{

	}
	*I2C_CCR |= clock;
	if (Mode == 'M' || Mode == 'm')
	{
		*I2C_CR2 |= (1u);
	}
	else if (Mode == 'S' || Mode == 's')
	{
		*I2C_CR2 &= ~(1u);
	}
	else
	{

	}
	uint8_t CCR = clock / (2 * SCL_Clock);
	*I2C_CCR |= CCR;

	*I2C_TRISE |= (clock + 1);

	*I2C_CR1 |= I2C_PE;
}

void Write4_Bit(uint8_t data)
{
	while (!TxE)
	{
		// Kiểm tra lỗi NACK giữa chừng (đề phòng LCD bị lỏng dây)
		if (AF)
		{
			*I2C_CR1 |= Stop_Bit;
			*I2C_SR1 &= ~0x0400; // Xóa cờ lỗi
			return;
		}
	}
	*I2C_DR = data | BL;
}

void I2C_Write_Byte(uint8_t data, uint8_t mode)
{
	uint8_t rs_bit = (mode == 1) ? RS : 0;

	uint8_t high = data & (0xF0);
	uint8_t low = (data<<4) & (0xF0);

	Write4_Bit(high | E | rs_bit);
	Write4_Bit(high | rs_bit);

	Write4_Bit(low | E | rs_bit);
	Write4_Bit(low | rs_bit);
}

void lcd_init()
{
	delay_ms(16);
	// first try
	Write4_Bit(0x30 | E);
	Write4_Bit(0x30);
	delay_ms(5);
	// second try
	Write4_Bit(0x30 | E );
	Write4_Bit(0x30);
	delay_us(101);
	// third try
	Write4_Bit(0x30 | E);
	Write4_Bit(0x30);
	delay_ms(1);
	// 4 bit mode
	Write4_Bit(0x20 | E);
	Write4_Bit(0x20);
	delay_ms(1);

    uint8_t cmd;

    // Bước 6: Function Set (2 lines, 5x8 font) -> 0x28
    cmd = 0x28;
    I2C_Write_Byte(cmd, 0);
    delay_ms(1);

    // Bước 7: Display OFF -> 0x08
    cmd = 0x08;
    I2C_Write_Byte(cmd, 0);
    delay_ms(1);

    // Bước 8: Clear Display -> 0x01
    cmd = 0x01;
    I2C_Write_Byte(cmd, 0);
    delay_ms(2); // Lệnh Clear tốn nhiều thời gian (>1.52ms)

    // Bước 9: Entry Mode Set (Increment cursor) -> 0x06
    cmd = 0x06;
    I2C_Write_Byte(cmd, 0);
    delay_ms(1);

    // Bước 10: Display ON, Cursor OFF -> 0x0C
    cmd = 0x0C;
    I2C_Write_Byte(cmd, 0);
}

void I2C_Transmit_LCD(uint8_t Address, uint8_t *pData, int Size)
{
	while (Bus_Busy);
	*I2C_CR1 |= Start_Bit;
	while (!Start_Bit_Gen);

	*I2C_DR = Address ;
	while (!Addr_Matched)
	{
		if (AF)
		{ // Check an toàn
			*I2C_CR1 |= Stop_Bit;
			return;
		}
	}
	(void)*I2C_SR1; (void)*I2C_SR2; // Clear ADDR
    lcd_init();

    /* --- BƯỚC 3: DATA LOOP (WRITE DATA) --- */
    for (int i = 0; i < Size; i++)
    {
        // Ghi dữ liệu vào DR
        I2C_Write_Byte(pData[i], 1);
        while (!BTF)
		{
			 if (AF)
			 { // Check an toàn
				*I2C_CR1 |= Stop_Bit;
				return;
			 }
		}
    }

    /* --- BƯỚC 4: STOP CONDITION --- */
    // Đợi byte cuối cùng được truyền đi hết (BTF flag = EV8_2

    // Tạo xung Stop
    *I2C_CR1 |= Stop_Bit;
}


