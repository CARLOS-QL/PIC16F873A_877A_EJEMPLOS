
//////////////////////////////////////////////////////////////////////////
////  Mombre :      LCD.h                                             ////
////  Creación :    04/11/2018                                        ////
////  Descripción:  Configurable con cualquier PIN                    ////
////                Para familia mejorada LAT                         ////
////  LCD_init()    Inicializa PORTB con pull up.                     ////
////  LCD_dato(c)   Envia dato por el LCD                             ////
////                                                                  ////
//////////////////////////////////////////////////////////////////////////

//#ifndef LCD_H
//#define LCD_H

#define _XTAL_FREQ 4000000

#include <xc.h>
#include <stdlib.h>	//Para poder mostrar enteros
#include <stdint.h>	//Para poder usar tipo uint


//******** Pines para los datos del LCD *********

#define D4          PORTCbits.RC0          // pin 11 lcd         
#define D5          PORTCbits.RC1          // pin 12 lcd            
#define D6          PORTCbits.RC2          // pin 13 lcd               
#define D7          PORTBbits.RB3          // pin 14 lcd  
#define TRIS_D4     TRISCbits.TRISC0
#define TRIS_D5     TRISCbits.TRISC1
#define TRIS_D6     TRISCbits.TRISC2
#define TRIS_D7     TRISBbits.TRISB3

//******** Pines para el control del LCD **********

#define RS          PORTAbits.RA2           //Pin
#define EN          PORTAbits.RA3           //Pin
#define TRIS_RS     TRISAbits.TRISA2  	
#define TRIS_EN     TRISAbits.TRISA3  

#define ON  1
#define OFF 0

/******** Comandos para LCD *******/

#define LCD_CLEAR       0X01    //Limpia pantalla
#define LCD_CURSOR_ON   0X0F    //Cursor ON
#define LCD_CURSOR_OFF  0X0C    //Cursor off
#define LCD_LINEA1      0X02    //Primera línea
#define LCD_LINEA2      0XC0    //Segunda línea
#define LCD_LINEA3      0x94    //Tercera línea
#define LCD_LINEA4      0XD4    //Cuarta línea
#define LCD_LEFT        0X10    //Mueve cursor izquierda
#define LCD_RIGHT       0X14    //Mueve cursor derecha

#define ROT_LEFT        0X18    //Rotar izquierda
#define ROT_RIGHT       0X1C    //Rotar derecha

/************ Prototipos de funciones *************/

void LCD_init(void);                    	//Inicializa LCD
void LCD_cmd(unsigned char);                //Envia comando
void LCD_dato(unsigned char);               //Envia dato
void LCD_write(unsigned char dato);         //Rutina para enviar dato
void LCD_printf(unsigned char*);            //Imprime cadena de caracteres
void LCD_integer(int);                      //Imprime un entero
void LCD_goto(uint8_t, uint8_t);            //Mueve cursor a un XY
void LCD_cursor(unsigned char);             //Activa o desactiva cursor
void LCD_segunda_linea(void);
void LCD_clear(void);
void LCD_home(void);
void LCD_custom_char(unsigned char loc,unsigned char *msg);

//unsigned char TestBusyLCD (void);



