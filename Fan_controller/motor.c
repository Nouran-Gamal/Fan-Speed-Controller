/**********************************************************************************
 *
 * Module: DC motor
 *
 * File name:motor.c
 *
 * Description: Source file for the Motor driver
 *
 * Author: Nouran Gamal
 *
 ***********************************************************************************/
#include "common_macros.h"
#include "motor.h"
#include "gpio.h"
#include "std_types.h"
#include "PWM.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(MOTOR_PORT_ID,IN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID,IN2_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID,EN_ID,PIN_OUTPUT);
	GPIO_writePin(MOTOR_PORT_ID,EN_ID,LOGIC_LOW);

}


void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	if(state == stop)
	{
		GPIO_writePin(MOTOR_PORT_ID,IN1_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID,IN2_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID,EN_ID,LOGIC_LOW);
		PWM_Timer0_Start(speed);
	}
	else if(state == CW)
	{
		GPIO_writePin(MOTOR_PORT_ID,IN1_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID,IN2_ID,LOGIC_HIGH);
		PWM_Timer0_Start(speed);

	}
	else if(state == A_CW)
	{
		GPIO_writePin(MOTOR_PORT_ID,IN1_ID,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID,IN2_ID,LOGIC_LOW);
		PWM_Timer0_Start(speed);
	}


}
