/*
 * File:   main_uart_rx.c
 * Author: QUINO B. JEFFRY
 * Created on 22 de julio de 2020, 12:13 AM
 */

/*inclusion de archivos cabecera*/
#include "config.h"
#include <stdio.h>
/*defincion de macros*/
#define FCY                     20000000UL
#define BRGVAL(BAUDRATE)      (((FCY/BAUDRATE)/16) - 1)

/*prototipo de funciones*/
/**
 @brief CONFIGURA LOS PARAMETROS DEL UART1
 *@param BaudRate:   velocidad en baudios
 @verbatim
 *  1 Stop bit
 *  No Parity, 8 data bits
 *  Auto-Baud Disabled
 */
void UART1_Init(uint32_t BaudRate);
/**
 @brief RECEPCION DE DATOS RX
 *@param none
 *@return char 8-bit
 @verbatim
 *  retorno el caracter recibidos por el uart1
 */
char UART1_ReceiveByte(void);
/**
 @brief ENVIO DE UN CARACTER POR UART1
 *@param ch: caracter a enviar
 @verbatim
 * funcion que envia un caracter por el uart1
 */
void UART1_putChar(char ch);

/*definicion de variables globales*/
char ch;        //esta variable ses usa para mostrar el valor recibido en la interrupcion

int main(void) {
    UART1_Init(9600);
    printf("CONFIGURACION EXITOSA\n\r");
    
    while(1){
        
        
    }
    return 0;
}
/*DEFINICION DE FUNCIONES*/


void UART1_Init(uint32_t BaudRate){
    U1MODEbits.STSEL = 0; // 1 Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8 data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1BRG = BRGVAL(BaudRate); // BAUD Rate Setting for 9600
    U1STAbits.URXISEL = 0; // Interrupt after one RX character is received
    IFS0bits.U1RXIF = 0; // Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 0; // Enable Recieve Interrupts
    U1MODEbits.UARTEN = 1; // Enable UART
    
    IPC2bits.U1RXIP = 4;  //prioridad 4
    IFS0bits.U1RXIF = 0;  //limpia la bandera la interrupcion
    IEC0bits.U1RXIE = 1; // Enable UART Receive interrupt
    
    U1STAbits.UTXEN = 1; // Enable UART TX
}

char UART1_ReceiveByte(void){
    while(!U1STAbits.URXDA);
    U1STAbits.URXDA = 0;       //0 = Receive buffer is empty
    return U1RXREG;
}

void UART1_putChar(char ch){
    while (U1STAbits.UTXBF == 1);
    U1TXREG = ch;
}
/*****************************************************************************
 *      ESTA FUNCION SIRVE PARA EL USO DE LA FUNCION PRINTF                  *
 ****************************************************************************/
int    write(int handle, void *buffer, unsigned int len)
{
  int i;
   switch (handle)
  {
      case 0:        // handle 0 corresponds to stdout
      case 1:        // handle 1 corresponds to stdin
      case 2:        // handle 2 corresponds to stderr
      default:
          for (i=0; i<len; i++)
              
              UART1_putChar(*(char*)buffer++);
  }
  return(len);
}
/*******************************************************************************/

/*FUNCION DE RUTINA DE SERVICIO DE INTERRUPCION*/
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    if(U1STAbits.OERR == 1) {
        U1STAbits.OERR = 0; // Clear Overrun Error to receive data
   } else if ((U1STAbits.FERR ==0) && (U1STAbits.PERR ==0) ) {
        ch = U1RXREG; // Read Data if there is no parity or
   }
   IFS0bits.U1RXIF = 0; // clear TX interrupt flag
   printf("se recibio por interrupcin->%c\r\n",ch);
}