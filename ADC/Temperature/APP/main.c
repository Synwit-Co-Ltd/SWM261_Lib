#include "SWM261.h"


void SerialInit(void);

int main(void)
{
	ADC_InitStructure ADC_initStruct;
	ADC_SEQ_InitStructure ADC_SEQ_initStruct;
	
	SystemInit();
	
	SerialInit();
	
	/* ʹ���¶ȴ��������¶ȴ��������� ADC0 �� CH9
	 * �¶ȴ����������ѹ���¶ȱ仯������Ϊ7mV/��
	 * ����� ADC �������¶Ȼ����ϵ���ɸ��ݹ�ʽ��y = kx + b
	 * ����������֪�¶Ⱥ����Ӧ ADC ������������� k �� b
	 ******************************************************/
	SYS->TEMPCR |= SYS_TEMPCR_EN_Msk;
	
	ADC_initStruct.clkdiv = 4;
	ADC_initStruct.refsrc = ADC_REF_VDD;
	ADC_initStruct.samplAvg = ADC_AVG_SAMPLE1;
	ADC_Init(ADC0, &ADC_initStruct);
	
	ADC_SEQ_initStruct.trig_src = ADC_TRIGGER_SW;
	ADC_SEQ_initStruct.samp_tim = 6;
	ADC_SEQ_initStruct.conv_cnt = 1;
	ADC_SEQ_initStruct.EOCIntEn = 0;
	ADC_SEQ_initStruct.channels = (uint8_t []){ ADC_CH9, 0xF };
	ADC_SEQ_Init(ADC0, ADC_SEQ0, &ADC_SEQ_initStruct);
	
	ADC_Open(ADC0);
	
	while(1==1)
	{
		ADC_Start(ADC_SEQ0, 0);
		while(ADC_Busy(ADC0)) __NOP();
		printf("%4d,", ADC_Read(ADC0, ADC_CH9));
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
