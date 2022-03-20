/*
 * File:   main.c
 * Author: Carlos QL
 *
 * Created on 4 de marzo de 2018, 02:47 PM
 */

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000
#include <xc.h>
#include "UART.h"

#define LED1 PORTBbits.RB0
#define LED2 PORTBbits.RB1
#define LED3 PORTBbits.RB2

void main(void) {
       
    char dato_rx;
    TRISB = 0B11111000;     //RB0 RB1 RB2 OUTPUT
    PORTB = 0X00;
    UART_init();
    __delay_ms(1000);
    
    while(1)
    {
        
        //RB0 encienda A apague B
        //RB1 encienda C apague D
        //RB2 encienda E apague F
                
        dato_rx = UART_read();
          
        switch(dato_rx)
        {            
            case 'A':
                LED1 = 1;
                UART_write('a');
                break;
                
            case 'B':
                UART_write('b');
                LED1 = 0;
                break;
                
            case 'C':
                LED2 = 1;
                UART_write('c');
                     break;
                     
            case 'D':
                LED2 = 0;
                UART_write('d');
                      break;
                      
            case 'E':
                LED3 = 1;
                UART_write('e');
                     break;
                     
            case 'F':
                LED3 = 0;
                UART_write('f');
                      break;                                         
        }           
    }
    return;
}
