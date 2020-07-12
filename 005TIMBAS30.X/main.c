#include <p30F4013.h>

#include "config.h"

int main(void) {
    TIMER1_Init(); //se inicializa el timer1
    TIMER2_Init(); //se inicializa el tiner2
    TIMER3_Init();
    GPIO_Init();

    while (1) {
        if (IFS0bits.T1IF) {
            LATBbits.LATB0 ^= 1; //toggle pin
            IFS0bits.T1IF = 0;
        }
        if (IFS0bits.T2IF) {
            LATBbits.LATB1 ^= 1;
            IFS0bits.T2IF = 0; //se restea el flag del conteo
        }
        if (IFS0bits.T3IF) {
            LATBbits.LATB2 ^= 1;
            IFS0bits.T3IF = 0; //se resetea el flag de conteo
        }

    }
}

//DEFINICION DE FUNCIONES DE INICIALIZACION DE TIMERs

void TIMER1_Init(void) {
    T1CON = 0x0000; //se restea el timer 1
    T1CONbits.TCKPS = 0x3; //PS ->256
    PR1 = 57578; //valor de autorecarga->500ms
    T1CONbits.TON = 1; //se habilita el conteo del timer
}

void TIMER2_Init(void) {
    T2CON = 0x0000; //resetea el timer 2
    T2CONbits.TCKPS = 0x3; //PS->256
    PR2 = 11515; //valor de autorecarga->100ms
    T2CONbits.TON = 1; //se habilita el conteo
}

void TIMER3_Init(void) {
    T3CON = 0x0000; //resetea el timer 3
    T3CONbits.TCKPS = 0x3; //PS->256
    PR3 = 28789; //250ms
    T3CONbits.TON = 1; //se habilita el conteo
}
//DEFINICION DE FUNCION QUE INICIALIZA LOS PINES

void GPIO_Init(void) {
    ADPCFG = 0xFFFF; //se desabilita la funcion ADC
    TRISBbits.TRISB0 = 0; //RB0 ->salida digital para timer 1
    TRISBbits.TRISB1 = 0; //RB1 ->salida digital para el timer 2
    TRISBbits.TRISB2 = 0; //RB2 ->salida digital para el timer 3
}