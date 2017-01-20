/*
 * SPI1class.cpp
 *
 *  Created on: 18.01.2017
 *      Author: cwiec
 */

#include <Core/SPI1class.h>
#include "spiCommon.h"

SPI1_class* SPI1_class::spiInstance = 0;



static void  enableCS()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_4);
}

static int getByte()
{
	int retVal = BUFFER_EMPTY;
	SPI1_class & sp = SPI1_class::getInstance();
	retVal = sp.getMessage();
	return retVal;
}

static void storeByte(int byte)
{
	SPI1_class & sp = SPI1_class::getInstance();
	sp.storeData(byte);
}

SPI1_class& SPI1_class::getInstance()
{
	static SPI1_class sp;
	spiInstance = &sp;
	return sp;
}

SPI1_class::SPI1_class()
{
	ID = eSPI1;
	pin_CS = GPIO_Pin_4;
	pin_D_C = GPIO_Pin_6;

	setPointers(getByte,storeByte,enableCS);

}

SPI1_class::~SPI1_class()
{
	spiInstance = 0;
}

void SPI1_class::send()
{
	SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_TXE,ENABLE);
}


