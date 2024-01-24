/* ***************************************************************************************
 *  Project:    task1 - running LED
 *  File:       stm32l4xx_it.c
 *
 *  Language:   C
 *
 *  Hardware:   STefi v1.0b
 *  Processor:  STM32L476RG
 *
 *  Author:     Manuel Lederhofer
 *  Datum:      02.09.2019
 *
 *  Version:    0.2
 *  History:
 *      02.09.2019  ML  create project, implement LED blinker example
 *      20.12.2019  HL  startup_stm32l476xx.s changed to startup_stm32l476xx_ohne_EVT.s
 *
 *  Status:     under development
 *
 *  Description:
 *          this file contains the interrupt vector table and the implementation of all
 *          interrupt handlers used in this project.
 *
 *
 *  Notes:
 *      - default MCU speed at startup is ~ 4 MHz.
 *
 *  ToDo:
 *      - change the code example to match the description of the program
 *          (see header of main.c)
 ************************************************************************************** */

/* ------------------------------------ INCLUDES -------------------------------------- */
#include "STefi_Stud.h"
#include "stm32l476xx.h"


/* ------------------------------------ DEFINES --------------------------------------- */
/* ------------------------------------ TYPE DEFINITIONS ------------------------------ */


/* ------------------------------------ GLOBAL VARIABLES ------------------------------ */
extern void* _estack;           // initial stack pointer from ldscript
extern void* Reset_Handler;     // exception handler from gcc startup code


/* ------------------------------------ PRIVATE VARIABLES ----------------------------- */
/* ------------------------------------ PROTOTYPES ------------------------------------ */


/* ------------------------------------ GLOBAL FUNCTIONS ------------------------------ */

/* ------------------------------------------------------------------------------------ *\
 * method:  void ISR_error(void)
 *
 * Default interrupt handler for core interrupts.
 * Enables the green and red LED on the STefi board.
\* ------------------------------------------------------------------------------------ */
void ISR_error(void)
{
    /* init */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    GPIOC->ODR |= MASK_LED_ALL;
    GPIOC->MODER = ~(0xAA << 8);

    while(1)
    {   /* light up the LEDs */
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
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    GPIOC->ODR |= MASK_LED_ALL;
    GPIOC->MODER = ~(0xAA << 8);

    while(1)
    {   /* light up the LEDs */
        GPIOC->ODR &= ~(MASK_LED_BLUE | MASK_LED_YELLOW);
    }
}


/* ------------------------------------ PRIVATE FUNCTIONS ----------------------------- */


/* ------------------------------------ INTERRUPT VECTOR TABLE ------------------------ */
__attribute__ ((section (".isr_vector")))
void (* const paIsrFunc[98])(void) =
{
/* --- core vectors --- */
    (void *)&_estack,       /* 00 (0x00000000) (prio:  x) initial stack pointer */
    (void *)&Reset_Handler, /* 01 (0x00000004) (prio: -3) initial program counter (leads to first command to execute) */
    ISR_error,              /* 02 (0x00000008) (prio: -2) non-maskable interrupt */
    ISR_error,              /* 03 (0x0000000C) (prio: -1) hard fault exception */
    ISR_error,              /* 04 (0x00000010) (prio:  0) memory management exception */
    ISR_error,              /* 05 (0x00000014) (prio:  1) bus fault exception */
    ISR_error,              /* 06 (0x00000018) (prio:  2) usage fault exception  */
    ISR_error,              /* 07 (0x0000001C) (prio:  -) reserved interrupt 7 */
    ISR_error,              /* 08 (0x00000020) (prio:  -) reserved interrupt 8 */
    ISR_error,              /* 09 (0x00000024) (prio:  -) reserved interrupt 9 */
    ISR_error,              /* 10 (0x00000028) (prio:  -) reserved interrupt 10 */
    ISR_error,              /* 11 (0x0000002C) (prio:  3) supervisor call exception */
    ISR_error,              /* 12 (0x00000030) (prio:  4) debug monitor exception */
    ISR_error,              /* 13 (0x00000034) (prio:  -) reserved interrupt 13 */
    ISR_error,              /* 14 (0x00000038) (prio:  5) pended service call exception  */
    ISR_error,              /* 15 (0x0000003C) (prio:  6) SysTick exception */
/* --- non-core vectors --- */
    ISR_default,            /*  0 (0x00000040) (prio:  7) WWDG interrupt */
    ISR_default,            /*  1 (0x00000044) (prio:  8) PVD_PVM interrupt */
    ISR_default,            /*  2 (0x00000048) (prio:  9) TAMP_STAMP interrupt */
    ISR_default,            /*  3 (0x0000004C) (prio: 10) RTC_WKUP interrupt */
    ISR_default,            /*  4 (0x00000050) (prio: 11) FLASH interrupt */
    ISR_default,            /*  5 (0x00000054) (prio: 12) RCC interrupt */
    ISR_default,            /*  6 (0x00000058) (prio: 13) EXTI0 interrupt */
    ISR_default,            /*  7 (0x0000005C) (prio: 14) EXTI1 interrupt */
    ISR_default,            /*  8 (0x00000060) (prio: 15) EXTI2 interrupt */
    ISR_default,            /*  9 (0x00000064) (prio: 16) EXTI3 interrupt */
    ISR_default,            /* 10 (0x00000068) (prio: 17) EXTI4 interrupt */
    ISR_default,            /* 11 (0x0000006C) (prio: 18) DMA1_Channel1 interrupt */
    ISR_default,            /* 12 (0x00000070) (prio: 19) DMA1_Channel2 interrupt */
    ISR_default,            /* 13 (0x00000074) (prio: 20) DMA1_Channel3 interrupt */
    ISR_default,            /* 14 (0x00000078) (prio: 21) DMA1_Channel4 interrupt */
    ISR_default,            /* 15 (0x0000007C) (prio: 22) DMA1_Channel5 interrupt */
    ISR_default,            /* 16 (0x00000080) (prio: 23) DMA1_Channel6 interrupt */
    ISR_default,            /* 17 (0x00000084) (prio: 24) DMA1_Channel7 interrupt */
    ISR_default,            /* 18 (0x00000088) (prio: 25) ADC1_2 interrupt */
    ISR_default,            /* 19 (0x0000008C) (prio: 26) CAN1_TX interrupt */
    ISR_default,            /* 20 (0x00000090) (prio: 27) CAN1_RX0 interrupt */
    ISR_default,            /* 21 (0x00000094) (prio: 28) CAN1_RX1 interrupt */
    ISR_default,            /* 22 (0x00000098) (prio: 29) CAN1_SCE interrupt */
    ISR_default,            /* 23 (0x0000009C) (prio: 30) EXTI9_5 interrupt */
    ISR_default,            /* 24 (0x000000A0) (prio: 31) TIM1_BRK_TIM15 interrupt */
    ISR_default,            /* 25 (0x000000A4) (prio: 32) TIM1_UP_TIM16 interrupt */
    ISR_default,            /* 26 (0x000000A8) (prio: 33) TIM1_TRG_COM_TIM17 interrupt */
    ISR_default,            /* 27 (0x000000AC) (prio: 34) TIM1_CC interrupt */
    ISR_default,            /* 28 (0x000000B0) (prio: 35) TIM2 interrupt */
    ISR_default,            /* 29 (0x000000B4) (prio: 36) TIM3 interrupt */
    ISR_default,            /* 30 (0x000000B8) (prio: 37) TIM4 interrupt */
    ISR_default,            /* 31 (0x000000BC) (prio: 38) I2C1_EV interrupt */
    ISR_default,            /* 32 (0x000000C0) (prio: 39) I2C1_ER interrupt */
    ISR_default,            /* 33 (0x000000C4) (prio: 40) I2C2_EV interrupt */
    ISR_default,            /* 34 (0x000000C8) (prio: 41) I2C2_ER interrupt */
    ISR_default,            /* 35 (0x000000CC) (prio: 42) SPI1 interrupt */
    ISR_default,            /* 36 (0x000000D0) (prio: 43) SPI2 interrupt */
    ISR_default,            /* 37 (0x000000D4) (prio: 44) USART1 interrupt */
    ISR_default,            /* 38 (0x000000D8) (prio: 45) USART2 interrupt */
    ISR_default,            /* 39 (0x000000DC) (prio: 46) USART3 interrupt */
    ISR_default,            /* 40 (0x000000E0) (prio: 47) EXTI15_10 interrupt */
    ISR_default,            /* 41 (0x000000E4) (prio: 48) RTC_Alarm interrupt */
    ISR_default,            /* 42 (0x000000E8) (prio: 49) DFSDM1_FLT3 interrupt */
    ISR_default,            /* 43 (0x000000EC) (prio: 50) TIM8_BRK interrupt */
    ISR_default,            /* 44 (0x000000F0) (prio: 51) TIM8_UP interrupt */
    ISR_default,            /* 45 (0x000000F4) (prio: 52) TIM8_TRG_COM interrupt */
    ISR_default,            /* 46 (0x000000F8) (prio: 53) TIM8_CC interrupt */
    ISR_default,            /* 47 (0x000000FC) (prio: 54) ADC3 interrupt */
    ISR_default,            /* 48 (0x00000100) (prio: 55) FMC interrupt */
    ISR_default,            /* 49 (0x00000104) (prio: 56) SDMMC1 interrupt */
    ISR_default,            /* 50 (0x00000108) (prio: 57) TIM5 interrupt */
    ISR_default,            /* 51 (0x0000010C) (prio: 58) SPI3 interrupt */
    ISR_default,            /* 52 (0x00000110) (prio: 59) UART4 interrupt */
    ISR_default,            /* 53 (0x00000114) (prio: 60) UART5 interrupt */
    ISR_default,            /* 54 (0x00000118) (prio: 61) TIM6_DAC interrupt */
    ISR_default,            /* 55 (0x0000011C) (prio: 62) TIM7 interrupt */
    ISR_default,            /* 56 (0x00000120) (prio: 63) DMA2_Channel1 interrupt */
    ISR_default,            /* 57 (0x00000124) (prio: 64) DMA2_Channel2 interrupt */
    ISR_default,            /* 58 (0x00000128) (prio: 65) DMA2_Channel3 interrupt */
    ISR_default,            /* 59 (0x0000012C) (prio: 66) DMA2_Channel4 interrupt */
    ISR_default,            /* 60 (0x00000130) (prio: 67) DMA2_Channel5 interrupt */
    ISR_default,            /* 61 (0x00000134) (prio: 68) DFSDM1_FLT0 interrupt */
    ISR_default,            /* 62 (0x00000138) (prio: 69) DFSDM1_FLT1 interrupt */
    ISR_default,            /* 63 (0x0000013C) (prio: 70) DFSDM1_FLT2 interrupt */
    ISR_default,            /* 64 (0x00000140) (prio: 71) COMP interrupt */
    ISR_default,            /* 65 (0x00000144) (prio: 72) LPTIM1 interrupt */
    ISR_default,            /* 66 (0x00000148) (prio: 73) LPTIM2 interrupt */
    ISR_default,            /* 67 (0x0000014C) (prio: 74) OTG_FS interrupt */
    ISR_default,            /* 68 (0x00000150) (prio: 75) DMA2_Channel6 interrupt */
    ISR_default,            /* 69 (0x00000154) (prio: 76) DMA2_Channel7 interrupt */
    ISR_default,            /* 70 (0x00000158) (prio: 77) LPUART1 interrupt */
    ISR_default,            /* 71 (0x0000015C) (prio: 78) QUADSPI interrupt */
    ISR_default,            /* 72 (0x00000160) (prio: 79) I2C3_EV interrupt */
    ISR_default,            /* 73 (0x00000164) (prio: 80) I2C3_ER interrupt */
    ISR_default,            /* 74 (0x00000168) (prio: 81) SAI1 interrupt */
    ISR_default,            /* 75 (0x0000016C) (prio: 82) SAI2 interrupt */
    ISR_default,            /* 76 (0x00000170) (prio: 83) SWPMI1 interrupt */
    ISR_default,            /* 77 (0x00000174) (prio: 84) TSC interrupt */
    ISR_default,            /* 78 (0x00000178) (prio: 85) LCD interrupt */
    ISR_default,            /* 79 (0x0000017C) (prio: 86) AES interrupt */
    ISR_default,            /* 80 (0x00000180) (prio: 87) RNG interrupt */
    ISR_default,            /* 81 (0x00000184) (prio: 88) FPU interrupt */
};


/* ************************************ E O F ***************************************** */
