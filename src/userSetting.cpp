/*
 * userSetting.cpp
 *
 *  Created on: 27.12.2016
 *      Author: Jan Cwiecek
 */

#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "userSettings.h"

void init()
{
	initUsart();
}

void initUsart()
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO , ENABLE);
	GPIO_InitTypeDef usartPinTx;
	usartPinTx.GPIO_Pin = USART1_TX;
	usartPinTx.GPIO_Mode = GPIO_Mode_AF_PP;
	usartPinTx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&usartPinTx);

	GPIO_InitTypeDef usartPinRx;
	usartPinRx.GPIO_Pin = USART1_RX;
	usartPinRx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&usartPinRx);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef usartCtrPin;
	usartCtrPin.GPIO_Pin = GPIO_Pin_9;
	usartCtrPin.GPIO_Mode = GPIO_Mode_Out_PP;
	usartCtrPin.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&usartCtrPin);

	USART_InitTypeDef initStruct;
	initStruct.USART_BaudRate 				= 9600;
	initStruct.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	initStruct.USART_Mode 					= USART_Mode_Rx | USART_Mode_Tx;
	initStruct.USART_Parity 				= USART_Parity_No;
	initStruct.USART_StopBits 				= USART_StopBits_2;
	initStruct.USART_WordLength 			= USART_WordLength_8b;
	USART_Init(USART1,&initStruct);
	USART_Cmd(USART1, ENABLE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_EnableIRQ(USART1_IRQn);
}



