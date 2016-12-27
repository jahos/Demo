/*
 * USART.h
 *
 *  Created on: 27.12.2016
 *      Author: cwiec
 */

#ifndef CORE_USART_USART_H_
#define CORE_USART_USART_H_
#include "stdint.h"

#define USART1_TX 	GPIO_Pin_9
#define USART1_RX 	GPIO_Pin_10
#define USART_BUFFER_SIZE	20

class USART {
	char m_RxBuffer[USART_BUFFER_SIZE];
	char * m_beginOfBuffer;
	char * m_endOfBuffer;
	char * m_ptrToBuffer;
public:
	USART();
	~USART();
};

#endif /* CORE_USART_USART_H_ */
