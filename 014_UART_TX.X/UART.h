/*
 * File:   UART.h
 * Author: QUINO B. JEFFRY
 *
 * Created on 16 de julio de 2020, 08:04 PM
 */

#ifndef __UART_H
#define __UART_H

/*inclusion de librerias*/
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "reloj.h"
/******DEFINCION DE MACROS********/
/***************************************
 * definir __UART_1 si se usa el UART1 *
 * definir __UART_2 si se usa el UART2 *
 * *************************************/
#define __UART_1
//#define __UART_2

/*define la velocidad en baudios*/
//#define BAUDRATE    9600            //se tiene que modificar a la velocidad deseado
#define BRGVAL(BAUDRATE)      (((FCY/BAUDRATE)/16) - 1)


#define UART_PARITY_NONE        0       //!<00 = 8-bit data, no parity            
#define UART_PARITY_EVEN        0b01    //!<01 = 8-bit data, even parity            
#define UART_PARITY_ODD         0b10    //!<10 = 8-bit data, odd parity
#define UART_PARITY_9BIT_NONE   0b11    //!<11 = 9-bit data, no parity

#define UART_STOPBITS_1         0       //!<0 = 1 Stop bit                  
#define UART_STOPBITS_2         1       //!<1 = 2 Stop bits

#define ABAUD_ON                1       //!<1 = Input to Capture module from UxRX pin
#define ABAUD_OFF               0       //!<0 = Input to Capture module from ICx pin

/*defincion de prototipo de funciones*/
#ifdef __UART_1
/**
 @brief CONFIGURA LOS PARAMETROS BASICOS PARA LA COMUNICACION UART1
 *@param BaudRate:   velocidad en baudios
 @verbatim
 *  1 Stop bit
 *  No Parity, 8 data bits
 *  Auto-Baud Disabled
 * 
 */
void UART1_Init_Default(uint32_t BaudRate);
/**
@brief CONFIGURA/ACTIVA EL UART1
 *@param  none
 *@return none
@verbatim
 * esta funcion inicizaliza la lcd en moodo 4bits
@endverbatim
 */
void UART1_Init(uint32_t BaudRate,uint8_t StopBits, uint8_t Parity);
/**
@brief ENVIA UN CARACTER POR EL PUERTO SERIAL
 *@param ch: el caracter que se desea enviar
@verbatim
 * esta funcion se utiliza para enviar
 * una caracter por el uart1
 */
void UART1_PutChar(char ch);
/**
 @brief RECEPCION DE DATOS RX
 *@param none
 *@return char 8-bit
 @verbatim
 *  retorno el caracter recibidos por el uart1
 */
char UART1_ReceiveByte(void);
/**
@brief HABILITA LA INTERRUPCION TX UART
 *@param priority: prioridad de la interrupcion
@verbatim
 * activa la interrupcion tx uart1
 */

void UART1_ItTxEnable(uint8_t priority);
/**
@brief ACTIVA LA INTERRUPCION RX
 *@param rx_Imode: modo de interrupcion 0-3
 *@param priority: prioridad de la interrupcion [7:1]
@verbatim
 * activa la interrupcion RX uart1
 */
void UART1_ItRxEnable(uint8_t rx_Imode, uint8_t priority);
/**
@brief  DESABILITA EL UART1
@verbatim
 * borra la configuracion uart1
 */
void UART1_Close(void);


#endif /* __UART1 */

#ifdef __UART_2
void UART2_Init_Default(uint32_t BaudRate);

void UART2_Init(uint32_t BaudRate,uint8_t StopBits, uint8_t Parity);

void UART2_PutChar(char ch);

void UART2_ItTxEnable(uint8_t priority);
void UART2_ItRxEnable(uint8_t priority);

void UART2_Close(void);

#endif /* __UART2 */

#endif /* __UART_H */

