/*
 * File:   main_ADC.c
 * Author: QUINO B. JEFFRY
 *
 * Created on 7 de julio de 2020, 07:59 PM
 */

/*****************INCLUSION DE ARCHIVOS CABECERA**************************+*/
#include "configuracion.h"
#include "dsPIC_ADC.h"
#include <libpic30.h>

//definicion de macros
#define Fcy         (7370000/2)
#define delay_ms(x)    __delay32((Fcy/1000)*x)
int main(void) {
    TRISB &=~(0xFF);
    ADC_Init();//SE INICIALIZA EL EL ADC
    uint16_t data;
    while(1){
        data = ADC_ReadData();
        if(data<20)
            LATB = 0x00;
        else if(data<100)
            LATB = 0x1;
        else if(data<200)
            LATB = 0x3;
        else if(data<300)
            LATB = 0x7;
        else if(data<500)
            LATB = 0xF;
        else if(data<600)
            LATB = 0x1F;
        else if(data<800)
            LATB = 0x3F;
        else if(data<900)
            LATB = 0x7F;
        else if(data<1023)
            LATB = 0xFF;
    }
    return 0;
}
