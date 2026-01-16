/*
 * uart.c
 *
 *  Created on: Jan 16, 2026
 *      Author: atran
 */
/*
Enable the USART by writing the UE bit in USART_CR1 register to 1.
Program the M bit in USART_CR1 to define the word length.
Program the number of stop bits in USART_CR2.
Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take place.
Configure the DMA register as explained in multibuffer communication.
Select the desired baud rate using the USART_BRR register.
Set the TE bit in USART_CR1 to send an idle frame as first transmission.
Write the data to send in the USART_DR register (this clears the TXE bit).
Repeat this for each data to be transmitted in case of single buffer.
After writing the last data into the USART_DR register, wait until TC=1.
This indicates that the transmission of the last frame is complete.
This is required for instance when the USART is disabled or enters the Halt mode to avoid corrupting the last
transmission.
*/

void uart_init(uint8_t baudrate, uint8_t word_length, uint8_t num_stop_bit)
{
	*USART_CR1 |= EN;
	if (word_length == eight_data_bits)
	{

	}
	else if (word_length == nine_data_bits)
	{

	}
	else
	{
		return;
	}

	switch (num_stop_bit)
	{
	case 0b00:
		*USART_CR2 &= ~(3u<<12);
		break;
	case 0b01:
			*USART_CR2 |= (1u<<12);
			break;
	case 0b10:
			*USART_CR2 |= (2u<<12);
			break;
	case 0b11:
			*USART_CR2 |= (3u<<12);
			break;
	case _:
		return;
	}
	*USART_BRR |= ;
}

