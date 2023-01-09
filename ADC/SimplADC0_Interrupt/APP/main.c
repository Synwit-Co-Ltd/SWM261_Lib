#include "SWM261.h"

void SerialInit(void);

int main(void)
{
	ADC_InitStructure ADC_initStruct;
#if defined(CHIP_SWM200)
	ADC_SEQ_InitStructure ADC_SEQ_initStruct;
#endif
	
	SystemInit();
	
	SerialInit();	
	
#if defined(CHIP_SWM201)
	PORT_Init(PORTA, PIN14, PORTA_PIN14_ADC0_CH0, 0);		//PA.14 => ADC0.CH0
	PORT_Init(PORTA, PIN13, PORTA_PIN13_ADC0_CH1, 0);		//PA.13 => ADC0.CH1
	PORT_Init(PORTB, PIN3,  PORTB_PIN3_ADC0_CH2,  0);		//PB.3  => ADC0.CH2
	PORT_Init(PORTA, PIN11, PORTA_PIN11_ADC0_CH3, 0);		//PA.11 => ADC0.CH3
	PORT_Init(PORTB, PIN6,  PORTB_PIN6_ADC0_CH4,  0);		//PB.6  => ADC0.CH4
	PORT_Init(PORTB, PIN5,  PORTB_PIN5_ADC0_CH5,  0);		//PB.5  => ADC0.CH5
	PORT_Init(PORTB, PIN4,  PORTB_PIN4_ADC0_CH6,  0);		//PB.4  => ADC0.CH6
	PORT_Init(PORTA, PIN8,  PORTA_PIN8_ADC0_CH7,  0);		//PA.8  => ADC0.CH7
	PORT_Init(PORTB, PIN9,  PORTB_PIN9_ADC0_CH8,  0);		//PB.9  => ADC0.CH8
	PORT_Init(PORTB, PIN7,  PORTB_PIN7_ADC0_CH9,  0);		//PB.7  => ADC0.CH9
	PORT_Init(PORTM, PIN9,  PORTM_PIN9_ADC0_CH10, 0);		//PM.9  => ADC0.CH10
	PORT_Init(PORTM, PIN8,  PORTM_PIN8_ADC0_CH11, 0);		//PM.8  => ADC0.CH11
#elif defined(CHIP_SWM261)	
	PORT_Init(PORTA, PIN14, PORTA_PIN14_ADC0_CH0, 0);		//PA.14 => ADC0.CH0
	PORT_Init(PORTA, PIN11, PORTA_PIN11_ADC0_CH1, 0);		//PA.11 => ADC0.CH1
	PORT_Init(PORTA, PIN8,  PORTA_PIN8_ADC0_CH2,  0);		//PA.8  => ADC0.CH2
	PORT_Init(PORTB, PIN9,  PORTB_PIN9_ADC0_CH3,  0);		//PB.9  => ADC0.CH3
	PORT_Init(PORTA, PIN13, PORTA_PIN13_ADC0_CH4, 0);		//PA.13 => ADC0.CH4
	PORT_Init(PORTB, PIN7,  PORTB_PIN7_ADC0_CH5,  0);		//PB.7  => ADC0.CH5
	PORT_Init(PORTB, PIN6,  PORTB_PIN6_ADC0_CH6,  0);		//PB.6  => ADC0.CH6
	PORT_Init(PORTB, PIN5,  PORTB_PIN5_ADC0_CH7,  0);		//PB.5  => ADC0.CH7
	PORT_Init(PORTB, PIN4,  PORTB_PIN4_ADC0_CH8,  0);		//PB.4  => ADC0.CH8
	PORT_Init(PORTB, PIN3,  PORTB_PIN3_ADC0_CH9,  0);		//PB.3  => ADC0.CH9
	PORT_Init(PORTM, PIN9,  PORTM_PIN9_ADC0_CH10, 0);		//PM.9  => ADC0.CH10
	
	/* 注意：
	 * 在 SWM261CB 上，ADC0_CH4 的通道初始化须改为： PORT_Init(PORTB, PIN0, 0, 0);
	 *
	 * 在 SWM21PG6 上，ADC0_CH4 的通道初始化须改为： PORT_Init(PORTM, PIN4, 0, 0);
	 *
	 * 在 SWM21DK6 上，ADC0_CH4 的通道初始化须改为： PORT_Init(PORTM, PIN8, 0, 0);
	 *
	 ****************************************************************************/
#elif defined(CHIP_SWM200)
	PORT_Init(PORTA, PIN11, PORTA_PIN11_ADC0_CH0,  0);		//PA.11 => ADC0.CH0
	PORT_Init(PORTA, PIN9,  PORTA_PIN9_ADC0_CH1,   0);		//PA.9  => ADC0.CH1
	PORT_Init(PORTA, PIN8,  PORTA_PIN8_ADC0_CH2,   0);		//PA.8  => ADC0.CH2
	PORT_Init(PORTB, PIN9,  PORTB_PIN9_ADC0_CH3,   0);		//PB.9  => ADC0.CH3
	PORT_Init(PORTA, PIN10, PORTA_PIN10_ADC0_CH4,  0);		//PA.10 => ADC0.CH4
	PORT_Init(PORTB, PIN7,  PORTB_PIN7_ADC0_CH5,   0);		//PB.7  => ADC0.CH5
	PORT_Init(PORTB, PIN6,  PORTB_PIN6_ADC0_CH6,   0);		//PB.6  => ADC0.CH6
	PORT_Init(PORTB, PIN5,  PORTB_PIN5_ADC0_CH7,   0);		//PB.5  => ADC0.CH7
	PORT_Init(PORTB, PIN4,  PORTB_PIN4_ADC0_CH8,   0);		//PB.4  => ADC0.CH8
	PORT_Init(PORTB, PIN3,  PORTB_PIN3_ADC0_CH9,   0);		//PB.3  => ADC0.CH9
	PORT_Init(PORTB, PIN2,  PORTB_PIN2_ADC0_CH10,  0);		//PB.2  => ADC0.CH10
	PORT_Init(PORTB, PIN1,  PORTB_PIN1_ADC0_CH11,  0);		//PB.1  => ADC0.CH11
	PORT_Init(PORTB, PIN15, PORTB_PIN15_ADC0_CH12, 0);		//PB.15 => ADC0.CH12
	PORT_Init(PORTB, PIN14, PORTB_PIN14_ADC0_CH13, 0);		//PB.14 => ADC0.CH13
//	PORT_Init(PORTM, PIN1,  PORTM_PIN1_ADC0_CH14,  0);		//PM.1  => ADC0.CH14	SWDIO
//	PORT_Init(PORTM, PIN0,  PORTM_PIN0_ADC0_CH15,  0);		//PM.0  => ADC0.CH15	SWCLK
#endif

#if defined(CHIP_SWM201) || defined(CHIP_SWM261)
#if defined(CHIP_SWM201)
	ADC_initStruct.clk_src = ADC_CLKSRC_HRC_DIV8;
	ADC_initStruct.clk_div = 15;
#elif defined(CHIP_SWM261)
	ADC_initStruct.clk_src = ADC_CLKSRC_HRC_DIV2;
	ADC_initStruct.clk_div = 6;
#endif
	ADC_initStruct.ref_src = ADC_REFSRC_3V6;
	ADC_initStruct.channels = ADC_CH0 | ADC_CH1 | ADC_CH2 | ADC_CH3;
	ADC_initStruct.samplAvg = ADC_AVG_SAMPLE1;
	ADC_initStruct.trig_src = ADC_TRIGGER_SW;
	ADC_initStruct.Continue = 0;						//非连续模式，即单次模式
	ADC_initStruct.EOC_IEn = ADC_CH3;	
	ADC_initStruct.OVF_IEn = 0;
	ADC_Init(ADC0, &ADC_initStruct);					//配置ADC
	
	ADC_Open(ADC0);										//使能ADC
	ADC_Start(ADC0);
#elif defined(CHIP_SWM200)
	ADC_initStruct.clk_src = ADC_CLKSRC_HRC_DIV8;
	ADC_initStruct.samplAvg = ADC_AVG_SAMPLE1;
	ADC_initStruct.EOC_IEn = ADC_SEQ0;	
	ADC_initStruct.HalfIEn = 0;
	ADC_Init(ADC0, &ADC_initStruct);					//配置ADC
	
	ADC_SEQ_initStruct.channels = ADC_CH0;
	ADC_SEQ_initStruct.trig_src = ADC_TRIGGER_SW;
	ADC_SEQ_initStruct.conv_cnt = 1;
	ADC_SEQ_initStruct.samp_tim = ADC_SAMPLE_1CLOCK;
	ADC_SEQ_Init(ADC0, ADC_SEQ0, &ADC_SEQ_initStruct);
	
	ADC_Open(ADC0);										//使能ADC
	ADC_Calibrate(ADC0);								//校准ADC
	
	ADC_Start(ADC0, ADC_SEQ0);
#endif

	while(1==1)
	{
	}
}


#if defined(CHIP_SWM201) || defined(CHIP_SWM261)
void ADC0_Handler(void)
{
	ADC0->IF = (1 << ADC_IF_CH3EOC_Pos);
	
#if 0
	printf("%4d\t%4d\t%4d\t%4d\r\n", ADC_Read(ADC0, ADC_CH0), ADC_Read(ADC0, ADC_CH1), ADC_Read(ADC0, ADC_CH2), ADC_Read(ADC0, ADC_CH3));
#else
	printf("%4d,", ADC_Read(ADC0, ADC_CH0));
#endif
	ADC_Start(ADC0);
}
#elif defined(CHIP_SWM200)
void ADC0_Handler(void)
{
	uint32_t chn;
	
	ADC0->IF = (1 << ADC_IF_SEQ0EOC_Pos);
	
	printf("%4d,", ADC_Read(ADC0, ADC_SEQ0, &chn));
	
	ADC_Start(ADC0, ADC_SEQ0);
}
#endif


void SerialInit(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTA, PIN0, PORTA_PIN0_UART0_RX, 1);	//GPIOA.0配置为UART0 RXD
	PORT_Init(PORTA, PIN1, PORTA_PIN1_UART0_TX, 0);	//GPIOA.1配置为UART0 TXD
 	
 	UART_initStruct.Baudrate = 57600;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThresholdIEn = 0;
	UART_initStruct.TXThresholdIEn = 0;
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
