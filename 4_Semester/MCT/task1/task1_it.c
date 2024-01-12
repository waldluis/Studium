/* ***************************************************************************************
 *  Project:    task1 - running LED with key control
 *  File:       task1_it.c
 *
 *  Language:   C
 *
 *  Hardware:   STefi Simulator
 *  Processor:  STM32F411x
 *
 *  Author:     Holger Lenkowski
 *  Datum:      10.03.2020
 *
 *  Version:    0.1
 *  History:
 *      10.03.2020  HL  create project, implement LED blinker example
 *      09.04.2020  FPN adapted for the Jumper simulator
 *      18.09.2020  ML  add: formatting, comments
 *
 *  Status:     working
 *
 *  Description:
 *          this file contains the interrupt vector table and the implementation of all
 *          interrupt handlers used in the lab exercises.
 *
 *  Notes:
 *      - processing speed of the simulator varies depending on computer performance
 *
 ************************************************************************************** */

/* ------------------------------------ INCLUDES -------------------------------------- */
#include "stm32f411xe.h"
#include "STefi.h"


/* ------------------------------------ DEFINES --------------------------------------- */
/* ------------------------------------ TYPE DEFINITIONS ------------------------------ */


/* ------------------------------------ GLOBAL VARIABLES ------------------------------ */
extern void* _estack;           // initial stack pointer from ldscript
extern void* Reset_Handler;     // exception handler from gcc startup code


/* ------------------------------------ PRIVATE VARIABLES ----------------------------- */
/* ------------------------------------ PROTOTYPES ------------------------------------ */


/* ------------------------------------ GLOBAL FUNCTIONS (Exceptions Handlers) -------- */

/* ------------------------------------------------------------------------------------ *\
 * method:  void ISR_error(void)
 *
 * Default interrupt handler for core interrupts.
 * Enables the green and red LED on the STefi board.
\* ------------------------------------------------------------------------------------ */
void ISR_error(void)
{
    /* init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;	// PA clock on (LEDs)
    GPIOC->ODR |= MASK_LED_ALL;
    GPIOC->MODER = ~(0xAA << 8);

    while(1)
    {   /* light up the LEDs permanently */
        GPIOC->ODR &= ~(MASK_LED_GREEN | MASK_LED_RED);
    }
}


/* ------------------------------------------------------------------------------------ *\
 * method:  void ISR_default(void)
 *
 * Default interrupt handler for non-core interrupts.
 * Enables the blue and yellow LED on the STefi board.
\* ------------------------------------------------------------------------------------ */
void ISR_default(void)
{
    /* init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;	// PA clock on (LEDs)
    GPIOC->ODR |= MASK_LED_ALL;
    GPIOC->MODER = ~(0xAA << 8);

    while(1)
    {   /* light up the LEDs permanently */
        GPIOC->ODR &= ~(MASK_LED_BLUE | MASK_LED_YELLOW);
    }
}


/* ------------------------------------ INTERRUPT VECTOR TABLE ------------------------ */

__attribute__ ((section (".isr_vector")))
void (* const paIsrFunc[102])(void) =
{
    /* --- core vectors --- */
    (void *)&_estack,       /* 00 (0x00000000)  initial stack pointer */
    (void *)&Reset_Handler, /* 01 (0x00000004)  (prio: -3) initial program counter (leads to first command to execute) */
    ISR_error,              /* 02 (0x00000008)  (prio: -2) non-maskable interrupt */
    ISR_error,              /* 03 (0x0000000C)  (prio: -1) hard fault exception */
    ISR_error,              /* 04 (0x00000010)  memory management exception */
    ISR_error,              /* 05 (0x00000014)  bus fault exception */
    ISR_error,              /* 06 (0x00000018)  usage fault exception  */
    ISR_error,              /* 07 (0x0000001C)  reserved interrupt 7 */
    ISR_error,              /* 08 (0x00000020)  reserved interrupt 8 */
    ISR_error,              /* 09 (0x00000024)  reserved interrupt 9 */
    ISR_error,              /* 10 (0x00000028)  reserved interrupt 10 */
    ISR_error,              /* 11 (0x0000002C)  supervisor call exception */
    ISR_error,              /* 12 (0x00000030)  debug monitor exception */
    ISR_error,              /* 13 (0x00000034)  reserved interrupt 13 */
    ISR_error,              /* 14 (0x00000038)  pended service call exception  */
    ISR_error,              /* 15 (0x0000003C)  SysTick exception */
	/* --- non-core vectors --- */
	ISR_default,            /*  0 (0x00000040)  Window WatchDog Interrupt */
	ISR_default,            /*  1 (0x00000044)  EXTI Line 16/PVD through EXTI Line detection Interrupt  */
	ISR_default,            /*  2 (0x00000048)  EXTI Line 21/Tamper and TimeStamp interrupts through the EXTI line */
	ISR_default,            /*  3 (0x0000004C)  EXTI Line 22/RTC Wakeup interrupt through the EXTI line  */
	ISR_default,            /*  4 (0x00000050)  Flash global interrupt */
	ISR_default,            /*  5 (0x00000054)  RCC global interrupt */
	ISR_default,            /*  6 (0x00000058)  EXTI Line0 interrupt */
	ISR_default,            /*  7 (0x0000005C)  EXTI Line1 interrupt */
	ISR_default,            /*  8 (0x00000060)  EXTI Line2 interrupt */
	ISR_default,            /*  9 (0x00000064)  EXTI Line3 interrupt */
	ISR_default,            /* 10 (0x00000068)  EXTI Line4 interrupt */
	ISR_default,            /* 11 (0x0000006C)  DMA1 Stream0 global interrupt */
	ISR_default,            /* 12 (0x00000070)  DMA1 Stream1 global interrupt */
	ISR_default,            /* 13 (0x00000074)  DMA1 Stream2 global interrupt */
	ISR_default,            /* 14 (0x00000078)  DMA1 Stream3 global interrupt  */
	ISR_default,            /* 15 (0x0000007C)  DMA1 Stream4 global interrupt */
	ISR_default,            /* 16 (0x00000080)  DMA1 Stream5 global interrupt */
	ISR_default,            /* 17 (0x00000084)  DMA1 Stream6 global interrupt */
	ISR_default,            /* 18 (0x00000088)  ADC1, ADC2 and ADC3 global Interrupts  */
	ISR_default,            /* 19 (0x0000008C)  reserved */
	ISR_default,            /* 20 (0x00000090)  reserved */
	ISR_default,            /* 21 (0x00000094)  reserved */
	ISR_default,            /* 22 (0x00000098)  reserved */
	ISR_default,            /* 23 (0x0000009C)  EXTI Line[9:5] interrupts */
	ISR_default,            /* 24 (0x000000A0)  TIM1 Break interrupt and TIM9 global interrupt */
	ISR_default,            /* 25 (0x000000A4)  TIM1 Update interrupt and TIM10 global interrupt */
	ISR_default,            /* 26 (0x000000A8)  TIM1 Trigger and Commutation interrupts and TIM11 global interrupt */
	ISR_default,            /* 27 (0x000000AC)  TIM1 Capture Compare Interrupt */
	ISR_default,            /* 28 (0x000000B0)  TIM2 global Interrupt */
	ISR_default,            /* 29 (0x000000B4)  TIM3 global interrupt */
	ISR_default,            /* 30 (0x000000B8)  TIM4 global interrupt */
	ISR_default,            /* 31 (0x000000BC)  I2C1 event interrupt  */
	ISR_default,            /* 32 (0x000000C0)  I2C1 error interrupt */
	ISR_default,            /* 33 (0x000000C4)  I2C2 event interrupt */
	ISR_default,            /* 34 (0x000000C8)  I2C2 error interrupt */
	ISR_default,            /* 35 (0x000000CC)  SPI1 global interrupt */
	ISR_default,            /* 36 (0x000000D0)  SPI2 global interrupt */
	ISR_default,            /* 37 (0x000000D4)  USART1 global interrupt */
	ISR_default,            /* 38 (0x000000D8)  USART2 global interrupt */
	ISR_default,            /* 39 (0x000000DC)  reserved  */
	ISR_default,            /* 40 (0x000000E0)  EXTI Line[15:10] interrupts */
    ISR_default,            /* 41 (0x000000E4)  EXTI Line 17/RTC Alarm (A and B) through EXTI Line Interrupt  */
    ISR_default,            /* 42 (0x000000E8)  EXTI Line 18/USB OTG FS Wakeup through EXTI line interrupt */
    ISR_default,            /* 43 (0x000000EC)  reserved  */
    ISR_default,            /* 44 (0x000000F0)  reserved  */
    ISR_default,            /* 45 (0x000000F4)  reserved  */
    ISR_default,            /* 46 (0x000000F8)  reserved  */
    ISR_default,            /* 47 (0x000000FC)  DMA1 Stream7 Interrupt  */
    ISR_default,            /* 48 (0x00000100)  reserved  */
    ISR_default,            /* 49 (0x00000104)  SDIO global Interrupt  */
    ISR_default,            /* 50 (0x00000108)  TIM5 global Interrupt  */
    ISR_default,            /* 51 (0x0000010C)  SPI3 global Interrupt  */
    ISR_default,            /* 52 (0x00000110)  reserved  */
    ISR_default,            /* 53 (0x00000114)  reserved  */
    ISR_default,            /* 54 (0x00000118)  reserved  */
    ISR_default,            /* 55 (0x0000011C)  reserved  */
    ISR_default,            /* 56 (0x00000120)  DMA2 Stream 0 global Interrupt  */
    ISR_default,            /* 57 (0x00000124)  DMA2 Stream 1 global Interrupt  */
    ISR_default,            /* 58 (0x00000128)  DMA2 Stream 2 global Interrupt  */
    ISR_default,            /* 59 (0x0000012C)  DMA2 Stream 3 global Interrupt  */
    ISR_default,            /* 60 (0x00000130)  DMA2 Stream 4 global Interrupt  */
    ISR_default,            /* 61 (0x00000134)  reserved  */
    ISR_default,            /* 62 (0x00000138)  reserved  */
    ISR_default,            /* 63 (0x0000013C)  reserved  */
    ISR_default,            /* 64 (0x00000140)  reserved  */
    ISR_default,            /* 65 (0x00000144)  reserved  */
    ISR_default,            /* 66 (0x00000148)  reserved  */
    ISR_default,            /* 67 (0x0000014C)  USB OTG FS global Interrupt  */
    ISR_default,            /* 68 (0x00000150)  DMA2 Stream 5 global interrupt  */
    ISR_default,            /* 69 (0x00000154)  DMA2 Stream 6 global interrupt  */
    ISR_default,            /* 70 (0x00000158)  DMA2 Stream 7 global interrupt  */
    ISR_default,            /* 71 (0x0000015C)  USART6 global interrupt  */
    ISR_default,            /* 72 (0x00000160)  I2C3 event interrupt  */
    ISR_default,            /* 73 (0x00000164)  I2C3 error interrupt  */
    ISR_default,            /* 74 (0x00000168)  reserved  */
    ISR_default,            /* 75 (0x0000016C)  reserved  */
    ISR_default,            /* 76 (0x00000170)  reserved  */
    ISR_default,            /* 77 (0x00000174)  reserved  */
    ISR_default,            /* 78 (0x00000178)  reserved  */
    ISR_default,            /* 79 (0x0000017C)  reserved  */
    ISR_default,            /* 80 (0x00000180)  reserved  */
    ISR_default,            /* 81 (0x00000184)  FPU global interrupt  */
    ISR_default,            /* 82 (0x00000188)  reserved  */
    ISR_default,            /* 83 (0x0000018C)  reserved  */
    ISR_default,            /* 84 (0x00000190)  SPI4 global Interrupt  */
    ISR_default,            /* 85 (0x00000194)  SPI5 global Interrupt  */
};


/* ************************************ E O F ***************************************** */
