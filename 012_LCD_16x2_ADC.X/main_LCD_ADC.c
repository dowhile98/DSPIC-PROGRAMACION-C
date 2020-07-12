/*
 * File:   main_LCD_ADC.c
 * Author: QUINO B. JEFFRY
 *
 * Created on 11 de julio de 2020, 06:45 PM
 */

/*INCLUSION DE LIBRERIAS Y ARCHIVOS CABECERA*/
#include "config.h"
#include "reloj.h"
#include "xlcd.h"
#include <libpic30.h>
#include "ADC_dsPIC30_12bit.h"

/*funcion principal*/
int main(void) {
    /*INICIALIZACION DE PERIFERICOS*/
    
    ADPCFG=0XFFFF;//SE DESACTIVA LAS ENTRADAS ANALOGICAS
    
    /*inicializacion de pin para el led*/
    TRISBbits.TRISB9 = 0;       //RB9 SALIDA
    TRISBbits.TRISB10 = 0;      //RB10 SALIDA
    TRISBbits.TRISB11= 0;       //RB11 SALIDA
    //inicializacion de perifericos
    LCDInit();  //SE INICIA EL LCD
    ADC_Init(); //se inicialliza el adc
    
    /*SE MUESTRA EL MENSAJE DE BIENVENIDA*/
    LCD_clear();
    LCD_print("JQB----FIE UNAC");
    LCD_setCursor(1,0);         //mueve el cursor para la segunda fila
    LCD_print("ADC------>12 BIT");
    delay_ms(2000);
    
    uint16_t data;
    for(;;){
        data = ADC_ReadData();  //lee el valor analogico
        LCD_clear();
        LCD_setCursor(0,3);     //mueve el cursor
        LCD_print("ADC->AN8");
        LCD_setCursor(1,0);     //mueve el cursor a la segunda fila
        LCD_print("LECTURA->");
        LCD_printInt(data);     //se muestra el valor leido
        
        /*se enciende los tres leds de acuerdo al rango de lectura*/
        if(data<20){
            LATBbits.LATB9 = 0;
            LATBbits.LATB10 = 0;
            LATBbits.LATB11 = 0;
        }
            
        else if(data<1365){
            LATBbits.LATB9 = 1;
            LATBbits.LATB10 = 0;
            LATBbits.LATB11 = 0;
        }
        else if(data<2700){
            LATBbits.LATB9 = 1;
            LATBbits.LATB10 = 1;
            LATBbits.LATB11 = 0;
        }
        else if(data<4080){
            LATBbits.LATB9 = 1;
            LATBbits.LATB10 = 1;
            LATBbits.LATB11 = 1;
        }
            
        delay_ms(100);
        
    }
    return 0;
}

