#include "bsp_exti.h"


/*
  整体思路，
	首先配置EXTI
	再配置NVIC
*/
static void EXTI_NVIC_Config(void)//static限制该函数只能被本文件使用
{
	NVIC_InitTypeDef NVIC_InitStructure;//这个结构体的意义是为了调用NVIC初始化函数做准备，也就是作函数的实参
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//  优先级分组，修改scb->aicr
/*
	GPIO接口
	EXTI0_IRQn                  = 6,      !< EXTI Line0 Interrupt                             
  EXTI1_IRQn                  = 7,      !< EXTI Line1 Interrupt                             
  EXTI2_IRQn                  = 8,      !< EXTI Line2 Interrupt                             
  EXTI3_IRQn                  = 9,      !< EXTI Line3 Interrupt                                
  EXTI4_IRQn                  = 10,     !< EXTI Line4 Interrupt    
	EXTI9_5_IRQn                = 23,     !< External Line[9:5] Interrupts  
  EXTI15_10_IRQn              = 40,     !< External Line[15:10] Interrupts          
*/
	NVIC_InitStructure.NVIC_IRQChannel=KEY1_INT_EXTI_IRQ;//使能中断请求    见stm32f10x_exit.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//优先级数字越小，优先级越高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//配置信息进入NVIC
	
	NVIC_InitStructure.NVIC_IRQChannel=KEY2_INT_EXTI_IRQ;//使能中断请求	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//优先级数字越小，优先级越高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);//配置信息进入NVIC
}
 

void EXIT_Key_Config(void)
{
//初始化GPIO，这里键盘-->gpio
	GPIO_InitTypeDef GPIO_InitStructure;//
	
	EXTI_InitTypeDef EXTI_InitStructure;//
	

//key1的配置*****	
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);	//打开gpioa的时钟
	
	
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入，即这个GPIO口的电平由外部决定  
	GPIO_InitStructure.GPIO_Pin=KEY1_INT_GPIO_PIN;//选择要控制的GPIO引脚，就是odr偏移地址	
	GPIO_Init(KEY1_INT_GPIO_PORT,&GPIO_InitStructure);
	

	
	//初始化exti,即选择输入线为GPIOA的pin0，原文Selects the GPIO pin used as EXTI Line.
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);//pinsource0要和exti_line0重合

 	
	
  //exit的初始化
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;//输入线，前16根用于gpio
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//请求挂起，中断或者事件模式
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;//边沿触发器
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;//中断屏蔽器，使能
	EXTI_Init(&EXTI_InitStructure);
	
	//初始化NVIC
	EXTI_NVIC_Config();
	
//key2的配置******
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK,ENABLE);	//打开gpioC的时钟	
	
	//gpioc初始化
	GPIO_InitStructure.GPIO_Pin=KEY2_INT_GPIO_PIN;//选择要控制的GPIO引脚，就是odr偏移地址
	/*模式已经设置过*/
	GPIO_Init(KEY2_INT_GPIO_PORT,&GPIO_InitStructure);
	//gpioc的pin13作为exit的输入线
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
	
	/*exit时钟已经打开过*/
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	/*模式已经设置过*/
	/*边沿触发器已经设置过*/
	//EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	/*中断屏蔽器已经设置过*/	
	EXTI_Init(&EXTI_InitStructure);
	
	/*NVIC已经初始化过*/
 
}


void Delayx(__IO uint32_t nCount)
{
	for(; nCount !=0;nCount--);
}
