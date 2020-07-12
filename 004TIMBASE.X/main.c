/*
 *ESTE PROGRAMA CONFIGURA EL TIMER 1 COMO GENERADOR DE BASE DE TIEMPO
 */

/***************************************
 * PASOS PARA LA CONFIGURACION DEL TIMER:
1. Establezca el bit TON (= 1) en el registro T1CON.
2. Seleccione la relación de preescaler del temporizador 
 * utilizando los bits TCKPS <1: 0> en el registro T1CON.
3. Configure los modos Reloj y Compuerta utilizando los 
 * bits TCS y TGATE en el registro T1CON.
4. Establezca o borre el bit TSYNC en T1CON
 * para seleccionar la operación síncrona o asíncrona.
5. Cargue el valor del período del temporizador en el registro PR1.
6. Si se requieren interrupciones, establezca el bit de habilitación
 * de interrupciones, T1IE. Use los bits de prioridad, 
 * T1IP <2: 0>, para establecer la prioridad de interrupción.
***************************************/

//INCLUSION DE ARCHIVOS CABECERA
#include <p33FJ32MC202.h>

#include "CONFIGURACION.h"

int main(void) {
    //configuracion de un pin como salida
    AD1PCFGLbits.PCFG2 = 1;             //se establece que el pin sea digital
    TRISBbits.TRISB0 =  0;              //Se configura el pin como salida digital
    
    
    //configuracion del timer
    T1CON = 0x0000;                     //resetea el timer 1
    TMR1 = 0x0000;
     T1CONbits.TON = 1;
    T1CONbits.TCKPS = 2;                //ps->64
   
    PR1 = 3906;                         //(FOSC/2=5MHZ)---retardo a 50ms
    
    for (;;) {
        if((IFS0bits.T1IF)){
            LATBbits.LATB0 ^=0x1;
            IFS0bits.T1IF = 0;          //se resetea
        }   
    }
    return 0;
}
