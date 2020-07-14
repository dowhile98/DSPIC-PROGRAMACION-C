/*
 * File:   main_timer32bit.c
 * Author: Ronald Quino Bueno
 *
 * Created on 13 de julio de 2020, 07:06 PM
 */

#include "config.h"
#include "TIM32.h"

int main(void) {
    ADPCFG = 0xFFFF;//desactiva todas las entradas analogicas
    TRISBbits.TRISB9 = 0;//RB9 salida digital
    TIM32_Init();
    while(1){
        LATBbits.LATB9 ^=1;
        while(!(IFS0bits.T3IF));
        
    }
    return 0;
}
