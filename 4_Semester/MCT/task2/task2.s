#****************************************************************************************#
#   Project:    task2 - switch triggered LEDs
#   File:       task2.s
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
#       31.10.2014  ML  create file
#       27.09.2018  ML  edit comments, extend vector table
#       18.12.2018  ML  port from MKL05Z32VLC4 to STM32L476RG
#       27.02.2019  ML  move section of exception handlers to bottom of file
#		25.09.2019	ML	minor changes for a better code and comment understanding
#       04.09.2020  HL  port from STM32L476RG to STM32F411xE
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

                                // Umbenennung der Register für bessere Übersicht
    old_S0 .req r12             // Status s0 alt
    now_S0 .req r11             // Status s0 aktuell
    temp1  .req r10             // Zwischenspeicher
    temp2  .req r9              // Zwischenspeicher
    old_S3 .req r8
    now_S3 .req r7


    CPSIE   i                   // enable interrupts globally


#----------------------------------------------------------------------------------------#

    .align  2
    .syntax unified
    .thumb
    .thumb_func
    .global main
    .type   main, %function

main:
     //Abfrage für Taster 0
    LDR     r1, =GPIOB_IDR
    LDR     now_S0, [r1, #0]            // get current value of port C mode register
    MOV     r6, #0                      // set r6 to zero
    BFI     now_S0, r6, #8, #8          // set front 8 bits to 0
    AND     now_S0, now_S0, #0x01       // delete all Bits except Bit 0 -> S0 Bit
    EOR     now_S0, now_S0, #0x01       // xor to get last bit representing button
    MOV     temp1, now_S0
    MOV     temp2, old_S0               // old_S0 speichern für Vergleich ("=old_old_S0")
    EOR     now_S0, now_S0, old_S0      // xor old with new, safe in new
    MOV     old_S0, temp1

    CMP     now_S0, temp2               //Sprung zu Taster 3 falls keine Änderung
    BEQ     taster3

    CMP     temp1, now_S0               //Sprung zu Taster 3 falls fallende Flanke
    BNE     taster3

        // toggle LED0 & LED1
    LDR     r1, =GPIOC_ODR              // load port C output data register
    LDR     r0, [r1, #0]                // load value of port C
    EOR     r0, #0x30                   // invert bits for LED0 & LED1
    STR     r0, [r1, #0]                // apply mask

taster3:

    LDR     r1, =GPIOB_IDR
    LDR     now_S3, [r1, #0]            // get current value of port C mode register
    MOV     r6, #0                      // set r6 to zero
    BFI     now_S3, r6, #8, #8          // set front 8 bits to 0
    AND     now_S3, now_S3, #0x08       // delete all Bits except Bit 3 -> S3 Bit
    EOR     now_S3, now_S3, #0x08       // xor to get bit 3 representing button
    MOV     temp1, now_S3
    MOV     temp2, old_S3               // old_S3 speichern für Vergleich ("=old_old_S3")
    EOR     now_S3, now_S3, old_S3      // xor old with new, safe in new
    MOV     old_S3, temp1

    CMP     now_S3, temp2               //Sprung zum Anfang falls keine Änderung
    BEQ     main

    CMP     temp1, now_S3               //Sprung zu Anfang falls fallende Flanke
    BNE     main

        // LED 2 und 3 Toggle
    LDR     r1, =GPIOC_ODR              // load port C output data register
    LDR     r0, [r1, #0]                // load value of port C
    EOR     r0, #0xC0                   // invert bits for LED2 & LED3
    STR     r0, [r1, #0]                // apply mask

    B       main                // back to start of loop


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
.lp2:           // this label is only to nicify the line up in the .lst file
    .ltorg
#----------------------------------------------------------------------------------------#

    .end


#************************************** E O F *******************************************#
