/*
 * File:   main_IC.c
 * Author: QUINO B. JEFFRY
 * Created on 24 de julio de 2020, 05:39 PM
 */

/*INCLUSION DE ARCHIVOS CABECERA*/
#include "config.h"
#include <stdint.h>
#include <stdio.h>
#include "UART.h"
/*DEFINICION DE PROTOTIPO DE FUNCIONES*/

/**
 @brief INICIALIZA EL MODULO DE CAPTURA DE ENTRADA
 *@param none
 *@return none
 @verbatim
 *  inicializa el modulo captura de entrada
 */
void InputCapture_Init(void);

/*definicion de variables globales*/
float timePeriod;        //para almacenar el valor de la freq
uint16_t count = 1;         //para verificar el valor que se va leer
uint16_t value[2];          //para la lectura del buffer

/*funcion principal*/
int main(void) {
    ADPCFG = 0xFFFF;        //se desabilita todos las entradas analogicas
    TRISBbits.TRISB0 = 0;   //RB0->SALIDA DIGITAL
    InputCapture_Init();
    UART1_Init_Default(9600);
    printf("INICIO EXITOSO\r\n");
    while(1){
        LATBbits.LATB0 ^= 1;
        delay_ms(0.5);
    }
    return 0;
}

/*DEFINICION DE FUNCIONES*/
void InputCapture_Init(void){
    T2CON = 0;
    T2CONbits.TCKPS = 1;    //PSC->8
    T2CONbits.TON = 1;      //HABILITA EL CONTEO DEL TIMER
    PR2 = 0xFFFF;           //PRESCALER A VALOR MAXIMO
    TMR2 = 0;               //SE RESETEA EL VALOR DEL REGISTRO DE CONTEO
    TRISDbits.TRISD8 = 1;   //ENTRADA->RD8
    IPC0bits.IC1IP = 1;     //PRIORIDAD 1
    IFS0bits.IC1IF = 0;     //SE BORRA EL FLAG
    IEC0bits.IC1IE = 1;     //HABILITA LA INTERRUPCION IC1->MODULO 1
    IC1CONbits.ICM = 3;     //CAPTURA POR FLANCO ASENDENTE
    IC1CONbits.ICI = 0;     //CAPTURA EN CADA DETECCION DE FLANCO
    IC1CONbits.ICTMR = 1;   //SELECCIONA EL TIMER 2 
}

void __attribute__((interrupt, no_auto_psv)) _IC1Interrupt(void){
    
    IFS0bits.IC1IF = 0;     //SE BORRA EL FLAG  
    
    if(IC1CONbits.ICBNE)//Input capture buffer is not empty
    {
        if(count==1){
            value[0] = IC1BUF;  //se lee el valor
            count++;            //count = count + 1
        }
        else{
            value[1] = IC1BUF;  //se lee el valor
            count = 1;      
            if(value[1]>value[0]){
                timePeriod = value[1] - value[0];
            }
            else{
                timePeriod = PR2 - value[0] + value[1] + 1;
            }
            timePeriod = (FCY/8)/(timePeriod);
            printf("frecuencia medida->%.2f Hz\r\n",timePeriod);
            
        }
    }
}