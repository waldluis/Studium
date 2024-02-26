/* ***************************************************************************************
 *  Project:    Embedded II, WS2812
 *  File:       EMB2_WS2812_init.c
 *
 *  Language:   C
 *
 *  Hardware:   STefi v1.0b
 *  Processor:  STM32L476RG
 *
 *  Author:     Holger Lenkowski
 *  Datum:      09.10.2019
 *
 *  Version:    0.2
 *  History:
 *      25.08.2020  HL  create project, implement LED blinker example
 *
 *  Status:     under development
 *
 *  Description:
 *      All init routines
 *
 *
 *  Notes:
 *
 ************************************************************************************** */


#include "stm32l476xx.h"
#include "EMB2_WS2812_init.h"

#define WAITTIME 200					// 200 * 12 cycles (31,25 ns) = 75 �s
#define LED_COUNT 23					// 23 leds on STefi-EMB-AddOn-Board
#define COLOR_COUNT 31					// 31 different colors


/* ------------------------------------------------------------------------------------
 * method:  void L476_Clock_init_32MHz_MSI (void)
 *
 * Switches system clock from 4 MHz MSI (default value) to 32 MHz MSI over PLL
 * After RESET the voltage regulator Vcore runs in Range1.
 *
 * parameters:  - none -
 * returns:     - nothing -
 * ------------------------------------------------------------------------------------
*/

void L476_Clock_init_32MHz_MSI(void)
{
	// Change CPU clock to 32 MHz.
	FLASH->ACR |= FLASH_ACR_LATENCY_2WS;				// Reduce Flash latency to 2 wait cycles
	while ((FLASH->ACR & FLASH_ACR_LATENCY_2WS) == 0); 	// Wait till done

	RCC->CR &= (uint32_t)(~RCC_CR_PLLON);				// Disable PLL. After reset default: RCC->CR &= ~(1<<24)
	while((RCC->CR & RCC_CR_PLLRDY) != 0);				// Wait until PLLRDY is cleared

	//RCC->PLLCFGR |= (1<<12);							// Configure PLL: 4 MHZ (default) *16 /2 (default) = 32 MHz.
	RCC->PLLCFGR |= (5<<11);							// Configure PLL: 4 MHZ (default) *40 /2 (default) = 80 MHz.
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_MSI;				// take MSI as input for PLL
	RCC->PLLCFGR |= (1<<24);							// activate PLL's clock output

	// Clear PLLM-Prescaler because it is set to 0b001 (devide by 2) by Debugger during Flash programming
	//   and is  N O T  reseted after programming is ready
//	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_0 | RCC_PLLCFGR_PLLM_1 | RCC_PLLCFGR_PLLM_2);

	RCC->CR |= RCC_CR_PLLON; 							// enable PLL: RCC->CR |= (1<<24)
	while ((RCC->CR & RCC_CR_PLLRDY) == 0);				// Wait for PLL ready flag

	RCC->CFGR |= (RCC_CFGR_MCOSEL_0)|(1<<26);			// MCOSEL[2:0]=101: PLLCLK output
	RCC->CFGR |= (RCC_CFGR_SW_0|RCC_CFGR_SW_1); 		// use PLL as SYSCLK
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS);	// Wait for System clock sWitch Status is PLL (0xC)
}


/*
 *** Description Port_init ***********************************************
 *
 * Init ports for STefi (LEDs and buttons)
 * and user LED and blue button on Nucleo board
 *
 * Nucleo:
 * green LED on PA5
 * blue button on PC13
 *
 * STefi:
 * LED0 (red) on PC4
 * LED1 (yellow) on PC5
 * LED2 (green) on PC6
 * LED3 (blue) on PC7
 *
 * S0 on PB0 (EXTI0)
 * S1 on PB1 (EXTI1)
 * S2 on PB2 (EXTI2)
 * S3 on PB3 (EXTI3)
 * All buttons are configured as interrupts.
 *
 * Hardware connections of WS2812B LED stripe:
 *   PC2 = Power on of the led stripe
 *   PC3 = DATA_IN of the led stripe
 *
 *
 ******************************************************************************
 */
void Port_init(void)
{
	// Enable port clocks.
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;	// PC clock on (WS2812B control pins)
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;	// PA clock on (SYSCLK output)


	// configure PA8 as SYSCLK output
	RCC->CFGR |= RCC_CFGR_MCOPRE_1;		// MCOPRE[2:0]=010: SYSCLK output divided by 4
	RCC->CFGR |= RCC_CFGR_MCOSEL_0;		// MCOSEL[3:0]=0001: SYSCLK output
	GPIOA->MODER &= ~(1 << 16);			// PA8: MCO is alternate function AF0 (microcontroller clock out --> 32.0 MHz)
	GPIOA->OSPEEDR |= (1 << 16) | (1 << 17);		// PA8 = clock out very high speed

	// Initialize data output for WS2812B LEDs on STefi-Emb-AddOn
	//   PC3 is output
	GPIOC->MODER &= ~(1<<7);							// Set DDR: PC3 is output
	GPIOC->OSPEEDR |= (1<<7); 							// Set PC3 to High Speed

	// PC2 (power supply for WS2812 LEDs on STefi-Emb-AddOn) is activated in main()!
	// MOSFET Q1 can't be deactivated by setting port PC2 to high, because U_Source = 5 V and U_Gate is only 3,3 V,
	//  so set port pin to analog and use pull up resistor R17 to switch Q1 off
}



/* ------------------------------------------------------------------------------------ *\
 * method:  void TIM6_init(void)
 *
 * Timer 6 runs with 1 kHz to 200, so one overflow every 200 ms occurs
 * Timer 6 is used for WS2812B 
 *
 * parameters:  - none -
 * returns:     - nothing -
\* ------------------------------------------------------------------------------------ */
void TIM6_init(void)
{
    RCC -> APB1ENR1 |= RCC_APB1ENR1_TIM6EN; // enable clock

    TIM6 -> PSC  = 31999;					//
    TIM6 -> ARR  = 499;
    TIM6 -> DIER |= TIM_DIER_UIE;           // enable interrupt generation in TIM5
//    TIM6 -> CR1 |= TIM_CR1_DIR;             // down counting
    TIM6 -> EGR  |= TIM_EGR_UG;             // reset Timer5
    TIM6 -> SR &= ~TIM_SR_UIF;              // Clear Tim6 Interrupt flag

    NVIC_SetPriority(TIM6_DAC_IRQn, 15);        // set lowest prio
    NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);        // clear potentially pending bits
    NVIC_EnableIRQ(TIM6_DAC_IRQn);              // enable TIM6 interrupt in NVIC
}
