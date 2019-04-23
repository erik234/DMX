/* 
 * File:   TM1650.c
 * Author: Erik
 *
 * Created on March 24, 2019, 3:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mcc_generated_files/i2c1.h"
#include "TM1650.h"
#define _XTAL_FREQ 4000


//Variable that controls position on display
static int TABVALUE;
static bool isEnabled; 

//Char  table that bit masks the raw char value to something that can be read on the display
//Given by lab
const uint8_t charTable[] = 
{
    0x00, 0x82, 0x21, 0x00, 0x00, 0x00, 0x00, 0x02, 0x39, 0x0F, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00,
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x6f, 0x00, 0x00, 0x00, 0x48, 0x00, 0x53,
    0x00, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x6F, 0x76, 0x06, 0x1E, 0x00, 0x38, 0x00, 0x54, 0x3F,
    0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x00, 0x0F, 0x00, 0x08, 
    0x63, 0x5F, 0x7C, 0x58, 0x5E, 0x7B, 0x71, 0x6F, 0x74, 0x02, 0x1E, 0x00, 0x06, 0x00, 0x54, 0x5C,
    0x73, 0x67, 0x50, 0x6D, 0x78, 0x1C, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x30, 0x0F, 0x00, 0x00 
};
    
//This function sends data out to the TM1650. This can send commands or just data depending on the address that it sends to
//This is the most importat function in this document because it is the only way we can move data to the TM1650
static void writeData(uint8_t address, uint8_t data){
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;
    I2C1_MasterWrite(&data, 1, address, &status);
    while(status == I2C1_MESSAGE_PENDING);
}

//Uses the write data to send an init command
//Also clears the display to prevent stuck letters from previous programs
void TM1650_init(void){
    TM1650_enable(1);
    clearDisplay();
    
}

//writes a char to a display address. Can also add a decimal point.
void TM1650_setDigit(uint8_t didgit, char data, uint8_t DP){
    
    uint8_t letter;
    
    letter = (charTable[data - 32]);
    if(DP == 1){
        letter += 128;
    } 
    writeData((didgit + 0x34) , letter);
    
}

//This is the function this is used for printf. This checks for \r and that we are not writing off teh display
//This allows for writing strings longer than four charecters.
void putch(char letter){
    
    if(letter == '\r'){
        TABVALUE = 0;
    } else {
    
        TM1650_setDigit(TABVALUE, letter, 0);
        TABVALUE++;
        if(TABVALUE == 4){
            TABVALUE = 0;
            //This delay allows reading of 4 chars at a time
            __delay_ms(100000);
        }
    }
    
}

//Simple clear display function
void clearDisplay(void){
    TM1650_setDigit(0 , 32, 0);
    TM1650_setDigit(1 , 32, 0);
    TM1650_setDigit(2 , 32, 0);
    TM1650_setDigit(3 , 32, 0);
}

void TM1650_fastPrintNum(uint16_t num){ 
    
    int arr[4];
    
    arr[3] = num % 10;
    arr[2] = (num/10) % 10 ;
    arr[1] = (num/100) % 10;
    arr[0] = (num/1000) % 10;
    
    for(int i = 0; i < 4; i++){
        TM1650_setDigit(i, arr[i] + 48, 0);
    }
}

//This will enable the display when a button is pressed
void TM1650_enable(bool enable){
    if(enable){ 
         writeData(0x24, 1);
         isEnabled = 1;
    } else {
         writeData(0x24, 0);
         isEnabled = 0;
    }
}

//Will check a variable and return a bool.
bool TM1650_isEnabled(void) {
    return isEnabled;
}
