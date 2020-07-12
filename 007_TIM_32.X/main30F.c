/*
 * File:   main30F.c
 * Author: Ronald Quino Bueno
 *
 * Created on 16 de junio de 2020, 03:40 PM
 */


#include "config.h"

/*DEFINICION DE FUNCIONES*/
void delay_ms(uint16_t delay);  //iniciando
void delay32(uint32_t delay); //
void GPIO_Init(void);

int main(void) {
    ADPCFG = 0xFFFF;
    TRISBbits.TRISB0 = 0;
    while(1){
        LATBbits.LATB0 ^=1;
        delay_ms(100);
    }
    return 0;
}

/***************************************************************************/
//DEFINICION DE FUNCIONES
void delay32(uint32_t delay){
    T3CON = 0x0000;         //se limpia cualquier configuracion existente del timer
    T2CON = 0x0000;         //se limpia cualquier configuracion existente del timer
    T2CONbits.T32 = 1;      //se une timer 2 con el timer3
    T2CONbits.TCKPS = 3;    //prescaler de 256
    
    uint32_t time = (uint32_t)((7370000*16)/(4*256*1000))*delay;
    
    PR3 = time>>16;         //se le asignan los bits 16 bits superiores
    PR2 = time & 0xFFFF;    //se asignan los bits inferiores
    TMR2 = 0x0000;
    TMR3 = 0x0000;
    _T3IF = 0;              //se borra el flag
    T2CONbits.TON = 1;      //se habilita el conteo
    while(_T3IF == 0);
    _T3IF = 0;              //se borra el flag
    T2CONbits.TON = 0;
}

void delay_ms(uint16_t delay){
    T1CON = 0x0000;         //Se resetea la configurion del timer1
    T1CONbits.TCKPS = 3;    //PS->256
    PR1 = 115;              //actualizacion de conteo cada 1ms
    TMR1 = 0;
    T1CONbits.TON = 1;      //se activa el contador
    uint16_t i;
    for( i = 0;i<delay;i++){
        while(IFS0bits.T1IF ==0);
        IFS0bits.T1IF =0;           //se resetea el flag
    }
    T1CONbits.TON = 0;              //se deshabilita el timer 1
}