/* ***************************************************************************************
* Project: task1 - running LED
* File: main.c
*
* Language: C
*
* Hardware: STefi v1.0b
* Processor: STM32L476RG
*
* Author: Manuel Lederhofer
* Datum: 02.09.2019
*
* Version: 0.1
* History:
* 02.09.2019 ML create project, implement LED blinker example
*
* Status: under development
*
* Description:
* Change this code example to a running LED.
* See the description and requirements of the requested application
* in the lab exercise guide.
*
*
* Notes:
* - default MCU speed at startup is ~ 4 MHz.
*
************************************************************************************** */



/* ------------------------------------ INCLUDES -------------------------------------- */
#include "STefi_Stud.h"
#include "stm32l476xx.h"
#include "core_cm4.h"



/* ------------------------------------ DEFINES --------------------------------------- */
/* ------------------------------------ TYPE DEFINITIONS ------------------------------ */
/* ------------------------------------ GLOBAL VARIABLES ------------------------------ */
static int start = 0;
static int rueck = 1;



/* ------------------------------------ PRIVATE VARIABLES ----------------------------- */



/* ------------------------------------ PROTOTYPES ------------------------------------ */
void delay(const uint16_t ms);
static void GPIO_init(void);
static int LED_SCHIEBEN(int rueck, int start);
static int TASTER_ABFRAGE(void);



/* ------------------------------------ MAIN ------------------------------------------ */
int main(void)
{
    /* --- initialization --- */
    __disable_irq();
    GPIO_init(); // LEDs and buttons
    __enable_irq();

    /* --- one time tasks --- */
    // none
    /* --- infinite processing loop --- */
    while (1)
    {
        //Variablendef. zum Zurücksetzen und starten
        //Abfrage nach momentaner Tasterstellung
        if (start != TASTER_ABFRAGE())
        {
            rueck = 1;
            start = LED_SCHIEBEN(rueck, start);
        }
        else
        {
            rueck = 0; //zurücksetzen auf LED0 bei erneuter Tasterbetätigung
            start = LED_SCHIEBEN(rueck ,start);
        }
    }
    return 1;
}



/* ------------------------------------ GLOBAL FUNCTIONS ------------------------------ */



/* ------------------------------------------------------------------------------------ *\
* method: void delay(const uint16_t ms)
*
* It realizes a millisecond delay by very bad busy-wait.
*
* requires: - nothing -
* parameters: ms - delay time in milliseconds
* returns: - nothing -
\* ------------------------------------------------------------------------------------ */
void delay(const uint16_t ms)
{
    for (uint16_t i = 0; i < ms; ++i)
    {
        for (uint16_t j = 0; j < 400; ++j)
        {
            __asm("NOP");
        }
    }
}



/* ------------------------------------ PRIVATE FUNCTIONS ----------------------------- */
//Delay function with button
static int delay_taster(const uint16_t ms)
{
    for (uint16_t i = 0; i < ms; ++i)
        {
        for (uint16_t j = 0; j < 400; ++j)
        {
            if (TASTER_ABFRAGE())
            {
                return 1;
            }
            else
            {
                __asm("NOP");
            }
        }
    }
    return 0;
}


/* ------------------------------------------------------------------------------------ *\
* method: void LED_SCHIEBEN(int rueck)
*
* walks through the LED-Lights and back
*
* requires: -"stm32f411xe.h" "STefi.h" "uart.h"
* parameters: -rueck variable to reset the process back to idle state-
* returns: - nothing -
\* ------------------------------------------------------------------------------------ */
int LED_SCHIEBEN(int rueck, int start)
{
    //Variablen zum speichern des momentanen Zustandes und zurücksetzen
    static int vergleich = 1, count = 0, schieben = 4;

    //Durchlauf von LED0-LED3
    if (count < 4 && vergleich == rueck)
    {
        GPIOC->ODR ^= (1 << schieben);
        //LED anschalten
        if (delay_taster(30) == 1)
        {
            GPIOC->ODR ^= (1 << schieben); //LED ausschalten
            rueck = 0;
            count = 0;
            return 0;
        }

        GPIOC->ODR ^= (1 << schieben); //LED ausschalten
        schieben++; //ansteuern der nächsten LED
        count++;
        return 1;
    }
    //Rücklauf von LED3-LED0
    else if (count >= 4 && count <= 5 && vergleich == rueck)
    {
        schieben--; //ansteuern der vorherigen LED
        GPIOC->ODR ^= (1 << (schieben - 1)); //LED anschalten

        if (delay_taster(30) == 1)
        {
            GPIOC->ODR ^= (1 << (schieben - 1)); //LED ausschalten
            rueck = 0;
            start = 0;          //Überflüssig
            return 0;
        }

        GPIOC->ODR ^= (1 << (schieben - 1)); //LED ausschalten
        count++;
        return 1;//zurücksetzen der Parameter auf Anfang
    }
    else
    {
        count = 0;
        schieben = 4;
        if(rueck == 1)
            return 1;
        else
            return 0;
    }
}


/* ------------------------------------------------------------------------------------ *\
* method: static int TASTER_ABFRAGE(void)
*
* finds out the switches current position and returns it´s value
*
* requires: -"stm32f411xe.h" "STefi.h" "uart.h"
* parameters: -nothing-
* returns: - current position -
\* ------------------------------------------------------------------------------------ */
static int TASTER_ABFRAGE(void)
{
    //Variable zum speichern der momentanen Tasterstellung
    static int taster_stellung = 0;

    //Abfrage ob Taster gedrückt wurde und vorherige Stellung 0 war->Rückgabe 1
    if ((!(GPIOB->IDR & MASK_S0)) == 0x1 && taster_stellung == 0x0)
    {
        delay(10);
        taster_stellung = 1;
        return 1;
    }
    //bei loslassen des tasters wird die Stellung auf 0 -> Rückgabe 0(erneutes Drücken möglich
    else if ((!(GPIOB->IDR & MASK_S0)) != 0x1)
    {
        delay(10);
        taster_stellung = 0;
        return 0;
    }
    //wird der Taster gedrückt gehalten -> Rückgabe 0
    else
        return 0;
}


/* ------------------------------------------------------------------------------------ *\
* method: static void GPIO_init(void)
*
* Initializes GPIOs on STefi for pins with peripherals attached.
* LED0 (red) on PC4
* LED1 (yellow) on PC5
* LED2 (green) on PC6
* LED3 (blue) on PC7
*
* requires: - nothing -
* parameters: - none -
* returns: - nothing -
\* ------------------------------------------------------------------------------------ */
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
}
/* ************************************ E O F ***************************************** */
