




#include "DMX.h"
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "clock.h"

int dmxPointer = 0;
uint8_t dmxFrame[514];

bool dmxEnable;
time_t dmxTime;

void DMX_handler(void){
    if(RC1STAbits.OERR){
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }
    
   if(RC1STAbits.FERR){
       dmxPointer = 0;
    }
   
   
    dmxFrame[dmxPointer++] = RC1REG;
    dmxTime = CLOCK_getTime();
    dmxEnable = true;
}


void dmxTimer(void){
    if(CLOCK_getTime() - dmxTime > 5000){
        dmxEnable = false;
    }
}