
/* 
 * File: ADC_dsPIC_12bit.h  
 * Author: QUINO B. jEFFRY
 * Comments: Encabezado para la configuracion del ADC del dsPIC30f4013
 * Revision history: v 1.0
 */ 

#ifndef __ADC_DSPIC30_12BIT_H
#define __ADC_DSPIC30_12BIT_H

/*******************INCLUSION DE LIBRERIAS**********************************/
#include <xc.h>     // include processor files - each processor file is guarded.  
#include <stdint.h>//contiene las definicion de datos uintx_t <x:8,16,64>

/********************DEFINICION DE MACROS***********************************/

/*********************DEFINCION  DE PROTOTIPO DE FUNCIONES******************/

/**
@brief CONFIGURA LOS PARAMETROS DEL ADC-DSPIC3F4013
@param :none
@returns: none
@verbatim
 * esta funcion sirve para la inicializacion del ADC del 
 * dsPIC30. se tiene que modificar la funcion a conveniencia
 * de la aplicacion a la que esta destinada
@endverbatim
 */
void ADC_Init(void);
/**
@brief LECTURA DE DATOS DEL ADC
@param :none 
@returns: Data(16-bits)
@verbatim
 * esta funcion retorna el valor del contenido del registro ADCBUFx
@endverbatim
 */
uint16_t ADC_ReadData(void);
#endif /* __ADC_DSPIC30_12BIT_H */

