#include "SWM261.h"
#include "CircleBuffer.h"

volatile bool msg_rcvd = false;

CircleBuffer_t CirBuf;

void SerialInit(void);

int main(void)
{
	SystemInit();
	
	SerialInit();
	
	USART_InitStructure USART_initStruct;
	
 	PORT_Init(PORTA, PIN2, PORTA_PIN2_USART0_TX, 0);
	PORT_Init(PORTA, PIN3, PORTA_PIN3_USART0_RX, 1);
 	
 	USART_initStruct.Baudrate = 57600;
	USART_initStruct.DataBits = USART_DATA_8BIT;
	USART_initStruct.Parity = USART_PARITY_NONE;
	USART_initStruct.StopBits = USART_STOP_1BIT;
	USART_initStruct.RXReadyIEn = 1;
	USART_initStruct.TXReadyIEn = 0;
	USART_initStruct.TimeoutIEn = 1;
	USART_initStruct.TimeoutTime = 50;	// 50 �� bit ʱ����δ���յ��µ����ݣ��������ճ�ʱ�ж�
 	USART_Init(USART0, &USART_initStruct);
	USART_Open(USART0);
	
	while(1==1)
	{
		if(msg_rcvd)
		{
			msg_rcvd = false;
			
			USART_INTEn(USART0, USART_IT_TX_RDY);
		}
	}
}


void USART0_Handler(void)
{
	uint8_t chr;
	
	if(USART_INTStat(USART0, USART_IT_RX_RDY))
	{
		chr = USART_Read(USART0);
		
		CirBuf_Write(&CirBuf, &chr, 1);
	}
	else if(USART_INTStat(USART0, USART_IT_RX_TO))
	{
		USART_INTClr(USART0, USART_IT_RX_TO);
		
		msg_rcvd = true;
	}
	
	if(USART_INTStat(USART0, USART_IT_TX_RDY))
	{
		CirBuf_Read(&CirBuf, &chr, 1);
		
		USART_Write(USART0, chr);
		
		if(CirBuf_Empty(&CirBuf))
		{
			USART_INTDis(USART0, USART_IT_TX_RDY);
		}
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
