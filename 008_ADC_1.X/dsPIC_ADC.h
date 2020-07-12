/**
 @file dsPIC_ADC.h

@brief encabezado para la inicializacion del ADC

@author JEFFRY QUINO BRICEÑO

@date 07/07/2020
 */
#ifndef __DSPIC_ADC
#define __DSPIC_ADC

/*******************INCLUSION DE LIBRERIAS**********************************/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include "../../dsPIC33F/h/p33FJ32MC202.h" 

/********************DEFINICION DE MACROS***********************************/


/*********************DEFINCION  DE PROTOTIPO DE FUNCIONES******************/

/**
@brief inicializa el ADC 
@param :none
@returns: none
@verbatim
 * esta funcion sirve para la inicializacion del ADC del dsPIC33 
 * y dsPIC30. se tiene que modificar la funcion a conveniencia
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
#endif	/* __DSPIC_ADC */

