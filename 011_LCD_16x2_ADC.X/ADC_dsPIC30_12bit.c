
/************************inclusion de archivos encabezado******************/
#include "ADC_dsPIC30_12bit.h"

/*****************************************************************************
 *                      DEFINICION DE FUNCIONES                              *
 * **************************************************************************/
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
void ADC_Init(void){
    /*PASOS POR PARA LA INICIAR LOS PARAMETROS DEL ADC*/
    ADPCFG = 0xFFFF;                //se desactivan las entradas analogicas
    /*1. definir los pines de entradas analogicas*/
    ADPCFGbits.PCFG8 = 0;           //AN8
    TRISBbits.TRISB8 = 1;           //entrada analogica
    /*2. Seleccione la fuente de referencia de voltaje para que coincida 
     * con el rango esperado en las entradas anal�gicas ADCON2 <15:13>*/
    ADCON2bits.VCFG = 0;            //AVdd - AVss
    /*3. Seleccione el reloj de conversi�n anal�gico para que coincida 
     *con la velocidad de datos deseada con el reloj del procesador ADCON3 <5: 0>*/
    ADCON3bits.ADCS = 21;           //11Tcy
    /*4. Determine c�mo se asignar�n las entradas a los canales S / H ADCHS <15: 0>*/
    ADCHSbits.CH0SA = 8;            //AN8->MUX A
    ADCHSbits.CH0NA = 0;            //-Vref
    /*5. Seleccione la muestra apropiada / secuencia de conversi�n 
     * ADCON1 <7: 0> y ADCON3 <12: 8>*/
    ADCON1bits.SSRC = 7;            //conversion cuando SAMP es puesto a 0
    ADCON1bits.ASAM = 1;            //muestreo aotomatico despues de la conversion
    ADCON3bits.SAMC = 2;            //2Tad
    /*6. Seleccione c�mo se presentan los resultados de conversi�n en 
     * el b�fer ADCON1 <9: 8>*/
    ADCON1bits.FORM = 0;            //entero
    /*7. Seleccione la tasa de interrupci�n ADCON2 <5: 9>*/
    
    /*8. Encienda el m�dulo A / D ADCON1 <15>*/
    ADCON1bits.ADON = 1;            //enciende el modulo adc
    /*9. Configure la interrupci�n A / D (si es necesario)
        ? Borrar bit ADIF
        ? Seleccione prioridad de interrupci�n A / D*/
}
/**
@brief LECTURA DE DATOS DEL ADC
@param :none 
@returns: Data(16-bits)
@verbatim
 * esta funcion retorna el valor del contenido del registro ADCBUFx
@endverbatim
 */
uint16_t ADC_ReadData(void){
    /*ADCON1bits.SAMP = 0;//inicio de conversion
    while(!ADCON1bits.DONE);
    ADCON1bits.DONE = 0;*/
    return ADCBUF0;
}