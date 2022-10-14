/**********************************************************************************
 *
 * Module: Temp_sensor
 *
 * File name:temp_sensor.h
 *
 * Description: Header file for the Temp_sensor driver
 *
 * Author: Nouran Gamal
 *
 ***********************************************************************************/

#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void);

#endif /* TEMP_SENSOR_H_ */
