#ifndef __FUNC__
#define __FUNC__
#include "stm32f10x.h"
 
#define SOFT_DELAY      Delay(0x0FFFFF);

void Delay(__IO uint32_t nCount)
{
	for(; nCount !=0;nCount--);
}



 
#endif
