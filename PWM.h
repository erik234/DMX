/* 
 * File:   PWM.h
 * Author: Erik
 *
 * Created on April 8, 2019, 3:08 PM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */



void LED_init();
void LED_setColor(uint8_t R, uint8_t B, uint8_t G, uint8_t W);
void LED_WHITE_Flash();
void LED_RGB();