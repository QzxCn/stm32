#ifndef __BSP_KEYBOARD__
#define __BSP_KEYBOARD__
#include "stm32f10x.h"


//对于GPIO，初始化都是一个套路，哪怕现在是输入口


#define KEY1_GPIO_PIN    GPIO_Pin_0
/*
结构体指针，GPIO_Init()函数，修改的目标就是它，数据来自进步对象GPIO_Initstructure
并且这个局部对象的成员，他们的相对位置刚好对应内存中的位置
*/
#define KEY1_GPIO_PORT   GPIOA  
#define KEY1_GPIO_CLK    RCC_APB2Periph_GPIOA


#define KEY2_GPIO_PIN    GPIO_Pin_13
#define KEY2_GPIO_PORT   GPIOC
#define KEY2_GPIO_CLK    RCC_APB2Periph_GPIOC

#define KEY_ON     1
#define KEY_OFF    0

void KEY_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);  

#endif

