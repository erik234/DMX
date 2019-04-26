/* 
 * File:   beat.h
 * Author: Erik
 *
 * Created on April 23, 2019, 3:20 PM
 */

#ifndef BEAT_H
#define	BEAT_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BEAT_H */

#include <stdbool.h>

static void adcThresholdHandler();
void BEAT_init();
bool BEAT_detected();
void putch(char character);
void BEAT_task();