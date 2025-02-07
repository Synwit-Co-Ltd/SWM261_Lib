#include "SWM261.h"


void SerialInit(void);
void SystemInit_72MHz(void);

int main(void)
{
	SystemInit();
	
	SerialInit();
   	
	printf("SystemCoreClock = %d\r\n", SystemCoreClock);
	
	while(1==1)
	{
		SystemInit_72MHz();
		
		UART_SetBaudrate(UART0, 57600);		// �л�ϵͳ��Ƶ����Ҫ�������ò�����
		
		for(int i = 0; i < 4; i++)
		{
			printf("SystemCoreClock = %d\r\n", SystemCoreClock);
			
			for(int j = 0; j < SystemCoreClock / 8; j++) __NOP();
		}
		
		SystemInit();
		
		UART_SetBaudrate(UART0, 57600);
		
		for(int i = 0; i < 4; i++)
		{
			printf("SystemCoreClock = %d\r\n", SystemCoreClock);
			
			for(int j = 0; j < SystemCoreClock / 8; j++) __NOP();
		}
	}
}


void SystemInit_72MHz(void)
{
	Flash_Param_at_xMHz(72);
	
	switchToHRC();
	
	switchOnPLL(SYS_CLK_8MHz, 2, 18);
	
	switchToDIV(SYS_CLK_PLL, SYS_CLK_DIV_1);
		
	Flash_Param_at_xMHz(CyclesPerUs);
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
