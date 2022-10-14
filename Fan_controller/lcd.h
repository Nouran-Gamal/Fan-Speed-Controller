/**********************************************************************************
 *
 * Module: LCD
 *
 * File name:lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Nouran Gamal
 *
 ***********************************************************************************/


#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/**********************************************************************************
 *                                   Definitions
 ***********************************************************************************/

#define LCD_DATA_BITS_MODE                  8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

#if (LCD_DATA_BITS_MODE == 4)
/*
 * If LCD is connected to last pins in port:
 * Define LCD_LAST_PORT_PINS
 */
#ifdef LCD_LAST_PORT_PINS
#define LCD_FIRST_DATA_PIN_ID               PIN4_ID
#define LCD_DATA_PORT_ID_4_BIT_MODE         (PORTC_ID & 0xF0)
#else
#define LCD_FIRST_DATA_PIN_ID               PIN0_ID
#define LCD_DATA_PORT_ID_4_BIT_MODE         (PORTC_ID & 0x0F)
#endif

#endif

#define NULL                               '\0'

/*LCD PORTS and PINS IDs*/
#define LCD_RS_PORT_ID                      PORTD_ID
#define LCD_RS_PIN_ID                       PIN0_ID

#define LCD_RW_PORT_ID                      PORTD_ID
#define LCD_RW_PIN_ID                       PIN1_ID

#define LCD_E_PORT_ID                       PORTD_ID
#define LCD_E_PIN_ID                        PIN2_ID

#define LCD_DATA_PORT_ID                    PORTC_ID


/*LCD Commands*/
#define LCD_CLEAR_SCREEN                    0x01
#define LCD_RETURN_HOME                     0x02
#define LCD_SHIFT_DISPLAY_RIGHT             0x05
#define LCD_SHIFT_DISPLAY_LEFT              0x07
#define LCD_CURSOR_OFF                      0x0C
#define LCD_CURSOR_ON                       0x0E
#define LCD_TWO_LINES_EIGHT_BITS_MODE       0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE        0x28
#define LCD_SET_CURSOR_LOCATION             0x80

/**********************************************************************************
 *                                Types Declarations
 ***********************************************************************************/

/**********************************************************************************
 *                               Functions prototypes
 ***********************************************************************************/

/*
 * Description:
 * Initialize LCD:
 * 1- Setup LCD pins directions and PORT by the GPIO driver
 * 2- Setup the LCD Data Mode (4 or 8 bits)
 */
void LCD_init(void);

/*
 * Description:
 * Function to send the required command to the LCD
 */
void LCD_sendCommand (uint8 command);

void LCD_displayCharacter(uint8 command);

void LCD_displayString(uint8* string);

void LCD_moveCursor (uint8 row,uint8 col);

void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8 *string);

void LCD_clearScreen();

void LCD_integerToString(int);


#endif /* LCD_H_ */
