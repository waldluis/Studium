/* ***************************************************************************************
 *  Project:    task1 - running LED with key control
 *  File:       uart.c
 *
 *  Language:   C
 *
 *  Hardware:   STefi-Simulator
 *  Processor:  STM32F411x
 *
 *  Author:     Flaviu Popp-Nowak
 *  Datum:      04.04.2020
 *
 *  Version:    0.1
 *  History:
 *      04.04.2020  FPN implement UART module
 *      18.09.2020  ML  add: formatting, comments
 *
 *  Status:     working
 *
 *  Description:
 *          Quit & dirty UART support to replace printf(). Suited for the simulator only.
 *
 *  Notes:
 *      - processing speed of the simulator varies depending on computer performance
 *
 ************************************************************************************** */

/* ------------------------------------ INCLUDES -------------------------------------- */
#include "stm32f411xe.h"
#include "uart.h"


/* ------------------------------------ DEFINES --------------------------------------- */
/* ------------------------------------ TYPE DEFINITIONS ------------------------------ */
/* ------------------------------------ GLOBAL VARIABLES ------------------------------ */
/* ------------------------------------ PRIVATE VARIABLES ----------------------------- */
/* ------------------------------------ PROTOTYPES ------------------------------------ */


/* ------------------------------------ GLOBAL FUNCTIONS ------------------------------ */

/* ------------------------------------------------------------------------------------ *\
 * method:  void UART_init(void)
 *
 * Initialization of the UART.
 *
 * requires:    - nothing -
 * parameters:  - none -
 * returns:     - nothing -
\* ------------------------------------------------------------------------------------ */
void UART_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;           // enable usart2 clock

    USART2->BRR = 52 << USART_BRR_DIV_Mantissa_Pos; // Mantissa for 19200: 16 MHz / (19200 * 16) = 52.1
    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE;     // transmit enable
}


/* ------------------------------------------------------------------------------------ *\
 * method:  void UART_send_char(char c)
 *
 * Send a single character by UART.
 *
 * requires:    a previous successful call to UART_init()
 * parameters:  c - the character to send
 * returns:     - nothing -
\* ------------------------------------------------------------------------------------ */
void UART_send_char(char c)
{
    while ((USART2->SR & USART_SR_TXE) == 0)
        ;                                       // transmitter busy, wait

    USART2->DR = c;
}


/* ------------------------------------------------------------------------------------ *\
 * method:  void UART_send_string(char str[])
 *
 * Send a complete string by UART.
 *
 * requires:    a previous successful call to UART_init()
 * parameters:  str - pointer to a valid C string
 * returns:     - nothing -
\* ------------------------------------------------------------------------------------ */
void UART_send_string(char str[])
{
    while (*str)
    {
        UART_send_char(*str);
        str++;
    }
}


/* ------------------------------------ PRIVATE FUNCTIONS ----------------------------- */
/* ------------------------------------ INTERRUPT SERVICE ROUTINES -------------------- */

/* ************************************ E O F ***************************************** */
