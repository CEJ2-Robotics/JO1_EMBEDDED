/**
 * @file uart_printf.h
 * @brief Retargets the standard C library printf function to transmit output over USART
 * @details This module allows the standard C library `printf` function to send output
 *          to a USART interface
 *          It defines the necessary function prototypes and provides the UART handler for communication
 */

#ifndef INC_UART_PRINTF_H_
#define INC_UART_PRINTF_H_

#include <stdio.h>

/* External Variables */

/** @brief UART handle for USART communication */

extern UART_HandleTypeDef huart3;

/* Function Prototypes */

/**
 * @brief Character output function for retargeting printf to USART
 *
 * This macro defines the prototype for the function that will be used to send
 * each character when the printf function is called
 * It sends the character via USART and returns the transmitted character
 *
 * @param ch The character to be transmitted over USART
 *
 * @return The transmitted character
 *
 * @note The implementation of this function is platform-specific
 * For GCC-based compilers, `__io_putchar` is used, and for other compilers,
 * `fputc` is used
 */

#ifdef __GNUC__
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

#endif /* INC_UART_PRINTF_H_ */
