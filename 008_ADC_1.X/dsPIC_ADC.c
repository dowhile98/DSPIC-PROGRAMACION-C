/************************inclusion de archivos encabezado******************/
#include "dsPIC_ADC.h"

/*****************************************************************************
 *                      DEFINICION DE FUNCIONES                              *
 * **************************************************************************/
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
void ADC_Init(void){
    AD1PCFGL = 0xFFFF;      //inicialmente se desactiva todas los pines adc
    /*0. Se selecciona 10-bit o 12-bit*/
    AD1CON1bits.AD12B = 0;  //10-bit, 4-channel ADC operation
    /*1. Seleccione los pines del puerto como entradas analógicas (AD1PCFGH <15: 0> o AD1PCFGL <15: 0>).*/
    AD1PCFGLbits.PCFG0 = 0; //AN0
    TRISAbits.TRISA0 = 1;   //entrada analogica
    /*2. Seleccione la fuente de referencia de voltaje para que coincida con el rango 
     * esperado en las entradas analógicas (AD1CON2 <15:13>).*/
    AD1CON2bits.VCFG = 0;   //AVDD-AVss 
    /*3. Seleccione el reloj de conversión analógico para que coincida con la 
     * velocidad de datos deseada con el reloj del procesador (AD1CON3 <7: 0>).*/
    AD1CON3bits.ADCS = 1;   //2Tcy
    /*4. Determine cuántos canales de muestreo y retención se utilizarán 
     * (AD1CON2 <9: 8> y AD1PCFGH <15: 0> o AD1PCFGL <15: 0>).*/
    AD1CON2bits.CHPS = 0;   //00 = Converts CH0
    /*5. Seleccione la muestra apropiada/secuencia de conversión (AD1CON1 <7: 5> y AD1CON3 <12: 8>).*/
    AD1CON1bits.SSRC = 0;   //000 = Clearing sample bit ends sampling and starts conversion
    /*6. Seleccione la forma en que se presentan los resultados de conversión 
     * en el búfer (AD1CON1 <9: 8>).*/
    AD1CON1bits.FORM = 0;   //enteros
    /*7. SELECCIÓN DE ENTRADA ANALÓGICA PARA CONVERSIÓN*/
    AD1CHS0bits.CH0SA = 0;  // Channel 0 positive input is AN0
    AD1CHS0bits.CH0NA = 0;  //0 = Channel 0 negative input is VREF
    /*8. Encienda el módulo ADC (AD1CON1 <15>).*/
    AD1CON1bits.ADON = 1;
    /*9. Configure la interrupción de ADC (si es necesario):
        a) Borrar el bit AD1IF.
        b) Seleccione la prioridad de interrupción de ADC.*/
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
    AD1CON1bits.SAMP = 1;   //Start sampling
    int i;
    for(i = 0;i<1000;i++);  //Wait for sampling time
    AD1CON1bits.SAMP = 0;   //Start the conversion
    while(!AD1CON1bits.DONE);//Wait for the conversion to complete
    AD1CON1bits.DONE = 0;
    return ADC1BUF0;
}
