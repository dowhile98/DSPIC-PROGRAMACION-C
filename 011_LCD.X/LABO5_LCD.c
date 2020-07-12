#include "config1.h"
#include "reloj.h"
#include "xlcd.h"
#include <libpic30.h>
#define delay_ms(x) __delay32((FCY/1000)*x) //macro para generar retardos en milisegundos

int main(void) {
    uint8_t i;//esta variable es usada para el desplazamiendo del display
    /*INICIALIZACION DE PERIFERICOS*/
    
    AD1PCFGL=0XFFFF;//SE DESACTIVA LAS ENTRADAS ANALOGICAS
    LCDInit();  //SE INICIA EL LCD
    TRISB=0x000;//SE INICIA LOS PINES PARA LA LCD
    
    /*SE MUESTRA EL MENSAJE DE BIENVENIDA*/
    LCD_clear();
    LCD_print("BIENVENIDO :)");
        delay_ms(1000);
    for(i=0;i<5;i++){
        LCD_shiftToLeft(i);
        delay_ms(300);
    }
    LCD_clear();
    LCD_setCursor(1,0);
    LCD_print("ING.ELECTRONICA");
    delay_ms(1000);
    
    for(i=0;i<5;i++){
        LCD_shiftToRight(i);
        delay_ms(300);
    }
    while(1){
        LCD_clear();
        LCD_cursorOn();
        LCD_cursorBlinkOn();
        LCD_print("  **intentos**");
        for(i=0;i<10;i++){
            LCD_setCursor(1,7);
            LCD_printInt(i);
            delay_ms(100);
        }
        LCD_clear();
        LCD_print("EL VALOR DE PI");
        LCD_setCursor(1,4);
        LCD_printFloat(3.1411323);
        delay_ms(1000);
        LCD_clear();
        LCD_print("MOVIMIENTO");
        for(i=1;i<16;i++){
            LCD_setCursor(1,(i-1));
            LCD_print(" ");
            LCD_print("*");
            delay_ms(100);
        }
        for(i=15;i>0;i--){
            LCD_setCursor(1,(i+1));
            LCD_print(" ");
            LCD_setCursor(1,(i));
            LCD_print("*");
            delay_ms(100);
        }
    }
    return 0;
}
