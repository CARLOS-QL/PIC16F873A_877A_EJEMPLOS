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


#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "LCD.h"
#include "ADC.h"


void main(void) {
      
    uint16_t dato;
    uint8_t str[10];
    ADC_init();
    LCD_init();
    
    while(1)
    {   
        LCD_cmd(LCD_CLEAR);
        dato = ADC_read(0);
        sprintf(str, "%d", dato);
        LCD_write_text(str);
        __delay_ms(100);
        
    }
    return;
}
 