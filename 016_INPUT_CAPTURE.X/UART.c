/*
 * File:   UART.c
 * Author: QUINO B. JEFFRY
 *
 * Created on 16 de julio de 2020, 08:04 PM
 */

/*INCLUSION DE LIBRERIAS*/
#include "UART.h"

/************************************************************************
 *                      DEFINCION DE FUNCIONES                          *
 * *********************************************************************/

#ifdef __UART_1
void UART1_Init_Default(uint32_t BaudRate){
    U1MODEbits.STSEL = UART_STOPBITS_1; // 1 Stop bit
    U1MODEbits.PDSEL = UART_PARITY_NONE; // No Parity, 8 data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1BRG = BRGVAL(BaudRate); // BAUD Rate Setting for 9600
    U1STAbits.URXISEL = 0; // Interrupt after one RX character is received

    IFS0bits.U1RXIF = 0; // Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 0; // Enable Recieve Interrupts
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX
}


void UART1_Init(uint32_t BaudRate,uint8_t StopBits, uint8_t Parity){
    U1MODEbits.STSEL = StopBits; // 1 Stop bit
    U1MODEbits.PDSEL = Parity; // No Parity, 8 data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1BRG = (uint16_t)BRGVAL(BaudRate); // BAUD Rate Setting for 9600
    U1STAbits.URXISEL = 0; // Interrupt after one RX character is received

    IFS0bits.U1RXIF = 0; // Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 0; // Enable Recieve Interrupts
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX;
}


void UART1_PutChar(char ch){
    while (U1STAbits.UTXBF == 1);
    U1TXREG = ch;
}

char UART1_ReceiveByte(void){
    while(!U1STAbits.URXDA);
    U1STAbits.URXDA = 0;       //0 = Receive buffer is empty
    return U1RXREG;
}
void UART1_ItTxEnable(uint8_t priority){
    U1STAbits.UTXISEL = 0;
    IPC2bits.U1TXIP = priority;
    IEC0bits.U1TXIE = 1;        //habilita la interrupcion
    IFS0bits.U1TXIF = 0;
}

void UART1_ItRxEnable(uint8_t rx_Imode,uint8_t priority){
    U1STAbits.URXISEL = rx_Imode;
    IFS0bits.U1RXIF = 0;  //limpia la bandera la interrupcion
    IPC2bits.U1RXIP = priority;
    IEC0bits.U1RXIE = 1;
}

void UART1_Close(void){
    U1MODEbits.UARTEN = 0;
	
    IEC0bits.U1RXIE = 0;
    IEC0bits.U1TXIE = 0;
	
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0;
}
#endif /*__UART_1*/

#ifdef __UART_2
/**
 @brief CONFIGURA LOS PARAMETROS BASICOS PARA LA COMUNICACION UART1
 *@param BaudRate:   velocidad en baudios
 @verbatim
 *  1 Stop bit
 *  No Parity, 8 data bits
 *  Auto-Baud Disabled
 * 
 */
void UART2_Init_Default(uint32_t BaudRate){
    U2MODEbits.STSEL = UART_STOPBITS_1; // 1 Stop bit
    U2MODEbits.PDSEL = UART_PARITY_NONE; // No Parity, 8 data bits
    U2MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U2BRG = BRGVAL(BaudRate); // BAUD Rate Setting for 9600
    U2STAbits.URXISEL = 0; // Interrupt after one RX character is received

    IFS1bits.U2RXIF = 0; // Clear the Recieve Interrupt Flag
    IEC1bits.U2RXIE = 0; // Enable Recieve Interrupts
    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable UART TX
}
/**
@brief CONFIGURA/ACTIVA EL UART1
 *@param BaudRate: velocidad en baudios         
 *@param StopBits : número de bits de parada transmitidos @ref UART_STOPBITS_X
 *@param Parity: Especifica el modo de paridad @ref UART_PARITY_x
@verbatim
 * configura los parametros y pone en marcha 
 * el UART1
@endverbatim
 */
void UART2_Init(uint32_t BaudRate,uint8_t StopBits, uint8_t Parity){
    U2MODEbits.STSEL = StopBits; // 1 Stop bit
    U2MODEbits.PDSEL = Parity; // No Parity, 8 data bits
    U2MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U2BRG = (uint16_t)BRGVAL(BaudRate); // BAUD Rate Setting for 9600
    U2STAbits.URXISEL = 0; // Interrupt after one RX character is received

    IFS1bits.U2RXIF = 0; // Clear the Recieve Interrupt Flag
    IEC1bits.U2RXIE = 0; // Enable Recieve Interrupts
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX;
}
/**
@brief ENVIA UN CARACTER POR EL PUERTO SERIAL
 *@param ch: el caracter que se desea enviar
@verbatim
 * esta funcion se utiliza para enviar
 * una caracter por el uart1
 */
void UART2_PutChar(char ch){
    while (U2STAbits.UTXBF == 1);
    U1TXREG = ch;
}
#endif /*__UART_2*/
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
              
              UART1_PutChar(*(char*)buffer++);
  }
  return(len);
}
