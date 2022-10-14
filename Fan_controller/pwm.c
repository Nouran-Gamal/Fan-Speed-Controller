/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM driver
 *
 * Author: Nouran Gamal
 *
 *******************************************************************************/

#include "pwm.h"
#include "gpio.h"
#include <avr/io.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* Configure timer control register
		 * 1. Fast PWM mode FOC0=0
		 * 2. Fast PWM Mode WGM01=1 & WGM00=1
		 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
		 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
		 */
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);
	// Set Timer Initial Value to 0
	TCNT0 = 0;
	// Set Compare Value
	OCR0  = ((float)duty_cycle / 100) * 255; /* Set Compare value */
	// Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC
	GPIO_setupPinDirection(PWM_PORT_ID,PWM_PIN_ID,PIN_OUTPUT);
}
