/*
 * File:   main_stepper.c
 * Author: Ronald Quino Bueno
 *
 * Created on 17 de agosto de 2020, 08:11 PM
 */
/*Este programa solo se hizo con la finalidad de probar un motor unipolar*/
#include "config.h"
#include <libpic30.h>
#define FCY         20000000//FCY = FOSC/4
#define delay_ms(x) __delay32((FCY/1000)*x)

int main(void) {
    
    ADPCFG = 0xFFFF;        //SE DESACTIVAN LAS ENTRADAS ANALOGICAS
    TRISBbits.TRISB0 = 0;   //RBO->SALIDA
    TRISBbits.TRISB1 = 0;   //RB1->SALIDA
    TRISBbits.TRISB2 = 0;   //RB2->SALIDA
    TRISBbits.TRISB3 = 0;   //RB3->SALIDA
    
    while(1){
        LATB = 0b1000;//A
        delay_ms(50);
        LATB = 0b1100;//A-B
        delay_ms(50);
        LATB = 0b0100;//B
        delay_ms(50);
        LATB = 0b0110;//B-C
        delay_ms(50);
        LATB = 0b0010;//C
        delay_ms(50);
        LATB = 0b0011;//C-D
        delay_ms(50);
        LATB = 0b0001;//D
        delay_ms(50);
        LATB = 0b1001;//D-A
        delay_ms(50);

    }
    return 0;
}
