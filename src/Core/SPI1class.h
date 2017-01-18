/*
 * SPI1class.h
 *
 *  Created on: 18.01.2017
 *      Author: cwiec
 */

#ifndef CORE_SPI1CLASS_H_
#define CORE_SPI1CLASS_H_

#include "Spi.h"

extern "C"
{
	int SPI1_IRQHandler();
	int SPI2_IRQHandler();
	int SPI3_IRQHandler();
}


class SPI1_class : public Spi
{
private:
	SPI1_class();
		/*Instance to SPI object*/
	static SPI1_class * spiInstance;
public:
	static CSpi1 & getInstance();
	void send();
	~SPI1_class();
};

#endif /* CORE_SPI1CLASS_H_ */
