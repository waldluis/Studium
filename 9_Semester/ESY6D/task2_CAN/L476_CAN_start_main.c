/*
 ******************************************************************************
 *
 * Project:		CAN send and receive with receive ISR
 * Name:    	L476_CAN_start
 * Part:     	Main
 * Author:     	Peter Urbanek, Holger Lenkowski
 * Compiler:   	AVR-GCC in AC6
 * Hardware:   	STefi with Nucleo-STM32L476
 * Version:    	1.1
 * History: 	12.04.2018	PU first entry
 *              17.10.2022  HL changed for control of the LEGO car
 *      		06.09.2023  HL acknowledgement CAN paket from car added
 * Status:		running
 *
 ******************************************************************************
*/

/*
 *** Description **************************************************************
 *
 * CAN control for LEGO car:
 * (in addition of diploma theses of Manuel Meschnig
 * "Aufbau einer Entwicklungsumgebung unter Einbindung des CAN-Busses
 * zur Simulation von Sensoren und Aktoren eines Kfz" from 2002)
 *
 * Send CAN packages to the car to control motor speed, steering and the lights of the LEGO car.
 * Check the acknowledgement packages from the car!
 *
 * The Car receives from 0x200 ... 0x20F and 0xFF,
 * and the Car sends acknowledgement at = 0x400 ... 0x40F (see CAN_Car.h).
 *
 * Reception is always active.
 *
 *
 * The CAN parameters obey to the Embedded Lab CAN: 500kbit/s, sample at 75%.
 * Here, the CPU frequency and the CAN module's entry frequency are set to 80 MHz.
 *
 * A physical connection with the transceiver must be established.
 * Connect hardware:
 * Transceiver Pin 1 = TXD = PA12
 * Transceiver Pin 2 = 0 V
 * Transceiver Pin 3 = 3,3 V
 * Transceiver Pin 4 = RXD = PA11
 * Transceiver Pin 5 = nc
 * Transceiver Pin 6 = CANL
 * Transceiver Pin 7 = CANH
 * Transceiver Pin 8 = S = PB4 (set CAN_RTX_S low to enable CAN transceiver)
 *
 ******************************************************************************
 */


#include "L476_CAN_start.h"
#include "CAN_Car.h"
			
/* Global variables ----------------------------------------------------------*/
uint8_t  g_S0_pressed = 0;
uint8_t  g_S1_pressed = 0;
uint8_t  g_S2_pressed = 0;
uint8_t  g_S3_pressed = 0;

int main(void)
{
	// Local variables
	uint32_t i, w;
	uint8_t tx_candata[8] = {0};			// transmit array
	uint8_t rx_candata[8];					// receive array
	uint32_t rx_dlc;						// receive dlc
	uint32_t rx_id;							// receive id
	int j = 0;
	uint8_t data[8] = {0};

	// Init system
	__disable_irq();						// Disable Interrupts
	DBGMCU -> APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM6_STOP;	// Stop timer in Debug mode, when CPU is halted

	L476_80MHz_MSI();						// Change to 80 MHz
	CAN_port_init();						// Init ports
	CAN_init();								// Init CAN
	TIM6_init();
	__enable_irq();							// Enable Interrupts

	// Endless loop
	while(1)
	{

		// do something if button S0 was pressed
		if (g_S0_pressed)						
		{
			GPIOC->ODR |= (0xF<<4);
			// put your code here
			if(j == 0)
			{
				data[0] = 0x1;
				CAN_send(BLINKER_RIGHT, 1, data);
				j = 1;
			}
			else
			{
				data[0] = 0x0;
				CAN_send(BLINKER_RIGHT, 0x1, data);
				j = 0;
			}
			g_S0_pressed = 0;
		}

		// Receive Part
		if (is_CAN_active() > 0 )			// a frame is in the global array
		{
			rx_id = get_CAN_id();			// read ID (not used here)
			rx_dlc = get_CAN_dlc();			// read DLC (not used here)
			get_CAN_data(rx_candata);		// read DATA
			
			// put your code here

			if(rx_id == ACK_BLINKER_RIGHT)
			{
				if(rx_candata[0] == data[0])			// Data right
				{
					GPIOC->ODR &= (0xB<<4);
				}
				else									// Data false
				{
					GPIOC->ODR &= (0xE<<4);
				}
			}


			// Check transfer errors
			if (is_errorcode() != 0 )		// any errors?
			{
				tx_candata[0] = ERROR_code;		// TYPE is ERROR
				tx_candata[1] = CAN_RX_ERROR;	// CODE is CAN_RX_ERROR
				tx_candata[2] = 0;				// clear the rest
				tx_candata[3] = 0;
				tx_candata[4] = 0;
				tx_candata[5] = 0;
				tx_candata[6] = 0;
				tx_candata[7] = 0;
				CAN_send(ID_ERROR, 8, tx_candata);		// send error frame now

				reset_errorcode();			// clear error now

				for (i=0; i<10; i++)    	// red LED on for a long time.
				{
					LEDFLASH;			
				}
			}
			dec_CAN_active();				// one frame processed
		}
		
		__WFI();
	}
	return 1;
}

