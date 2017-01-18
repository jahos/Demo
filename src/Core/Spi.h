/*
 * Spi.h
 *
 *  Created on: 08.01.2017
 *      Author: cwiec
 */

#ifndef CORE_SPI_H_
#define CORE_SPI_H_

#include <queue>
#include <stdint.h>

#define BUFFER_EMPTY	256

enum CommandE
{
		COMMAND = 0
	,	DATA	= 1
};

struct CommandS
{
	int msg;
	CommandE d_c;
};

enum SpiE
{
		eSPI1 = 0
	,	eSPI2 = 1
	, 	eSPI3 = 2
};


class Spi {

private:

	/*queue for as outBuffer of command*/
	std::queue<CommandS> outBuffer;

	/*queue for as inBuffer of command*/
	std::queue<int> inBuffer;

	/**/
	uint16_t pin_CS;
	uint16_t pin_D_C;
	GPIO_TypeDef* portGPIOx;

public:

	SpiE ID;

	/*Sending data*/
	/**
	 * @brief  Add message to outBuffer
	 * @param1 Message which should be send
	 * @param2 Type of message
	 * @retval None
	 */
	void addToQ(int msg,CommandE d_c = COMMAND);

	/**
	 * @brief  Get message from outBuffer and send
	 * @retval None
	 */
	int getMessage();

	/*Receiving data*/

	/**
	 * @brief  copy received data to inBuffer
	 * @param  Instance of SPI object
	 * @retval None
	 */
	void storeData();

	/**
	 * @brief  Get data from inBUffer
	 * @retval byte
	 */
	int getData();

	/*destructor*/
	virtual ~Spi() {};
};

/**
 * @brief  GetMessageFrom Queue
 * @param  Message which should be send
 * @retval None
 */


#endif /* CORE_SPI_H_ */
