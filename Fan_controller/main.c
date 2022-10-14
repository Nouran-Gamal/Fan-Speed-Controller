/*
 ======================================================================================
 Name        : main.c
 Author      : Nouran Gamal
 Description : Fan controller system
 ======================================================================================
 */

#include "adc.h"
#include "lcd.h"
#include "temp_sensor.h"
#include "motor.h"

int main(void)
{
	uint8 temp;
	ADC_ConfigType setup = {INTERNAL,FCPU8};
	LCD_init(); /* initialize LCD driver */
	ADC_init(&setup); /* initialize ADC driver */
	DcMotor_Init();

	/* Display this string "Temp =   C" only once on LCD at the first row */
	LCD_moveCursor(1,3);
	LCD_displayString("Temp =    C");
	LCD_moveCursor(0,3);
	LCD_displayString("Fan is ");


	while(1)
	{
		temp = LM35_getTemperature();

		/* Display the temperature value every time at same position */
		if(temp < 30 && temp>0)
		{
			LCD_moveCursor(1,10);
			LCD_intgerToString(temp);
			DcMotor_Rotate(stop,0);
			LCD_displayCharacter(' ');
			LCD_moveCursor(0,10);
			LCD_displayString("OFF");
		}
		else if(temp >= 30 && temp<60)
		{
			LCD_moveCursor(1,10);
			LCD_intgerToString(temp);
			DcMotor_Rotate(CW,25);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
			LCD_moveCursor(0,10);
			LCD_displayString("ON");
		}
		else if(temp >= 60 && temp<90)
		{
			LCD_moveCursor(1,10);
			LCD_intgerToString(temp);
			DcMotor_Rotate(CW,50);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
			LCD_moveCursor(0,10);
			LCD_displayString("ON");
		}
		else if(temp >= 90 && temp<100)
		{
			LCD_moveCursor(1,10);
			LCD_intgerToString(temp);
			DcMotor_Rotate(CW,75);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
			LCD_moveCursor(0,10);
			LCD_displayString("ON");
		}
		else if(temp>100 && temp<120)
		{
			LCD_moveCursor(1,10);
			LCD_intgerToString(temp);
			DcMotor_Rotate(CW,75);
			LCD_moveCursor(0,10);
			LCD_displayString("ON");
		}
		else if(temp >= 120 && temp<150)
		{
			LCD_moveCursor(1,10);
			LCD_intgerToString(temp);
			DcMotor_Rotate(CW,100);
			LCD_moveCursor(0,10);
			LCD_displayString("ON");
		}

	}

}
