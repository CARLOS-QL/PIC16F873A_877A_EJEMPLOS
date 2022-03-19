
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

#define _XTAL_FREQ 4000000      //Necesita para los retardos
#include <xc.h>
#include <stdint.h>	//Para poder usar tipo uint


/******** Pines para los datos del LCD *********/

#define D4          PORTCbits.RC0          // pin 11 lcd         
#define D5          PORTCbits.RC1          // pin 12 lcd            
#define D6          PORTBbits.RB2          // pin 13 lcd               
#define D7          PORTCbits.RC3           // pin 14 lcd 

#define TRIS_D4     TRISCbits.TRISC0        //D4 Out
#define TRIS_D5     TRISCbits.TRISC1        //D5 Out
#define TRIS_D6     TRISBbits.TRISB2        //D6 Out
#define TRIS_D7     TRISCbits.TRISC3        //D7 Out   

//******** Pines para el control del LCD **********


#define RS          PORTAbits.RA2           //Pin 4 LCD
#define EN          PORTAbits.RA3          //Pin 6 LCD
#define TRIS_RS     TRISAbits.TRISA2        //RS Out   
#define TRIS_EN     TRISAbits.TRISA3        //EN Out


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

void LCD_write_nible(unsigned char);
void LCD_init(void);                            //Inicializa LCD
void LCD_cmd(unsigned char);                    //Envia comando
void LCD_dato(unsigned char);                   //Envia dato
void LCD_write_txt(unsigned char*);             //Imprime cadena de caracteres
void LCD_gotoxy(unsigned char, unsigned char);  //Mueve cursor a un XY
void LCD_clear(void);
void LCD_custom_char(unsigned char loc,unsigned char *msg);




