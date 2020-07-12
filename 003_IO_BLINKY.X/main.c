/*
 * File:   main.c
 * Author: Ronald Quino Bueno
 *
 * Created on 8 de mayo de 2020, 06:02 PM
 */


#include "CONFIG.h"
#define Freq 4000000

#define delay(x) __delay32((Freq/1000)*x) //delay en milisegundos

int main(void) {
    
    PLLFBDbits.PLLDIV = 0x06;           //pll div M = 8
    CLKDIVbits.PLLPOST = 0x0;           //POST VCO: division de salida N2 = 2
    CLKDIVbits.PLLPRE = 0x0;            //PLL PHASE N1 = 2
    
    /*configuraciones de pines*/
    AD1PCFGL = 0xFFFF;
    TRISBbits.TRISB0 = 0;
    while(1){
        LATBbits.LATB0 ^=0x1;
        delay(500);
    }
    return 0;
}
