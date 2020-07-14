#include "TIM32.h"

/************DEFINIICON DE FUNCIONES*/
/**
@brief CONFIGURA EL TIMER 2 Y TIMER 3 COMO 32 BIT
@param :none
@returns: none
@verbatim
 * esta funcion sirve para la inicializacion de timer 2 y timer 3
 * como un solo timer de 32 bit
@endverbatim
 */
void TIM32_Init(void){
    T2CON = 0x0;                //BORRA TODA LA CONFIGURACION DEL TIMER 2
    T3CON = 0x0;                //BORRA TODA LA CONFIGURACION DEL TIMER 3
    T2CONbits.T32 = 1;          //activa el del el timer2 para 32 bit
    T2CONbits.TCKPS = 0b11;     //PSC-> 256
    PR2 = 0xB3F0;               //LSB
    PR3 = 0x1A;                 //MSB
    TMR2 = 0;
    TMR3 = 0;
    T2CONbits.TON = 1;          //inicia el conteo
}
