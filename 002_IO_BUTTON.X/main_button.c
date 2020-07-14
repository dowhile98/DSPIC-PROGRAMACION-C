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
    
    /*CONFIGURACION DEL PUERTOS DE SALIDA*/
    AD1PCFGL = 0xFFFF;                      //todos los pines como digitales
    TRISBbits.TRISB0 = 0;                   //RB0 -> salida
    TRISBbits.TRISB1 = 1;                   //RA0 -> entrada
    PORTBbits.RB0 = 0;                      //se resetea el valor del pin
    while(1){
        
		if(PORTBbits.RB1==0){					//es verdadero sea diferente de cero
            
            LATBbits.LATB0 = 1;				//prende el led conectado a RB0
            delay_ms(100);					//retardo
        }
        else{
            LATBbits.LATB0 = 0; // si no esta presionado lo apagas
        }
 
    }
}
