/*
 * SPI1class.cpp
 *
 *  Created on: 18.01.2017
 *      Author: cwiec
 */

#include <Core/SPI1class.h>

SPI1_class* SPI1_class::spiInstance = 0;

static int (*ptrFunGet)() = 0;
static void (*ptrFunStore)(int byte) = 0;

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

	ptrFunGet = getByte;
	ptrFunStore = storeByte;
}

SPI1_class::~SPI1_class()
{
	spiInstance = 0;
}

void SPI1_class::send()
{
	SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_TXE,ENABLE);
}

extern "C"
{

void SPI1_IRQHandler()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_4);

	if(SPI_I2S_GetITStatus(SPI1,SPI_I2S_IT_TXE) != RESET)
	{
		int c = ptrFunGet();
		if(c <= 0xFF)
		{
			SPI_I2S_SendData(SPI1,(uint8_t)c);
		}
		else
		{
			 SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
		}

	}

	if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) != RESET)
	{
		int tmp = SPI_I2S_ReceiveData(SPI1);
		ptrFunStore(tmp);
	}
}

}
