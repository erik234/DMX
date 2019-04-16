
#include "mcc_generated_files/tmr0.h"
#include "clock.h"

static time_t currentTime = 0;

static void CLOCK_timerCallback(void);

void CLOCK_init(void)
{
    // redirect MCC's timer callback to our custom function
    TMR0_SetInterruptHandler(CLOCK_timerCallback);
    
    // if not using MCC, init Timer0 here
}

time_t CLOCK_getTime(void) {
    return currentTime;
}

static void CLOCK_timerCallback(void) {
    currentTime++;
}

