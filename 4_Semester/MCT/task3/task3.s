#****************************************************************************************#
#   Project:    task3 - switch triggered LEDs (interrupts)
#   File:       task3.s
#
#   Language:   ASM
#
#   Hardware:   STefi-Simulator
#   Processor:  STM32F411xE
#
#   Author:     Manuel Lederhofer
#   Datum:      25.09.2019
#
#   Version:    0.4
#   History:
#       10.11.2014  ML  create file
#       27.09.2018  ML  edit comments, extend vector table
#       18.12.2018  ML  port from MKL05Z32VLC4 to STM32L476RG
#       27.02.2019  ML  move section of exception handlers to bottom of file,
#                           change ASM pseudo commands from .space to .org
#		25.09.2019	ML	minor changes for a better code and comment understanding
#       27.03.2020  FPN Adapted to work on the F411 Simulator
#       21.09.2020  ML  tidy up, comments and formatting
#
#   Status:     working
#
#   Description:
#       See the description and requirements of the requested application
#       in the lab exercise guide.
#
#   Notes:
#       - processing speed of the simulator varies depending on computer performance
#
#   ToDo:
#       - change the example code to match the description of the program
#****************************************************************************************#

    .include "F411_addr.s"


#----------------------------------------------------------------------------------------#
    .section .vectortable,"a"   // vector table at begin of ROM
#----------------------------------------------------------------------------------------#

    .align  2

    .word   0x20018000          // initial Stack Pointer
    .word   0x08000401          // initial Program Counter
    .word   _nmi                // NMI
    .word   _hardf              // hard fault

    /* ... place your code here ... */

    .org    0x58
    .word   _exti0              // EXTI0
    .org    0x64
    .word   _exti3              // EXTI3


#----------------------------------------------------------------------------------------#
    .text                       // section .text (default section for program code)
#----------------------------------------------------------------------------------------#

    .align  2
    .syntax unified
    .thumb
    .thumb_func
    .global init
    .type   init, %function
init:
    CPSID   i                   // disable interrupts globally

    MOV     r0, #0              // safely initialize the GPRs
    MOV     r1, #0
    MOV     r2, #0
    MOV     r3, #0
    MOV     r4, #0
    MOV     r5, #0
    MOV     r6, #0
    MOV     r7, #0
    MOV     r8, #0
    MOV     r9, #0
    MOV     r10, #0
    MOV     r11, #0
    MOV     r12, #0

#--- enable port clocking
    LDR     r1, =RCC_AHB1ENR    // load address of RCC_AHB1ENR
    LDR     r2, =0x06           // load mask for adjusting port clock gating (B: buttons, C: LEDs)
    LDR     r0, [r1, #0]        // get current value of RCC_AHB1ENR
    ORRS    r0, r0, r2          // configure clock gating for ports
    STR     r0, [r1, #0]        // apply settings

#--- port init
#- LEDs
    LDR     r1, =GPIOC_MODER    // load port C mode register address
    MOV     r2, #0x55           // load configuration mask
    LDR     r0, [r1, #0]        // get current value of port C mode register
    BFI     r0, r2, #8, #8      // replace bit 8-15 of r0 with bit 0-7 of r2
    STR     r0, [r1, #0]        // apply result to port C mode register

#- switch all LEDs off
    LDR     r1, =GPIOC_ODR      // load port C output data register
    MOV     r2, #0xF0           // load mask for all LEDs
    STR     r2, [r1, #0]        // apply mask

#- buttons
    /* ... place your code here ... */
    LDR     r1, =GPIOB_MODER    // load port B mode register address
    MOV     r2, #0x3C           // load configuration mask to input
    LDR     r0, [r1, #0]        // get current value of port B mode register
    BFI     r0, r2, #0, #8      // replace bit 0-7 of r0 with bit 0-7 of r2
    STR     r0, [r2, #0]        // apply mask

    LDR     r1, =GPIOB_PUPDR    // load port B pull up/pull down register address
    MOV     r2, #0x41           // set mask for pull up for S0 and S3
    LDR     r0, [r1, #0]        // get current value of port B mode register
    BFI     r0, r2, #0, #8      // replace bit 0-7 of r0 with bit 0-7 of r2
    STR     r0, [r2, #0]        // apply mask


#--- button interrupt config



#- enable clock for SYSCFG module
    LDR     r1, =RCC_APB2ENR    // load RCC APB2 peripheral clock enable register address
    MOV     r2, #0x4000         // bit 14: SYSCFGEN --> SYSCFG + COMP + VREFBUF clock
    LDR     r0, [r1, #0]        // get current value
    ORR     r0, r0, r2          // set bit
    STR     r0, [r1, #0]        // enable clock

#- connect GPIO pins of the buttons to EXTended Interrupt controller lines (EXTI)
#  in SYSCFG module (SYSCFG_* registers)

    /* ... place your code here ... */
    LDR     r1, =SYSCFG_EXTICR1
    LDR     r2, =0x1001               // load mask for PBO and PB3 bit
    LDR     r0, [r1, #0]
    ORRS    r0, r0, r2
    STR     r0, [r1, #0]            // apply mask


#- configure lines in EXTI module (EXTI_* registers)

    /* ... place your code here ... */
    LDR     r1, =EXTI_IMR    // enable mask register
    LDR     r2, =0x09               // load mask for MR0 and MR3
    LDR     r0, [r1, #0]
    ORRS    r0, r0, r2
    STR     r0, [r1, #0]            // apply mask

    LDR     r1, =EXTI_RTSR   // enable rising trigger
    LDR     r2, =0x09               // load mask for MR0 and MR3
    LDR     r0, [r1, #0]
    ORRS    r0, r0, r2
    STR     r0, [r1, #0]            // apply mask

    //LDR     r1, =EXTI_FTSR   // disable falling trigger
    //LDR     r2, =0x00               // load mask for MR0 and MR3
    //LDR     r0, [r1, #0]
    //ORRS    r0, r0, r2
    //STR     r0, [r1, #0]            // apply mask

    LDR     r1, =EXTI_PR   // clear pending bit register
    LDR     r2, =0x09               // load mask for MR0 and MR3
    LDR     r0, [r1, #0]
    ORRS    r0, r0, r2
    STR     r0, [r1, #0]            // apply mask




#- NVIC: set interrupt priority, clear pending bits
#  and enable interrupts for buttons (see: PM, ch. 4.3)

    /* ... place your code here ... */


    LDR     r1, =NVIC_IPR1      // enable interrupt priority register
    LDR     r2, =0x400000           // load mask for IP6
    LDR     r0, [r1, #0]
    ORRS    r0, r0, r2
    STR     r0, [r1, #0]        // apply mask

    LDR     r1, =NVIC_IPR2      // enable interrupt priority register
    LDR     r2, =0x4000          // load mask for IP9
    LDR     r0, [r1, #0]
    ORRS    r0, r0, r2
    STR     r0, [r1, #0]        // apply mask

    LDR     r1, =NVIC_ISER0         // enable interrupt
    LDR     r2, =0x240
    LDR     r0, [r1, #0]
    ORRS    r0, r0, r2
    STR     r0, [r1, #0]

    LDR     r1, =NVIC_ICPR0         // reset pending bit
    LDR     r2, =0x240
    LDR     r0, [r1, #0]
    ORRS    r0, r0, r2
    STR     r0, [r1, #0]


    CPSIE   i                   // enable interrupts globally


#----------------------------------------------------------------------------------------#

    .align  2
    .syntax unified
    .thumb
    .thumb_func
    .global main
    .type   main, %function
main:
    NOP                         // do nothing (currently, NOP is only here to avoid a debugger crash)
    B       main                // do nothing, again, again, aga...



#----------------------------------------------------------------------------------------#

    .align  2
    .syntax unified
    .thumb
    .thumb_func
    .global delay
    .type   delay, %function
delay:
    MOVS    r6, #0              // ...
    LDR     r7, =20000          // ...
.L1:
    ADDS    r6, r6, #1          // ...
    CMP     r6, r7              // ...
    BNE     .L1                 // ...
    BX      lr                  // ...


#----------------------------------------------------------------------------------------#

    .align 2
    .global stop
stop:
    NOP                         // do nothing (NOP is here to avoid a debugger crash, only)
    B       stop                // if this line is reached, something went wrong


#----------------------------------------------------------------------------------------#
.lp1:           // this label is only to nicify the line up in the .lst file
    .ltorg
#----------------------------------------------------------------------------------------#


#----------------------------------------------------------------------------------------#
    .section .exhand,"ax"       // section for exception handlers
#----------------------------------------------------------------------------------------#

    .align  2
    .syntax unified
    .thumb
    .type   _nmi, %function
_nmi:
#--- enable clock
    LDR     r1, =RCC_AHB1ENR    // load address of RCC_AHB1ENR
    LDR     r2, =0x04           // load mask
    LDR     r0, [r1, #0]        // get current value of RCC_AHB1ENR
    ORRS    r0, r0, r2          // enable clock gating for port
    STR     r0, [r1, #0]        // apply settings

#--- init pins
    LDR     r1, =GPIOC_MODER    // load port C mode register address
    MOV     r2, #0x8800         // load configuration mask
    LDR     r0, [r1, #0]        // get current value of port C mode register
    BIC     r0, r0, r2          // apply mask
    STR     r0, [r1, #0]        // apply settings to port C mode register

#--- switch some LEDs on
    LDR     r1, =GPIOC_ODR      // load port C data output register address
    MOV     r2, #0xA0           // load mask for blue and yellow LED
    LDR     r0, [r1, #0]
    BIC     r0, r0, r2
    STR     r0, [r1, #0]        // switch LEDs on
    B   _nmi


#----------------------------------------------------------------------------------------#

    .align  2
    .syntax unified
    .thumb
    .type   _hardf, %function
_hardf:
#--- enable clock
    LDR     r1, =RCC_AHB1ENR    // load address of RCC_AHB1ENR
    LDR     r2, =0x04           // load mask
    LDR     r0, [r1, #0]        // get current value of RCC_AHB1ENR
    ORRS    r0, r0, r2          // enable clock gating for port
    STR     r0, [r1, #0]        // apply settings

#--- init pins
    LDR     r1, =GPIOC_MODER    // load port C mode register address
    MOV     r2, #0x2200         // load configuration mask
    LDR     r0, [r1, #0]        // get current value of port C mode register
    BIC     r0, r0, r2          // apply mask
    STR     r0, [r1, #0]        // apply settings to port C mode register

#--- switch some LEDs on
    LDR     r1, =GPIOC_ODR      // load port C data output register address
    MOV     r2, #0x50           // load mask for red and green LED
    LDR     r0, [r1, #0]
    BIC     r0, r0, r2
    STR     r0, [r1, #0]        // switch LEDs on

    B       _hardf


#----------------------------------------------------------------------------------------#

    .align  2
    .syntax unified
    .thumb
    .type   _exti0, %function
_exti0:
    PUSH    {lr}                // save special content

#--- do the work

    /* ... place your code here ... */

    // LED 0 und 1 Toggle
    LDR     r1, =GPIOC_ODR              // load port C output data register
    LDR     r0, [r1, #0]                // load value of port C
    EOR     r0, #0x30                   // invert bits for LED0 & LED1
    STR     r0, [r1, #0]                // apply mask

#--- clear interrupt

    /* ... place your code here ... */
    LDR     r1, =EXTI_PR         // reset pending bit for S0
    LDR     r2, =0x01
    LDR     r0, [r1, #0]
    ORRS    r0, r0, r2
    STR     r0, [r1, #0]

#--- leave ISR
    POP     {r1}                // get special content back
    BX      r1                  // go back to where we came from


#----------------------------------------------------------------------------------------#

    .align  2
    .syntax unified
    .thumb
    .type   _exti3, %function
_exti3:
    PUSH    {lr}                // save special content

#--- do the work

    /* ... place your code here ... */

    // LED 2 und 3 Toggle
    LDR     r1, =GPIOC_ODR              // load port C output data register
    LDR     r0, [r1, #0]                // load value of port C
    EOR     r0, #0xC0                   // invert bits for LED2 & LED3
    STR     r0, [r1, #0]                // apply mask

#--- clear interrupt flag

    /* ... place your code here ... */
    LDR     r1, =EXTI_PR         // reset pendig bit for S3
    LDR     r2, =0x08
    LDR     r0, [r1, #0]
    ORRS    r0, r0, r2
    STR     r0, [r1, #0]

#--- leave ISR
    POP     {r1}                // get special content back
    BX      r1                  // go back to where we came from


#----------------------------------------------------------------------------------------#
.lp2:           // this label is only to nicify the line up in the .lst file
    .ltorg
#----------------------------------------------------------------------------------------#

    .end


#************************************** E O F *******************************************#
