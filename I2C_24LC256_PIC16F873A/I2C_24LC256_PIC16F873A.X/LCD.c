
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

void LCD_init() {
   
    TRIS_D4 = 0;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    
    TRIS_RS = 0;             //Pin RS output
    TRIS_EN = 0;             //Pin E output
    RS = 0;                  //RS en 0            
    EN = 0;                  //E en 0
   
    D4 = 0;
    D5 = 0;
    D6 = 0;
    D7 = 0;
     
    __delay_ms(50);         //Tiempo de espera a que se estabilicen los puertos
    LCD_cmd(0x02);          //Asegura el Cursos del LCD Al inicio (Home)
    LCD_cmd(0x28);          //Configura el LCD a 4 Bits, 2 Lineas Y Fuente de 5*8
    LCD_cmd(0x0C);          //LCD Prendido, Cursor Apagado, Destello Cursor apagado
    LCD_cmd(0x06);          //No rota el mensaje Y se incrementa el contador de direccion
    LCD_cmd(0X01);          //Limpia la pantalla
    __delay_ms(300);
}

/***********************************************
 ---- Rutina para enviar datos y comandos ------
 ***********************************************/

void LCD_write(unsigned char dato){
    
    if (dato & (1<<4)) D4 = 1; else D4 = 0;             
    if (dato & (1<<5)) D5 = 1; else D5 = 0;
    if (dato & (1<<6)) D6 = 1; else D6 = 0;
    if (dato & (1<<7)) D7 = 1; else D7 = 0;
    EN = 1;     
    NOP();
    EN = 0;     
    
    dato = (dato << 4);
    if (dato & (1<<4)) D4 = 1; else D4 = 0;
    if (dato & (1<<5)) D5 = 1; else D5 = 0;
    if (dato & (1<<6)) D6 = 1; else D6 = 0;
    if (dato & (1<<7)) D7 = 1; else D7 = 0;
    EN = 1;     
    NOP();
    EN = 0;     
    __delay_us(50);
}
/***********************************************
 ---------- Envía comandos por el LCD ----------
 ***********************************************/

void LCD_cmd(uint8_t dato) {
   
    //while(TestBusyLCD());
    RS = 0;
    LCD_write(dato);
}

/***********************************************
 ----------- Envía datos por el LCD ------------
 ***********************************************/

void putch(unsigned char dato){
    LCD_dato(dato);
}


void LCD_dato(uint8_t dato) {
    
    // while(TestBusyLCD());
     RS = 1;
     LCD_write(dato);
}


/***********************************************
 ----------- Imprime string por LCD ------------
 ***********************************************/

void LCD_printf(uint8_t *dato) {
    while (*dato){
        LCD_dato(*dato);    // Envio el dato al LCD
        dato++;             // Incrementa el buffer de dato
    }
}

/***********************************************
 ---------- Imprime un entero por LCD ----------
 ***********************************************/

void LCD_integer(int data){
    
   char st[8] = "";         //save enough space for result
   itoa(st,data,10);        //convert to ascii
   LCD_printf(st);          //display in on LCD   
}

/***********************************************
 ----- Mueve el cursor a una posición x y ------
 ***********************************************/

void LCD_goto(uint8_t x, uint8_t y){
    uint8_t posicion;
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
 --------- Activa o desactiva cursor ----------
 ***********************************************/

void LCD_cursor(unsigned char cursor){
    if(cursor) 
        LCD_cmd(0x0F);
    else 
        LCD_cmd(0x0C);
}

/***********************************************
 --------- Limpia toda la pantalla LCD ---------
 ***********************************************/

void  LCD_segunda_linea(){
    LCD_cmd(0xC0);
}

/***********************************************
 --------- Limpia toda la pantalla LCD ---------
 ***********************************************/

void LCD_clear(void) {
    LCD_cmd(0x01);
    __delay_ms(2);
}

/***********************************************
 ---------- Cursor Regresa al inicio ----------
 ***********************************************/

void LCD_home(void) {
    LCD_cmd(0x02);
   __delay_ms(2);
}

/***********************************************
 --------- Para personalizar caracter ----------
 ***********************************************/

void LCD_custom_char(unsigned char loc,unsigned char *msg){
    
    unsigned char i;
    if(loc<8){
        LCD_cmd(0x40+(loc*8));  /* Command 0x40 and onwards forces the device to point CGRAM address */
        for(i=0;i<8;i++)        /* Write 8 byte for generation of 1 character */
            LCD_dato(msg[i]);
    }   
}





