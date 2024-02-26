/*
 ******************************************************************************
 *
 * Project:		CAN send and receive 8 Byte with receive ISR
 * Name:    	L476_CAN_start
 * Part:     	Init  functions
 * Author:     	Peter Urbanek
 * Compiler:   	AVR-GCC in AC6
 * Hardware:   	Nucleo Board with STM32L476
 * Version:    	1.0
 * History: 	12.04.2018	first entry.
 *              06.09.2023  HL  can_init() changed: preset of transmit mailbox 0 and parameters deleted 
 * Status:     	running
 *
 ******************************************************************************
*/

#include "L476_CAN_start.h"


/*
 *** Description **************************************************************
 *
 * CAN Module is on APB1.
 * CAN needs high speed on CANTX, CANRX pins.
 * CAN is Alternate Function AF9.
 * CAN1_RX = PA11
 * CAN1_TX = PA12
 * Pins are set to AF in MODER.
 * CAN_RTX_S = PB4
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
 ******************************************************************************
 */
void CAN_port_init(void)
{
	// Enable port clocks
	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN|RCC_AHB2ENR_GPIOCEN);	// PA and PC clock on (CAN, STefi LEDs)
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;						// PB clock on (CAN_RTX_S, STefi buttons)


	GPIOA->OSPEEDR &= ~(1<<22);			// set RX = PA11 to high speed
	GPIOA->OSPEEDR |= (1<<23);			// set RX = PA11 to high speed
	GPIOA->OSPEEDR &= ~(1<<24);			// set TX = PA12 to high speed
	GPIOA->OSPEEDR |= (1<<25);			// set TX = PA12 to high speed
	GPIOA->AFR[1] |= (9<<12); 			// AF9 is CAN for pin A11
	GPIOA->AFR[1] |= (9<<16); 			// AF9 is CAN for pin A12
	GPIOA->MODER &= ~(1<<22);			// CAN1_RX = PA11; set to alternate function
	GPIOA->MODER |= (1<<23);
	GPIOA->MODER &= ~(1<<24);			// CAN1_TX = PA12; set to alternate function
	GPIOA->MODER |= (1<<25);

	GPIOB->ODR &= ~(1<<4);			 	// set CAN_RTX_S low to enable CAN transceiver
	GPIOB->MODER |= (1<<8);				// PB4 is output (CAN_RTX_S), driver strength is weak
	GPIOB->MODER &= ~(1<<9);		    

	// STefi LEDs
	GPIOC->ODR |= (0xF<<4);						// all LEDs off at the beginning
	GPIOC->MODER |= (1<<8);						// PC4 is output (LED0), driver strength is weak
	GPIOC->MODER &= ~(1<<9);
	GPIOC->MODER |= (1<<10);					// PC5 is output (LED1), driver strength is weak
	GPIOC->MODER &= ~(1<<11);					
	GPIOC->MODER |= (1<<12);					// PC6 is output (LED2), driver strength is weak
	GPIOC->MODER &= ~(1<<13);
	GPIOC->MODER |= (1<<14);					// PC7 is output (LED3), driver strength is weak
	GPIOC->MODER &= ~(1<<15);

	// STefi buttons
	GPIOB->MODER &= ~(3<<0);					// PB0 is input (S0)
	GPIOB->PUPDR |= (1<<0);						// Pull up for PB0 on
	GPIOB->MODER &= ~(3<<2);					// PB1 is input (S1)
	GPIOB->PUPDR |= (1<<2);						// Pull up for PB1 on
	GPIOB->MODER &= ~(3<<4);					// PB2 is input (S2)
	GPIOB->PUPDR |= (1<<4);						// Pull up for PB2 on
	GPIOB->MODER &= ~(3<<6);					// PB3 is input (S3)
	GPIOB->PUPDR |= (1<<6);						// Pull up for PB3 on

	// Initialize EXTI for interrupt on S0
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // for EXTI used: SYSCFG + COMP + VREFBUF clock enabled
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PB; // EXTI0 configured to PB = PB0. SYSCFG_EXTICR1 = EXTICR[0]!
	EXTI->IMR1  |= EXTI_IMR1_IM0; 		// Enable interrupt 0 (IM0).
	EXTI->FTSR1 |= EXTI_FTSR1_FT0; 		// Trigger EXTI0 on falling edge. Possible with L476, not with L053.
	NVIC_SetPriority(EXTI0_IRQn,4);		// PB0 priority = 4
	NVIC_EnableIRQ(EXTI0_IRQn);			// PB0 is IRQ6
	// Initialize EXTI for interrupt on S1
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PB; // EXTI1 configured to PB = PB1. SYSCFG_EXTICR1 = EXTICR[0]!
	EXTI->IMR1  |= EXTI_IMR1_IM1; 		// Enable interrupt 1 (IM1).
	EXTI->FTSR1 |= EXTI_FTSR1_FT1; 		// Trigger EXTI1 on falling edge. Possible with L476, not with L053.
	NVIC_SetPriority(EXTI1_IRQn,5);		// PB1 priority = 5
	NVIC_EnableIRQ(EXTI1_IRQn);			// PB1 is IRQ7
	// Initialize EXTI for interrupt on S2
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PB; // EXTI2 configured to PB = PB2. SYSCFG_EXTICR1 = EXTICR[0]!
	EXTI->IMR1  |= EXTI_IMR1_IM2; 		// Enable interrupt 2 (IM2).
	EXTI->FTSR1 |= EXTI_FTSR1_FT2; 		// Trigger EXTI2 on falling edge. Possible with L476, not with L053.
	NVIC_SetPriority(EXTI2_IRQn,6);		// PB2 priority = 6
	NVIC_EnableIRQ(EXTI2_IRQn);			// PB2 is IRQ8
	// Initialize EXTI for interrupt on S3
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PB; // EXTI3 configured to PB = PB3. SYSCFG_EXTICR1 = EXTICR[0]!
	EXTI->IMR1  |= EXTI_IMR1_IM3; 		// Enable interrupt 3 (IM3).
	EXTI->FTSR1 |= EXTI_FTSR1_FT3; 		// Trigger EXTI1 on falling edge. Possible with L476, not with L053.
	NVIC_SetPriority(EXTI3_IRQn,7);		// PB3 priority = 7
	NVIC_EnableIRQ(EXTI3_IRQn);			// PB3 is IRQ9
	
//  configure PA8 as SYSCLK output
//	RCC->CFGR |= RCC_CFGR_MCOSEL_0;		// MCOSEL[3:0]=0001: SYSCLK output
//	GPIOA->MODER &= ~(1 << 16);			// PA8: MCO is alternate function AF0 (microcontroller clock out --> 32.0 MHz)
//	GPIOA->OSPEEDR |= (1 << 16) | (1 << 17);		// PA8 = clock out very high speed

}


/*
 *** Description **************************************************************
 *
 * CAN is connected to APB1 with 80 MHz.
 * Receive function: set for car IDs and pc.
 * Transmit function: use only TXB0.
 *
 * CAN Timing parameters:
 * 		CAN bus frequency is 500 kbit/s -> Tbit = 2000 ns
 * 		Fsys = 80 MHz
 * 		Set BRP to 8 because TS2 cannot be greater then 8.
 *
 * 		Tq = BRP/fsys = 8/80 MHz = 100 ns.
 * 		Nbit = Tbit/Tq = 2000 ns/100 ns = 20
 * 		Sample Point at 75 % => TS2 = 5 (-1=4), TS1 = 14 (-1=13), SYNC = 1.
 * 		SJW = 1 (safety)
 *
 *	Set filter for accurate filtering for CAR acknowledge (0x400...0x40F) and pc (0xFF)
 *	Filter bank0: two 16bit filters in mask mode ->  M0, F0	(32 bit of R0(R1))
 *													 M1, F1 (32 bit of R1(R2))
 *	Used: F0. Unused F1
 *	Filter bank1: four 16bit filters in list mode -> F3, F2	(32 bit of R0(R1))
 *													 F5, F4 (32 bit of R1(R2))
 *	Used: F2. Unused: F3, F4, F5
 *	Each filter bank has 2 registers, CAN_FxR0 and CAN_FxR1 (or RM: CAN_FxR1 and CAN_FxR2)
 *	IDs are left bound in registers: ID11 = Bit31 or Bit15
 *
 ******************************************************************************
 */
void CAN_init()
{
	// Local variables
	uint32_t id_pc = CAN_ID_pc;							// preset CAN ID for efiCAN node

	// Enable CAN clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_CAN1EN;				// CAN1 clock enable

	// Prepare initialization
	CAN->MCR |= CAN_MCR_INRQ;							// Request Init Mode
    while ((CAN->MSR & CAN_MSR_INAK) != CAN_MSR_INAK);	// Wait for the acknowledge

	CAN->MCR &= ~CAN_MCR_SLEEP;							// no sleep mode

 	// Init CANC with timing parameters: set bit timing
    CAN->BTR = 0x004D0007;								// PRE=8. 20tq= 1+5+14.  TS2=5 bei 75%. SJW=1.
														// 1tq=100ns, because fsys/8=10 MHz -> tq=100ns

	// Set filter for car IDs and pc
    CAN->FMR  |=  ((uint32_t)CAN_FMR_FINIT);			// Filter Mode Register: set filter to init mode

	CAN->FA1R &= ~((uint32_t)CAN_FA1R_FACT0);			// Filter bank Activation1 Register: deactivate FB0
	CAN->FA1R &= ~((uint32_t)CAN_FA1R_FACT1);			// Filter bank Activation1 Register: deactivate FB1

	CAN->FS1R &= ~((uint32_t)CAN_FS1R_FSC0);			// Filter bank0 Scale Register: two 16bit instead of one 32bit
	CAN->FM1R &= ~((uint32_t)CAN_FM1R_FBM0);			// Filter bank0 Mode Register: mask mode -> 16bit mask | 16bit ID

	CAN->FS1R &= ~((uint32_t)CAN_FS1R_FSC1);			// Filter bank1 Scale Register: two 16bit instead of one 32bit
	CAN->FM1R |=  ((uint32_t)CAN_FM1R_FBM1);			// Filter bank1 Mode Register: all in list mode -> F2...F5 = 16bit ID

	CAN->sFilterRegister[0].FR1 = (0 | (ID_CAR_ACKNOWLEDGE<<5)); // set one F0 to CAR control ID
	CAN->sFilterRegister[0].FR1 |= (MASK_ID_CAR_CONTROL<<21);	// mask the lowest 4 bits of the ID: Mask1=0x7F0. 1=must match.
	CAN->sFilterRegister[1].FR1 = (0 | (id_pc<<5));	    // set F2 to pc ID
//	CAN->sFilterRegister[1].FR1 |= (0x7FF<<21);			// set Mask to "each bit" = 0x7FF

	CAN->FFA1R &= ~((uint32_t)CAN_FFA1R_FFA0);			// Filter FIFO Assignment Register: assign FilterBank0 to FIFO0
	CAN->FFA1R &= ~((uint32_t)CAN_FFA1R_FFA1);			// Filter FIFO Assignment Register: assign FilterBank1 to FIFO0

	CAN->FA1R |= ((uint32_t)CAN_FA1R_FACT0);			// activate FB0
	CAN->FA1R |= ((uint32_t)CAN_FA1R_FACT1);			// activate FB1

    CAN->FMR &= ~((uint32_t)CAN_FMR_FINIT);				// leave filter init mode
	CAN->ESR = 0; 										// clear all errors

	// Interrupt handling
	CAN->IER |= CAN_IER_FMPIE0;							// set FMPIE bit in CAN_IER to enable RX0 interrupt
	NVIC_EnableIRQ(CAN1_RX0_IRQn);						// CAN_RXB0 is irq20/27
	NVIC_SetPriority(CAN1_RX0_IRQn,1);					// CAN_RXB0 priority = 1

    // Leave Init Mode
    CAN->MCR &= ~CAN_MCR_INRQ;							// request leave Init Mode
    while ((CAN->MSR & CAN_MSR_INAK) == CAN_MSR_INAK);	// wait for the acknowledge
}

/* ------------------------------------------------------------------------------------
 * method:  void TIM6_init(void)
 *
 * Timer 6 runs with 10 kHz to 200, so one overflow every 20 ms occurs
 * Timer 6 is used for debounce the buttons
 *
 * parameters:  - none -
 * returns:     - nothing -
 * ------------------------------------------------------------------------------------
*/
void TIM6_init(void)
{
    RCC -> APB1ENR1 |= RCC_APB1ENR1_TIM6EN; // enable clock

    TIM6 -> PSC  = 7999;					// 80 MHz / 8000 = 10 kHz
    TIM6 -> ARR  = 199;
    TIM6 -> DIER |= TIM_DIER_UIE;           // enable interrupt generation in TIM6
    TIM6 -> CR1 |= TIM_CR1_DIR;             // down counting
	TIM6 -> CR1 |= TIM_CR1_OPM;             // on pulse mode

    TIM6 -> EGR  |= TIM_EGR_UG;             // reset Timer6
    TIM6 -> SR &= ~TIM_SR_UIF;              // Clear Tim6 Interrupt flag

    NVIC_SetPriority(TIM6_DAC_IRQn, 15);        // set lowest prio
    NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);        // clear potentially pending bits
    NVIC_EnableIRQ(TIM6_DAC_IRQn);              // enable TIM6 interrupt in NVIC
}
