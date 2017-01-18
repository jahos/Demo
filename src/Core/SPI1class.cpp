/*
 * SPI1class.cpp
 *
 *  Created on: 18.01.2017
 *      Author: cwiec
 */

#include <Core/SPI1class.h>

SPI1_class::SPI1_class() {
	// TODO Auto-generated constructor stub

}

SPI1_class::~SPI1_class() {
	// TODO Auto-generated destructor stub
}

extern "C"
{

void SPI1_IRQHandler()
{
	if(SPI_I2S_GetITStatus(SPI1,SPI_I2S_IT_TXE) != RESET)
	{
//		int c = wsk();
//		if(c <= 0xFF)
//		{
//			SPI_I2S_SendData(SPI1,(uint8_t)c);
//		}
//		else
//		{
//			 SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
//		}
	}

	   if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) != RESET)
	   {
//		   uint8_t tmp = SPI_I2S_ReceiveData(SPI1);
//		   printf("%c",tmp);
	   }

}

}
