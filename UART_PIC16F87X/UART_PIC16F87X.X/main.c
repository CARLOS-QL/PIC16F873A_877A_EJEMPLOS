/*
 * File:   main.c
 * Author: Carlos QL
 *
 * Created on 4 de marzo de 2018, 02:47 PM
 */

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#define _XTAL_FREQ 20000000
#include <xc.h>
#include "UART.h"


void main(void) {
   
    char dato_rx;
    TRISBbits.TRISB0 = 0;
    PORTBbits.RB0 = 0;
    
    UART_init();
    UART_printf("Encender led con 1 y apagar led con 0\n\r");
    
    while(1)
    {
        dato_rx = UART_read();
        
        if(dato_rx == '1'){
            UART_printf("led encendido \n\r");
            PORTBbits.RB0 = 1;
        }
        
        if(dato_rx == '0'){
            UART_printf("led apagado \n\r");
            PORTBbits.RB0 = 0;
        }
        
    }
    return;
}
