/*
 * File:   main_uart_tx.c
 * Author: Ronald Quino Bueno
 *
 * Created on 16 de julio de 2020, 08:04 PM
 */

/*********inclusion de archivos cabecera**********/
#include "config.h"
#include "UART.h"



int main(void) {
    UART1_Init_Default(57600);
    printf("BIENVENIDO AL UART1\r\n");
    while(1){
        
        int i;
        for(i=0;i<100;i++){
            printf("iteracion->%d\r\n",i);
            delay_ms(500);
        }
        
    }
    return 0;
}
