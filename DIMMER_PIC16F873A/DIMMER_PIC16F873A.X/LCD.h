
/**********************************************
 * Libreria:    LCD.h
 * Author:      Carlos QL
 * Contacto:    carlos.quispe.359@gmail.com
 * Descripcion  Para el manejo de LCD para PIC16 y PIC18
 * Todos los pines son remapeables      
 * 4 Bits de datos
 * 2 Bits de control, sin R/W
 **********************************************/


/********** Declaración de Pines de Datos y Control **************/

#define RS          PORTAbits.RA2          //Pin 4 LCD
#define EN          PORTAbits.RA3          //Pin 6 LCD

#define D4          PORTCbits.RC0          //Pin 11 lcd         
#define D5          PORTCbits.RC1          //Pin 12 lcd            
#define D6          PORTCbits.RC2          //Pin 13 lcd               
#define D7          PORTCbits.RC3          //Pin 14 lcd

/********* DeclaraciÃ³n de Pines de entrada y salida ***********/

#define TRIS_RS          TRISAbits.TRISA2          //Pin 4 LCD
#define TRIS_EN          TRISAbits.TRISA3          //Pin 6 LCD

#define TRIS_D4          TRISCbits.TRISC0          //Pin 11 lcd         
#define TRIS_D5          TRISCbits.TRISC1          //Pin 12 lcd            
#define TRIS_D6          TRISCbits.TRISC2          //Pin 13 lcd               
#define TRIS_D7          TRISCbits.TRISC3          //Pin 14 lcd

/********** Definiciones de Comandos de LCD *********/

#define     LCD_CLEAR	    0x01    //Limpia pantalla
#define     LCD_HOME	    0x02    //Retorno al inicio
#define     LCD_CURSOR_ON	0x0F    //Cursor on
#define     LCD_CURSOR_OFF	0x0C    //Cursor off
#define     LCD_LINEA1	    0x00	//Promera Fila
#define     LCD_LINEA2		0XC0	//Segunda Fila
#define     LCD_LINEA3		0x94	//Tercera Fila
#define     LCD_LINEA4		0xD4	//Cuarta Fila
#define     LCD_LEFT		0x10	//Cursor a la izquierda
#define     LCD_RIGHT		0x14	//Cursor a la derecha
#define     LCD_ROT_LEFT	0x18	//Rotar a la izquierda
#define     LCD_ROT_RIGHT	0x1C	//Rotar a la derecha	
#define     LCD_OFF 		0x08	//apaga el display

/************** Declaración de funcione *****************/

void LCD_init(void);                    //Inicializa LCD
void LCD_write_nible(unsigned char);    //Envia nible a LCD   
void LCD_cmd(unsigned char comando);    //Envia comando a LCD
void LCD_char(char caracter);           //Envia caracteer a LCD
void LCD_write_text(char *dato);
void LCD_gotoxy(char x, char y);        //Posiciona cursor
void LCD_custom_char(unsigned char loc, unsigned char *msg);

/*********************************************************
---------------- Inicializacion de LCD -------------------
**********************************************************/

void LCD_init(void)
{
    EN = 0;                     //Limpiamos pines de Control
    RS = 0;     
    D4 = 0;                     //Limpiamos pines de Datos
    D5 = 0;
    D6 = 0;
    D7 = 0;

    TRIS_EN = 0;                //Pines de control como salida
    TRIS_RS = 0;    
    TRIS_D4 = 0;                //Pines de datos como salida
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;

    __delay_ms(20);             //Espera que se estabilicen puertos

    LCD_write_nible(0x03);      //por fabricante
    __delay_ms(5);
    LCD_write_nible(0x03);      //por fabricante
    __delay_us(100);
    LCD_write_nible(0x03);      //por fabricante
    __delay_us(100);
    LCD_write_nible(0x02);      //Initial function set to change interface,   
    __delay_us(100);            //Configurar modo 4 bits

    LCD_cmd(0x28);				//LCD con fuente de 5*7
    LCD_cmd(LCD_CURSOR_OFF);    //Cursor apagado
    LCD_cmd(LCD_CLEAR);
    LCD_cmd(0x06);              //Modo incremental, sin desplazamiento
    LCD_cmd(0x80);              //Address DDRam superior izquierda
}

/****************************************************
 ---------- Envia Nible al puerto de datos ----------
 ****************************************************/

void LCD_write_nible(unsigned char nible)
{  
    if (nible & (1<<0)) D4 = 1; else D4 = 0;             
    if (nible & (1<<1)) D5 = 1; else D5 = 0;
    if (nible & (1<<2)) D6 = 1; else D6 = 0;
    if (nible & (1<<3)) D7 = 1; else D7 = 0;
    EN = 1;     
    NOP(); NOP();	    //Enable pulse width PWeh min 230ns
    EN = 0; 
}

/****************************************************
 ---------- Envia comando al LCD ----------
 ****************************************************/

void LCD_cmd(unsigned char comando)
{   
    RS = 0; 
    LCD_write_nible(comando >> 4);
    LCD_write_nible(comando & 0x0F);
    if(comando == LCD_CLEAR || comando == LCD_HOME)
        __delay_ms(2);              //Tiempo mínimo 1.6ms    
    else
        __delay_us(55);             //Tiempo 55us en real	
}

/**************************************************
 -------------- Envia caracter al LCD -------------
 **************************************************/

void LCD_char(char caracter)
{   
    RS = 1; 
    LCD_write_nible(caracter >> 4);
    LCD_write_nible(caracter & 0x0F);
	__delay_us(55);                 //Tiempo 55us en real	
}

/*************************************************
 ------ Envía cadena de caracteres al LCD --------
 ************************************************/

void LCD_write_text(char *dato)
{
    while (*dato){
        LCD_char(*dato);    // Envio el dato al LCD
        dato++;             // Incrementa el buffer de dato
    }
}

/*********************************************
 -------- Cursior a una posición x y ---------
 ********************************************/

void LCD_gotoxy(char x, char y)
{
    char posicion;
    switch (y)
    {
        case 1: posicion = 0x00 + x - 1; break;
        case 2: posicion = 0x40 + x - 1; break;
        case 3: posicion = 0x14 + x - 1; break;
        case 4: posicion = 0x54 + x - 1; break;
        default: posicion = 0x00 + x - 1; break;
    }
    LCD_cmd(0x80 | posicion);
}

/***********************************************
 --------- Para personalizar caracter ----------
 ***********************************************/

void LCD_custom_char(unsigned char loc,unsigned char *msg)
{
    unsigned char i;
    if(loc<8){
        LCD_cmd(0x40+(loc*8));  /* Command 0x40 and onwards forces the device to point CGRAM address */
        for(i=0;i<8;i++)        /* Write 8 byte for generation of 1 character */
            LCD_char(msg[i]);
    }   
}
