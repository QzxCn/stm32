//bsp:board support package 板级支持包
#include "bsp_led.h"   // 自己新建的头文件，必须用魔术棒c/c++指定头文件路径


void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//
	//开启led相关gpio外设时钟
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK|LED2_GPIO_CLK|LED3_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//速度50Mhz
	
	GPIO_InitStructure.GPIO_Pin=LED1_GPIO_PIN;//选择要控制的GPIO引脚，就是odr偏移地址
	GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStructure);   // 第一个参数为基址，就是GPIOB，第二个参数包含偏移地址

	GPIO_InitStructure.GPIO_Pin=LED2_GPIO_PIN;//选择要控制的GPIO引脚，
  GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStructure);   
	
	GPIO_InitStructure.GPIO_Pin=LED3_GPIO_PIN; 
	GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStructure);   
	
	
	GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);
	GPIO_SetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);
	GPIO_SetBits(LED3_GPIO_PORT,LED3_GPIO_PIN);
}

 
