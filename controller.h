/* 
 * File:   controller.h
 * Author: Erik
 *
 * Created on April 16, 2019, 5:26 PM
 */
#include <stdint.h>

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif


void CONTROLLER_init();
void address_inc();
void address_dec();
void CONTROLLER_task();

extern uint16_t address;

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLLER_H */

