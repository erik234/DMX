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

int dmxPointer = 0;
uint8_t dmxFrame[514];

//This interrupt check for overrun error and allows debugging. Then checks for framing error.
//The framing error indicates the end of the possible adresses. This then reads the data
//and puts it into the array. This function sets the the third element as the first address avalible. sdlkfnsoidfnsdi
void dmx_isr(void) {
    if(RC1STAbits.OERR){
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }
    
   if(RC1STAbits.FERR){
       dmxPointer = 0;
    }
   
   
    dmxFrame[dmxPointer++] = RC1REG;
   
}

/*
                         Main application
 */

//This main function calls inits and then sets the color in a while loop.
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    EUSART1_SetRxInterruptHandler(dmx_isr);
    LED_init();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    while (1)
    {
        //Addresses 2-5 are used because 0 and 1 are the framing error and start byte.
           LED_setColor(dmxFrame[2],dmxFrame[3],dmxFrame[4],dmxFrame[5]);
           
    }
}
/**
 End of File
*/