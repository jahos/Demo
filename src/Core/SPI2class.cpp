/*
 * SPI2class.cpp
 *
 *  Created on: 19.01.2017
 *      Author: cwiec
 */

#include <Core/SPI2class.h>
#include "userSettings.h"
#include <stdio.h>
#include <queue>

SPI2_class* SPI2_class::spiInstance = 0;

static int (*ptrFunGet2)() = 0;
static void (*ptrFunStore2)(int byte) = 0;

static int getByte()
{
	int retVal = BUFFER_EMPTY;
	SPI2_class & sp = SPI2_class::getInstance();
	retVal = sp.getMessage();
	return retVal;
}

static void storeByte(int byte)
{
	SPI2_class & sp = SPI2_class::getInstance();
	sp.storeData(byte);
}

SPI2_class& SPI2_class::getInstance()
{
	static SPI2_class sp;
	spiInstance = &sp;
	return sp;
}

SPI2_class::SPI2_class()
{
	ID = eSPI2;
	pin_CS = SPI2_CS_PIN;
	pin_D_C = SPI1_D_C_PIN;

	ptrFunGet2 = getByte;
	ptrFunStore2 = storeByte;
}

SPI2_class::~SPI2_class()
{
	spiInstance = 0;
}

void SPI2_class::send()
{
	SPI_I2S_ITConfig(SPI2,SPI_I2S_IT_TXE,ENABLE);
}

void SPI2_class::printAll()
{
	printf("Posiada [%d]",outBuffer.size());
}

extern "C"
{

void SPI2_IRQHandler()
{
	GPIO_SetBits(GPIOB,SPI2_CS_PIN);

	if(SPI_I2S_GetITStatus(SPI2,SPI_I2S_IT_TXE) != RESET)
	{
		int c = ptrFunGet2();
		if(c <= 0xFF)
		{
			SPI_I2S_SendData(SPI2,(uint8_t)c);
		}
		else
		{
			 SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, DISABLE);
		}

	}

	if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) != RESET)
	{
		int tmp = SPI_I2S_ReceiveData(SPI2);
		ptrFunStore2(tmp);
	}
}

}

