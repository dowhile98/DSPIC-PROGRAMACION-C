/*
 * File:   main_OC.c
 * Author: QUINO B. JEFFRY
 * Created on 25 de julio de 2020, 02:44 PM
 */

/*INCLUSION DE ARCHIVOS CABECERA*/
#include "config.h"
#include <libpic30.h>
/*DEFININICION DE MACROS*/
#define FCY         (7370000/2)
#define delay_ms(x) __delay32((FCY/1000)*x)

/*DEFINICION DE PROTOTIPO DE FUNCIONES*/
/**
 * @brief INICIALIZA EL OC1
 * @param : none
 * @return :none
 * @verbatim
 */
void OC1_Init(void);

int main(void) {
    /*inicializacion de perifericos*/
    OC1_Init();
    uint16_t duty;
    while(1){
        for(duty = 0;duty<1300;duty+=1){
            OC1RS = duty;
            delay_ms(20);
        }
    }
    return 0;
}
/*DEFINICION DE FUNCIONES*/
void OC1_Init(void){
    
    OC1R = 0;         // Duty cycle en 0
    OC1RS = 1;     // Initialize Secondary Compare Register1 with 0x0026
    OC1CONbits.OCTSEL = 1; // Select Timer 3 as output compare time base
    OC1CONbits.OCM = 0b110; // PWM mode without fault protection
    TMR3 = 0x00;          // Clear timer register
    PR3 = 1301;          // Initialize PR3 with 60HZ
    T3CONbits.TCKPS = 3;  //Preescaler 256
    T3CONbits.TON = 1;    // Start Timer3 with assumed settings

}