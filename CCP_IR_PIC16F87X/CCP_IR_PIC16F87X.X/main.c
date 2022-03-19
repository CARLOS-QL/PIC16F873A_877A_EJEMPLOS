/*
 * File:   main.c
 * Author: CarlosQL
 *
 * Created on 31 de julio de 2019, 10:36 PM
 */
// CONFIG
#pragma config FOSC = XT // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdio.h>
#include "LCD.h"

unsigned char llave=0;
unsigned int contador_bits=0;
unsigned char ir_comando=0, ir_direccion=0;
unsigned int resultado[35];

void __interrupt() isr(void)
{
    if(TMR1IE && TMR1IF)
    {
        TMR1=0;         //Limpiamos temporizador
        TMR1IF=0;       //0.25us * 4 = 1us
        llave=0;
        contador_bits=0;   
    }
    if(CCP1IF)
    {
         TMR1=0;
        CCP1IE=0;
        CCP1IF=0;
        if(!llave)
        {
            resultado[contador_bits]=CCPR1;
            contador_bits++;
            if(contador_bits>33)
            {
                ir_comando = 0;
                ir_direccion = 0;
                for(unsigned char i=8; i>0 ;i--)
                {
                    ir_direccion >>= 1;        
                    ir_comando >>= 1;
                                      
                    if(resultado[i+1]>240) ir_direccion |= 0b10000000;
                    if(resultado[i+17]>240) ir_comando |= 0b10000000;                                      
                }
                contador_bits=0;
                llave=1;
            }
        }
        CCP1IE=1;
    }

}


void main(void) {
   
     ADCON1 = 0X06;
    LCD_init();
    char str1[21];
    TRISC2=1;
    CCP1IE=1;           //Habilitamos interrupcion poc ccp1
    CCP1CON=0x04;       //Modo captura cada flanco descendente
    CCP1IF=0;           //Limpiamos bandera de ccp1
    
    T1CKPS0=1;          //Prescaler a 8
    T1CKPS1=1;
    TMR1CS=0;           //Modo temporizador
    TMR1IE=1;           //Habilitamos interrrupcion por timer1
    GIE=0X1;            //Habilitamos interrupción global
    PEIE=0X1;           //Habilitamos interrupcion por perifericos
    TMR1ON=1;           //Encendemos timer1
   
    
    while(1)
    {
        LCD_clear();
        sprintf(str1,"Comando:   0x%02X ", ir_comando);
        LCD_write_txt(str1); 
        sprintf(str1,"Direccion: 0x%02X ", ir_direccion);
        LCD_gotoxy(1, 2);       
        LCD_write_txt(str1); 
        __delay_ms(100);  
        
    }
    return;
}
