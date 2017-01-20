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

void Spi::addToQ(int msg,CommandE d_c)
{
	CommandS command;
	command.msg = msg;
	command.d_c = d_c;
	outBuffer.push(command);
	//koment test
}

int Spi::getMessage()
{
	int msg = BUFFER_EMPTY;

	if(!(outBuffer.empty()))
	{
		CommandS command = outBuffer.front();
		msg = command.msg;

		//update D/C# line
		GPIO_WriteBit(GPIOA,pin_D_C, (BitAction)command.d_c);

		GPIO_ResetBits(GPIOB,pin_CS);

		//remove job from queue
		outBuffer.pop();
	}
	return msg;
}

void Spi::storeData(int byte)
{
	inBuffer.push(byte);
}

int Spi::getData()
{
	int retVal = BUFFER_EMPTY;
	if(inBuffer.size() != 0)
	{
		retVal = inBuffer.front();
		inBuffer.pop();
	}
	return retVal;
}


/*---------------private methods-----------------------------------------------*/



