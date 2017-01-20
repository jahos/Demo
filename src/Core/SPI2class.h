/*
 * SPI2class.h
 *
 *  Created on: 19.01.2017
 *      Author: cwiec
 */

#ifndef CORE_SPI2CLASS_H_
#define CORE_SPI2CLASS_H_

#include "Spi.h"

class SPI2_class : public Spi
{
private:

		/*Instance to SPI object*/
	static SPI2_class * spiInstance;
	bool busy;
public:
	SPI2_class();
	static SPI2_class & getInstance();
	void printAll();
	void send();
	~SPI2_class();
};

#endif /* CORE_SPI2CLASS_H_ */
