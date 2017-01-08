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

/*Pins Config SPI1
 * CLK 	PA5
 * MOSI	PA7
 * CS	PA4
 *
 * D_C	PA6
 * RES	PC4
 * */

#define CLK_PIN		GPIO_Pin_5
#define CS_PIN  	GPIO_Pin_4
#define MOSI_PIN	GPIO_Pin_7
#define D_C_PIN 	GPIO_Pin_6
#define RES_PIN 	GPIO_Pin_4

#define BUFFER_EMPTY	256



int getMessage();

class Spi {

private:
	/**
	 * @brief  Private Construction -only one instance will be requre
	 * @param  None
	 * @retval None
	 */
	Spi();
	Spi(const Spi&);

	/**
	 * @brief  Set up SPI1 and NVIC interrup for SPI
	 * @note   This function should be used only after reset.
	 * @param  None
	 * @retval None
	 */
	void initSpi();

	/*queue for as buffer of command*/
	std::queue<int> buffer;

	/*Instance to SPI object*/
	static Spi* spiInstance;

public:
	/**
	 * @brief  Get message from Queue
	 * @param  Instance of SPI object
	 * @retval None
	 */
	friend int getMessage();

	/**
	 * @brief  Get SPI instance
	 * @param  none
	 * @retval Instance to SPI object
	 */
	static Spi& getInstance();
	/**
	 * @brief  Add message to Queue
	 * @param  Message which should be send
	 * @retval None
	 */
	void addToQ(int msg);

	/*destructor*/
	~Spi();
};

/**
 * @brief  GetMessageFrom Queue
 * @param  Message which should be send
 * @retval None
 */


#endif /* CORE_SPI_H_ */
