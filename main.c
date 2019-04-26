/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18446
        Driver Version    :  2.00
*/

#include "mcc_generated_files/eusart1.h"


/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "PWM.h"
#include "clock.h"
#include "TM1650.h"
#include "buttons.h"
#include "controller.h"
#include "beat.h"
#include "DMX.h"
#include <stdbool.h>
#include "LED.h"



//This interrupt check for overrun error and allows debugging. Then checks for framing error.
//The framing error indicates the end of the possible adresses. This then reads the data
//and puts it into the array. This function sets the the third element as the first address avalible.
void dmx_isr(void) {
    DMX_handler();
}


/*
                         Main application
 */

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    CLOCK_init();
 
    EUSART1_SetRxInterruptHandler(dmx_isr);
    INTERRUPT_GlobalInterruptEnable();

    INTERRUPT_PeripheralInterruptEnable();
    
    __delay_ms(1000);
    TM1650_init();
    
    BUTTONS_init();
    CONTROLLER_init();
    LED_init();
    BEAT_init();
    
    while(1)
    {
        BUTTONS_task();
        CONTROLLER_task();
        LED_task();
        BEAT_task();
        dmxTimer();//edit back to dmx file.
    }
}
/**
 End of File
*/