/*
 * userSettings.h
 *
 *  Created on: 27.12.2016
 *      Author: cwiec
 */

#ifndef USERSETTINGS_H_
#define USERSETTINGS_H_

#define USART1_TX 	GPIO_Pin_9
#define USART1_RX 	GPIO_Pin_10


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

void init();
void initUsart();
void initSPI();

#endif /* USERSETTINGS_H_ */
