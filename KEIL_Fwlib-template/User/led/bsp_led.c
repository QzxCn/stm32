//bsp:board support package �弶֧�ְ�
#include "bsp_led.h"   // �Լ��½���ͷ�ļ���������ħ����c/c++ָ��ͷ�ļ�·��


void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//
	//����led���gpio����ʱ��
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK|LED2_GPIO_CLK|LED3_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//�ٶ�50Mhz
	
	GPIO_InitStructure.GPIO_Pin=LED1_GPIO_PIN;//ѡ��Ҫ���Ƶ�GPIO���ţ�����odrƫ�Ƶ�ַ
	GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStructure);   // ��һ������Ϊ��ַ������GPIOB���ڶ�����������ƫ�Ƶ�ַ

	GPIO_InitStructure.GPIO_Pin=LED2_GPIO_PIN;//ѡ��Ҫ���Ƶ�GPIO���ţ�
  GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStructure);   
	
	GPIO_InitStructure.GPIO_Pin=LED3_GPIO_PIN; 
	GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStructure);   
	
	
	GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);
	GPIO_SetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);
	GPIO_SetBits(LED3_GPIO_PORT,LED3_GPIO_PIN);
}

 
