/**********************************************
* Libreria:    ADC.h
* Author:      Carlos QL
* Contacto:    carlos.quispe.359@gmail.com
* Descripcion  Para el manejo del ADC del PIC16F
* TAD mínimo 1.6us 
* Tiempo de AdquisiciÃ³n mÃ­nimo 20us	
 **********************************************/

#include <stdint.h>

/******************************************
* Inicialización del ADC
******************************************/

void ADC_init(void)
{
    ADCON1bits.ADFM = 1;        // 1 derecha, 0 izquierda
    ADCON1bits.PCFG = 0b1110;   // Todo como analogico
    ADCON1bits.ADCS2 = 0;       // Seleccion de reloj para ADC
    ADCON0bits.ADCS1 = 0;       // debe ser mayor a 1.6us
    ADCON0bits.ADCS1 = 1;   
    ADCON0bits.ADON = 1;        //ADC on
}

/*****************************************
* Lectura de un canal Analogico
*****************************************/

uint16_t ADC_read(uint8_t channel)
{
    ADCON0bits.ADCS = channel;                  //Seleccion e canal
    __delay_us(25);                             //Tiempo de adquisicion
    ADCON0bits.GO = 1;                          //ADC start
    while(ADCON0bits.GO_DONE);                  //Espera termine la conversion
    return ((uint16_t)((ADRESH<<8)+ADRESL));    //Retorna el valor del ADC
}