/* ***************************************************************************************
 *  Project:    task5 - timer and interrupts
 *  File:       task5.c
 *
 *  Language:   C
 *
 *  Hardware:   STefi-Simulator
 *  Processor:  STM32F411x
 *
 *  Author:     Manuel Lederhofer
 *  Datum:      12.03.2021
 *
 *  Version:    0.1
 *  History:
 *		12.03.2021  ML  creating project; it is based upon task4
 *
 *  Status:     under development
 *
 *  Description:
 *          Currently, red LED0 blinks.
 *          This file contains the main routine and the initialization.
 *
 *  Notes:
 *      - processing speed of the simulator varies depending on computer performance
 *
 ************************************************************************************** */

/* ------------------------------------ INCLUDES -------------------------------------- */
#include "stm32f411xe.h"
#include "STefi.h"
#include "uart.h"


/* ------------------------------------ DEFINES --------------------------------------- */
#define WAITTIME_WALKING_LIGHT	125			// 125 ms
#define WAITTIME_DEBOUNCE		10			// 10 ms

#define LOOPS_PER_MS    5000        // NOP-loops for 1 ms, experiment to get it right


/* ------------------------------------ TYPE DEFINITIONS ------------------------------ */
/* ------------------------------------ GLOBAL VARIABLES ------------------------------ */
/* ------------------------------------ PRIVATE VARIABLES ----------------------------- */


/* ------------------------------------ PROTOTYPES ------------------------------------ */
static void GPIO_init(void);
static void delay(const uint16_t ms);
static void EXTI_init(void);


/* ------------------------------------ M A I N --------------------------------------- */
int main(void)
{
    /* --- initialization --- */
    __disable_irq();          // actually already disabled. good if the debugger can move to a line.

    UART_init();                    // the UART prints to simulator window
    GPIO_init();
    EXTI_init();

    SysTick->CTRL = 0;
    SysTick->LOAD = 100000000;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x7;                // connect to Processor -> 100Mhz

    __enable_irq();                 // Enable interrupts. No effect in this example

    GPIOC->ODR |=0xF0;               // switch all LEDs off

    /* --- one time tasks --- */
    UART_send_string("Task5 up and running\r\n"); 	// always append CR LF (\r\n) to flush the output


    /* --- infinite processing loop --- */
    while (1)
    {
    }

    return 1;
}


/* ------------------------------------ GLOBAL FUNCTIONS ------------------------------ */


/* ------------------------------------ PRIVATE FUNCTIONS ----------------------------- */

/* ------------------------------------------------------------------------------------ *\
 * method:  static void GPIO_init(void)
 *
 * Initializes GPIOs on STefi for pins with peripherals attached.
 *
 * requires:    - nothing -
 * parameters:  - none -
 * returns:     - nothing -
\* ------------------------------------------------------------------------------------ */
static void GPIO_init(void)
{
    /* enable port clocks */
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;    // PC[7:4]: LEDs
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;    // PB[3:0]: Taster

        /* GPIO LED0 init */
        GPIOC->ODR |= MASK_LED0;                // default is LED off
        GPIOC->MODER &= ~(0x03 << 8);           // clear mode bits for PC4
        GPIOC->MODER |= (0x01 << 8);            // set PC4 to output

        /* GPIO LED1 init*/
        GPIOC->ODR |= MASK_LED1;                // default is LED off
        GPIOC->MODER &= ~(0x03 << 10);          // clear mode bits for PC5
        GPIOC->MODER |= (0x01 << 10);           // set PC5 to output

        /* GPIO LED2 init*/
        GPIOC->ODR |= MASK_LED2;                // default is LED off
        GPIOC->MODER &= ~(0x03 << 12);          // clear mode bits for PC6
        GPIOC->MODER |= (0x01 << 12);           // set PC6 to output

        /* GPIO LED3 init*/
        GPIOC->ODR |= MASK_LED3;                // default is LED off
        GPIOC->MODER &= ~(0x03 << 14);          // clear mode bits for PC7
        GPIOC->MODER |= (0x01 << 14);           // set PC7 to output

        /*GPIO S0 init*/
        GPIOB->MODER &= ~(0x03);                // PB0 set to input
        GPIOB->PUPDR |= (0x01);                 // Pullup-Widerstand setzen
}

static void EXTI_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;                   // activate clock for SYSCFG at APB2

    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PB;           // PB0 -> EXTI0
    EXTI->IMR |= EXTI_IMR_IM0;                              // activate interrupts for PB0
    EXTI->FTSR |= EXTI_FTSR_TR0;                            // falling edge for PB0

    NVIC_SetPriority(EXTI0_IRQn, 3);                        // set proirity for interrupt IRQ6 to 3
    NVIC_ClearPendingIRQ(EXTI0_IRQn);                       // clear pending bit for IRQ6
    NVIC_EnableIRQ(EXTI0_IRQn);                             // set interrupt for IRQ6
}
/* ------------------------------------------------------------------------------------ *\
 * method:  static void delay(const uint16_t ms)
 *
 * It realizes a millisecond delay by very bad busy-wait.
 *
 * requires:    - nothing -
 * parameters:  ms - delay time in milliseconds
 * returns:     - nothing -
\* ------------------------------------------------------------------------------------ */
static void delay(const uint16_t ms)
{
    for (uint16_t i = 0; i < ms; ++i)
    {
        for (uint16_t j = 0; j < LOOPS_PER_MS; ++j)
        {
            __asm("NOP");
        }
    }
}


/* ************************************ E O F ***************************************** */
