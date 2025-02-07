#include <string.h>
#include "SWM261.h"


#define TX_N	8
#define TX_LEN 32
char TX_Buffer[TX_N][TX_LEN] = {
	"TestString\r\n",
	"TestString1\r\n",
	"TestString12\r\n",
	"TestString123\r\n",
	"TestString1234\r\n",
	"TestString12345\r\n",
	"TestString123456\r\n",
	"TestString1234567\r\n",
};
char RX_Buffer[TX_LEN] = {0};


void SerialInit(void);

int main(void)
{
	DMA_InitStructure DMA_initStruct;
	
	SystemInit();
	
	SerialInit();
	
	DMA_initStruct.Mode = DMA_MODE_SINGLE;
	DMA_initStruct.Unit = DMA_UNIT_BYTE;
	DMA_initStruct.Count = strlen(TX_Buffer[0]);
	DMA_initStruct.MemoryAddr = (uint32_t)TX_Buffer[0];
	DMA_initStruct.MemoryAddrInc = 1;
	DMA_initStruct.PeripheralAddr = (uint32_t)RX_Buffer;
	DMA_initStruct.PeripheralAddrInc = 1;
	DMA_initStruct.Handshake = DMA_HS_NO;	// �������źţ������� Memory to Memory ���䣬MemoryAddr ����Դ��ַ��PeripheralAddr ����Ŀ�ĵ�ַ
	DMA_initStruct.Priority = DMA_PRI_LOW;
	DMA_initStruct.INTEn = 0;
	DMA_CH_Init(DMA_CH0, &DMA_initStruct);
	
	for(int i = 0; i < TX_N; i++)
	{
		DMA_CH_SetAddrAndCount(DMA_CH0, (uint32_t)TX_Buffer[i], strlen(TX_Buffer[i]));
		
		DMA_CH_Open(DMA_CH0);
		
		while(DMA_CH_INTStat(DMA_CH0, DMA_IT_DONE) == 0) __NOP();
		DMA_CH_INTClr(DMA_CH0, DMA_IT_DONE);
		
		printf("RX_Buffer: %s\n", RX_Buffer);
	}
	
	while(1==1)
	{
	}
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
