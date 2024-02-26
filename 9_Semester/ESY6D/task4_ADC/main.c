/* ***************************************************************************************
 *  Project:    Embedded II, ADC
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
 *      25.08.2020  HL  create project, implement LED blinker example
 *
 *  Status:     under development
 *
 *  Description:
 *      See the description and requirements of the requested application
 *      in the lab exercise guide.
 *
 *
 *  Notes:
 *      - default MCU speed at startup is ~ 4 MHz.
 *
 ************************************************************************************** */

#include "STefi_Stud.h"
#include "stm32l476xx.h"
#include "core_cm4.h"

#define WAIT for(uint16_t j = 0; j < 9; ++j){__asm("NOP");};

void port_init(void);
void TIM6_init(void);
void ADC1_init(void);
void TIM3_init(void);

// global variables
volatile uint16_t ADC_value = 0;

int main(void) {

	/* --- initialization --- */
	__disable_irq();

	// Stop Timers, when CPU is halted by debugger
	DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM6_STOP;
	port_init();
	TIM6_init();
	ADC1_init();
	TIM3_init();

	__enable_irq();

	TIM6->CR1 |= TIM_CR1_CEN;   // start TIM6
	TIM3->CR1 |= TIM_CR1_CEN;	// start TIM3

	for (;;) {
	}
}

/*
 *** Description **************************************************************
 *
 * Init port PC7 as output (LED3, blue).
 *
 ******************************************************************************
 */
void port_init(void) {
	// Enable PC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;	// PC clock on

	// STefi LEDs
	GPIOC->ODR |= (0xF << 4);					// all LEDs off at the beginning
	GPIOC->MODER &= ~(1 << 15);	// PC7 is output (LED3), driver strength is weak

	// Enable GPIO Port A Clock
//	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Configure GPIO PC6 as Alternate Function for TIM3 Channel 1			// kontrolliert
	GPIOC->MODER &= ~GPIO_MODER_MODE6;
	GPIOC->MODER |= GPIO_MODER_MODE6_1;
	GPIOC->AFR[0] |= 0x2000000;					// AF2 TIM3_PWM

	GPIOC->MODER &= ~(1 << 11);
	GPIOC->MODER &= ~(1 << 9);
}

/* ------------------------------------------------------------------------------------ *\
 *
 * Timer 6 runs with 4 MHz system clock, prescaler is 4000 (4000 -1).
 * ARR is 49 for 50 ms
 *
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
void TIM6_init(void) {
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN; // enable clock

	TIM6->PSC = 3999;					// Timer runs with 1 kHz
	TIM6->ARR = 99;							// 100ms
	TIM6->DIER |= TIM_DIER_UIE;          // enable interrupt generation
	TIM6->CR1 |= TIM_CR1_ARPE;           // enable shadow registers
	TIM6->EGR |= TIM_EGR_UG;            // reset Timer
	TIM6->SR &= ~TIM_SR_UIF;             // Clear Timer Interrupt flag

	NVIC_SetPriority(TIM6_DAC_IRQn, 15);        // set lowest prio
	NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);       // clear potentially pending bits
	NVIC_EnableIRQ(TIM6_DAC_IRQn);              // enable interrupt in NVIC
}

/* ------------------------------------------------------------------------------------ *\
 *
 * ADC1 to read 10 Bit value from ADC12_IN5 every 100ms triggered by TIM6
 * ARR is 99 for 100 ms
 *
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
void ADC1_init(void) {
	// ADC Clock enable
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

	// Port A init
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;				// PA clock on
	GPIOA->MODER |= 0b11;
	GPIOA->ASCR |= 0b1;

	// wake from deep power mode
	ADC1->CR &= ~ADC_CR_DEEPPWD;
	ADC1->CR |= ADC_CR_ADVREGEN;
	WAIT;

	// ADC clock on
	ADC123_COMMON->CCR |= ADC_CCR_CKMODE_1;
	ADC123_COMMON->CCR |= ADC_CCR_PRESC_0;
	ADC1->ISR &= ~ADC_ISR_ADRDY;

	// set amount of conversion
	ADC1->SQR1 |= (0b101 << 6);

	// set conversion time 640,5 cycles
	ADC1->SMPR1 |= (0b111<<15);

	// ADC calibration
	ADC1->CR |= ADC_CR_ADCAL;

	// ADC enable
	ADC1->ISR |= ADC_ISR_ADRDY;
	ADC1->CR |= ADC_CR_ADEN;

	// Wait for ADC to be ready
	while (!(ADC1->ISR & ADC_ISR_ADRDY))
		;

	// Enable continuous mode
	ADC1->CFGR |= ADC_CFGR_CONT;

	// feedback
	GPIOC->ODR &= ~(MASK_LED_YELLOW);
}

/* ------------------------------------------------------------------------------------ *\
 *
 * Timer 6 runs with 4 MHz system clock, prescaler is 4000 (4000 -1).
 * ARR is 49 for 50 ms
 *
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
void TIM3_init(void) {
	// Enable TIM3 Clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;

	// Set TIM3 Prescaler to 1
	TIM3->PSC = 399;

	// Set TIM3 auto-reload register to 99 to allow for 100Hz frequency
	TIM3->ARR = 99;

	// timer counts down
	TIM3->CCR1 = 100;

	// Enable PWM Mode 1 for Channel 1			// kontrolliert
	TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_0);
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	TIM3->CCMR1 |= TIM_CCMR1_OC1PE;

	// Enable Output for Channel 1											// kontrolliert
	TIM3->CCER |= TIM_CCER_CC1E;

	// activate Interrupt
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->EGR |= TIM_EGR_UG;
	TIM3->SR &= ~TIM_SR_UIF;

	// configure NVIC
	NVIC_SetPriority(TIM3_IRQn, 14);               // set lowest priority
	NVIC_ClearPendingIRQ(TIM3_IRQn);               // clear pending bit
	NVIC_EnableIRQ(TIM3_IRQn);                     // enable interrupt

}

