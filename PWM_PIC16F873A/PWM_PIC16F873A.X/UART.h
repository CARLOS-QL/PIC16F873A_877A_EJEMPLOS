
/**********************************************
 * Libreria:    UART.h
 * Author:      Carlos QL
 * Contacto:    carlos.quispe.359@gmail.com
 * Descripcion  Para el manejo de UART de un PIC16F
 *              8 bits de datos
 * Formula Alta velocidad
 *              N = [Fosc/(BaudRate*16)]-1] 
 * Formula Baja Velocidad
 *              N = [Fosc/(BaudRate*64)]-1]
 **********************************************/

#include <stdio.h>
#include <stdbool.h>

/****************************************
 * Funcion para inicialiar UART 
 ***************************************/

void UART_init(void)
{
    TRISCbits.TRISC7 = 1;   //Pin RX input
    TRISCbits.TRISC6 = 0;   //Pin TX output 
    
    TXSTAbits.SYNC = 0;     //0= asíncrono, 1= síncrono
    TXSTAbits.TX9 = 0;      //0=8 bits, 1=9 bits
    TXSTAbits.BRGH = 1;     //0=baja velocidad, 1=alta velocidad
    SPBRG = 25;             //N = [Fosc/(BaudRate * 64)]]
    RCSTAbits.SPEN = 1;     //UART on    
    TXSTAbits.TXEN = 1;     //TX on
    RCSTAbits.CREN = 1;     //RX on
}

/****************************************
 * Funcion para leer por UART
 ****************************************/

unsigned char UART_read(void)
{
    while(!PIR1bits.RCIF);
    if(RCSTAbits.OERR == 1)   // Resetear si hay error
    {
        RCSTAbits.CREN = 0; 
        RCSTAbits.CREN = 1; 
    }
    return RCREG;
}

/****************************************
 * Funcion para escribir por UART
 ****************************************/

void UART_write(unsigned char dato)
{
    TXREG = dato;
    while(TXSTAbits.TRMT == 0);
}

/*****************************************
 * Retorna true si hay dato en RX
 * Para utilizar esta funcion necesitas 
 ****************************************/

bool UART_is_rx_ready(void)
{
    return (bool)(PIR1bits.RCIF);
}

/********************************************
 * Para enviar cadena de caracteres por TX
 *******************************************/

void UART_write_text(unsigned char *cadena)
{
    while(*cadena !=0x00){
        UART_write(*cadena);
        cadena++;
    }
}

/*************************************************
 * Para utilizar estas funciones necesitas stdio.h 
 ************************************************/

char getch(void)
{
    return UART_read();
}

void putch(char txData)
{
    UART_write(txData);
}

