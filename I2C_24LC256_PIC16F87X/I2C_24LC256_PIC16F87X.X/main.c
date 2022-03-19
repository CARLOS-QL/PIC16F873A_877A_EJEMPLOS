/*
 * File:   main.c
 * Author: CarlosQL
 *
 * Created on 9 de marzo de 2019, 11:48 AM
 */

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#define _XTAL_FREQ  4000000

#include <xc.h>
#include <stdint.h>
#include "I2C.h"
#include "LCD.h"

char datos[] = "PIC16F873A";

void main(void) {
    
    ADCON1 = 0X06;
    LCD_init();
    I2C_init();
    
    
    I2C_start();              
    I2C_write(0b10100000);      // Dirección de EEPROM, modo escritura
    I2C_write(0);               // parte alta de direcccion
    I2C_write(0);               // Parte baja de direccdion
   
    for(char i=0; i<8; i++){
        I2C_write(datos[i]);
    }
    
    
    I2C_stop();
    __delay_ms(20);
    
    
    I2C_start();
	I2C_write(0b10100000);      // Dirección de EEPROM , modo escritura
	I2C_write(0);               // parte alta de direcccion
    I2C_write(0);               // Parte baja de direccdion

	I2C_restart();
	I2C_write(0b10100001);      // Dirección de EEPROM , modo lectura

    for(char i=1; i<=8; i++){
       
         LCD_dato(I2C_read());
         if(i==8)  
            I2C_nack();
            
         else
            I2C_ack();
    }
	I2C_stop();
    
   
    while(1){    
        
    }
    return;
}
