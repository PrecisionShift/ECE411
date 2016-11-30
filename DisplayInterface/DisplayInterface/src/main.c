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
#define WIDTH			131
#define LENGTH			131
#define START_OFFSET	1
// From page 218 of data sheet

// function declarations
void SPI_MasterInit(void);
void SPI_MasterTransmit(uint8_t cData);
void tpFlag(void);
void smileFace(void);

int main (void)
{
	
	bool button_state;
	/* Insert system clock initialization code here (sysclk_init()). */
	
	
	uint8_t transmitByte;
	uint8_t display[24576];
	
	board_init();
	ioport_init();

	SPI_MasterInit();

	// Turns on back light :-)
	ioport_set_pin_mode(BACK_LIGHT, IOPORT_MODE_PULLUP);
	tpFlag();	
	
	while(1){
		button_state = ioport_get_pin_level(GPIO_PUSH_BUTTON_0);
		if(button_state){
				//LED_Off(LED0);
			}else{
				//LED_On(LED0);
				smileFace();
			}
		}
	return 0;
}

void tpFlag(void)
{
uint8_t transmitByte = 0;
ioport_set_pin_level(TFT_DC, 0);
transmitByte = 0x2c;  // write command
SPI_MasterTransmit(transmitByte); // Send byte
ioport_set_pin_level(TFT_DC, 1);



for (int j = 0; j < LENGTH; j++) // once for every three bytes
{
	for(int i = 0; i < WIDTH/10; i++)
	{
		transmitByte = 0xfc;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0x2f;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0xc2;
		SPI_MasterTransmit(transmitByte);
	}
	for(int i = 0; i < WIDTH/10; i++)
	{
		transmitByte = 0xba;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0xfb;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0xaf;
		SPI_MasterTransmit(transmitByte);
	}
	for(int i = 0; i < (WIDTH/10 + 1 ); i++)
	{
		transmitByte = 0xff;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0xff;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0xff;
		SPI_MasterTransmit(transmitByte);
	}
	for(int i = 0; i < WIDTH/10; i++)
	{
		transmitByte = 0xba;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0xfb;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0xaf;
		SPI_MasterTransmit(transmitByte);
	}
	for(int i = 0; i < WIDTH/10; i++)
	{
		transmitByte = 0xfc;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0x2f;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0xc2;
		SPI_MasterTransmit(transmitByte);
	}
	
}

}

void smileFace(void)
{
	uint8_t transmitByte = 0;
	ioport_set_pin_level(TFT_DC, 0);
	transmitByte = 0x2c;  // write command
	SPI_MasterTransmit(transmitByte); // Send byte
	ioport_set_pin_level(TFT_DC, 1);



	for (int x = 0; x < LENGTH; x++) // once for every three bytes
	{
		transmitByte = 0x0f;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0xf0;
		SPI_MasterTransmit(transmitByte);
		transmitByte = 0xff;
		SPI_MasterTransmit(transmitByte);

		for(int y = 0; y < WIDTH/2; y++)// each cycle puts out two pixels thus the "/2"
		{
			

			if ( ((30 < x && x < 42) || (90 < x && x < 102)) && (4 < y && y < 14))
			{
				transmitByte = 0x33;
				SPI_MasterTransmit(transmitByte);
				transmitByte = 0xf3;
				SPI_MasterTransmit(transmitByte);
				transmitByte = 0x3f;
				SPI_MasterTransmit(transmitByte);
			}
			else if ( ((60 < x && x < 72)) && (16 < y && y < 24))
			{
				transmitByte = 0x33;
				SPI_MasterTransmit(transmitByte);
				transmitByte = 0xf3;
				SPI_MasterTransmit(transmitByte);
				transmitByte = 0x3f;
				SPI_MasterTransmit(transmitByte);
			}
			else if ( ((24 < x && x < 36) || (95 < x && x < 105)) && (26 < y && y <= 28))
			{
				transmitByte = 0x33;
				SPI_MasterTransmit(transmitByte);
				transmitByte = 0xf3;
				SPI_MasterTransmit(transmitByte);
				transmitByte = 0x3f;
				SPI_MasterTransmit(transmitByte);
			}
			else if ( (24 < x && x < 105) && (28 < y && y < 36))
			{
				transmitByte = 0x33;
				SPI_MasterTransmit(transmitByte);
				transmitByte = 0xf3;
				SPI_MasterTransmit(transmitByte);
				transmitByte = 0x3f;
				SPI_MasterTransmit(transmitByte);
			}
			else
			{
				transmitByte = 0x0f;
				SPI_MasterTransmit(transmitByte);
				transmitByte = 0xf0;
				SPI_MasterTransmit(transmitByte);
				transmitByte = 0xff;
				SPI_MasterTransmit(transmitByte);
			}		
		}
	}
}

// initializes the spi and sets up display
void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB3)|(1<<DDB5);//|(1<<DDB2); // modified to make SS output
	
	// To prevent it from getting pulled out of Master mode
	ioport_set_pin_mode(SS_PIN, IOPORT_MODE_PULLUP);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

	PRR = 0x00;

	uint8_t transmitByte = 0 ;

	ioport_set_pin_dir(BACK_LIGHT, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(TFT_DC, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(TFT_RST, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(TFT_CS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(CARD_CS, IOPORT_DIR_OUTPUT);
	
	
	
	ioport_set_pin_level(TFT_DC, 0);
	ioport_set_pin_level(TFT_CS, 0);  // serial interface initializes when CS is high pg 33
	ioport_set_pin_level(CARD_CS, 1);  // Turn off card 

	ioport_set_pin_level(TFT_RST, 1);
	_delay_ms(500);
	ioport_set_pin_level(TFT_RST, 0);
	_delay_ms(500);
	ioport_set_pin_level(TFT_RST, 1);
	_delay_ms(500);
	ioport_set_pin_level(TFT_CS, 1); // active low
	_delay_ms(500);
	ioport_set_pin_level(TFT_CS, 0); // active low
	ioport_set_pin_level(TFT_DC, 0); // active low
	
	transmitByte = 0x29; // Turn on command
	SPI_MasterTransmit(transmitByte);
	_delay_ms(500);
	transmitByte = 0x11; // Turn off sleep
	SPI_MasterTransmit(transmitByte);
	_delay_ms(500);

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
	//ioport_set_pin_mode(TFT_CS, IOPORT_MODE_PULLDOWN);
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

	_delay_ms(500);
	
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