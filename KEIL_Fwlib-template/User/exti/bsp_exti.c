#include "bsp_exti.h"


/*
  ����˼·��
	��������EXTI
	������NVIC
*/
static void EXTI_NVIC_Config(void)//static���Ƹú���ֻ�ܱ����ļ�ʹ��
{
	NVIC_InitTypeDef NVIC_InitStructure;//����ṹ���������Ϊ�˵���NVIC��ʼ��������׼����Ҳ������������ʵ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//  ���ȼ����飬�޸�scb->aicr
/*
	GPIO�ӿ�
	EXTI0_IRQn                  = 6,      !< EXTI Line0 Interrupt                             
  EXTI1_IRQn                  = 7,      !< EXTI Line1 Interrupt                             
  EXTI2_IRQn                  = 8,      !< EXTI Line2 Interrupt                             
  EXTI3_IRQn                  = 9,      !< EXTI Line3 Interrupt                                
  EXTI4_IRQn                  = 10,     !< EXTI Line4 Interrupt    
	EXTI9_5_IRQn                = 23,     !< External Line[9:5] Interrupts  
  EXTI15_10_IRQn              = 40,     !< External Line[15:10] Interrupts          
*/
	NVIC_InitStructure.NVIC_IRQChannel=KEY1_INT_EXTI_IRQ;//ʹ���ж�����    ��stm32f10x_exit.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//���ȼ�����ԽС�����ȼ�Խ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);//������Ϣ����NVIC
	
	NVIC_InitStructure.NVIC_IRQChannel=KEY2_INT_EXTI_IRQ;//ʹ���ж�����	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//���ȼ�����ԽС�����ȼ�Խ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);//������Ϣ����NVIC
}
 

void EXIT_Key_Config(void)
{
//��ʼ��GPIO���������-->gpio
	GPIO_InitTypeDef GPIO_InitStructure;//
	
	EXTI_InitTypeDef EXTI_InitStructure;//
	

//key1������*****	
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);	//��gpioa��ʱ��
	
	
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//�������룬�����GPIO�ڵĵ�ƽ���ⲿ����  
	GPIO_InitStructure.GPIO_Pin=KEY1_INT_GPIO_PIN;//ѡ��Ҫ���Ƶ�GPIO���ţ�����odrƫ�Ƶ�ַ	
	GPIO_Init(KEY1_INT_GPIO_PORT,&GPIO_InitStructure);
	

	
	//��ʼ��exti,��ѡ��������ΪGPIOA��pin0��ԭ��Selects the GPIO pin used as EXTI Line.
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);//pinsource0Ҫ��exti_line0�غ�

 	
	
  //exit�ĳ�ʼ��
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;//�����ߣ�ǰ16������gpio
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//��������жϻ����¼�ģʽ
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;//���ش�����
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;//�ж���������ʹ��
	EXTI_Init(&EXTI_InitStructure);
	
	//��ʼ��NVIC
	EXTI_NVIC_Config();
	
//key2������******
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK,ENABLE);	//��gpioC��ʱ��	
	
	//gpioc��ʼ��
	GPIO_InitStructure.GPIO_Pin=KEY2_INT_GPIO_PIN;//ѡ��Ҫ���Ƶ�GPIO���ţ�����odrƫ�Ƶ�ַ
	/*ģʽ�Ѿ����ù�*/
	GPIO_Init(KEY2_INT_GPIO_PORT,&GPIO_InitStructure);
	//gpioc��pin13��Ϊexit��������
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
	
	/*exitʱ���Ѿ��򿪹�*/
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	/*ģʽ�Ѿ����ù�*/
	/*���ش������Ѿ����ù�*/
	//EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	/*�ж��������Ѿ����ù�*/	
	EXTI_Init(&EXTI_InitStructure);
	
	/*NVIC�Ѿ���ʼ����*/
 
}


void Delayx(__IO uint32_t nCount)
{
	for(; nCount !=0;nCount--);
}
