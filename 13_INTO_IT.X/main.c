/*
 * File:   main.c
 * Author: Jeffry Quino Briceño
 *
 * Created on 9 de junio de 2020, 10:55 PM
 */




#include "config.h"
//DEFINICION DE MACROS
#define MAX_DELAY 0xFFFF        //maximo valor que puede contar el timer
#define TICK_FREQ 1             //1KHz
//DEFINICION DE PROTOTIPO DE FUNCIONES
void CLK_Config(void);          //PARA CONFIGURAR EL PLL
void INTO_Init(void);           //funcion para iniciar la interrupcion externa                   
void GPIO_Init(void);           //funcion para la configuracion de pines
void TIMER1_Init(void);         //funcion para configurarar el timer 1
void delay_ms(uint16_t delay);  //funcion de retardo en tiempo exacto en ms


//DEFINICION DE VARIABLES GLOBALES
uint32_t tick;                  //variable global que aumentara en 1 su valor en cada interrupcion de timer


int main(void) {
    /*inicializacion de perifericos*/
    CLK_Config();
    INTO_Init();
    GPIO_Init();
    TIMER1_Init();
    while(1){
        LATBbits.LATB15 ^=1;
        delay_ms(50);
    }
    return 0;
}

/*DEFINICION DE FUNCIONES*/

//funcion que configura el PLL
//FRC->RC = 7.37MHz
void CLK_Config(void){
    //Fosc = Fin*(M/(N1*N2))            ->Fin salida del reloj primario o FRC
    CLKDIVbits.PLLPRE = 0x0000;         //N1->2
    CLKDIVbits.PLLPOST = 0x0;           //N2->2
    PLLFBD = 41;                      //M->43
    
    //Fosc = 7.37*1000000*(43/4)= 79MHz
    //Fy = Fosc/2 = 39MHz               ->maxima velocidad
}
//funcion que inicializa la interrupcion para el INT0
void INTO_Init(void){
    IPC0bits.INT0IP = 2;                //prioridad 2
    IFS0bits.INT0IF = 0;                //se resetea la bandera de interrupcion
    INTCON1bits.NSTDIS = 1;             //se habilitan las interrupciones andidadas
    INTCON2bits.INT0EP = 0;             //interrupcion flanco ascendente(rising)
    IEC0bits.INT0IE = 1;                //se habilita la interrupcion externa 
    
}
//funcion que inicializa los pines GPIO
void GPIO_Init(void){
    /**/
    TRISBbits.TRISB13 = 0;              //RB13 como salida digital
    TRISBbits.TRISB15 = 0;              //RB15 como salida digital
    TRISBbits.TRISB7 = 1;               //RB7 como entrada digital
    
}

//funcion que inicializa el TIMER1
void TIMER1_Init(void){
    T1CON = 0x0000;                     //se resetea el timer
    T1CONbits.TCKPS = 0x1;              //PS->8
    TMR1 = 0x0000;                      //se resetea el registro de conteo
    PR1 = 4951;                         //1ms periodo de conteo
    T1CONbits.TON = 1;                  //se habilita el conteo del timer 1
    //se activa la interrupcion
    IPC0bits.T1IP = 1;                  //prioridad de interrupcion 1
    IEC0bits.T1IE = 1;                  //se habilita la interrupcion por timer
}

/*DEFINICION DE LA FUNCION RETARDO*/
void delay_ms(uint16_t delay){
    uint32_t tickStart = tick;          //tick es una variable global
    uint16_t wait = delay;              
    
    if(wait<MAX_DELAY)                  //si el tiempo de espera es menor al maximo valor de conteo
    {
        wait += TICK_FREQ;
    }
    
    while((tick-tickStart)<wait);       //se espera hasta que diferencia sea mayor
}

/*RUTINAS DE SERIVICIO PARA LAS INTERRUPCIONES*/

//Interrupcion de timer1
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {

    IFS0bits.T1IF = 0; /* Ponemos a 0 el Flag de la Int Externa 0*/
    tick += TICK_FREQ;  //se suna el valor de frecuencia (1)
}
//interrupcion externa INT0
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void) {
    IFS0bits.INT0IF = 0;
    LATBbits.LATB13 ^=1;
}
