/* ***************************************************************************************
 *  Project:    task1 - running LED with key control
 *  File:       task1.c
 *
 *  Language:   C
 *
 *  Hardware:   STefi-Simulator
 *  Processor:  STM32F411x
 *
 *  Author:     Holger Lenkowski
 *  Datum:      10.03.2020
 *
 *  Version:    0.1
 *  History:
 *      10.03.2020  HL  create project, implement LED blinker example
 *      09.04.2020  FPN Adapted for the F411-based STefi - Simulator
 *      09.04.2020  FPN Added simple UART support
 *      18.09.2020  ML  add: formatting, comments
 *
 *  Status:     under development
 *
 *  Description:
 *          Currently, red LED0 blinks.
 *          This file contains the main routine and the initialization.
 *
 *  Expected program/system behaviour:
 *          Walking light in both directions with 8 Hz (one LED to the next).
 *          The walking light is started and stopped with S0.
 *
 *  Notes:
 *      - processing speed of the simulator varies depending on computer performance
 *
 ************************************************************************************** */

/* ------------------------------------ INCLUDES -------------------------------------- */
#include <stdio.h>
#include "stm32f411xe.h"
#include "STefi.h"
#include "uart.h"

/* ------------------------------------ DEFINES --------------------------------------- */
#define WAITTIME_WALKING_LIGHT  125         // 125 ms
#define WAITTIME_DEBOUNCE       10          // 10 ms

#define LOOPS_PER_MS    5000        // NOP-loops for 1 ms, experiment to get it right

/* ------------------------------------ TYPE DEFINITIONS ------------------------------ */
/* ------------------------------------ GLOBAL VARIABLES ------------------------------ */
/* ------------------------------------ PRIVATE VARIABLES ----------------------------- */

/* ------------------------------------ PROTOTYPES ------------------------------------ */
static void GPIO_init(void);
static void delay(const uint16_t ms);
static void test_number_to_UART(void);

/* ------------------------------------ M A I N --------------------------------------- */
int main(void)
{
    /* --- initialization --- */
    __disable_irq();          // actually already disabled. good if the debugger can move to a line.

    UART_init();                    // the UART prints to simulator window
    GPIO_init();

    __enable_irq();                 // Enable interrupts. No effect in this example

    /* --- one time tasks --- */
    UART_send_string("Task1 up and running\r\n");  // always append CR LF (\r\n) to flush the output
    test_number_to_UART();                          // see how number printing works

    int state;
    int LED_number = 0;
    int running = 0;
    int forward = 1;                                //Direction of LED movement (1= forward)
    int count;
    int buttonState = 0;
    int rising = 0;

    GPIOC->ODR ^= MASK_LED_RED;                //LED0 an- und abschalten dass alle LEDs beim
    GPIOC->ODR ^= MASK_LED_RED;                //Start aus sind
    state = GPIOC->ODR & MASK_LED_RED;

    /* --- infinite processing loop --- */
    while (1)
    {
        /* ... add your code to implement the lab assignment ... */

        if (buttonState == 0 && !(GPIOB->IDR & MASK_S2))        //Taster wird gedrückt (steigende Flanke)
        {
            buttonState = 1;
            rising = 1;
        }
        else if (buttonState == 1 && !(GPIOB->IDR & MASK_S2))   //Taster wird gehalten
        {
            buttonState = 2;
            rising = 0;
        }
        else if (buttonState == 2 && (GPIOB->IDR & MASK_S2))    //Taster wird losgelassen (fallende Flanke)
        {
            buttonState = 3;
            rising = 0;
        }
        else if (buttonState == 3 && (GPIOB->IDR & MASK_S2))    //Taster nicht gedrückt
        {
            buttonState = 0;
            rising = 0;
        }

        if (rising == 1)
        {
            if (running == 0)                       //Setzen der Variablen zum Start der LEDs
            {
                running = 1;
                count = 0;
                forward = 1;
                LED_number = 0;
                rising = 0;
            }
            else                                    //Stoppen der LEDs
            {
                running = 0;
                count = 0;
                forward = 1;

                switch (LED_number)
                //Abschalten der noch aktiven LED
                {
                case 0:
                    GPIOC->ODR ^= MASK_LED_RED;                // toggle LED
                    state = GPIOC->ODR & MASK_LED_RED;
                    UART_send_string(state ? "LED0 off\r\n" : "LED0 on\r\n");
                    break;

                case 1:
                    GPIOC->ODR ^= MASK_LED_YELLOW;             // toggle LED
                    state = GPIOC->ODR & MASK_LED_YELLOW;
                    UART_send_string(state ? "LED1 off\r\n" : "LED1 on\r\n");
                    break;

                case 2:
                    GPIOC->ODR ^= MASK_LED_GREEN;              // toggle LED
                    state = GPIOC->ODR & MASK_LED_GREEN;
                    UART_send_string(state ? "LED2 off\r\n" : "LED2 on\r\n");
                    break;

                case 3:
                    GPIOC->ODR ^= MASK_LED_BLUE;               // toggle LED
                    state = GPIOC->ODR & MASK_LED_BLUE;
                    UART_send_string(state ? "LED3 off\r\n" : "LED3 on\r\n");
                    break;

                }

                rising = 0;
                LED_number = 0;                //Rücksetzen, dass bei LED0 neu gestartet werden kann
            }
        }

        if (count == 12)                            //Weiterschalten der LEDs nach bestimmter Zeit
        {                                      //Bei 12 Durchläufen pro LED ca 2 Sekunden Gesamtzeit
            count = 0;

            if (forward == 1)                       //Hochzählen der LEDs (vorwärtslaufen)
                LED_number++;

            else
                LED_number--;                       //Runterzählen der LEDs (zurücklaufen)
        }

        if (running == 1)
        {
            switch (LED_number)
            //Steuern der jeweiligen LEDs
            {
            case 0:

                if (count == 0)
                {
                    if (forward == 0)           //Ausschalten von LED1 beim 'umdrehen'
                    {
                        GPIOC->ODR ^= MASK_LED_YELLOW;             // toggle LED
                        state = GPIOC->ODR & MASK_LED_YELLOW;
                        UART_send_string(state ? "LED1 off\r\n" : "LED1 on\r\n");
                    }

                    GPIOC->ODR ^= MASK_LED_RED;                // toggle LED
                    state = GPIOC->ODR & MASK_LED_RED;
                    UART_send_string(state ? "LED0 off\r\n" : "LED0 on\r\n");
                }

                forward = 1;
                break;

            case 1:

                if (count == 0)
                {
                    if (forward == 1)           //LED0 ausschalten
                    {
                        GPIOC->ODR ^= MASK_LED_RED;                // toggle LED
                        state = GPIOC->ODR & MASK_LED_RED;
                        UART_send_string(state ? "LED0 off\r\n" : "LED0 on\r\n");
                    }
                    else                        //LED2 ausschalten (rückwärts)
                    {
                        GPIOC->ODR ^= MASK_LED_GREEN;              // toggle LED
                        state = GPIOC->ODR & MASK_LED_GREEN;
                        UART_send_string(state ? "LED2 off\r\n" : "LED2 on\r\n");
                    }

                    GPIOC->ODR ^= MASK_LED_YELLOW;             // toggle LED
                    state = GPIOC->ODR & MASK_LED_YELLOW;
                    UART_send_string(state ? "LED1 off\r\n" : "LED1 on\r\n");
                }

                break;

            case 2:

                if (count == 0)
                {
                    if (forward == 1)           //LED1 ausschalten
                    {
                        GPIOC->ODR ^= MASK_LED_YELLOW;             // toggle LED
                        state = GPIOC->ODR & MASK_LED_YELLOW;
                        UART_send_string(state ? "LED1 off\r\n" : "LED1 on\r\n");
                    }
                    else                        //LED3 ausschalten (rückwärts)
                    {
                        GPIOC->ODR ^= MASK_LED_BLUE;               // toggle LED
                        state = GPIOC->ODR & MASK_LED_BLUE;
                        UART_send_string(state ? "LED3 off\r\n" : "LED3 on\r\n");
                    }

                    GPIOC->ODR ^= MASK_LED_GREEN;              // toggle LED
                    state = GPIOC->ODR & MASK_LED_GREEN;
                    UART_send_string(state ? "LED2 off\r\n" : "LED2 on\r\n");
                }

                break;

            case 3:
                if (count == 0)             //LED2 ausschalten
                {
                    GPIOC->ODR ^= MASK_LED_GREEN;              // toggle LED
                    state = GPIOC->ODR & MASK_LED_GREEN;
                    UART_send_string(state ? "LED2 off\r\n" : "LED2 on\r\n");

                    GPIOC->ODR ^= MASK_LED_BLUE;               // toggle LED
                    state = GPIOC->ODR & MASK_LED_BLUE;
                    UART_send_string(state ? "LED3 off\r\n" : "LED3 on\r\n");
                }

                forward = 0;
                break;
            }

        }
        delay(20);                      //Delay um für weniger Schleifendurchläufe
        count++;

    }
    return 1;
}

/* ------------------------------------ GLOBAL FUNCTIONS ------------------------------ */

/* ------------------------------------ PRIVATE FUNCTIONS ----------------------------- */

/* ------------------------------------------------------------------------------------ *\
 * method:  static void GPIO_init(void)
 *
 * Initializes GPIOs on STefi for pins with peripherals attached.
 *
 * requires:    - nothing -
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
static void GPIO_init(void)
{
    /* enable port clocks */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;    // PC[7:4]: LEDs

    /* GPIO LED0 init*/
    GPIOC->ODR |= MASK_LED0;                // default is LED off
    GPIOC->MODER &= ~(0x03 << 8);           // clear mode bits for PC4
    GPIOC->MODER |= (0x01 << 8);            // set PC4 to output

    /* GPIO LED1 init*/
    GPIOC->ODR |= MASK_LED1;                // default is LED off
    GPIOC->MODER &= ~(0x03 << 10);          // clear mode bits for PC5
    GPIOC->MODER |= (0x01 << 10);           // set PC5 to output

    /* GPIO LED2 init*/
    GPIOC->ODR |= MASK_LED2;                // default is LED off
    GPIOC->MODER &= ~(0x03 << 12);          // clear mode bits for PC6
    GPIOC->MODER |= (0x01 << 12);           // set PC6 to output

    /* GPIO LED3 init*/
    GPIOC->ODR |= MASK_LED3;                // default is LED off
    GPIOC->MODER &= ~(0x03 << 14);          // clear mode bits for PC7
    GPIOC->MODER |= (0x01 << 14);           // set PC7 to output

    /*GPIO S2 init*/
    GPIOB->MODER &= (0x03 << 6);            //PB2 set to input

}

/* ------------------------------------------------------------------------------------ *\
 * method:  static void delay(const uint16_t ms)
 *
 * It realizes a millisecond delay by very bad busy-wait.
 *
 * requires:    - nothing -
 * parameters:  ms - delay time in milliseconds
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
static void delay(const uint16_t ms)
{
    for (uint16_t i = 0; i < ms; ++i)
    {
        for (uint16_t j = 0; j < LOOPS_PER_MS; ++j)
        {
            __asm("NOP");
        }
    }
}

/* ------------------------------------------------------------------------------------ *\
 * method:  static void test_number_to_UART(void)
 *
 * Shows a way how to replace the usual printf() debug output.
 *
 * requires:    stdio.h
 * parameters:  - none -
 * returns:     - nothing -
 \* ------------------------------------------------------------------------------------ */
static void test_number_to_UART(void)
{
    char buffer[19];
    unsigned a = 0x123456;

    sprintf(buffer, "x=%x\r\n", a);

    UART_send_string(buffer);
}

/* ************************************ E O F ***************************************** */
