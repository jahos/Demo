/*
 * Spi.cpp
 *
 *  Created on: 08.01.2017
 *      Author: cwiec
 */

#include <Core/Spi.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include <stdio.h>

int (*wsk)(void) = 0;

Spi* Spi::spiInstance = 0;

int getMessage()
{
	Spi& spiInstance = Spi::getInstance();
	int retVal = BUFFER_EMPTY;

	if(!(spiInstance.buffer.empty()))
	{
		retVal =  spiInstance.buffer.front();
		spiInstance.buffer.pop();
	}
	return retVal;
}

/*---------------private methods-----------------------------------------------*/

Spi& Spi::getInstance()
{
	static Spi retInstance;
	spiInstance = &retInstance;
	return retInstance;
}

void Spi::addToQ(int msg)
{
	buffer.push(msg);
}

Spi::~Spi()
{
	spiInstance = 0;
}


/*---------------private methods-----------------------------------------------*/
Spi::Spi()
{
	wsk = &getMessage;
	initSpi();
}

void Spi::initSpi()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);


	GPIO_InitTypeDef spiGpio;
	spiGpio.GPIO_Mode =		GPIO_Mode_AF_PP;
	spiGpio.GPIO_Pin = 		MOSI_PIN | CLK_PIN | CS_PIN;
	spiGpio.GPIO_Speed = 	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&spiGpio);

	spiGpio.GPIO_Mode = 	GPIO_Mode_Out_PP;
	spiGpio.GPIO_Pin =		RES_PIN;
	spiGpio.GPIO_Speed = 	GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&spiGpio);

	spiGpio.GPIO_Mode = 	GPIO_Mode_Out_PP;
	spiGpio.GPIO_Pin =		D_C_PIN | CS_PIN ;
	spiGpio.GPIO_Speed = 	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&spiGpio);

	GPIO_SetBits(GPIOC, RES_PIN);
	GPIO_SetBits(GPIOA, D_C_PIN );

	SPI_InitTypeDef spiConfig;
	SPI_StructInit(&spiConfig);
	spiConfig.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	spiConfig.SPI_Mode = SPI_Mode_Master;
	spiConfig.SPI_NSS = SPI_NSS_Hard;
	spiConfig.SPI_DataSize = SPI_DataSize_8b;
	spiConfig.SPI_Direction = SPI_Direction_1Line_Tx;
	spiConfig.SPI_FirstBit = SPI_FirstBit_MSB;
	spiConfig.SPI_CPOL = SPI_CPOL_High;
	spiConfig.SPI_CPHA = SPI_CPHA_2Edge;
	spiConfig.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1,&spiConfig);
	SPI_SSOutputCmd(SPI1,ENABLE);
	SPI_Cmd(SPI1,ENABLE);


	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_EnableIRQ(SPI1_IRQn);
}

extern "C"
{

void SPI1_IRQHandler()
{
	if(SPI_I2S_GetITStatus(SPI1,SPI_I2S_IT_TXE) != RESET)
	{
		int c = wsk();
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
		   uint8_t tmp = SPI_I2S_ReceiveData(SPI1);
	   }

}

}

