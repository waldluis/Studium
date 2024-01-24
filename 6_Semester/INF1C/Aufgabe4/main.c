/* ***************************************************************************************
 *  Project:    Embedded I, Aufgabe 4 - SPI
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
 *      09.10.2019  HL  create project
 *
 *  Status:     under development
 *
 *  Description:
 *      Change this code example to write and read data to/from FRAM.
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
#include "L476_FRAM.h"

/* ------------------------------------ DEFINES --------------------------------------- */
/* ------------------------------------ TYPE DEFINITIONS ------------------------------ */
#define MAX_LENGTH 512
/* ------------------------------------ GLOBAL VARIABLES ------------------------------ */
uint8_t read_data;
uint16_t read_data16;
uint16_t txbyte[MAX_LENGTH] =
{ 0 };
uint16_t rxbyte[MAX_LENGTH] =
{ 0 };
/* ------------------------------------ PRIVATE VARIABLES ----------------------------- */

/* ------------------------------------ PROTOTYPES ------------------------------------ */
void port_init(void);
void SPI1_init(void);
void delay(const uint16_t ms);
void send_512_bytes(void);
void receive_512_bytes(void);
void SPI_TRx_16(uint16_t txdata);

void SPI_TRx(uint8_t txdata);

/* ------------------------------------ MAIN ------------------------------------------ */
int main(void)
{

    /* --- initialization --- */
    __disable_irq();

    port_init();
    SPI1_init();

    __enable_irq();

    int ok = 1;
    int start = 1;

    //fill array with 1 to 512
    for (int i = 0; i <= MAX_LENGTH; i++)
    {
        txbyte[i] = i + 1;
    }

    for (;;)
    {
        //Start with S0
        if (((!(GPIOB->IDR & MASK_S0))) == 0x1 && start == 1)
        {
            GPIOC->ODR ^= (1 << 7);         //LED3 anschalten, Prozess starten
            start = 0;

            send_512_bytes();

            receive_512_bytes();

            //check data
            for (int i = 0; i < 256; i++)
            {
                if (txbyte[i] != rxbyte[i])
                {
                    ok = 0;
                }
            }

            //Switch on LED to show if data right
            if (ok == 1)
            {
                GPIOC->ODR ^= (1 << 6);         //LED2 green on -> no error
            }
            else
            {
                GPIOC->ODR ^= (1 << 4);         //LED0 red on -> error
            }
            GPIOC->ODR ^= (1 << 7);         //LED3 blue off -> process done
        }

        //Reset with S1 to start again with
        if ((!(GPIOB->IDR & MASK_S1)) == 0x1)
        {
            start = 1;                                  // reset start variable
            ok = 1;                                     // reset to data ok
            GPIOC->ODR |= (0xF << 4);                   // all LEDs off

            for(int i = 0; i < MAX_LENGTH; i++)         // reset received data
            {
                rxbyte[i] = 0;
            }
        }
    }
    return 1;
}

/* ------------------------------------ GLOBAL FUNCTIONS ------------------------------ */

/* ------------------------------------------------------------------------------------ *\
 * method:  void port_init(void)
 *
 * requires:    - nothing -
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
void port_init(void)
{
    // Enable PC clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOAEN;  // PC clock on
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;    //PB clock on

    GPIOA->MODER &= ~0xFF00; // delete the default values for PA4-7
    GPIOA->ODR |= (1 << 4); // PA4 = PCS is inactive
    GPIOA->MODER |= (1 << 8); // PA4 is output

    GPIOA->MODER |= (1 << 11); // PA5 is alternate function (SPI1-SCK)
    GPIOA->MODER |= (1 << 13); // PA6 is alternate function (SPI1-MISO)
    GPIOA->MODER |= (1 << 15); // PA7 is alternate function (SPI1-MOSI)
    GPIOA->AFR[0] |= (5 << GPIO_AFRL_AFSEL5_Pos); // AF5 is SPI1-SCK @ PA5
    GPIOA->AFR[0] |= (5 << GPIO_AFRL_AFSEL6_Pos); // AF5 is SPI1-MISO @ PA6
    GPIOA->AFR[0] |= (5 << GPIO_AFRL_AFSEL7_Pos); // AF5 is SPI1-MOSI @ PA7

    GPIOA->OSPEEDR |= (2 << 8) | (2 << 10) | (2 << 12) | (2 << 14); // PA4-7: high speed

    // LED setup: PC7..PC4 are outputs, PC7 is #CS
    GPIOC->MODER = ( GPIOC->MODER & ~0xFF00) | 0x5500;
    GPIOC->OTYPER |= 0xF0; // Set to open drain
    GPIOC->ODR |= 0xF0; // all LEDs off at the beginning

    //Button S0 to start writing
    GPIOB->MODER &= ~(0x03 << 0);           // PB0 set to input
    GPIOB->PUPDR &= ~(0x3 << 0);
    GPIOB->PUPDR |= (0x01 << 0);            // Pullup-Widerstand setzen

    /*GPIO S1 init*/
    GPIOB->MODER &= ~(0x03 << 2);           // PB1 set to input
    GPIOB->PUPDR &= ~(0x3 << 2);
    GPIOB->PUPDR |= (0x01 << 2);            // Pullup-Widerstand setzen

}

/* ------------------------------------------------------------------------------------ *\
 * method:  void SPI1_init()
 *
 * requires:    - nothing -
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
void SPI1_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // SPI1 clock on

    SPI1->CR1 |= SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_SSM | SPI_CR1_SSI;

    SPI1->CR2 |= SPI_CR2_FRXTH;
    SPI1->CR1 |= SPI_CR1_SPE;
}

/* ------------------------------------------------------------------------------------ *\
 * method:  void green_led_on(void)
 *
 * requires:    - nothing -
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */

/* SPI send one byte */
void SPI_TRx(uint8_t txdata)
{
    *(uint8_t*) &( SPI1->DR) = txdata;
    while (( SPI1->SR & SPI_SR_TXE) != SPI_SR_TXE)
        ;

    while (( SPI1->SR & SPI_SR_RXNE) != SPI_SR_RXNE)
        ;
    read_data = (uint8_t) SPI1->DR;
}

// SPI send two byte
void SPI_TRx_16(uint16_t txdata)
{
    SPI_TRx(txdata);                    // Write low byte
    read_data16 = read_data;            // Read low byte
    SPI_TRx(txdata >> 8);               // Write high byte
    read_data16 |= read_data << 8;      // Read high byte
}

/* ------------------------------------------------------------------------------------ *\
 * method:  void delay(const uint16_t ms)
 *
 * It realizes a millisecond delay by very bad busy-wait.
 *
 * requires:    - nothing -
 * parameters:  ms - delay time in milliseconds
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
void delay(const uint16_t ms)
{
    for (uint16_t i = 0; i < ms; ++i)
    {
        for (uint16_t j = 0; j < 400; ++j)
        {
            __asm( "NOP" );
        }
    }
}

// function writes 16 bit to two 8 bit in FRAM
void send_512_bytes(void)
{
    //Enable FRAM Write
    GPIOA->ODR &= ~(1 << 4);
    SPI_TRx(FRAM_WREN);
    GPIOA->ODR |= (1 << 4);

    //Write to FRAM
    GPIOA->ODR &= ~(1 << 4);
    SPI_TRx(FRAM_WRITE);
    SPI_TRx_16(0 >> 10);
    SPI_TRx_16(0);
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        SPI_TRx_16(txbyte[i]);
    }
    GPIOA->ODR |= (1 << 4);
}

// function read 16 bit from two 8 bit in FRAM
void receive_512_bytes(void)
{
    //Read from FRAM
    GPIOA->ODR &= ~(1 << 4);
    SPI_TRx(FRAM_READ);
    SPI_TRx_16(0 >> 10);
    SPI_TRx_16(0);
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        SPI_TRx_16(0x55);
        rxbyte[i] = read_data16;
    }
    GPIOA->ODR |= (1 << 4);
}

/* ------------------------------------ PRIVATE FUNCTIONS ----------------------------- */

/* ************************************ E O F ***************************************** */
