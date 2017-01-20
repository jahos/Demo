/*
 * spiCommon.cpp
 *
 *  Created on: 20.01.2017
 *      Author:
 */

#include <Core/spiCommon.h>
#include <stdio.h>

static int (*pGetByte)() = 0;
static void (*pStoreByte)(int byte) = 0;
static void (*pEnableCS)() = 0;

bool setPointers(int (*a_pGetByte)()
			   ,void (*a_pStoreByte)(int byte)
			   ,void (*a_pEnableCS)())
{
	bool retVal = false;
	if((a_pGetByte != 0) && (a_pStoreByte != 0) && (a_pEnableCS != 0))
	{
		pGetByte = a_pGetByte;
		pStoreByte = a_pStoreByte;
		pEnableCS = a_pEnableCS;
		retVal = true;
	}
	return retVal;
}


extern "C"
{

void SPI1_IRQHandler()
{
	if((pEnableCS != 0) && (pGetByte != 0) && (pStoreByte != 0))
	{
		pEnableCS();

		if(SPI_I2S_GetITStatus(SPI1,SPI_I2S_IT_TXE) != RESET)
		{
			int c = pGetByte();
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
			pStoreByte(tmp);
		}
	}
	else
	{
		printf("NULL pointers SPI1_IRQHandler\n\r");
	}
}

}
