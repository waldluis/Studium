/* ***************************************************************************************
 *  Project:    Embedded II, WS2812
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

/*
 *** Description **************************************************************
 *
 * LEDs should light only with 5 - 10% of the maximum brightness, because
 * the voltage regulator from the Nucleo-Board and USB deliver only 200 - 300 mA.
 * All WS2812 on the STefi_EMB_AddOn (23 pieces) need at maximum brightness
 *   23 * 3 * 20 mA = 1380 mA !!!
 *
 * Used knowledge: L053_LED_runner.
 *
 * The used led stripe WS2812 has shift registers inside each led.
 * So, not the entire chain, but each single led can be switched on/off.
 * The information, if a led is on or of, is handled by a protocol.
 * Protocol: 24 Databits (G8:R8:B8) for colors
 * Timing should be: 1 level: 800 ns + 450 ns = 1250 ns +/- 150 ns
 *		   			 0 level: 400 ns + 850 ns = 1250 ns +/- 150 ns
 *
 * Hardware connections:
 * PC2 = Power on of the led stripe
 * PC3 = DATA_IN of the led stripe
 *
 * L476 is running with 32 MHz
 *
 ******************************************************************************
 */


#include "STefi_Stud.h"
#include "stm32l476xx.h"
#include "core_cm4.h"
#include "EMB2_WS2812_init.h"
			

#define WAITTIME 200					// 200 * 12 cycles (31,25 ns) = 75 �s
#define LED_COUNT 23					// 23 leds on STefi-EMB-AddOn-Board
#define COLOR_COUNT 4					// different colors

/* Union for the WS2812 Colors */
/* type definition LED colors  - version for data @ bit[23:0]*/
typedef struct
{
    uint8_t blue;
    uint8_t red;
    uint8_t green;
} WS2812_Colors;

/* type definition LED data */
typedef union
{
    uint32_t        grbColor;
    WS2812_Colors   color;
} WS2812_Data;


// Prototypes
void ws2812_send(WS2812_Data *leddata, uint16_t arraylength);	// Prototype

// global variables
uint8_t  g_TIM6_ready = 0;


int main(void)
{
	uint32_t i, color = 0;
	WS2812_Data leddata[LED_COUNT];						//23 leds * 24 bit/led + 8 bit unused
	uint16_t arraylength = LED_COUNT;					// Length of entire array with all leds

	// Array defining color triplets (GRB) to be displayed. The 4th column is a dummy.
	uint8_t ledcolors[COLOR_COUNT][3] =
	{
		{5, 0, 5},			// off
		{0, 35, 0},			// red (GRB)
		{12, 0, 0},			// green
		{5, 20, 10}

	};
	
    /* --- initialization --- */
    __disable_irq();

	for (i = 0; i < LED_COUNT; i++)				// init array with all LEDs off
	{
		leddata[i].color.green = ledcolors[0][0];
		leddata[i].color.red = ledcolors[0][1];
		leddata[i].color.blue = ledcolors[0][2];
	}

	// Stop Timers, when CPU is halted by debugger
	DBGMCU -> APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM6_STOP;
	L476_Clock_init_32MHz_MSI();
	Port_init();
	TIM6_init();

	__enable_irq();

    TIM6 -> CR1 |= TIM_CR1_CEN;   // start Timer
	
	// Initialize MOSFET and activate power supply for WS2812 LEDs on STefi-Emb-AddOn
	//   PC2 is output, active low
	GPIOC->ODR &= ~(1 << 2);					// activate WS2812B
	GPIOC->MODER |= (1 << 4);					// PC2 is output, driver strength is weak
	GPIOC->MODER &= ~(1<<5);
	for (i = 0; i < 150*WAITTIME; i++);			// wait for WS2812B power supply to be stable, about 12,5 ms

	// To deactivate power supply for WS2812 LEDs on STefi-Emb-AddOn:
	// MOSFET Q1 can't be deactivated by setting port PC2 to high, because U_Source = 5 V and U_Gate is only 3,3 V,
	//  so set port pin to analog and use pull up resistor R17 to switch Q1 off
	// GPIOC->MODER |= (1<<5);

	i = 0;

	for(;;)
	{
		if (g_TIM6_ready)
		{
//			for (i = 0; i < 1; i++)				// use only first LED
//			{
				leddata[i].color.green = ledcolors[color][0];
				leddata[i].color.red = ledcolors[color][1];
				leddata[i].color.blue = ledcolors[color][2];

				if(i != 0)
				{
				leddata[i-1].color.green = ledcolors[0][0];
				leddata[i-1].color.red = ledcolors[0][1];
				leddata[i-1].color.blue = ledcolors[0][2];
				}
//			}
			ws2812_send(leddata, arraylength);	// transfer to leds

			color++;
			i++;
			if (color >= COLOR_COUNT)
			{
				color = 0;
			}
			if (i >= 23)
			{
				i = 0;
			}
			g_TIM6_ready = 0;
		}
	}
}


void ws2812_send(WS2812_Data *leddata, uint16_t arraylength)
/*
 *  R0 = shift mask
 *  R1 = address of GPIOC_ODR
 *  R2 = mask for bit 3 of R1
 *  R3 = currentled: Compiler uses R3 for currentled automatically !!!
 *  R4 = 24 = number of bits to shift out
 *  R5 = GPIOC_ODR3 = 0
 *  R6 = GPIOC_ODR3 = 1
 */
{
	uint32_t i;
	uint32_t k = 0;
	uint32_t currentled;

	__disable_irq();

	while (arraylength--)
	{

		currentled = leddata[k++].grbColor;		// take next word from array

		asm volatile
		(
		"		PUSH	{R0-R6}				\n\t"	// save registers

		"		MOV		R4, #24				\n\t"	// 24 bit to shift
		"		LDR		R1, =0x48000814		\n\t"	// GPIOC_ODR address
		"		LDR		R6, [R1, #0]		\n\t"	// load GPIOC_ODR content
		"		MOV		R0, #8				\n\t"	// mask = 0b1000
		"		ORR		R6, R6, R0			\n\t"	// preset R6 with PC3 = 1
		"		LDR		R5, [R1, #0]		\n\t"	// load GPIOC_ODR content
		"		BIC		R5, R5, R0			\n\t"	// preset R6 with PC3 = 0
		"  		LSL		R3,R3,R0			\n\t"   // shift grbColor 8 bit left for left alignment
		"		MOV		R0, #1				\n\t"	// shift mask = 1 for 24 bit downcounter

		".next:	SUB		R4, R4, R0			\n\t"	// count down from 23 to 0
		"		STR		R6, [R1, #0]		\n\t"	// Bit begins: PC3 = 1
		"		NOP							\n\t"	// create time of a 1 level for 1 and 0
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;  -> 400ns

		"		LSLS	R3, R3, R0			\n\t"	// shift next bit into carry
		"		BLO		.zero				\n\t"	// BCC = carry = if bit = 0 branch to .zero
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;  -> 400ns

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;  -> 400ns

		"		B		.end				\n\t"	// JMP to falling edge

		".zero:	STR		R5, [R1, #0]		\n\t"	// PC3 = 0

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;  -> 400ns

		".end:	STR		R5, [R1, #0]		\n\t"	// PC3 = 0. create time of a 0 level for 1 and 0

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;  -> 400ns

		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;
		"		NOP							\n\t"	// wait 12,5 ns;

		"		CMP		R4, #0				\n\t"	// 24 bit done?
		"		BNE		.next				\n\t"	// next bit

		"		POP		{R0-R6}				\n\t"	// restore registers
				:  /* No outputs */
				: "r" (currentled) 					// inputs: put currentled in register r3
				: "cc"           					//registers are modified
		);
	}
	__enable_irq();

	for (i = 0; i < WAITTIME; i++);					// wait min. 50 us for resetting
}


