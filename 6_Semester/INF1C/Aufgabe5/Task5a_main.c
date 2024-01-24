/*
 ******************************************************************************
 *
 * Project:     CAN send and receive 8 Byte with receive ISR
 * Name:        L476_CAN_start
 * Part:        Main
 * Author:      Peter Urbanek
 * Compiler:    AVR-GCC in AC6
 * Hardware:    Nucleo Board with STM32L476
 * Version:     1.0
 * History:     12.04.2018  first entry
 * Status:      running
 *
 ******************************************************************************
 */

/*
 *** Description **************************************************************
 *
 * Send own ID = 0x400.
 * Receive from 0xF0...0xF3 and 0xFF.
 *
 * Press the blue button to send a frame with ID 0x400 and Data[0] = 0x01.
 * Reception is always active.
 *
 * This program implements both, a CANbutton and CANled routine known from AVR.
 * Three components are realized:
 *-  CANinit with filter and mask management
 * - CANsend from TXB0
 * - CANreceive as ISR: CAN1_RX0_IRQHandler. A frame is received in RXB0 only.
 *
 * Test arrangement sender:
 * Change L053 node's filter from 0xF0 to 0x400.
 * Connect L053_CAN_receive400 and this node to the CAN. Press the button to send
 * with this node and receive with the L053 node.

 * Test arrangement receiver:
 * Connect L053_CAN_sendF0 and this node to the CAN. Press the button at the
 * L053 node to send a frame that is received with this node.
 *
 * Test arrangement with efiCAN:
 * Also efiCAN nodes with the CAN_receive program can be used as partner.
 * Change efiCAN's filter ID to 0x400 and evaluate Data[0].
 * Data[0] is fixed to 0x01 here, which toggles the yellow LED on the efiCAN board.
 *
 * Test arrangement with a CAN tester:
 * For receiving with this node, the CAN tester produces frames with
 * IDs 0xF0 to 0xF3 and 0xFF.
 * If a frame with one of these ID arrives, the ISR is entered and g_CANactive
 * is incremented. This node should listen to these IDs. Watch g_CAN_active!
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
 * Transceiver Pin 8 = S = 0 V
 *
 ******************************************************************************
 */

/* ------------------------------------ INCLUDES -------------------------------------- */
#include "L476_CAN_start.h"

/* ------------------------------------ DEFINES --------------------------------------- */
/* ------------------------------------ TYPE DEFINITIONS ------------------------------ */
/* ------------------------------------ GLOBAL VARIABLES ------------------------------ */
/* ------------------------------------ PRIVATE VARIABLES ----------------------------- */
/* ------------------------------------ PROTOTYPES ------------------------------------ */
static void GPIO_init(void);
static void EXTI_init(void);

/* ------------------------------------ MAIN ------------------------------------------ */

/*int main(void)
 {
 // Init system
 __disable_irq();                        // Disable Interrupts
 L476_80MHz_MSI();                       // Change to 80 MHz
 GPIO_init();                            // Init GPIO
 EXTI_init();
 __enable_irq();                         // Enable Interrupts

 while (1)
 {
 }

 }*/

int main(void)
{
    // Local variables
    uint32_t i, w;
    uint32_t can_id = MY_ID;                // preset CAN ID for efiCAN node
    uint8_t tx_candata[8] =
    { 0 };          // transmit array
    uint8_t rx_candata[8];                  // receive array
    uint32_t rx_dlc;                        // receive dlc
    uint32_t rx_id;                         // receive id

    // Init system
    __disable_irq();                        // Disable Interrupts
    L476_80MHz_MSI();                       // Change to 80 MHz
    CAN_port_init();                        // Init ports
    CAN_init(can_id);                       // Init CAN
    GPIO_init();                            // Init GPIO
    EXTI_init();
    __enable_irq();                         // Enable Interrupts

    // Preset test parameters
    tx_candata[0] = LED_yellow_efiCAN;          // preset with code for yellow led on efiCAN board

    // Endless loop
    while (1)
    {
        // Send part
        if (!BL_BUTTON)                     // if button was pressed
        {
            CAN_send8(tx_candata);          // send one frame
            LEDFLASH
            ;
            // note sending
        }

        // Receive Part
        if (is_CAN_active() > 0)            // a frame is in the global array
        {
            rx_id = get_CAN_id();           // read ID (not used here)
            rx_dlc = get_CAN_dlc();         // read DLC (not used here)
            get_CAN_data(rx_candata);       // read DATA
            if (rx_candata[0] == LED_yellow_efiCAN) // yellow led (=1) code?
            {
                LEDFLASH
                ;
                // note receiving
            }

            // Check transfer errors
            if (is_errorcode() != 0)        // any errors?
            {
                tx_candata[0] = ERROR_code;     // TYPE is ERROR
                tx_candata[1] = CAN_RX_ERROR;   // CODE is CAN_RX_ERROR
                tx_candata[2] = 0;              // clear the rest
                tx_candata[3] = 0;
                tx_candata[4] = 0;
                tx_candata[5] = 0;
                tx_candata[6] = 0;
                tx_candata[7] = 0;
                CAN_send8(tx_candata);      // send error frame now

                reset_errorcode();          // clear error now

                for (i = 0; i < 10; i++)        // LED_gn on for a long time.
                {
                    LEDFLASH
                    ;
                    // Later: red LED.
                }
            }
            dec_CAN_active();               // one frame processed
        }
    }
    return 1;
}

/* ------------------------------------ GLOBAL FUNCTIONS ------------------------------ */
static void GPIO_init(void)
{
    /* enable port clocks */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    /* GPIO LED0 init*/
    GPIOC->ODR |= MASK_LED0; // default is LED off
    GPIOC->MODER &= ~(0x03 << 8); // clear mode bits for PC4
    GPIOC->MODER |= (0x01 << 8); // set PC4 to output

    /* GPIO LED1 init*/
    GPIOC->ODR |= MASK_LED1; // default is LED off
    GPIOC->MODER &= ~(0x03 << 10); // clear mode bits for PC5
    GPIOC->MODER |= (0x01 << 10); // set PC5 to output

    /* GPIO LED2 init*/
    GPIOC->ODR |= MASK_LED2; // default is LED off
    GPIOC->MODER &= ~(0x03 << 12); // clear mode bits for PC6
    GPIOC->MODER |= (0x01 << 12); // set PC6 to output

    /* LED3 init */
    GPIOC->ODR |= MASK_LED3; // default is LED off
    GPIOC->MODER &= ~(0x03 << 14); // clear mode bits for PC7
    GPIOC->MODER |= (0x01 << 14); // set PC6 to output

    /*GPIO S0 init*/
    GPIOB->MODER &= ~(0x03 << 0); // PB0 set to input
    GPIOB->PUPDR &= ~(0x3 << 0);
    GPIOB->PUPDR |= (0x01 << 0); // Pullup-Widerstand setzen

    /*GPIO S1 init*/
    GPIOB->MODER &= ~(0x03 << 2); // PB1 set to input
    GPIOB->PUPDR &= ~(0x3 << 2);
    GPIOB->PUPDR |= (0x01 << 2); // Pullup-Widerstand setzen

    /*GPIO S2 init*/
    GPIOB->MODER &= ~(0x03 << 4); // PB2 set to input
    GPIOB->PUPDR &= ~(0x3 << 4);
    GPIOB->PUPDR |= (0x01 << 4); // Pullup-Widerstand setzen

    /*GPIO S3 init*/
    GPIOB->MODER &= ~(0x03 << 6); // PB3 set to input
    GPIOB->PUPDR &= ~(0x3 << 6);
    GPIOB->PUPDR |= (0x01 << 6); // Pullup-Widerstand setzen
}

static void EXTI_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;                   // activate clock for SYSCFG at APB2

    //EXTI0
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PB;           // PB0 -> EXTI0
    EXTI->IMR1 |= EXTI_IMR1_IM0;                            // activate interrupts for PB0
    EXTI->FTSR1 |= EXTI_FTSR1_FT0;                          // falling edge for PB0

    NVIC_SetPriority(EXTI0_IRQn, 3);                        // set proirity for interrupt IRQ6 to 3
    NVIC_ClearPendingIRQ(EXTI0_IRQn);                       // clear pending bit for IRQ6
    NVIC_EnableIRQ(EXTI0_IRQn);                             // set interrupt for IRQ6

    //EXTI1
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PB;           // PB1 -> EXTI1
    EXTI->IMR1 |= EXTI_IMR1_IM1;                            // activate interrupts for PB1
    EXTI->FTSR1 |= EXTI_FTSR1_FT1;                          // falling edge for PB1

    NVIC_SetPriority(EXTI1_IRQn, 3);                        // set proirity for interrupt IRQ7 to 3
    NVIC_ClearPendingIRQ(EXTI1_IRQn);                       // clear pending bit for IRQ7
    NVIC_EnableIRQ(EXTI1_IRQn);                             // set interrupt for IRQ7

    //EXTI2
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PB;           // PB2 -> EXTI2
    EXTI->IMR1 |= EXTI_IMR1_IM2;                            // activate interrupts for PB2
    EXTI->FTSR1 |= EXTI_FTSR1_FT2;                          // falling edge for PB2

    NVIC_SetPriority(EXTI2_IRQn, 3);                        // set proirity for interrupt IRQ8 to 3
    NVIC_ClearPendingIRQ(EXTI2_IRQn);                       // clear pending bit for IRQ8
    NVIC_EnableIRQ(EXTI2_IRQn);                             // set interrupt for IRQ8

    //EXTI3
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PB;           // PB3 -> EXTI3
    EXTI->IMR1 |= EXTI_IMR1_IM3;                            // activate interrupts for PB3
    EXTI->FTSR1 |= EXTI_FTSR1_FT3;                          // falling edge for PB3

    NVIC_SetPriority(EXTI3_IRQn, 3);                        // set proirity for interrupt IRQ9 to 3
    NVIC_ClearPendingIRQ(EXTI3_IRQn);                       // clear pending bit for IRQ9
    NVIC_EnableIRQ(EXTI3_IRQn);                             // set interrupt for IRQ9
}
/* ------------------------------------ PRIVATE FUNCTIONS ----------------------------- */

/* ************************************ E O F ***************************************** */
