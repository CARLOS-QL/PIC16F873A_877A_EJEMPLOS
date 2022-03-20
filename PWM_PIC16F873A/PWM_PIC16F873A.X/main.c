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
#include "ADC.h"
#include "UART.h"


void TIMER2_init(void)
{
    TMR2 = 0;
    PR2 = 249;
    T2CONbits.TOUTPS = 0b1111;      //POSTSCALER 1:16
    T2CONbits.T2CKPS = 0b00;        //Prescaler 1:16
    T2CONbits.TMR2ON = 1;           //tmr2 on    
}


void main(void){
    
   uint8_t dato[15];
    TRISCbits.TRISC2 = 0;
    TIMER2_init();
    ADC_init();
    UART_init();
    
    CCP1CON = 0B00001100;
   
//    unsigned int dc = 100;
//    CCP1CONbits.CCP1Y = dc & (1<<0);
//    CCP1CONbits.CCP1X = dc & (1<<1);
//    CCPR1L = dc>>2;
    
    while (1) {
        
        unsigned int dc = ADC_read(0);
        sprintf(dato, "adc = %d\n\r", dc);
        UART_write_text(dato);
        if(dc>1000) dc =1000;
        CCP1CONbits.CCP1Y = dc & (1<<0);
        CCP1CONbits.CCP1X = dc & (1<<1);
        CCPR1L = dc>>2;    
        
    }
}
