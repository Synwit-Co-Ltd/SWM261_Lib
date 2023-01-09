#include "SWM261.h"


int main(void)
{	
	SystemInit();
	
	GPIO_Init(GPIOA, PIN5, 1, 0, 0, 0);			//输出，接LED
	
	GPIO_Init(GPIOA, PIN2, 0, 1, 0, 0);			//输入，上拉使能，接KEY
	
	EXTI_Init(GPIOA, PIN2, EXTI_FALL_EDGE);		//下降沿触发中断
	
	NVIC_EnableIRQ(GPIOA2_GPIOM2_IRQn);
	
	EXTI_Open(GPIOA, PIN2);
	
	while(1==1)
	{
	}
}

void GPIOA2_GPIOM2_Handler(void)
{
	EXTI_Clear(GPIOA, PIN2);
	
	GPIO_InvBit(GPIOA, PIN5);
}
