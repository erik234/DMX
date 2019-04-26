/* 
 * File:   LED.h
 * Author: Erik
 *
 * Created on April 23, 2019, 3:38 PM
 */


#include <xc.h>
#include <stdint.h>

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

typedef struct{
    uint8_t red;
    uint8_t blue;
    uint8_t green;
    uint8_t white;
} color_t;

typedef enum{
    MODE_SOUND,
    MODE_DMX,
    MODE_AUTO,
} mode_t;

void LED_task(void);
void autoTask();
void dmxTask();
void soundTask();
void dmxTimer(void);
void LED_setColor(uint8_t R, uint8_t B, uint8_t G, uint8_t W);