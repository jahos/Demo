/**
  ******************************************************************************
  * @file    stm32f1xx_it.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-February-2014
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F1XX_IT_H
#define __STM32F1XX_IT_H





#define USART_BUFFER_SIZE	100
#define ENTER 				13


#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
 /* Local Var --------------------------------------------------------------- */
char outBuffer[USART_BUFFER_SIZE];
char* outPtrBegin = &outBuffer[0];
char* outPtrEnd = &outBuffer[0];
const char* outlast = &outBuffer[USART_BUFFER_SIZE-1];

char inBuffer[USART_BUFFER_SIZE];
char* inPtrBegin = &inBuffer[0];
char* inPtrEnd = &inBuffer[0];
const char* inlast = &inBuffer[USART_BUFFER_SIZE-1];

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void EXTI15_10_IRQHandler(void);
void USART1_IRQHandler();

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1XX_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
