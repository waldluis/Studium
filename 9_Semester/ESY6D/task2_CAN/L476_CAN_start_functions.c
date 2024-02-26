/*
 ******************************************************************************
 *
 * Project:		CAN send and receive 8 Byte with receive ISR
 * Name:    	L476_CAN_start
 * Part:     	Application functions used in this project
 * Author:     	Peter Urbanek
 * Compiler:   	AVR-GCC in AC6
 * Hardware:   	Nucleo Board with STM32L476
 * Version:    	1.0
 * History: 	12.04.2018	first entry.
 *              06.09.2023  HL  can_send(): parameters changed
 * Status:     	running
 *
 ******************************************************************************
*/

#include "L476_CAN_start.h"


// Module-Global variables !!
static volatile uint8_t g_CAN_active = 0;	// a CAN frame arrived
static volatile uint8_t g_error = 0;		// error code
static volatile uint32_t g_rxframe[4];		// one complete received frame

/*
  *** Description **************************************************************
 *
 * Send routine.
 * Take id, dlc and the CAN message array with  max 8 bytes as input.
 * Transmit error is returned if TXB0 was not empty.
 * No transmit timeout is set. Function will hang if transmission fails.
 *
 ******************************************************************************
 */
int CAN_send(uint16_t id, uint8_t dlc, uint8_t *data)
{
    uint16_t count = 0;
	uint32_t temp_data[2] = {0};
	
	if((dlc > 8) || (dlc == 0))
	{
		set_errorcode(CAN_TX_ERROR);		// TX error
		return 1;							//error dlc too big or zero
	}
	// Compose frame in transmit mailbox 0 (TM0) and send
	if ((CAN->TSR & CAN_TSR_TME0) == CAN_TSR_TME0) 			// Only if TM0 empty
	{
		CAN->sTxMailBox[0].TIR =  (0 | (id<<21));		// 11 bit ID, IDE=0, RTR=0, TXRQ=0
		CAN->sTxMailBox[0].TDTR = (0 | dlc);			// set DLC, no Timestamp

		while (count < dlc)
		{
			*(((uint8_t *) temp_data)+count) = *(data+count);		//copy data to 32 bit array
			count++;
		}
		
		CAN->sTxMailBox[0].TDHR = temp_data[1];			// fill Transmit Data High Register with data[7:4]
		CAN->sTxMailBox[0].TDLR = temp_data[0];			// fill Transmit Data Low  Register with data[3:0]

		CAN->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;			// TXRQ=1, i.e. send one frame
		while ((CAN->TSR & CAN_TSR_TXOK0) != CAN_TSR_TXOK0);// wait till TXB0 is sent

		reset_errorcode();									// no error
		return 0;
	}
	else
	{
		set_errorcode(CAN_TX_ERROR);						// TX error
	}
	return 1;
}


/*
 *** Description **************************************************************
 *
 * Copy received frame from FIFO to SRAM.
 * ID | DLC | DataLO | DataHI
 *
 ******************************************************************************
 */
void copy_rxframe(void)
{
	g_rxframe[0] = CAN->sFIFOMailBox[0].RIR >> 21;	// copy id right bound
	g_rxframe[1] = CAN->sFIFOMailBox[0].RDTR;		// copy dlc and timestamp
	g_rxframe[2] = CAN->sFIFOMailBox[0].RDLR;		// copy data[3:0]
	g_rxframe[3] = CAN->sFIFOMailBox[0].RDHR;		// copy data[7:4]
}


/*
 *** Description **************************************************************
 *
 * Pass ID.
 *
 ******************************************************************************
 */
int get_CAN_id(void)
{
	uint32_t id;
	id = g_rxframe[0];
	return id;
}

/*
 *** Description **************************************************************
 *
 * Pass DLC.
 *
 ******************************************************************************
 */
int get_CAN_dlc(void)
{
	uint32_t dlc;
	dlc = g_rxframe[1];
	return dlc;
}

/*
 *** Description **************************************************************
 *
 * Pass DATA.
 *
 ******************************************************************************
 */
void get_CAN_data(uint8_t data[])
{
	data[0] = (uint8_t)(g_rxframe[2]);
	data[1] = (uint8_t)(g_rxframe[2] >> 8);
	data[2] = (uint8_t)(g_rxframe[2] >> 16);
	data[3] = (uint8_t)(g_rxframe[2] >> 24);
	data[4] = (uint8_t)(g_rxframe[3]);
	data[5] = (uint8_t)(g_rxframe[3] >> 8);
	data[6] = (uint8_t)(g_rxframe[3] >> 16);
	data[7] = (uint8_t)(g_rxframe[3] >> 24);
}


/*
 *** Description 80MHz_MSI ****************************************************
 *
 * Increase CPU Frequency to 80 MHz.
 * Set Flash to 1 WS.
 * Details see Project: L476_80MHz_MSI
 *
 ******************************************************************************
 */
void L476_80MHz_MSI(void)
{
	FLASH->ACR |= FLASH_ACR_LATENCY;					// Reduce Flash latency to 1 wait cycle
	while ((FLASH->ACR & FLASH_ACR_LATENCY) == 0); 		// Wait till done

	RCC->CR &= (uint32_t)(~RCC_CR_PLLON);				// Disable PLL. After reset default: RCC->CR &= ~(1<<24)
	while((RCC->CR & RCC_CR_PLLRDY) != 0);				// Wait until PLLRDY is cleared

	RCC->PLLCFGR |= (1<<13)|(1<<11);					// Configure PLL: 4 MHZ (default) *40 /2 (default) = 80 MHz. 40dez = 0x28.
	RCC->PLLCFGR &= ~(1<<12);							// clear the default preset bit
	RCC->PLLCFGR |= (1<<0);								// take MSI as input for PLL
	RCC->PLLCFGR |= (1<<24);							// activate PLL's clock output

	RCC->CR |= RCC_CR_PLLON; 							// enable PLL: RCC->CR |= (1<<24)
	while ((RCC->CR & RCC_CR_PLLRDY) == 0);				// Wait for PLL ready flag

	RCC->CFGR |= (5<<24);								// MCOSEL[2:0]=101: PLLCLK output
	RCC->CFGR |= (3<<0); 								// use PLL as SYSCLK
}


/*
 *** Description **************************************************************
 *
 * Pass CAN_active.
 *
 ******************************************************************************
 */
int is_CAN_active(void)
{
   return g_CAN_active;
}


/*
 *** Description **************************************************************
 *
 * Get CAN_active.
 *
 ******************************************************************************
 */
void get_CAN_active(void)
{
	g_CAN_active = (CAN->RF0R & ((uint32_t) 0x3));				// set to FIFO level
}


/*
 *** Description **************************************************************
 *
 * Decrease CAN_active.
 *
 ******************************************************************************
 */
void dec_CAN_active(void)
{
	g_CAN_active--;				// decrease
}


/*
 *** Description **************************************************************
 *
 * Pass error code.
 *
 ******************************************************************************
 */
int is_errorcode(void)
{
   return g_error;
}


/*
 *** Description **************************************************************
 *
 * Set error code.
 *
 ******************************************************************************
 */
void set_errorcode(uint8_t code)
{
	g_error = code;
}


/*
 *** Description **************************************************************
 *
 * Reset error code.
 *
 ******************************************************************************
 */
void reset_errorcode(void)
{
	g_error = 0;
}

