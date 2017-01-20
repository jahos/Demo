/*
 * SPI1class.h
 *
 *  Created on: 18.01.2017
 *      Author: cwiec
 */

#ifndef CORE_SPI1CLASS_H_
#define CORE_SPI1CLASS_H_

#include "Spi.h"

class SPI1_class : public Spi
{
private:
	SPI1_class();
		/*Instance to SPI object*/
	static SPI1_class * spiInstance;
public:
	static SPI1_class & getInstance();
	void send();
	~SPI1_class();
};

#endif /* CORE_SPI1CLASS_H_ */
