#include "bsp_clkconfig.h"

void HSE_SetSysClock(uint32_t pllmul)
{
	__IO uint32_t StartUpCounter=0,HSEStartUpStatus=0;
	
	//把rcc外设初始化为复位状态
	RCC_DeInit();
	
	//使能HSE，开启外部晶振，野火。。用8M
	RCC_HSEConfig(RCC_HSE_ON);
	
	//等待HSE启动稳定
	HSEStartUpStatus=RCC_WaitForHSEStartUp();
	
	//等待HSE稳定后继续向下执行
	if(HSEStartUpStatus==SUCCESS)
	{
		//这两句是操作FLASH闪存用到的，如果不操作FLASH，这两个注释掉也没有影响
		//使能FLASH预存取缓冲区
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
		//SYSCLK周期与闪存访问时间得比例设置，这里统一设置为2**FLASH_Latency_2**
		//设置成2得时候，SYSCLK低于48m也可以工作，如果设置成0或者1得时候，如果配置的SYSCLK超出了范围的话，则进入硬件错误，程序就死了
		// 0：0 < SYSCLK <= 24M
		// 1：24< SYSCLK <= 48M
		// 2：48< SYSCLK <= 72M
		FLASH_SetLatency(FLASH_Latency_2);
//-------------------------------------------------
    
    //AHB预分频因子设置为1分频**RCC_SYSCLK_Div1**，HCLK=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
		// APB2 预分频因子设置为 1 分频，PCLK2 = HCLK
    RCC_PCLK2Config(RCC_HCLK_Div1);
    
    // APB1 预分频因子设置为 1 分频，PCLK1 = HCLK/2
    RCC_PCLK1Config(RCC_HCLK_Div2);
    
    //-----------------设置各种频率主要就是在这里设置-------------------//
    // 设置 PLL 时钟来源为 HSE，设置 PLL 倍频因子
    // PLLCLK = 8MHz * pllmul
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmul);
    //-------------------------------------------------------------//
		// 开启 PLL
    RCC_PLLCmd(ENABLE);
    
    // 等待 PLL 稳定
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
    }
    // 当 PLL 稳定之后，把 PLL 时钟切换为系统时钟 SYSCLK
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
    // 读取时钟切换状态位，确保 PLLCLK 被选为系统时钟
    while (RCC_GetSYSCLKSource() != 0x08) {
    }
    } 
	 else 
	{
    // 如果 HSE 开启失败，那么程序就会来到这里，用户可在这里添加出错的代码处理
    // 当 HSE 开启失败或者故障的时候，单片机会自动把 HSI 设置为系统时钟，
    // HSI 是内部的高速时钟，8MHZ
      while (1) 
		 {
     }
   }
}

void HSI_SetSysClock(uint32_t pllmul)
 {
 __IO uint32_t HSIStartUpStatus = 0;
 
  // 把 RCC 外设初始化成复位状态
  RCC_DeInit();
 
 //使能 HSI
  RCC_HSICmd(ENABLE);
// 等待 HSI 就绪
  HSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY;
 
 // 只有 HSI 就绪之后则继续往下执行
  if (HSIStartUpStatus == RCC_CR_HSIRDY) {
  //-------------------------------------------------------------//
  // 这两句是操作 FLASH 闪存用到的，如果不操作 FLASH，这两个注释掉也没影响
  // 使能 FLASH 预存取缓冲区
  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
 
  // SYSCLK 周期与闪存访问时间的比例设置，这里统一设置成 2
  // 设置成 2 的时候，SYSCLK 低于 48M 也可以工作，如果设置成 0 或者 1 的时候，
  // 如果配置的 SYSCLK 超出了范围的话，则会进入硬件错误，程序就死了
  // 0：0 < SYSCLK <= 24M
  // 1：24< SYSCLK <= 48M
  // 2：48< SYSCLK <= 72M
  FLASH_SetLatency(FLASH_Latency_2);
  //------------------------------------------------------------//
 
  // AHB 预分频因子设置为 1 分频，HCLK = SYSCLK
  RCC_HCLKConfig(RCC_SYSCLK_Div1);
 
  // APB2 预分频因子设置为 1 分频，PCLK2 = HCLK
  RCC_PCLK2Config(RCC_HCLK_Div1);
 
  // APB1 预分频因子设置为 1 分频，PCLK1 = HCLK/2
  RCC_PCLK1Config(RCC_HCLK_Div2);
 
  //-----------设置各种频率主要就是在这里设置-------------------//
  // 设置 PLL 时钟来源为 HSE，设置 PLL 倍频因子
  // PLLCLK = 4MHz * pllmul
  RCC_PLLConfig(RCC_PLLSource_HSI_Div2, pllmul);
//-- -----------------------------------------------------//
 
  // 开启 PLL
  RCC_PLLCmd(ENABLE);
 
  // 等待 PLL 稳定
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {
  }
 
  // 当 PLL 稳定之后，把 PLL 时钟切换为系统时钟 SYSCLK
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
 
  // 读取时钟切换状态位，确保 PLLCLK 被选为系统时钟
  while (RCC_GetSYSCLKSource() != 0x08) {
  }
  } else {
  // 如果 HSI 开启失败，那么程序就会来到这里，用户可在这里添加出错的代码处理
  // 当 HSE 开启失败或者故障的时候，单片机会自动把 HSI 设置为系统时钟，
  // HSI 是内部的高速时钟，8MHZ
  while (1) {
  }
  }
  }

  /*
  * 初始化 MCO 引脚 PA8
  * 在 F103 系列中 MCO 引脚只有一个，即 PA8，在 F4 系列中，MCO 引脚有两个
  */
	void MCO_GPIO_Config(void)
  {
  GPIO_InitTypeDef GPIO_InitStructure;
  // 开启 GPIOA 的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
 
  // 选择 GPIO8 引脚
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 
  //设置为复用功能推挽输出
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 
  //设置 IO 的翻转速率为 50M
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // 初始化 GPIOA8
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  }
	