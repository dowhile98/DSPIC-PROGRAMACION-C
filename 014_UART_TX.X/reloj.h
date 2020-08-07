/*
 * File:   reloj.h
 * Author: QUINO B. JEFFRY
 *
 * Created on 16 de julio de 2020, 08:04 PM
 */
#ifndef __RELOJ_H
#define __RELOJ_H

/*inclusion de librerias*/
#include <libpic30.h>

#define FCY             20000000                //FCY = Fosc/4  (dsPIC30)
#define delay_ms(x)     __delay32((FCY/1000)*x)  //retardo en milisegundos

#endif /* __RELOJ_H */