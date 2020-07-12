/*
 * File:   main.c
 * Author: Ronald Quino Bueno
 *
 * Created on 4 de junio de 2020, 10:44 PM
 */


#include "configuration.h"

int main(void) {
    
    TIMER2_Init();
    while(1){
        
    }
    return 0;
}

//PROTOTIPO DE FUNCIONES
void TIMER2_Init(void){
    T2CON = 0x0000;                 //Se resetea el timer2
    T2CONbits.TCKPS = 0x3;          //PS->256
    PR2 = 23031;                    //valor de autorecarga ->200ms
    
    //SE CONFIGURA LA INTERRUPCION PARA EL TIMER
    
}
void GPIO_Init(void);