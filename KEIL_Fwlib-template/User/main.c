#include "stm32f10x.h"   //<>先去系统安装目录找，""先在当前工程文件目录下找，再去keil软件根目录下找
#include "bsp_led.h"
#include "bsp_keyboard.h"  
#include "bsp_bitband.h"
#include "bsp_clkconfig.h"
#include "funcs.h"
#include "bsp_exti.h"
//LED  GPIO输入例子
void ledk()
{
	//来到这里的时候，系统的时钟已经被配置成72M
	LED_GPIO_Config();
/*modified through git here */	
	while(1)
	{
//	   LED1_ON;
//		 SOFT_DELAY;
//		 LED1_OFF;
//		
//	 	 LED2_ON;
//		 SOFT_DELAY;
//		 LED2_OFF;
//		
//		 LED3_ON;
//		 SOFT_DELAY;
//		 LED3_OFF;
		
		 LED_RED;
		 SOFT_DELAY;
		 
		 LED_GREEN;
		 SOFT_DELAY;
		
		 LED_BLUE;
		 SOFT_DELAY;
		
		 LED_YELLOW;
		 SOFT_DELAY;
		 
		 LED_PURPLE;
		 SOFT_DELAY;
		 
		 LED_CYAN;
		 SOFT_DELAY;
		 
		 LED_WHITE;
		 SOFT_DELAY;
		 
		 LED_REGOFF;
		 SOFT_DELAY;
		
	}
	
	
	
}


//按键检测  GPIO输出例子
void key()
{
		LED_GPIO_Config();
	  KEY_GPIO_Config();
	  while(1)
		{
			if(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN)==KEY_ON)
			{
 
				 LED_RED;
		     SOFT_DELAY;
		 
		     LED_GREEN;
	  	   SOFT_DELAY;
		
	  	   LED_BLUE;
	  	   SOFT_DELAY;
		
		     LED_YELLOW;
		     SOFT_DELAY;
		 
	  	   LED_PURPLE;
	  	   SOFT_DELAY;
		 
		     LED_CYAN;
		     SOFT_DELAY;
		  
	  	   LED_WHITE;
		     SOFT_DELAY;
		 
	  	   LED_REGOFF;
		     SOFT_DELAY;
 
			 }
				

		  if(Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN)==KEY_ON)
			{   
				 LED_RED;
			   SOFT_DELAY;
				 LED_REGOFF;

			}
		}			
}
	







void bit_ctl()
{
  // 程序来到 main 函数之前，启动文件：statup_stm32f10x_hd.s 已经调用
  // SystemInit() 函数把系统时钟初始化成 72MHZ
  //SystemInit() 在 system_stm32f10x.c 中定义
  // 如果用户想修改系统时钟，可自行编写程序修改

  LED_GPIO_Config();

  while ( 1 ) {
  // PB0 = 0, 点亮 LED
 
  PBout(0)=0;
  SOFT_DELAY;

  //PB1 = 1, 熄灭 LED
  PBout(0)=1;
  SOFT_DELAY;
}
	
} 

void clkset()
{
	// 程序来到 main 函数之前，启动文件：statup_stm32f10x_hd.s 已经调用
  // SystemInit() 函数把系统时钟初始化成 72MHZ
  // SystemInit() 在 system_stm32f10x.c 中定义
  // 如果用户想修改系统时钟，可自行编写程序修改
 
  // 重新设置系统时钟，这时候可以选择使用 HSE 还是 HSI
 
  // 使用 HSE 时，SYSCLK = 8M * RCC_PLLMul_x, x:[2,3,...16], 最高是 128M
  HSE_SetSysClock(RCC_PLLMul_16);
 
 // 使用 HSI 时，SYSCLK = 4M * RCC_PLLMul_x, x:[2,3,...16], 最高是 64MH
	//HSI_SetSysClock(RCC_PLLMul_16);
 
 // MCO 引脚初始化
  MCO_GPIO_Config();
 
  // 设置 MCO 引脚输出时钟，用示波器即可在 PA8 测量到输出的时钟信号，
  // 我们可以把 PLLCLK/2 作为 MCO 引脚的时钟来检测系统时钟是否配置准确
  // MCO 引脚输出可以是 HSE,HSI,PLLCLK/2,SYSCLK
  //RCC_MCOConfig(RCC_MCO_HSE);
  //RCC_MCOConfig(RCC_MCO_HSI);
  //RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);
  RCC_MCOConfig(RCC_MCO_SYSCLK);
 
  // LED 端口初始化
  LED_GPIO_Config();
  while (1) 
	{
   LED1_ON ; // 亮
   Delay(0x0FFFFF);
   LED1_OFF ; // 灭
   Delay(0x0FFFFF);
  }
 }
 



 //中断
void kexti()
{
	LED_GPIO_Config();
	EXIT_Key_Config();
	while(1)
	{
		bit_ctl();
	}
	 
}
 
 int main()
{
	//key();
	//bit_ctl();
	kexti();
}

