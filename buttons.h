/* 
 * File:   buttons.h
 * Author: Erik
 *
 * Created on April 16, 2019, 5:25 PM
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

typedef enum {
    EVENT_IDLE,
    EVENT_PRESSED,
    EVENT_HELD
} event_t;

typedef enum {
    STATE_UNPRESSED,
    STATE_PRESSED
} btnState_t;

typedef struct {
    volatile uint8_t* port;
    uint8_t pin;
    btnState_t state;
    btnState_t lastState;
    event_t event;
    
} button_t;

extern button_t *up, *down, *enter, *menu;

static void init(button_t* btn, volatile uint8_t* port, uint8_t pin);
void BUTTONS_init();
void BUTTONS_task();
bool BUTTONS_isClicked(button_t* button);
bool BUTTONS_isHeld(button_t* button);