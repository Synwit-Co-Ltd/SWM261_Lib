#include "SWM261.h"


/* ע�⣺EnterSleepMode() ������RAM��ִ�У�Keil��ʵ�ַ����У�
   ����һ��Scatter file
   ��������code_in_ra.c���Ҽ� =��Options for File "SWM261_sleep.c" =��Properties =��Memory Assignment =��Code/Conts ѡ�� IRAM1
*/

void EnterSleepMode(void) 
{ 
		volatile int i;
	
		SYS->SLEEP |= (1 << SYS_SLEEP_SLEEP_Pos);
			
		while((SYS->PAWKSR & (1 << PIN4)) == 0)
		{
				__NOP();
		}
		SYS->PAWKSR |= (1 << PIN4);							//�������״̬

		for(i=0;i<1000;i++)//�ȴ�FLASH����,������Ҫ20uS.
		{
			__NOP();
		}
}  
