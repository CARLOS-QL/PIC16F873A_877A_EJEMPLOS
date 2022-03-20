/*
 * File:   main.c
 * Author: Carlos QL
 *
 * Created on 26 de mayo de 2020, 02:58 PM
 */


// PIC16F873A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#define _XTAL_FREQ 4000000
#include <xc.h>


#define LED PORTBbits.RB1

void TIMER2_init(void)
{
    TMR2 = 0;
    PR2 = 195;
    T2CONbits.TOUTPS = 0b1111;      //POSTSCALER 1:16
    T2CONbits.T2CKPS = 0b11;        //Prescaler 1:16
    T2CONbits.TMR2ON = 1;           //tmr2 on    
}

void __interrupt() ISR_timer2(void)
{
    if(PIR1bits.TMR2IF == 1)
    {
        LED = !LED; 
        PIR1bits.TMR2IF = 0;
    }    
}

void main(void){
    
    TRISBbits.TRISB1 = 0;
    LED = 0;
    
    TIMER2_init();
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR2IE = 1;
    

    while (1) {
        
      
    }
}
