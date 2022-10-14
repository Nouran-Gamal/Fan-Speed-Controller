/**********************************************************************************
 *
 * Module: Motor
 *
 * File name:motor.h
 *
 * Description: Header file for the Motor driver
 *
 * Author: Nouran Gamal
 *
 ***********************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

typedef enum DcMotor_State
{
	stop,CW,A_CW
}DcMotor_State;

#define MOTOR_PORT_ID PORTB_ID
#define IN1_ID PIN0_ID
#define IN2_ID PIN1_ID
#define EN_ID PIN4_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the Dc motor driver.
 */
void DcMotor_Init(void);


/*
 * Description :
 * Function responsible for rotation of motor
 */

void DcMotor_Rotate(DcMotor_State , uint8);




#endif /* MOTOR_H_ */
