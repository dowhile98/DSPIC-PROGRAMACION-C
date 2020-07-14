/*
 * File:   main_button.c
 * Author: Ronald Quino Bueno
 *
 * Created on May 8, 2020, 10:26 PM
 */


#include "CONFIG.h"

//DEFINICION DE MACROS
#define Freq        7370000
#define delay_ms(x)    __delay32((Freq/1000)*x) 
int main(void) {
    
    /*CONFIGURACION DEL RELOJ*/
    PLLFBDbits.PLLDIV = 0x06;           //pll div M = 8
    CLKDIVbits.PLLPOST = 0x0;           //POST VCO: division de salida N2 = 2
    CLKDIVbits.PLLPRE = 0x0;            //PLL PHASE N1 = 2
    /*CONFIGURACION DEL PUERTOS DE SALIDA*/
    AD1PCFGL = 0xFFFF;                      //todos los pines como digitales
    TRISBbits.TRISB0 = 0;                   //RB0 -> salida
    TRISBbits.TRISB1 = 1;                   //RA0 -> entrada
    PORTBbits.RB0 = 0;                      //se resetea el valor del pin
    while(1){
        if(PORTBbits.RB1){
            
            PORTBbits.RB1 =0;
            LATBbits.LATB0 = 1;
            delay_ms(100);
        }
        else{
            LATBbits.LATB0 = 0; // si no esta presionado lo apagas
        }
 
    }
}
