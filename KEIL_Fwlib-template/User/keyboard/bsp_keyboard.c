#include "bsp_keyboard.h"

void KEY_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	
  GPIO_InitStruct.GPIO_Pin=KEY1_GPIO_PIN;
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin=KEY2_GPIO_PIN; 
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStruct);
	
	
	
}

/*
  一个按键对应一个pin，
*/
uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)     
{
	//第一次按下，程序执行，机械震动部分的输入用while消耗掉
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)  
	{
		//松手检测
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON);
		return KEY_ON;
		
	}
	else return KEY_OFF;
}
