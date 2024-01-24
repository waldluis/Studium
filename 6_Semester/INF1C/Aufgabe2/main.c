/* ***************************************************************************************
 *  Project:    task2 - running LED with interrupt
 *  File:       main.c
 *
 *  Language:   C
 *
 *  Hardware:   STefi v1.0b
 *  Processor:  STM32L476RG
 *
 *  Author:     Manuel Lederhofer
 *  Datum:      02.09.2019
 *
 *  Version:    0.1
 *  History:
 *      02.09.2019  ML  create project, implement LED blinker example
 *
 *  Status:     under development
 *
 *  Description:
 *      Change this code example to a running LED.
 *      See the description and requirements of the requested application
 *      in the lab exercise guide.
 *
 *
 *  Notes:
 *      - default MCU speed at startup is ~ 4 MHz.
 *
 ************************************************************************************** */

/* ------------------------------------ INCLUDES -------------------------------------- */
#include "STefi_Stud.h"
#include "stm32l476xx.h"
#include "core_cm4.h"

/* ------------------------------------ DEFINES --------------------------------------- */
/* ------------------------------------ TYPE DEFINITIONS ------------------------------ */
/* ------------------------------------ GLOBAL VARIABLES ------------------------------ */
extern int runLED;

/* ------------------------------------ PRIVATE VARIABLES ----------------------------- */

/* ------------------------------------ PROTOTYPES ------------------------------------ */
void delay(const uint16_t ms);
static void GPIO_init(void);
static void EXTI_init(void);

/* ------------------------------------ MAIN ------------------------------------------ */
int main(void)
{
    /* --- initialization --- */
    __disable_irq();

    GPIO_init();        // LEDs and buttons
    EXTI_init();        //Exti initialisation

    __enable_irq();

    runLED = 0;
    int first = 1;
    /* --- one time tasks --- */
    // none
    /* --- infinite processing loop --- */
    while (1)
    {
        if ((!(GPIOB->IDR & MASK_S0)) == 0x1)
        {
            runLED = 1;
            first = 1;
        }

        if (runLED == 1)
        {
            if (first == 1)     //Erster Durchlauf
            {
                GPIOC->ODR ^= (1 << 4);         //LED 0 anschalten
                delay(150);
                GPIOC->ODR ^= (1 << 4);         //LED 0 ausschalten
                first = 0;
            }

            for (int i = 5; i < 8; i++)     //LED1 bis LED3 hochlaufen
            {
                GPIOC->ODR ^= (1 << i);         //LED anschalten
                delay(150);
                GPIOC->ODR ^= (1 << i);         //LED ausschalten
            }

            for (int i = 6; i > 3; i--)     //LED3 bis LED0 runterlaufen
            {
                GPIOC->ODR ^= (1 << i);          //LED anschalten
                delay(150);
                GPIOC->ODR ^= (1 << i);         //LED ausschalten
            }
        }
    }
    return 1;
}

/* ------------------------------------ GLOBAL FUNCTIONS ------------------------------ */

/* ------------------------------------------------------------------------------------ *\
 * method:  void delay(const uint16_t ms)
 *
 * It realizes a millisecond delay by very bad busy-wait.
 *
 * requires:    - nothing -
 * parameters:  ms - delay time in milliseconds
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
void delay(const uint16_t ms)
{
    for (uint16_t i = 0; i < ms; ++i)
    {
        for (uint16_t j = 0; j < 400; ++j)
        {
            __asm("NOP");
        }
    }
}

/* ------------------------------------ PRIVATE FUNCTIONS ----------------------------- */
/* ------------------------------------------------------------------------------------ *\
 * method:  static void GPIO_init(void)
 *
 * Initializes GPIOs on STefi for pins with peripherals attached.
 * LED0 (red) on PC4
 * LED1 (yellow) on PC5
 * LED2 (green) on PC6
 * LED3 (blue) on PC7
 *
 * requires:    - nothing -
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
static void GPIO_init(void)
{
    /* enable port clocks */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    /* GPIO LED0 init*/
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

    /* LED3 init */
    GPIOC->ODR |= MASK_LED3;              // default is LED off
    GPIOC->MODER &= ~(0x03 << 14);          // clear mode bits for PC7
    GPIOC->MODER |= (0x01 << 14);           // set PC6 to output

    /*GPIO S0 init*/
    GPIOB->MODER &= ~(0x03 << 0);           // PB0 set to input
    GPIOB->PUPDR &= ~(0x3 << 0);
    GPIOB->PUPDR |= (0x01 << 0);            // Pullup-Widerstand setzen

    /*GPIO S1 init*/
    GPIOB->MODER &= ~(0x03 << 2);           // PB1 set to input
    GPIOB->PUPDR &= ~(0x3 << 2);
    GPIOB->PUPDR |= (0x01 << 2);            // Pullup-Widerstand setzen
}

static void EXTI_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;                   // activate clock for SYSCFG at APB2

    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PB;           // PB1 -> EXTI1
    EXTI->IMR1 |= EXTI_IMR1_IM1;                            // activate interrupts for PB1
    EXTI->FTSR1 |= EXTI_FTSR1_FT1;                         // falling edge for PB1

    NVIC_SetPriority(EXTI1_IRQn, 3);                        // set proirity for interrupt IRQ7 to 3
    NVIC_ClearPendingIRQ(EXTI1_IRQn);                       // clear pending bit for IRQ7
    NVIC_EnableIRQ(EXTI1_IRQn);                             // set interrupt for IRQ7
}

/* ************************************ E O F ***************************************** */
