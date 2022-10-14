/**********************************************************************************
 *
 * Module: LCD
 *
 * File name:lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Nouran Gamal
 *
 ***********************************************************************************/

#include "lcd.h"  /*header file for the LCD driver*/
#include "common_macros.h"  /*including macros like SET_BIT*/
#include "gpio.h"
#include <util/delay.h>

/**********************************************************************************
 *                                  Functions Definitions
 ***********************************************************************************/

/*
 * Description:
 * Initialize LCD:
 * 1- Setup LCD pins directions and PORT by the GPIO driver   (this is done as init step as it,s done only once)
 * 2- Setup the LCD Data Mode (4 or 8 bits)
 */
void LCD_init(void)   /*called once in main before while(1)*/
{
	/*configure the (RS, RW, E) pins as output pins*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID,LCD_RW_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);

#if (LCD_DATA_BITS_MODE == 8)

	/*Configure the data port as output port*/
	GPIO_setupPortDirection(LCD_DATA_PORT_ID , PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE); /* use 2-line lcd 8-bit data Mode */

#elif (LCD_DATA_BITS_MODE == 4)

	/* Configure the data First or Last port pins as output port
	 * Depending on LCD_LAST_PORT_PINS defined or not           */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+1,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+2,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+3,PIN_OUTPUT);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE); /* use 2-line lcd 4-bit data Mode */

#endif


	LCD_sendCommand (LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand (LCD_CLEAR_SCREEN); /* clear LCD at the beginning */

}


/* Description:
 * Send the required command to the LCD screen
 */
void LCD_sendCommand (uint8 command)
{

	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); /* Instruction Mode RS=0 */
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW); /* write data to LCD so RW=0 */
	_delay_ms(1);
	/*delays using ms instead of us as the LCD hardware may not support us*/

	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /*Enable LCD (E=1)*/
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,command);
	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /*Disable LCD (E=1)*/
	_delay_ms(1);

#elif (LCD_DATA_BITS_MODE == 4)
	/*get the port value and save it to var lcd_port_value to mask it with the command*/
	lcd_port_value = GPIO_readPort (LCD_DATA_PORT_ID);
	/*Send the last 4 bits of the cpmmand to LCD*/
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = ( (lcd_port_value & 0x0F) | (command & 0xF0) );
#else
	lcd_port_value = ( (lcd_port_value & 0xF0) | ( (command & 0xF0) >>4) );
#endif
	GPIO_writePort (LCD_DATA_PORT_ID,lcd_port_value);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/*Send the last 4 bits of the cpmmand to LCD*/
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((command & 0x0F) << 4);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | (command & 0x0F);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#endif
}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data)
{

		GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH); /* Data Mode RS=1 */
		GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW); /* write data to LCD so RW=0 */
		_delay_ms(1);
		/*delays using ms instead of us as the LCD hardware may not support us*/

		GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /*Enable LCD (E=1)*/
		_delay_ms(1);

	#if (LCD_DATA_BITS_MODE == 8)
		GPIO_writePort(LCD_DATA_PORT_ID,data);
		_delay_ms(1);

		GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /*Disable LCD (E=1)*/
		_delay_ms(1);

	#elif (LCD_DATA_BITS_MODE == 4)
		/*get the port value and save it to var lcd_port_value to mask it with the command*/
		lcd_port_value = GPIO_readPort (LCD_DATA_PORT_ID);
		/*Send the last 4 bits of the cpmmand to LCD*/
	#ifdef LCD_LAST_PORT_PINS
		lcd_port_value = ( (lcd_port_value & 0x0F) | (data & 0xF0) );
	#else
		lcd_port_value = ( (lcd_port_value & 0xF0) | ( (data & 0xF0) >>4) );
	#endif
		GPIO_writePort (LCD_DATA_PORT_ID,lcd_port_value);

		_delay_ms(1); /* delay for processing Tdsw = 100ns */
		GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
		_delay_ms(1); /* delay for processing Th = 13ns */
		GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
		_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

		/*Send the last 4 bits of the cpmmand to LCD*/
	#ifdef LCD_LAST_PORT_PINS
		lcd_port_value = (lcd_port_value & 0x0F) | ((data & 0x0F) << 4);
	#else
		lcd_port_value = (lcd_port_value & 0xF0) | (data & 0x0F);
	#endif
		GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

		_delay_ms(1); /* delay for processing Tdsw = 100ns */
		GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
		_delay_ms(1); /* delay for processing Th = 13ns */

	#endif
	}

/*
 * Description:
 * Display the sent string
 */
void LCD_displayString( uint8* string)
{
	uint8 i=0;
	while (*string != NULL)
	{
		LCD_displayCharacter( string[i] );
		(string)++;
	}
}

/*
 * Description:
 * Move the cursor to any row and column on the screen
 */
void LCD_moveCursor (uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

		/* Calculate the required address in the LCD DDRAM */
		switch(row)
		{
			case 0:
				lcd_memory_address=col;
					break;
			case 1:
				lcd_memory_address=col+0x40;
					break;
			case 2:
				lcd_memory_address=col+0x10;
					break;
			case 3:
				lcd_memory_address=col+0x50;
					break;
		}
		/* Move the LCD cursor to this specific address */
			LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);

}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8 *string)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(string); /* display the string */
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data, buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_SCREEN); /* Send clear display command */
}


