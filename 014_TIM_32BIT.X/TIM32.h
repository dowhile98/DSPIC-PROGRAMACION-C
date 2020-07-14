
/* 
 * File: TIM32.h
 * Author: QUINO B. jEFFRY
 * Comments: ENCABEZADO PARA LA CONFIGURACION DE TIMER DE 32 BIT
 * Revision history: v 1.0
 */ 
#ifndef __TIM32_H
#define __TIM32_H
/*****************************************************
 *      inclusion de archivos cabecera               *
 * **************************************************/
#include <xc.h>

/************DEFINIICON DE PROTOTIPO DE FUNCIONES*/
/**
@brief CONFIGURA EL TIMER 2 Y TIMER 3 COMO 32 BIT
@param :
@returns: 
@verbatim
 * esta funcion sirve para la inicializacion 
 * de timer 2 y timer 3
 * como un solo timer de 32 bit
@endverbatim
 */
void TIM32_Init(void);

#endif /*__TIM32_H*/