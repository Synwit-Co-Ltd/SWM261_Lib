#include <string.h>
#include "SWM261.h"

CAN_RXMessage CAN_RXMsg;
volatile uint32_t CAN_Received = 0;

void SerialInit(void);

int main(void)
{
	uint32_t i, n = 0;
	CAN_InitStructure CAN_initStruct;
	uint8_t tx_data[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
	
	SystemInit();
	
	SerialInit();
	
	PORT_Init(PORTM, PIN3, PORTM_PIN3_CAN0_RX, 1);	//GPIOM.3配置为CAN0输入引脚
	PORT_Init(PORTM, PIN4, PORTM_PIN4_CAN0_TX, 0);	//GPIOM.4配置为CAN0输出引脚
	
	CAN_initStruct.Mode = CAN_MODE_NORMAL;
	CAN_initStruct.CAN_bs1 = CAN_BS1_5tq;
	CAN_initStruct.CAN_bs2 = CAN_BS2_4tq;
	CAN_initStruct.CAN_sjw = CAN_SJW_2tq;
	CAN_initStruct.Baudrate = 50000;
	CAN_initStruct.RXNotEmptyIEn = 1;
	CAN_initStruct.ArbitrLostIEn = 0;
	CAN_initStruct.ErrPassiveIEn = 0;
	CAN_Init(CAN0, &CAN_initStruct);
	
	CAN_SetFilter32b(CAN0, CAN_FILTER_1, 0x00122122, 0x1FFFFFFE);		//接收ID为0x00122122、0x00122123的扩展包
	CAN_SetFilter16b(CAN0, CAN_FILTER_2, 0x122, 0x7FE, 0x101, 0x7FF);	//接收ID为0x122、123、0x101的标准包
	
	CAN_Open(CAN0);
	
	while(1==1)
	{
		CAN_RXMessage msg;
		
		if(CAN_Received)
		{
			CAN_Received = 0;
			
			__disable_irq();
			memcpy(&msg, &CAN_RXMsg, sizeof(msg));
			__enable_irq();
			
			if(msg.size > 0)
			{
				printf("\r\nReceive %s: %08X, ", msg.format == CAN_FRAME_STD ? "STD" : "EXT", msg.id);
				for(i = 0; i < msg.size; i++) printf("%02X, ", msg.data[i]);
			}
			else if(msg.remote == 1)	//远程帧
			{
				printf("\r\nReceive %s Remote Request", msg.format == CAN_FRAME_STD ? "STD" : "EXT");
			}
		}
		
		if(++n % (SystemCoreClock/5) == 0)
			CAN_Transmit(CAN0, CAN_FRAME_STD, 0x177, tx_data, 8, 1);	//方便调试，测量SWM341 CAN发出波形
	}
}


void GPIOB2_GPIOA10_CAN0_Handler(void)
{
	uint32_t int_sr = CAN_INTStat(CAN0);
	
	if(int_sr & CAN_IF_RXDA_Msk)
	{
		CAN_Receive(CAN0, &CAN_RXMsg);
		
		CAN_Received = 1;
	}
}


void SerialInit(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTA, PIN0, PORTA_PIN0_UART0_RX, 1);	//GPIOA.0配置为UART0 RXD
	PORT_Init(PORTA, PIN1, PORTA_PIN1_UART0_TX, 0);	//GPIOA.1配置为UART0 TXD
 	
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
* 函数名称: fputc()
* 功能说明: printf()使用此函数完成实际的串口打印动作
* 输    入: int ch		要打印的字符
*			FILE *f		文件句柄
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
int fputc(int ch, FILE *f)
{
	UART_WriteByte(UART0, ch);
	
	while(UART_IsTXBusy(UART0));
 	
	return ch;
}
