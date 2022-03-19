

#define BAUDRATE 100000UL
#define VALOR ((_XTAL_FREQ/(4UL*BAUDRATE))-1)


void I2C_init(){
    
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    
    SSPSTAT = 0b10000000;       //Velocidad standart, especificación I2C
	SSPCON =  0b00101000;       //I2C habilitado en modo maestro velocidad=Fosc/(4*SSPADD-1)
	SSPCON2 = 0x00;
	SSPADD = VALOR;
}

 void I2C_start(void){   
   
    SSPCON2bits.SEN = 1;           //inicia la comunicación i2c
    while(SSPCON2bits.SEN == 1);
}

void I2C_restart(void){    
   
    SSPCON2bits.RSEN = 1;          //reinicia la comunicación i2c
    while(SSPCON2bits.RSEN == 1); 
}

void I2C_stop(void){    
    
    SSPCON2bits.PEN = 1;           //detener la comunicación i2c
    while(SSPCON2bits.PEN == 1);
}

char I2C_read(void){
    
    PIR1bits.SSPIF = 0;         	//clear SSP interrupt bit
    SSPCON2bits.RCEN = 1;       	//set the receive enable bit to initiate a read of 8 bits from the serial eeprom
    while(PIR1bits.SSPIF == 0); 	//Espera que la transmisionse complete  
    return SSPBUF;                  //Retorna el dato leido
}

void I2C_ack(void)
{
    PIR1bits.SSPIF = 0;            //clear SSP interrupt bit
    SSPCON2bits.ACKDT = 0;         //clear the Acknowledge Data Bit - this means we are sending an Acknowledge or 'ACK'
    SSPCON2bits.ACKEN = 1;         //set the ACK enable bit to initiate transmission of the ACK bit to the serial eeprom
    while(PIR1bits.SSPIF == 0);    //Wait for interrupt flag to go high indicating transmission is complete
}

void I2C_nack(void)
{
    PIR1bits.SSPIF = 0;            //clear SSP interrupt bit
    SSPCON2bits.ACKDT = 1;         //set the Acknowledge Data Bit- this means we are sending a No-Ack or 'NAK'
    SSPCON2bits.ACKEN = 1;         //set the ACK enable bit to initiate transmission of the ACK bit to the serial eeprom
    while(PIR1bits.SSPIF == 0);    // Wait for interrupt flag to go high indicating transmission is complete
}

char  I2C_write(char I2C_data){    
    PIR1bits.SSPIF = 0;             
    SSPBUF = I2C_data;              //Envia data por I2C
    while(PIR1bits.SSPIF == 0);     //Wait for interrupt flag to go high indicating transmission is complete
    if(ACKSTAT)
        return 1;
    else
        return 2;
}