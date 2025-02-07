#include "SWM261.h"

#include "ugui.h"
#include "ST7789.h"

UG_GUI gui;

void SerialInit(void);

int main(void)
{
	SystemInit();
	
	SerialInit();
	
	ST7789_Init();
	
#if 1
	ST7789_Clear(C_RED);
#else
	ST7789_DMAClear(0, 0, C_RED, LCD_HPIX * LCD_VPIX / 2);
	while(!ST7789_DMADone()) __NOP();
	ST7789_DMAClear(0, LCD_VPIX / 2, C_RED, LCD_HPIX * LCD_VPIX / 2);
	while(!ST7789_DMADone()) __NOP();
#endif
	
	UG_Init(&gui,(void(*)(UG_S16,UG_S16,UG_COLOR))ST7789_DrawPoint, LCD_HPIX, LCD_VPIX);
	
	UG_DrawLine(0, 100, LCD_HPIX, 100, C_GREEN);
	UG_DrawLine(0, 150, LCD_HPIX, 150, C_GREEN);
	UG_DrawLine(0, 200, LCD_HPIX, 200, C_GREEN);
	
 	UG_FillFrame(0, 101, LCD_HPIX, 149, C_BLACK);
 	
  	UG_FontSelect(&FONT_12X20);
	UG_PutString(20, 110, "Hi from Synwit");
   	
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
