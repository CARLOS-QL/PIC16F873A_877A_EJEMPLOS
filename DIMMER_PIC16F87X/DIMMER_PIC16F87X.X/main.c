/*
 * File:   main.c
 * Author: Carlos QL
 *
 * Created on 18 de marzo de 2020, 02:03 PM
 */

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#define _XTAL_FREQ 400000
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "ADC.h"
#include "UART.h"

uint8_t tiempo;
uint8_t datos[10];

void __interrupt() Interrupcion(void){
     
    if(INTCONbits.TMR0IF == 1){
       
        PORTBbits.RB1 = 1;      //alto
        __delay_us(100);
        PORTBbits.RB1 = 0;      //bajo
        INTCONbits.TMR0IF = 0;
        INTCONbits.TMR0IE = 0;
            
    }else if(PIR1bits.RCIF == 1){
        
        char dataRX = RCREG;
        PIR1bits.RCIF = 0;
    
    }
    else if(INTCONbits.INTF == 1)
    {
        PORTBbits.RB1 = 0;      //triac apagdo
        TMR0 = tiempo;
        INTCONbits.TMR0IF = 0;  //Limpia bandera de tmr0
        INTCONbits.TMR0IE = 1;
        INTCONbits.INTF = 0;        
    }
    
}

void TIMER0_init(void)
{
    OPTION_REGbits.T0CS = 0;    //0 TEMP, 1 CONT
    OPTION_REGbits.PSA = 0;     //0= PRE-TMR0, 1=PRE-WDT
    OPTION_REGbits.PS = 0B100;   //256
    TMR0 = 255;       
}

void RB0_init(void)
{
    OPTION_REGbits.INTEDG = 1;  //1 subida, 0= bajda
    INTCONbits.INTF = 0;
}


void main(void) {
      
    TRISBbits.TRISB1 = 0;   //triac
    TRISBbits.TRISB0 = 1;   //in
   
    ADC_init();
    UART_init();
    TIMER0_init();
    RB0_init();
   
   INTCONbits.GIE = 1;     //Habilita interrupcion global       
   INTCONbits.INTE = 1;    //Habilita interrupcion por RB0
    __delay_ms(500); 
     
    while(1)
    {   
         tiempo = ADC_read(0);
         
         if(tiempo >= 210){
             PORTBbits.RB1 = 1;
             INTCONbits.INTE = 0;
        }else if(tiempo <= 10){
             PORTBbits.RB1 = 0;
             INTCONbits.INTE = 0;
        }else{
            INTCONbits.INTE = 1;
        }
         
//        sprintf(datos, "%d\n\r", tiempo);
//        UART_write_text(datos);
//        __delay_ms(10);
    }
    return;
}
 