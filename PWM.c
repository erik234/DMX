
/* Spencer Hagadorn wrote this file for PWM lab. My file went missing somehow.
 */

#include <xc.h>
#include <stdint.h>
#include "PWM.h"

#define _XTAL_FREQ 4000000

void LED_init()
{
    TRISC = 0b00000111; //LED output
    
    RC7PPS = 0x09; //RED
    RC3PPS = 0x0A; //BLUE
    RC6PPS = 0x0B; //GREEN
    RC4PPS = 0x0C; //WHITE
    
    T2CLKCON = 0x01; // configure Timer2's clock source to Fosc/4
    T2CONbits.ON = 1; // turn on Timer2
    
    CCP1CONbits.CCP1EN = 1;
    CCP1CONbits.MODE = 0b1100;
    CCP2CONbits.CCP2EN = 1;
    CCP2CONbits.MODE = 0b1100;
    CCP3CONbits.CCP3EN = 1;
    CCP3CONbits.MODE = 0b1100;
    CCP4CONbits.CCP4EN = 1;
    CCP4CONbits.MODE = 0b1100;
    
}

void LED_setColor(uint8_t R, uint8_t B, uint8_t G, uint8_t W)
{
    CCPR1L = R>>1;
    CCPR2L = B>>1;
    CCPR3L = G>>1;
    CCPR4L = W>>1;
}

void LED_WHITE_Flash()
{
    int A, B, C, D;
    while(1)
    {
        D = 255;
        LED_setColor(A, B, C, D);
        __delay_ms(100);
        D = 0;
        LED_setColor(A, B, C, D);
        __delay_ms(100);
    }
}

void LED_RGB()
{
    int A, B, C, D;
    while(1)
    {
        A = 255;
        B = 255;
        C = 255;
        LED_setColor(A, B, C, D);
        __delay_ms(175);
        A = 0;
        LED_setColor(A, B, C, D);
        __delay_ms(175);
        B = 0;
        LED_setColor(A, B, C, D);
        __delay_ms(175);
        C = 0;
        LED_setColor(A, B, C, D);
        __delay_ms(175);
        
        A = 255;
        LED_setColor(A, B, C, D);
        __delay_ms(175);
        B = 255;
        LED_setColor(A, B, C, D);
        __delay_ms(175);
        C = 255;
        LED_setColor(A, B, C, D);
        __delay_ms(175);
    }
}

