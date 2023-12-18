#ifndef __BSP_LED__
#define __BSP_LED__
//ʹ�ù̼������led��
#include "stm32f10x.h"

//gpio�˿�ʱ�ӡ�gpioĿ��Ϊ�������ģʽ������gio��������ߡ��͵�ƽ

//��������ĺ꣬��������Ӳ��������ֻҪ�ı�����
//��ɫ
#define LED1_GPIO_PORT     GPIOB
#define LED1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define LED1_GPIO_PIN      GPIO_Pin_5

//��ɫ
#define LED2_GPIO_PORT     GPIOB
#define LED2_GPIO_CLK      RCC_APB2Periph_GPIOB
#define LED2_GPIO_PIN      GPIO_Pin_0

//��ɫ
#define LED3_GPIO_PORT     GPIOB
#define LED3_GPIO_CLK      RCC_APB2Periph_GPIOB
#define LED3_GPIO_PIN      GPIO_Pin_1

//�Ƶ�����״̬��ת���ƶ���Ϊ��

/*ֱ�Ӳ����Ĵ����ķ�������IO   
�꺯��������ָ���pin���Ϳ�������
��������һ�κ�ı�д*/
#define digitalHi(p,i)     {p->BSRR=i;} //���Ϊ�ߵ�ƽ
#define digitalLo(p,i)     {p->BRR=i;} //���Ϊ�͵�ƽ
#define digitalToggle(p,i) {p->ODR^=i;} //���Ϊ��ת״̬

/*�������IO�ĺ�
�����Ͼ��ǵ��ú��������ǿ����������ֱ��
*/
#define LED1_TOGGLE         digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_OFF            digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_ON             digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)

#define LED2_TOGGLE         digitalToggle(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED2_OFF            digitalHi(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED2_ON             digitalLo(LED2_GPIO_PORT,LED2_GPIO_PIN)

#define LED3_TOGGLE         digitalToggle(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define LED3_OFF            digitalHi(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define LED3_ON             digitalLo(LED3_GPIO_PORT,LED3_GPIO_PIN)

/*������ɫ*/
#define LED_RED   \
                      LED1_ON\
                      LED2_OFF\
                      LED3_OFF 
											
#define LED_GREEN   \
                      LED1_OFF\
                      LED2_ON\
                      LED3_OFF 
											
#define LED_BLUE   \
                      LED1_OFF\
                      LED2_OFF\
                      LED3_ON 
																						
#define LED_YELLOW   \
                      LED1_ON\
                      LED2_ON\
                      LED3_OFF 

#define LED_PURPLE   \
                      LED1_ON\
                      LED2_OFF\
                      LED3_ON 
											
#define LED_CYAN   \
                      LED1_OFF\
                      LED2_ON\
                      LED3_ON 

#define LED_WHITE   \
                      LED1_ON\
                      LED2_ON\
                      LED3_ON 


#define LED_REGOFF   \
                      LED1_OFF\
                      LED2_OFF\
                      LED3_OFF 
 									
#define LED_G_TOGGLE    {LED2_GPIO_PORT->ODR^=GPIO_Pin_0;}
									
void LED_GPIO_Config(void);											



#endif
