/************************inclusion de archivos encabezado******************/
#include "ADC_dsPIC30.h"

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
    //DESACTIVAMOS TODAS LAS ENTRADAS ANALOGICAS INICIALMENTE
    ADPCFG = 0xFFFF;                                        //todas entradas analogicas como digitales
    
    /*1.-SELECCIONAR LAS PATITAS COMO ENTRADAS ANALOGICAS,ADPCFG<12:0>*/
    TRISBbits.TRISB10 = 1;                                  //como entrada
    ADPCFGbits.PCFG10 = 0;                                  //AN10
    
    /*2.-seleccionar la fuente de tension de referencia para que coincida el rango
     *de conversion con el de las tenciones de entrada, AD1CON2<15:13>*/
    //VCFG<2:0>: Converter Voltage Reference Configuration bits
    ADCON2bits.VCFG = 0b000;
    /*3.-Seleccionar el reloj de conversion analogico, respecto al reloj del procesador,
     ADCON3<5:0>,para que concuerde con la informacion a adquirir*/
    //ADCS<5:0>: A/D Conversion Clock Select bits
    ADCON3bits.ADCS = 39;                                   //ADCS=39-->Valor del TAD>667ns
    /*4.-Determinar cuantos canales de muestreo y retencion van a ser utilizados
     ,ADCON2<9:8> Y AD1PCFGL<8:0>(dspic33fj32mc202) o ADPCFG<15:0>(dspic30f)*/
    //CHPS<1:0>: Select Channels Utilized bits
    
    /*5.-determinar como ocurirá el muestreo AD1CON1<3> y AD1CSSL<8:0>(dspic33fj32mc202)
      ADPSSL<15:0>(dspic30f)*/
    //SIMSAM: Simultaneous Sample Select bit (applicable only when CHPS<1:0> = 01 or 1x)
    //PCFG<8:0>: ADC Port Configuration Control bits
    
    
    /*6.-Determinar como serán asignados las entradas a los canales de muestreo
     y retencion. AD1CHSX<15:0>*/
    ADCHSbits.CH0SA = 10;//AN0
    ADCHSbits.CH0NB = 0;//Vref-
    /*7.-Seleccionar la secuencia de muestreo y retencion apropiada, ADCON1<7:2>
     ADCON3<12:8>*/
    //SSRC<2:0>: Sample Clock Source Select bits
    //SAMC<4:0>: Auto Sample Time bits(1)
    ADCON1bits.SSRC = 0;//Conversion manual
    ADCON3bits.SAMC = 1;//0Tad
    /*8.-Seleccionar como se presentarán lso resultaodos de la conversion en el buffer
     de resultado.ADCON1<9;8>*/
    //FORM<1:0>: Data Output Format bits
    
    ADCON1bits.FORM = 0;//enteros
    /*9.-Seleccionar el numero de conversiones que se deben llevar a cabo para que
     se genere una interrupcion. ADCON2<5:2>*/
    //SMPI<3:0>: Sample/Convert Sequences Per Interrupt Selection bits
    
    /*10.-Encender el modulo analógico digital. ADCON1<15>*/
    //ADON: ADC Operating Mode bit
    ADCON1bits.ADON = 1;//se activa el ADC
    /*11.-(OPCIONAL) Configuracion de las interrupciones del modulo
     *poner el bit ADIF = 0
     *Seleccionar la prioridad de las interrupciones
     */
   
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
    ADCON1bits.SAMP = 1;//inicia el muestreo
    int i ;
    for(i=0;i<1500;i++);    //genera un retardo para el muetreo
    ADCON1bits.SAMP = 0;
    while(!ADCON1bits.DONE);//se esepera hasta que se termine la conversion
    ADCON1bits.DONE = 0;//se limpia el bit
    
    return (ADCBUF0);
}

