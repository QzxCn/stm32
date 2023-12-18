#include "stm32f10x.h"
//十四章，gpio位带的使用
 
/*
通过位操作控制gpio的odr和idr
首先获取每个gpio（比如gpiob,gpioa等）的idr，odr地址

然后输入要控制的io口，也就是pin，也就是要控制的寄存器的哪个位

然后通过公式计算这个位的位带转换地址

然后把地址转换为指针

最后就可以通过指针对这个位进行修改

 

*/
//计算某个位的地址
//addr & 0xF0000000)+0x02000000，取得别名区的起始地址，外带为42000000，flash为22000000
/*addr & 0x00FFFFFF)<<5，相当于乘上2的5次方，即32=8*4，见教程p194公式，  bitnum<<2相当于×4
  这里是区别每个外设的地方，每个外设相对于0x40000000的地址不同，因此计算出不同的bit数量

*/
#define BITBAND(addr, bitnum)  ((addr & 0xF0000000)+0x02000000+((addr & 0x00FFFFFF)<<5)+(bitnum<<2)) 


//宏定义一个操作，把地址转换为指针
#define MEM_ADDR(addr)   *((volatile unsigned int  *)(addr))
	//宏定义操作，把位带别名区地址转换为指针
#define BIT_ADDR(addr,bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

// GPIO ODR 和 IDR 寄存器地址映射    分别偏移12和8，因此首先定义二者的宏
#define GPIOA_ODR_Addr (GPIOA_BASE+0) //0x4001080C
#define GPIOB_ODR_Addr (GPIOB_BASE+12) //0x40010C0C
#define GPIOC_ODR_Addr (GPIOC_BASE+12) //0x4001100C
#define GPIOD_ODR_Addr (GPIOD_BASE+12) //0x4001140C
#define GPIOE_ODR_Addr (GPIOE_BASE+12) //0x4001180C
#define GPIOF_ODR_Addr (GPIOF_BASE+12) //0x40011A0C
#define GPIOG_ODR_Addr (GPIOG_BASE+12) //0x40011E0C

#define GPIOA_IDR_Addr (GPIOA_BASE+8) //0x40010808
#define GPIOB_IDR_Addr (GPIOB_BASE+8) //0x40010C08
#define GPIOC_IDR_Addr (GPIOC_BASE+8) //0x40011008
#define GPIOD_IDR_Addr (GPIOD_BASE+8) //0x40011408
#define GPIOE_IDR_Addr (GPIOE_BASE+8) //0x40011808
#define GPIOF_IDR_Addr (GPIOF_BASE+8) //0x40011A08
#define GPIOG_IDR_Addr (GPIOG_BASE+8) //0x40011E08

/* 单独操作 GPIO 的某一个 IO 口的位控制地址，n(0,1,2...16),n 表示具体是哪一个 IO 口,
   其实就是某个寄存器的某个位的地址*/
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr,n) //输出  odr
#define PAin(n)  BIT_ADDR(GPIOA_IDR_Addr,n) //输入  idr

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr,n) //输出  odr
#define PBin(n)  BIT_ADDR(GPIOB_IDR_Addr,n) //输入  idr

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr,n) //输出  odr
#define PCin(n)  BIT_ADDR(GPIOC_IDR_Addr,n) //输入  idr

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr,n) //输出
#define PDin(n)  BIT_ADDR(GPIOD_IDR_Addr,n) //输入

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr,n) //输出
#define PEin(n)  BIT_ADDR(GPIOE_IDR_Addr,n) //输入

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr,n) //输出
#define PFin(n)  BIT_ADDR(GPIOF_IDR_Addr,n) //输入

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr,n) //输出
#define PGin(n)  BIT_ADDR(GPIOG_IDR_Addr,n) //输入

//#define PBout(n)    *(unsigned int*)((GPIOB_ODR_Addr&0xF0000000)+0x02000000+((GPIOB_ODR_Addr&0x00FFFFFF)<<5)+(n<<2))
	 