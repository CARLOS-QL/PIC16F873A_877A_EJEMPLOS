
//////////////////////////////////////////////////////////////////////////
////  Mombre :      LCD.h                                             ////
////  Creación :    04/11/2018                                        ////
////  Descripción:  Configurable con cualquier PIN                    ////
////                Para familia mejorada LAT                         ////
////  LCD_init()    Inicializa PORTB con pull up.                     ////
////  LCD_dato(c)   Envia dato por el LCD                             ////
////                                                                  ////
//////////////////////////////////////////////////////////////////////////
 
 #include "LCD.h"

/***********************************************
 ------- Inicializa LCD 4 bits de datos -------
 ***********************************************/

void LCD_init(void) {
   
    TRIS_RS = 0;            //RS output
    TRIS_EN = 0;            //EN output
    
    RS = 0;                 //RS en 0            
    EN = 0;                 //EN en 0
         
    TRIS_D4 = 0;        //D4 output
    TRIS_D5 = 0;        //D3 output
    TRIS_D6 = 0;        //D2 output
    TRIS_D7 = 0;        //D1 output
        
    __delay_ms(20);     //Espera que se estabilicen puertos
    
    for(unsigned char i=0; i<3; i++){   //Recomendado 
        LCD_write_nible(0x03);          //por fabricante
        __delay_ms(5);
    }
 
    LCD_cmd(0x02);          //Asegura el Cursos del LCD Al inicio (Home)
    __delay_ms(5);
    LCD_cmd(0x28);          //Configura el LCD a 4 Bits, 2 Lineas Y Fuente de 5*8
    __delay_ms(5);
    LCD_cmd(0x0C);          //LCD Prendido, Cursor Apagado, Destello Cursor apagado
    __delay_ms(5);
    LCD_cmd(0x01);          //Limpia pantalla
    __delay_ms(5);
}

/***********************************************
 ---- Rutina para enviar datos y comandos ------
 ***********************************************/

void LCD_write_nible(unsigned char nible){
    
    if (nible & (1<<0)) D4 = 1; else D4 = 0;             
    if (nible & (1<<1)) D5 = 1; else D5 = 0;
    if (nible & (1<<2)) D6 = 1; else D6 = 0;
    if (nible & (1<<3)) D7 = 1; else D7 = 0;
    
    EN = 1;     
    NOP(); NOP();
    EN = 0; 
}

/***********************************************
 ---------- Envía comandos por el LCD ----------
 ***********************************************/

void LCD_cmd(unsigned char dato) {
   
    RS = 0;
    __delay_us(150);
    RS = 0;
    NOP();
     
    LCD_write_nible(dato>>4);
    LCD_write_nible(dato & 0x0F);
}

/***********************************************
 ----------- Envía datos por el LCD ------------
 ***********************************************/

void LCD_dato(unsigned char dato) {
    
    RS = 0;
    __delay_us(100);
    RS = 1;
    NOP();
    LCD_write_nible(dato>>4);
    LCD_write_nible(dato & 0x0F);
}

/***********************************************
 ----------- Imprime string por LCD ------------
 ***********************************************/

void LCD_write_txt(unsigned char *dato) {
    while (*dato){
        LCD_dato(*dato);    // Envio el dato al LCD
        dato++;             // Incrementa el buffer de dato
    }
}

/***********************************************
 ----- Mueve el cursor a una posición x y ------
 ***********************************************/

void LCD_gotoxy(unsigned char x, unsigned char y){
    unsigned char posicion;
    switch (y) {
        case 1: posicion = 0x00 + x - 1; break;
        case 2: posicion = 0x40 + x - 1; break;
        case 3: posicion = 0x14 + x - 1; break;
        case 4: posicion = 0x54 + x - 1; break;
        default: posicion = 0x00 + x - 1; break;
    }
    LCD_cmd(0x80 | posicion);
}

/***********************************************
 --------- Limpia toda la pantalla LCD ---------
 ***********************************************/

void LCD_clear(void) {
    LCD_cmd(0x01);
    __delay_ms(3);
}


/********************************************************
 ------------- Para personalizar caracter ---------------
 *******************************************************/

void LCD_custom_char(unsigned char GGRAM_adress,unsigned char *msg){
    
    unsigned char i;
    if(GGRAM_adress<8){
        LCD_cmd(0x40+(GGRAM_adress*8));  /* Command 0x40 and onwards forces the device to point CGRAM address */
        for(i=0;i<8;i++)  /* Write 8 byte for generation of 1 character */
            LCD_dato(msg[i]);
    }   
}






