#include "SWM261.h"

/* ע�⣺
 *	оƬ�� ISP��SWD ����Ĭ�Ͽ������������裬���������߹��ģ�������������߹��ģ�����ǰ��ر��������ŵ���������������
 *
 *	��Ҫע��FLASH��������˯��ģʽ��������Ҫ�ȴ�20uSʱ�䣬����˯�ߺ󣬲��ܷ���FLASH,���Խ��뻽�Ѻ͵ȴ���Ҫ��RAM��ִ�С�
 */
 
extern void EnterSleepMode(void) ;
void gpio_outhigh(void); //GPIO���������������,GPIO����߽��͹���,Ӧ���и���ʵ���������IO״̬


int main(void)
{
	uint32_t i;
	for(i = 0; i < SystemCoreClock/2; i++)  __NOP();//��ֹ���Թ����п���
	
	SystemInit();
	
	GPIO_Init(GPIOA, PIN5, 1, 0, 0, 0);						//�� LED��ָʾ����ִ��״̬
	GPIO_SetBit(GPIOA, PIN5);								      //����LED

	GPIO_Init(GPIOA, PIN4, 0, 1, 0, 0);						//�Ӱ���������ʹ��
	SYS->PAWKEN |= (1 << PIN4);								    //����PA4���ŵ͵�ƽ����
	
	SYS->RCCR |= SYS_RCCR_LON_Msk;							  //����ģʽʹ�õ�Ƶʱ�� 
	
	while(1==1)
	{
		GPIO_SetBit(GPIOA, PIN5);							//����LED
		for(int i = 0; i < SystemCoreClock/8; i++) __NOP();
		GPIO_ClrBit(GPIOA, PIN5);							//Ϩ��LED

		Flash_Param_at_xMHz(72);
		switchToHRC();//����ǰ�л����ڲ�RCʱ�ӣ�����͹���ģʽ֮���Զ��л����ڲ���Ƶʱ��
		
		SYS->XTALCR&= ~((1 << SYS_XTALCR_ON_Pos) | (1 << SYS_XTALCR_DET_Pos)  );//�ر�����,���͹���
		
		SYS->PLLCR &= ~(1<< SYS_PLLCR_OUTEN_Pos) ;
		SYS->PLLCR |=  (1<< SYS_PLLCR_PWRDN_Pos) ;//�ر�PLL,���͹���
		
		SYS->CLKEN0 &=~ (1 << SYS_CLKEN0_ANAC_Pos); //�ر�ģ��ģ��ʱ�ӽ�ʡ����--����ر�
		gpio_outhigh(); //IOû�����������£���GPIO����߹������

		EnterSleepMode();//��SRAM�н���sleep,�ȴ�����

		SYS->CLKEN0 |=(1 << SYS_CLKEN0_ANAC_Pos); 
		switchOnPLL(3,2,15);//���Ѻ��л���PLLʱ��
		switchToDIV(SYS_CLK_PLL, SYS_CLK_DIV_1);
		SystemCoreClockUpdate();
		Flash_Param_at_xMHz(CyclesPerUs);
	}
}


	
  void gpio_outhigh(void)
 {
		SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_GPIOA_Pos);
		SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_GPIOB_Pos);
		SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_GPIOC_Pos);

	 GPIO_Init(GPIOA ,0 ,1,0, 0, 0);//set gpio out modle
	 GPIO_Init(GPIOA ,1 ,1,0, 0, 0);
	 GPIO_Init(GPIOA ,2 ,1,0, 0, 0);
	 GPIO_Init(GPIOA ,3 ,1,0, 0, 0);
//	 GPIO_Init(GPIOA ,4 ,1,0, 0, 0);
//	 GPIO_Init(GPIOA ,5 ,1,0, 0, 0);
	 GPIO_Init(GPIOA ,6 ,1,0, 0, 0);
	 GPIO_Init(GPIOA ,7 ,1,0, 0, 0);
	 GPIO_Init(GPIOA ,8 ,1,0, 0, 0);
	 GPIO_Init(GPIOA ,9 ,1,0, 0, 0);
	 GPIO_Init(GPIOA ,10,1,0, 0, 0);
	 GPIO_Init(GPIOA ,11,1,0, 0, 0);
	 GPIO_Init(GPIOA ,12,1,0, 0, 0);
	 GPIO_Init(GPIOA ,13,1,0, 0, 0);
	 GPIO_Init(GPIOA ,14,1,0, 0, 0);
	 GPIO_Init(GPIOA ,15,1,0, 0, 0);
	 
	 GPIO_Init(GPIOB ,0 ,1,0, 0, 0);
	 GPIO_Init(GPIOB ,1 ,1,0, 0, 0);
	 GPIO_Init(GPIOB ,2 ,1,0, 0, 0);
	 GPIO_Init(GPIOB ,3 ,1,0, 0, 0);
	 GPIO_Init(GPIOB ,4 ,1,0, 0, 0);
	 GPIO_Init(GPIOB ,5 ,1,0, 0, 0);
	 GPIO_Init(GPIOB ,6 ,1,0, 0, 0);
	 GPIO_Init(GPIOB ,7 ,1,0, 0, 0);
	 GPIO_Init(GPIOB ,8 ,1,0, 0, 0);
	 GPIO_Init(GPIOB ,9 ,1,0, 0, 0);
	 GPIO_Init(GPIOB ,10,1,0, 0, 0);
	 GPIO_Init(GPIOB ,11,1,0, 0, 0);
	 GPIO_Init(GPIOB ,12,1,0, 0, 0);
	 GPIO_Init(GPIOB ,13,1,0, 0, 0);
	 GPIO_Init(GPIOB ,14,1,0, 0, 0);
	 GPIO_Init(GPIOB ,15,1,0, 0, 0);
	 
	 GPIO_Init(GPIOC ,0 ,1,0, 0, 0);
	 GPIO_Init(GPIOC ,1 ,1,0, 0, 0);
	 GPIO_Init(GPIOC ,2 ,1,0, 0, 0);
	 GPIO_Init(GPIOC ,3 ,1,0, 0, 0);
	 GPIO_Init(GPIOC ,4 ,1,0, 0, 0);
	 GPIO_Init(GPIOC ,5 ,1,0, 0, 0);
	 GPIO_Init(GPIOC ,6 ,1,0, 0, 0);
	 GPIO_Init(GPIOC ,7 ,1,0, 0, 0);
	 GPIO_Init(GPIOC ,8 ,1,0, 0, 0);
	 GPIO_Init(GPIOC ,9 ,1,0, 0, 0);
	 GPIO_Init(GPIOC ,10,1,0, 0, 0);
	 GPIO_Init(GPIOC ,11,1,0, 0, 0);
	 GPIO_Init(GPIOC ,12,1,0, 0, 0);
	 GPIO_Init(GPIOC ,13,1,0, 0, 0);
	 GPIO_Init(GPIOC ,14,1,0, 0, 0);
	 GPIO_Init(GPIOC ,15,1,0, 0, 0);
	 
	 GPIO_SetBits( GPIOA,0, 16); //set gpio 0-gpio15 out high
	 GPIO_SetBits( GPIOB,0, 16);
	 GPIO_SetBits( GPIOC,0, 16);
 }
	 
void SerialInit(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTA, PIN0, PORTA_PIN0_UART0_RX, 1);	//GPIOA.0����ΪUART0 RXD
	PORT_Init(PORTA, PIN1, PORTA_PIN1_UART0_TX, 0);	//GPIOA.1����ΪUART0 TXD
 	
 	UART_initStruct.Baudrate = 57600;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThreshold = 3;
	UART_initStruct.RXThresholdIEn = 0;
	UART_initStruct.TXThreshold = 3;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;
	UART_initStruct.TimeoutIEn = 0;
 	UART_Init(UART0, &UART_initStruct);
	UART_Open(UART0);
}

/****************************************************************************************************************************************** 
* ��������: fputc()
* ����˵��: printf()ʹ�ô˺������ʵ�ʵĴ��ڴ�ӡ����
* ��    ��: int ch		Ҫ��ӡ���ַ�
*			FILE *f		�ļ����
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
int fputc(int ch, FILE *f)
{
	UART_WriteByte(UART0, ch);
	
	while(UART_IsTXBusy(UART0));
 	
	return ch;
}


