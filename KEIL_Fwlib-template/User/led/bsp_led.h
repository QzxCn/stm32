#ifndef __BSP_LED__
#define __BSP_LED__
//使用固件库点亮led灯
#include "stm32f10x.h"

//gpio端口时钟、gpio目标为推挽输出模式、控制gio引脚输出高、低电平

//定义下面的宏，这样换了硬件条件，只要改变宏就行
//红色
#define LED1_GPIO_PORT     GPIOB
#define LED1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define LED1_GPIO_PIN      GPIO_Pin_5

//绿色
#define LED2_GPIO_PORT     GPIOB
#define LED2_GPIO_CLK      RCC_APB2Periph_GPIOB
#define LED2_GPIO_PIN      GPIO_Pin_0

//蓝色
#define LED3_GPIO_PORT     GPIOB
#define LED3_GPIO_CLK      RCC_APB2Periph_GPIOB
#define LED3_GPIO_PIN      GPIO_Pin_1

//灯的亮灭、状态反转控制定义为宏

/*直接操作寄存器的方法控制IO   
宏函数，输入指针和pin，就可以设置
方便下面一段宏的编写*/
#define digitalHi(p,i)     {p->BSRR=i;} //输出为高电平
#define digitalLo(p,i)     {p->BRR=i;} //输出为低电平
#define digitalToggle(p,i) {p->ODR^=i;} //输出为反转状态

/*定义控制IO的宏
本质上就是调用函数，但是看起来更简洁直接
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

/*基本颜色*/
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
