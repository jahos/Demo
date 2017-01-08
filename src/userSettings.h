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

void init();
void initUsart();
void initSPI();

#endif /* USERSETTINGS_H_ */
