/*
 * File:   main.c
 * Author: CarlosQL
 *
 * Created on 24 de febrero de 2019, 02:45 PM
 */

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
#include <stdio.h>
#include "UART.h"

// Solo para version hasta la 1.45 del compilador XC8
//void interrupt Interrupcion(void)
//{
//    
//}

void __interrupt() Interrupcion(void)
{   
    if(INTCONbits.INTF == 1){
        printf("Interupcion en RB0 \n\r");
        INTCONbits.INTF = 0;
    }else if(PIR1bits.RCIF == 1){
        
        char dataRX = RCREG;
        UART_write(dataRX);
        printf(" Interupcion en RX USART \n\r");
        PIR1bits.RCIF = 0;
    }   
}

void main(void) {
   
    UART_init();
    char numero = 0;
    
    INTCONbits.GIE = 1;         // Habilita interrupciones globales
    INTCONbits.PEIE = 1;        
    INTCONbits.INTE = 1;        // Habilita interrupcion por RB0
    PIE1bits.RCIE = 1;          // Habilita interrupcion por RX
    OPTION_REGbits.INTEDG = 1;  // Interrupcio por Flanco de subida
    
    while(1){
        
        printf("El numero es %d\n\r", numero++); 
       __delay_ms(1000);
   
    }
    return;
}
