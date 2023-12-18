#ifndef  __BSP_EXTI_H
#define __BSP_EXTI_H
#define SOFT_DELAYx      Delayx(0xFFFFFF);
//#define STM32F10X_LD
#include "stm32f10x.h"
//ºìÉ«
#define KEY1_INT_GPIO_PORT     GPIOA
#define KEY1_INT_GPIO_CLK     (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define KEY1_INT_GPIO_PIN      GPIO_Pin_0
#define KEY1_INT_EXTI_IRQ      EXTI0_IRQn
#define KEY1_IRQHandler        EXTI0_IRQHandler

#define KEY2_INT_GPIO_PIN      GPIO_Pin_13
#define KEY2_INT_GPIO_PORT     GPIOC
#define KEY2_INT_GPIO_CLK     (RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)
#define KEY2_INT_EXTI_IRQ      EXTI15_10_IRQn
#define KEY2_IRQHandler        EXTI15_10_IRQHandler

static void EXTI_NVIC_Config(void);
void EXIT_Key_Config(void);
void Delayx(__IO uint32_t nCount);


#endif


