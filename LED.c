





#include "LED.h"
#include "clock.h"
#include "controller.h"
#include <stdbool.h>
#include "beat.h"

extern uint16_t address;
extern bool dmxEnable;
extern uint8_t dmxFrame[514];

color_t colors[8];
time_t lastRun = 0;

int i;

void LED_init()
{
    
    
    
    // color 0: red
    colors[0].red = 255;

    // color 1: green
    colors[1].green = 255;

    // color 2: blue
    colors[2].blue = 255;

    // color 3: orange
    colors[3].red = 255;
    colors[3].green = 128;

    // color 4: purple
    colors[4].red = 128;
    colors[4].blue = 255;

        // colors 5: yellow
    colors[5].red = 255;
    colors[5].green = 255;

    // colors 6: seafoam
    colors[6].green = 255;
    colors[6].blue = 128;

    // colors 7: everything
    colors[7].red = 255;
    colors[7].green = 255;
    colors[7].blue = 255;
    colors[7].white = 255;
}

void LED_task(void)
{
  switch (MODE_AUTO)
  {
  case MODE_AUTO:
    autoTask();
    break;

  case MODE_DMX:
    dmxTask();
    break;

  case MODE_SOUND:
    soundTask();
    break;
  }
}

void autoTask(){
    if(dmxEnable){
        dmxTask();
    } else {
        soundTask();
    }
}

void dmxTask(){
    LED_setColor(dmxFrame[address] , dmxFrame[address+1] , dmxFrame[address+2] , dmxFrame[address+3]);
}

void soundTask(){
     if (CLOCK_getTime() - lastRun < 200)
        return;
    
    lastRun = CLOCK_getTime();
    
    
    if (BEAT_detected()) {
    LED_setColor(colors[i].red, colors[i].blue, colors[i].green, colors[i].white);
    i++;
    if(i == 8){
        i = 0;
    }
    
    
  }
}


//LED Funcitons 
void LED_setColor(uint8_t R, uint8_t B, uint8_t G, uint8_t W)
{
    CCPR1L = R>>1;
    CCPR2L = B>>1;
    CCPR3L = G>>1;
    CCPR4L = W>>1;
}
