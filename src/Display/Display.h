/*
 * Display.h
 *
 *  Created on: 20.01.2017
 *      Author:
 */

#ifndef DISPLAY_DISPLAY_H_
#define DISPLAY_DISPLAY_H_

#include "Core/SPI1class.h"

class Display
{
private:
	SPI1_class * sp;
public:
	Display();
	virtual ~Display();
};

#endif /* DISPLAY_DISPLAY_H_ */
