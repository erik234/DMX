/* 
 * File:   clock.h
 * Author: Erik
 *
 * Created on April 16, 2019, 3:48 PM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <stdint.h>
    
typedef uint16_t time_t;

void CLOCK_init();
time_t CLOCK_getTime();



#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

