/*
 * File:   main.c
 * Author: Carlos QL
 *
 * Created on 1 de marzo de 2018, 02:47 PM
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

void main(void) {
  
    TRISB = 0b00011000;     //RB3, RB4 entrada
    TRISDbits.TRISD3 = 0;   //RD3 salida
    PORTDbits.RD3 = 0;
    
    while(1)
    {
        //Preguntar por el estado de RB3 y RB4
        if(PORTBbits.RB3 == 0)      //Han presionado el pulsador en RB3?
        {
            PORTDbits.RD3 = 1;      //Activamos led
        }
        if(PORTBbits.RB4 == 0)      //Han presionado el pulsador en RB4?
        {
            PORTDbits.RD3 = 0;      //Desactivamos led
        }
    }
    return;
}
