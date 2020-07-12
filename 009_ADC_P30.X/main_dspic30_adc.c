/*
 * File:   main_dspic30_adc.c
 * Author: Ronald Quino Bueno
 *
 * Created on 8 de julio de 2020, 12:10 PM
 */


#include "CONFIGURACION.h"
#include "ADC_dsPIC30.h"


int main(void) {
    ADC_Init();
    uint16_t data;
    
    //inicializacion de pines
    TRISB &=~(0xFF);//RB0-RB7 salida digital
    while(1){
        data = ADC_ReadData();
        if(data<20)
            LATB = 0x00;
        else if(data<500)
            LATB = 0x1;
        else if(data<1000)
            LATB = 0x3;
        else if(data<1500)
            LATB = 0x7;
        else if(data<2000)
            LATB = 0xF;
        else if(data<2500)
            LATB = 0x1F;
        else if(data<3000)
            LATB = 0x3F;
        else if(data<3500)
            LATB = 0x7F;
        else if(data<4095)
            LATB = 0xFF;
        
    }
    return 0;
}
