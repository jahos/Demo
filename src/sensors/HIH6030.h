/*
 * HIH6030.h
 *
 *  Created on: 20.01.2017
 *      Author:
 */

#ifndef SENSORS_HIH6030_H_
#define SENSORS_HIH6030_H_

#include "Core/SPI2class.h"

class HIH6030
{
private:
	int temperature;
	int humidity;
	uint16_t pinCS;
	SPI2_class sp;
public:
	void measureRequest();
	int getTemperature();
	int getHumidity();
	HIH6030();
	virtual ~HIH6030();
};

#endif /* SENSORS_HIH6030_H_ */
