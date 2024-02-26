/* *****************************
 *  Project:    Embedded II, MC33999
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
 ****************************** */


#include "STefi_Stud.h"
#include "stm32l476xx.h"
#include "core_cm4.h"

void port_init(void);
void TIM6_init(void);

#if 1

void SPI1_init();

uint8_t SPI_WriteByte(uint8_t txdata);

void send24BitCommand(uint32_t command);

#endif

// global variables
#if 1
uint8_t SetupTimeElapsed = 0;

#define CS_0()        (GPIOA->ODR &= ~GPIO_ODR_OD1) // CS low
#define CS_1()        (GPIOA->ODR |= GPIO_ODR_OD1)  // CS high

#endif

int main(void) {

    /* --- initialization --- */
    __disable_irq();

    // Stop Timers, when CPU is halted by debugger
    DBGMCU -> APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM6_STOP;

    port_init();

    SPI1_init();

    TIM6_init();

    __enable_irq();

    //TIM6 -> CR1 |= TIM_CR1_CEN; //Start Timer
    //TIM6->CR1 &= ~TIM_CR1_CEN;  //Stop Timer

    uint32_t baseCommand = 0x00000000; //0x##00XXXX;


    //PC1:
    GPIOC->ODR &= ~GPIO_ODR_OD1; //Pin PC1 auf High setzen
    while (SetupTimeElapsed == 0) {
        TIM6 -> CR1 |= TIM_CR1_CEN; //Start Timer
        __WFI();
    }
    GPIOC->ODR |= GPIO_ODR_OD1;

    uint32_t ledCommand;
#if 1
    //Testsequenz:
    CS_0();

    uint8_t txdata = 1;

    SPI_WriteByte(txdata);
    txdata = 2;
    SPI_WriteByte(txdata);
    txdata = 3;
    SPI_WriteByte(txdata);

    uint8_t test1 = SPI_WriteByte(txdata);
    uint8_t test2 = SPI_WriteByte(txdata);
    uint8_t test3 = SPI_WriteByte(txdata);


    CS_1();

    ledCommand = baseCommand | (1 << (15 - 0));

    send24BitCommand(ledCommand);
#endif

    for (;;) {

        for (uint32_t i = 0; i < 16; ++i) {

            ledCommand = baseCommand | (1 << (15 - i));

            send24BitCommand(ledCommand);


            //Verzögerung, um die Geschwindigkeit des Lauflichts zu steuern:
            for (uint32_t j = 0; j < 50000; ++j) {
                __NOP();
            }

        }

    }
}

/*
 * Description **********************
 *
 * Init port PC7 as output (LED3, blue).
 *
 **************************
 */
void port_init(void) {
    // Enable PC clock
    //RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;	// PC clock on

    // STefi LEDs
    //GPIOC->ODR |= (0xF<<4);						// all LEDs off at the beginning
    //GPIOC->MODER &= ~(1<<15) ;					// PC7 is output (LED3), driver strength is weak

#if 1
    //GPIO initialisieren:

    //1) PA and PC clock on:
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;

    //2) Festlegen welche spezifische Funktion (-> SPI) die Pins PA5, PA6 und PA7 ausführen sollen:
    GPIOA->AFR[0] |= (5 << GPIO_AFRL_AFSEL5_Pos);
    GPIOA->AFR[0] |= (5 << GPIO_AFRL_AFSEL6_Pos);
    GPIOA->AFR[0] |= (5 << GPIO_AFRL_AFSEL7_Pos);

    //3) Betriebsmodus (Mode) für die Pins PA 5, PA6 und PA7 festlegen -> Alternate Function:

    //4) High-Speed-Modus für PA5, PA6 und PA7-> Ausgangsgeschwindigkeit der Pins setzen -> schnelle Signalwechsel:
    GPIOA->OSPEEDR |= (2 << 10) | (2 << 12) | (2 << 14);

    //5) PA1 = /SS:
    GPIOA->MODER = 0xABFFABF7;
    GPIOA->ODR |= GPIO_ODR_OD1;

    //6) PC0 = SOPWR:
    GPIOC->ODR |= GPIO_ODR_OD0;

    //7) PC1:
    GPIOC->MODER = 0xFFFFFFF5;
    GPIOC->ODR |= GPIO_ODR_OD1;

#endif
}

void SPI1_init() {

    // SPI1 (Pins PA4 - PA7) & SPI-Controller initialisieren:

    //1) SPI1 clock on:
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    //2) SPI1 Parameter setzen:

    SPI1->CR1 |= SPI_CR1_MSTR //SPI1-Controller als Master konfigurieren
            | SPI_CR1_BR_1 //Baudrate-Teiler konfigurieren -> Baudrate für die SPI-Kommunikation auf clk/8 setzen (^= SPI clock)
            | SPI_CR1_CPHA; //Clock Phase (CPHA) auf 1 konfigurieren -> Mode 1: CPOL=0, CPHA=1

    SPI1->CR2 |= SPI_CR2_FRXTH;

    SPI1->CR2 |= SPI_CR2_SSOE;

    //3) Enable SPI:
    SPI1->CR1 |= SPI_CR1_SPE;
}

void send24BitCommand(uint32_t command) {

    uint8_t rxdata;

    uint8_t byte1 = (command >> 16) & 0xFF;
    uint8_t byte2 = (command >> 8) & 0xFF;
    uint8_t byte3 = command & 0xFF;

    SetupTimeElapsed = 0;

    //1)
    CS_0();

    //2)
    //while(SetupTimeElapsed == 0){
    //TIM6 -> CR1 |= TIM_CR1_CEN; //Start Timer
    //__WFI();
    //}

    //3)
    while ((SPI1->SR & SPI_SR_TXE) != SPI_SR_TXE); //Ist der Sendepuffer bereit ein weiteres Byte zu akzeptieren?
    *(uint8_t *)&(SPI1->DR) = byte1;

    while ((SPI1->SR & SPI_SR_RXNE) != SPI_SR_RXNE); //Sind Daten im Empfangsbuffer verfügbar?
    rxdata = (uint8_t) SPI1->DR;

    while ((SPI1->SR & SPI_SR_TXE) != SPI_SR_TXE);
    *(uint8_t *)&(SPI1->DR) = byte2;

    while ((SPI1->SR & SPI_SR_RXNE) != SPI_SR_RXNE);
    rxdata = (uint8_t) SPI1->DR;

    while ((SPI1->SR & SPI_SR_TXE) != SPI_SR_TXE);
    *(uint8_t *)&(SPI1->DR) = byte3;

    while ((SPI1->SR & SPI_SR_RXNE) != SPI_SR_RXNE);
    rxdata = (uint8_t) SPI1->DR;

    //4)
    CS_1();


    return rxdata;
}

uint8_t SPI_WriteByte(uint8_t txdata) {

    //SPI send&receive one byte:

    uint8_t rxdata;
    while ((SPI1->SR & SPI_SR_TXE) != SPI_SR_TXE);
    *(uint8_t *)&(SPI1->DR) = txdata;

    while ((SPI1->SR & SPI_SR_RXNE) != SPI_SR_RXNE);
    rxdata = (uint8_t) SPI1->DR;

    return rxdata;
}

/* ------------------------------------------------------------------------------------ *\
 *
 * Timer 6 runs with 4 MHz system clock, prescaler is 4000 (4000 -1).
 * ARR is 249 for 250 ms
 *
 * parameters:  - none -
 * returns:     - nothing -
\* ------------------------------------------------------------------------------------ */
void TIM6_init(void) {
    RCC -> APB1ENR1 |= RCC_APB1ENR1_TIM6EN; // enable clock

    TIM6 -> PSC = 3999; // Timer runs with 1 kHz
    //TIM6 -> ARR  = 249;
    TIM6 -> ARR = 100; //->100ms
    TIM6 -> DIER |= TIM_DIER_UIE; // enable interrupt generation
    TIM6 -> CR1 |= TIM_CR1_ARPE; // enable shadow registers
    TIM6 -> EGR |= TIM_EGR_UG; // reset Timer
    TIM6 -> SR &= ~TIM_SR_UIF; // Clear Timer Interrupt flag

    NVIC_SetPriority(TIM6_DAC_IRQn, 15); // set lowest prio
    NVIC_ClearPendingIRQ(TIM6_DAC_IRQn); // clear potentially pending bits
    NVIC_EnableIRQ(TIM6_DAC_IRQn); // enable interrupt in NVIC
}
