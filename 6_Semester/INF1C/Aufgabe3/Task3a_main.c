/* ***************************************************************************************
 *  Project:    Embedded I, Aufgabe 3 - Timer
 *  File:       main.c
 *
 *  Language:   C
 *
 *  Hardware:   STefi v1.0b
 *  Processor:  STM32L476RG
 *
 *  Author:     Holger Lenkowski
 *  Datum:      09.10.2019
 *
 *  Version:    0.1
 *  History:
 *      09.10.2019  HL  create project, implement LED blinker example
 *
 *  Status:     under development
 *
 *  Description:
 *      Change this code example to a LED dimmer.
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
/* ------------------------------------ PRIVATE VARIABLES ----------------------------- */

/* ------------------------------------ PROTOTYPES ------------------------------------ */
void port_init(void);
void TIM3_init(void);
void TIM6_init(void);

/* ------------------------------------ MAIN ------------------------------------------ */
int main(void)
{

    /* --- initialization --- */
    __disable_irq();

    // Stop Timers, when CPU is halted by debugger
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM3_STOP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM6_STOP;
    port_init();
    TIM3_init();
    TIM6_init();

    __enable_irq();

    TIM6->CR1 |= TIM_CR1_CEN;   // start Timer
    TIM3->CR1 |= TIM_CR1_CEN;

    for (;;)
    {
    }
}

/* ------------------------------------ GLOBAL FUNCTIONS ------------------------------ */

/* ------------------------------------------------------------------------------------ *\
 * method:  void port_init(void)
 *
 * Init port PC7 as output (LED3, blue).
 *
 * requires:    - nothing -
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
void port_init(void)
{
    // Enable PC clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;    // PC clock on

    // STefi LEDs
    GPIOC->ODR |= (0xF << 4);                           // all LEDs off at the beginning
    GPIOC->MODER &= ~(1 << 15);                         // PC7 is output (LED3), driver strength is weak

    //LED PWM
    GPIOC->MODER &= ~(0x01 << 12);                       //PC6 alternate
    GPIOC->AFR[0] |= (0x02 << GPIO_AFRL_AFSEL6_Pos);     //TIM3_CH1 is AF2 of PC6
}

/* ------------------------------------------------------------------------------------ *\
 * method:  void TIM3_init(void)
 *
 * Timer 3 runs with 4 MHz system clock
 *
 * requires:    - nothing -
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
void TIM3_init(void)
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;               // enable clock

    //PWM Generation for LED
    TIM3->PSC = 7;                                      // Timer runs with 0,5MHz
    TIM3->ARR = 999;
    TIM3->DIER = TIM_DIER_UIE;                          // enable interrupt generation
    TIM3->CR1 |= TIM_CR1_ARPE;                          // enable auto reload
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; //OCM1 = PWM
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;                     //OC1 preload enable
    TIM3->CCER |= TIM_CCER_CC1E;                        //OC1 signal output
    TIM3->CCER |= TIM_CCER_CC1P;                        //OC1 active low
    TIM3->CCR1 = 0;                                     //Set PWM to off
    TIM3->EGR |= TIM_EGR_UG;                            // reset Timer
    TIM3->SR &= ~TIM_SR_UIF;                            // Clear Timer Interrupt flag
    NVIC_SetPriority(TIM3_IRQn, 14);                    // set 2nd lowest prio
    NVIC_ClearPendingIRQ(TIM3_IRQn);                    // clear potentially pending bits
    NVIC_EnableIRQ(TIM3_IRQn);                          // enable interrupt in NVIC
}

/* ------------------------------------------------------------------------------------ *\
 * method:  void TIM6_init(void)
 *
 * Timer 6 runs with 4 MHz system clock, prescaler is 4000 (4000 -1).
 * ARR is 249 for 250 ms
 *
 * requires:    - nothing -
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
void TIM6_init(void)
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;                   // enable clock

    TIM6->PSC = 3999;                                          // Timer runs with 2 MHz
    TIM6->ARR = 249;                                        // Interrupt frequency 2 kHz
    TIM6->DIER |= TIM_DIER_UIE;                             // enable interrupt generation
    TIM6->CR1 |= TIM_CR1_ARPE;                              // enable shadow registers
    TIM6->EGR |= TIM_EGR_UG;                                // reset Timer
    TIM6->SR &= ~TIM_SR_UIF;                                // Clear Timer Interrupt flag


    NVIC_SetPriority(TIM6_DAC_IRQn, 15);                    // set lowest prio
    NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);                    // clear potentially pending bits
    NVIC_EnableIRQ(TIM6_DAC_IRQn);                          // enable interrupt in NVIC
}

/* ------------------------------------ PRIVATE FUNCTIONS ----------------------------- */

/* ************************************ E O F ***************************************** */
