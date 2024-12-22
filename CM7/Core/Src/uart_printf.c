/**
 * @file uart_printf.c
 * @brief Retargets the standard C library printf function to USART
 */

#include "main.h"
#include "uart_printf.h"

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
	return ch;
}
