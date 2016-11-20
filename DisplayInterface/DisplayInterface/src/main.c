/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>


#define BACK_LIGHT		IOPORT_CREATE_PIN(PORTB, 1)
#define TFT_DC			IOPORT_CREATE_PIN(PORTB, 0)
#define TFT_RST			IOPORT_CREATE_PIN(PORTD, 7)
#define TFT_CS			IOPORT_CREATE_PIN(PORTD, 6)
#define CARD_CS			IOPORT_CREATE_PIN(PORTD, 5)
#define SS_PIN			IOPORT_CREATE_PIN(PORTB, 2)



// From page 218 of data sheet
void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB3)|(1<<DDB5);//|(1<<DDB2); // modified to make SS output
	
	// To prevent it from getting pulled out of Master mode
	ioport_set_pin_mode(SS_PIN, IOPORT_MODE_PULLUP);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

// from page 218 of data sheet
void SPI_MasterTransmit(uint8_t cData)
{
	
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}


int main (void)
{
	
	bool button_state;
	/* Insert system clock initialization code here (sysclk_init()). */
	
	
	uint8_t transmitByte;
	uint8_t display[24576];
	
	board_init();
	ioport_init();

	SPI_MasterInit();
	
	ioport_set_pin_dir(BACK_LIGHT, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(TFT_DC, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(TFT_RST, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(TFT_CS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(CARD_CS, IOPORT_DIR_OUTPUT);
	
	//ioport_set_pin_mode(BACK_LIGHT, IOPORT_MODE_PULLDOWN);
	
	ioport_set_pin_level(TFT_DC, 0);
	ioport_set_pin_level(TFT_CS, 1);  // serial interface initializes when CS is high pg 33
	ioport_set_pin_level(CARD_CS, 1);  // Turn off card 

	ioport_set_pin_level(TFT_RST, 0);
	_delay_ms(5);
	ioport_set_pin_level(TFT_RST, 1);
	_delay_ms(5);

	ioport_set_pin_level(TFT_CS, 0); // active low
	ioport_set_pin_level(TFT_DC, 0); // active low

	transmitByte = 0x29; // Turn on command
	SPI_MasterTransmit(transmitByte);

	// failed attempt to read from display
	/*transmitByte = 0x04; 
	SPI_MasterTransmit(transmitByte);
	ioport_set_pin_level(TFT_DC, 1);
	uint8_t temp;
	for (int i = 0; i <=2; i++)
	{
		temp = SPDR;
	}
	*/


	transmitByte = 0x3a; // Color mode
	SPI_MasterTransmit(transmitByte);
	ioport_set_pin_level(TFT_DC, 1);
	transmitByte = 0x03;// 4-4-4 RGB
	SPI_MasterTransmit(transmitByte); // send byte
	
	// Here be were I program the LUT
	ioport_set_pin_level(TFT_DC, 0);
	transmitByte = 0x2d;  // write command
	SPI_MasterTransmit(transmitByte); // Sen byte
	ioport_set_pin_level(TFT_DC, 1);

	for(int i = 0; i <= 0x0f; i++) // Red part1
	{
		transmitByte = i;
		SPI_MasterTransmit(transmitByte);
	}
	for(int i = 17; i <= 32; i++) // red part2
	{
		transmitByte = 0;
		SPI_MasterTransmit(transmitByte);
	}
	for(int i = 0; i <= 0x0f; i++) // green part1
	{
		transmitByte = i;
		SPI_MasterTransmit(transmitByte);
	}
	for(int i = 49; i <= 96; i++) // green part 2
	{
		transmitByte = 0;
		SPI_MasterTransmit(transmitByte);
	}
	for(int i = 0; i <= 0x0f; i++) // Blue part1
	{
		transmitByte = i;
		SPI_MasterTransmit(transmitByte);
	}
	for(int i = 113; i <= 128; i++) // blue part 2
	{
		transmitByte = 0;
		SPI_MasterTransmit(transmitByte);
	}

	ioport_set_pin_level(TFT_DC, 0);
	transmitByte = 0x2c;  // write command
	SPI_MasterTransmit(transmitByte); // Sen byte
	ioport_set_pin_level(TFT_DC, 1);
	
	for (int i = 0; i <= 8192; i++) // once for every three bytes
	{
		transmitByte = 0xf0;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0x0f;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0x00;
		SPI_MasterTransmit(transmitByte);
		//display[i*3    ] = 0xf0;
		//display[i*3 + 1] = 0x0f;
		//display[i*3 + 2] = 0x00;	
	}
	ioport_set_pin_level(TFT_DC, 0);
	transmitByte = 0x13;
	SPI_MasterTransmit(transmitByte);
	ioport_set_pin_level(TFT_CS, 1);
	while(1){
		button_state = ioport_get_pin_level(GPIO_PUSH_BUTTON_0);
		if(button_state){
				//LED_Off(LED0);
			}else{
				//LED_On(LED0);
				// Turns on display (-:
				
				ioport_set_pin_mode(BACK_LIGHT, IOPORT_MODE_PULLUP);
			//ioport_set_pin_level(TFT_DC, 0);
			//transmitBit = 0x01;
			//SPI_MasterTransmit(transmitBit);
			}
			}
			return 0;
}
