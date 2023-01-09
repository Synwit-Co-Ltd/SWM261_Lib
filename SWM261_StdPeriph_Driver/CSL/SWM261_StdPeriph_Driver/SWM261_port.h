#ifndef __SWM261_PORT_H__
#define __SWM261_PORT_H__

void PORT_Init(PORT_TypeDef * PORTx, uint32_t n, uint32_t func, uint32_t digit_in_en);	//端口引脚功能选择，其可取值如下：



#define PORTA_PIN0_GPIO         0
#define PORTA_PIN0_UART5_TX     1
#define PORTA_PIN0_PWM4B        2
#define PORTA_PIN0_HALL_IN1     3
#define PORTA_PIN0_ADC1_CH2     4
#define PORTA_PIN0_ACMP1_INP    7

#define PORTA_PIN1_GPIO         0
#define PORTA_PIN1_SPI0_DAT3    1
#define PORTA_PIN1_UART5_RX     2
#define PORTA_PIN1_PWM4A        3
#define PORTA_PIN1_HALL_IN2     4
#define PORTA_PIN1_TIMR2_IN     5
#define PORTA_PIN1_TIMR2_OUT    6
#define PORTA_PIN1_ADC1_CH1     7
#define PORTA_PIN1_ACMP2_INP    7

#define PORTA_PIN2_GPIO         0
#define PORTA_PIN2_JTAG_TMSSWIO 1
#define PORTA_PIN2_UART4_TX     2
#define PORTA_PIN2_BTIMR3_OUT   3

#define PORTA_PIN3_GPIO         0
#define PORTA_PIN3_SPI0_DAT2    1
#define PORTA_PIN3_PWM3B        2
#define PORTA_PIN3_BTIMR2_OUT   3

#define PORTA_PIN4_GPIO         0
#define PORTA_PIN4_JTAG_SWCLK   1
#define PORTA_PIN4_UART4_RX     2
#define PORTA_PIN4_BTIMR1_OUT   3

#define PORTA_PIN5_GPIO         0
#define PORTA_PIN5_SPI0_SSEL    1
#define PORTA_PIN5_PWM3A        2
#define PORTA_PIN5_BTIMR0_OUT   3
#define PORTA_PIN5_ADC1_CH0     7

#define PORTA_PIN6_GPIO         0
#define PORTA_PIN6_SPI0_MISO    1
#define PORTA_PIN6_UART2_RX     2
#define PORTA_PIN6_TIMR2_IN     3
#define PORTA_PIN6_TIMR2_OUT    4

#define PORTA_PIN7_GPIO         0
#define PORTA_PIN7_SPI0_MOSI    1
#define PORTA_PIN7_UART2_TX     2
#define PORTA_PIN7_PWM_CLK1     3
#define PORTA_PIN7_TIMR1_IN     4
#define PORTA_PIN7_TIMR1_OUT    5
#define PORTA_PIN7_ADC0_CH7     7

#define PORTA_PIN8_GPIO         0
#define PORTA_PIN8_SPI0_SCLK    1
#define PORTA_PIN8_TIMR0_IN     2
#define PORTA_PIN8_TIMR0_OUT    3
#define PORTA_PIN8_ADC0_CH6     7

#define PORTA_PIN9_GPIO         0
#define PORTA_PIN9_UART2_TX     1
#define PORTA_PIN9_PWM_BRK0     2
#define PORTA_PIN9_ADC0_CH5     7

#define PORTA_PIN10_GPIO        0
#define PORTA_PIN10_SPI1_SSEL   1
#define PORTA_PIN10_UART2_RX    2
#define PORTA_PIN10_TIMR0_IN    3
#define PORTA_PIN10_TIMR0_OUT   4
#define PORTA_PIN10_ADC0_CH4    7

#define PORTA_PIN11_GPIO        0
#define PORTA_PIN11_I2C5_SCL    1
#define PORTA_PIN11_SPI1_SCLK   2
#define PORTA_PIN11_UART5_CTS   3
#define PORTA_PIN11_PWM0A       4
#define PORTA_PIN11_TIMR2_IN    5
#define PORTA_PIN11_TIMR2_OUT   6
#define PORTA_PIN11_ADC0_CH3    7

#define PORTA_PIN12_GPIO        0
#define PORTA_PIN12_I2C5_SDA    1
#define PORTA_PIN12_SPI1_MOSI   2
#define PORTA_PIN12_UART1_TX    3
#define PORTA_PIN12_PWM0B       4
#define PORTA_PIN12_TIMR0_IN    5
#define PORTA_PIN12_TIMR0_OUT   6
#define PORTA_PIN12_ADC0_CH2    7

#define PORTA_PIN13_GPIO        0
#define PORTA_PIN13_SPI1_MISO   1
#define PORTA_PIN13_UART1_RX    2
#define PORTA_PIN13_TIMR1_IN    3
#define PORTA_PIN13_TIMR1_OUT   4
#define PORTA_PIN13_ADC0_CH1    7

#define PORTA_PIN14_GPIO        0
#define PORTA_PIN14_SPI1_DAT2   1
#define PORTA_PIN14_UART5_RTS   2
#define PORTA_PIN14_PWM_CLK1    3
#define PORTA_PIN14_RTC_OUT		5
#define PORTA_PIN14_ADC0_CH0    7

#define PORTA_PIN15_GPIO        0

#define PORTB_PIN0_GPIO         0
#define PORTB_PIN0_PWM_CLK0     1
#define PORTB_PIN0_ADC1_TRIG0   3

#define PORTB_PIN1_GPIO         0
#define PORTB_PIN1_SPI1_DAT2    1
#define PORTB_PIN1_PWM2A        2
#define PORTB_PIN1_XTAL_IN    	7

#define PORTB_PIN2_GPIO         0
#define PORTB_PIN2_SPI1_DAT3    1
#define PORTB_PIN2_PWM2B        2
#define PORTB_PIN2_XTAL_OUT   	7

#define PORTB_PIN3_GPIO         0
#define PORTB_PIN3_PWM4A        1

#define PORTB_PIN4_GPIO         0
#define PORTB_PIN4_TIMR3_IN     1
#define PORTB_PIN4_TIMR3_OUT    2
#define PORTB_PIN4_ACMP0_INN    3

#define PORTB_PIN5_GPIO         0
#define PORTB_PIN5_UART5_RX     1
#define PORTB_PIN5_PWM3BN       2
#define PORTB_PIN5_ACMP1_INN    3

#define PORTB_PIN6_GPIO         0
#define PORTB_PIN6_UART5_TX     1
#define PORTB_PIN6_PWM3AN       2
#define PORTB_PIN6_ACMP2_INN    3

#define PORTB_PIN7_GPIO         0
#define PORTB_PIN7_UART5_TX     1

#define PORTB_PIN8_GPIO         0
#define PORTB_PIN8_UART5_RX     1
#define PORTB_PIN8_PWM_BRK2     2
#define PORTB_PIN8_BTIMR3_OUT   3

#define PORTB_PIN9_GPIO         0
#define PORTB_PIN9_MPU_D15      1
#define PORTB_PIN9_SPI1_MISO    2
#define PORTB_PIN9_UART1_RX     3
#define PORTB_PIN9_PWM1BN       4
#define PORTB_PIN9_OPA2_INN     7

#define PORTB_PIN10_GPIO        0
#define PORTB_PIN10_MPU_RD		1
#define PORTB_PIN10_I2C5_SDA    2
#define PORTB_PIN10_SPI1_MOSI   3
#define PORTB_PIN10_UART1_TX    4
#define PORTB_PIN10_PWM1AN      5
#define PORTB_PIN10_OPA2_INP    7

#define PORTB_PIN11_GPIO        0
#define PORTB_PIN11_MPU_WR		1
#define PORTB_PIN11_I2C5_SCL    2
#define PORTB_PIN11_SPI1_SCLK   3
#define PORTB_PIN11_ADC1_CH5    7
#define PORTB_PIN11_OPA2_OUT    7

#define PORTB_PIN12_GPIO        0
#define PORTB_PIN12_MPU_RS		1
#define PORTB_PIN12_SPI1_MISO   2
#define PORTB_PIN12_UART3_RX    3
#define PORTB_PIN12_PWM4BN      4
#define PORTB_PIN12_TIMR1_IN    5
#define PORTB_PIN12_TIMR1_OUT   6
#define PORTB_PIN12_OPA3_INN    15

#define PORTB_PIN13_GPIO        0
#define PORTB_PIN13_MPU_CS		1
#define PORTB_PIN13_SPI1_MOSI   2
#define PORTB_PIN13_UART3_TX    3
#define PORTB_PIN13_PWM4AN      4
#define PORTB_PIN13_TIMR0_IN    5
#define PORTB_PIN13_TIMR0_OUT   6
#define PORTB_PIN13_OPA3_INP    15

#define PORTB_PIN14_GPIO        0
#define PORTB_PIN14_UART3_CTS   1
#define PORTB_PIN14_TIMR3_IN    2
#define PORTB_PIN14_TIMR3_OUT   3
#define PORTB_PIN14_ADC1_CH4	7
#define PORTB_PIN14_OPA3_OUT    7

#define PORTB_PIN15_GPIO        0
#define PORTB_PIN15_UART3_RTS   1
#define PORTB_PIN15_HALL_IN0    2
#define PORTB_PIN15_ADC1_CH3    3
#define PORTB_PIN15_ACMP0_INP   4

#define PORTC_PIN0_GPIO         0
#define PORTC_PIN0_MPU_D0       1
#define PORTC_PIN0_UART4_CTS    2
#define PORTC_PIN0_PWM_BRK1     3
#define PORTC_PIN0_ADC0_TRIG0   4

#define PORTC_PIN1_GPIO         0
#define PORTC_PIN1_MPU_D1       1
#define PORTC_PIN1_I2C4_SDA     2
#define PORTC_PIN1_UART4_RTS    3
#define PORTC_PIN1_PWM2B        4
#define PORTC_PIN1_TIMR0_IN     5
#define PORTC_PIN1_TIMR0_OUT    6

#define PORTC_PIN2_GPIO         0
#define PORTC_PIN2_MPU_D2       1
#define PORTC_PIN2_I2C4_SCL     2
#define PORTC_PIN2_PWM2A        3
#define PORTC_PIN2_TIMR1_IN     4
#define PORTC_PIN2_TIMR1_OUT    5

#define PORTC_PIN3_GPIO         0
#define PORTC_PIN3_MPU_D3       1
#define PORTC_PIN3_UART4_TX     2
#define PORTC_PIN3_PWM1B        3

#define PORTC_PIN4_GPIO         0
#define PORTC_PIN4_MPU_D4       1
#define PORTC_PIN4_UART4_RX     2
#define PORTC_PIN4_PWM1A        3

#define PORTC_PIN5_GPIO         0
#define PORTC_PIN5_MPU_D5       1
#define PORTC_PIN5_SPI0_MISO    2
#define PORTC_PIN5_UART3_RX     3
#define PORTC_PIN5_PWM_CLK0     4
#define PORTC_PIN5_HALL_IN2     5
#define PORTC_PIN5_TIMR0_IN     6
#define PORTC_PIN5_TIMR0_OUT    7
#define PORTC_PIN5_WAKEUP		15

#define PORTC_PIN6_GPIO         0
#define PORTC_PIN6_MPU_D6       1
#define PORTC_PIN6_SPI0_MOSI    2
#define PORTC_PIN6_UART3_TX     3
#define PORTC_PIN6_PWM3BN       4
#define PORTC_PIN6_TIMR1_IN     5
#define PORTC_PIN6_TIMR1_OUT    6
#define PORTC_PIN6_DAC_8B_OUT   7

#define PORTC_PIN7_GPIO         0
#define PORTC_PIN7_MPU_D7       1
#define PORTC_PIN7_PWM3AN       2
#define PORTC_PIN7_ACMP3_INN    3

#define PORTC_PIN8_GPIO         0
#define PORTC_PIN8_MPU_D8       1
#define PORTC_PIN8_UPDN_OUT     2
#define PORTC_PIN8_SPI0_MISO    3
#define PORTC_PIN8_UART2_RX     4
#define PORTC_PIN8_PWM_CLK1     5
#define PORTC_PIN8_HALL_IN1     6
#define PORTC_PIN8_TIMR1_IN     7
#define PORTC_PIN8_TIMR1_OUT    8
#define PORTC_PIN8_ACMP3_INP    15

#define PORTC_PIN9_GPIO         0
#define PORTC_PIN9_MPU_D9       1
#define PORTC_PIN9_SPI0_MOSI    2
#define PORTC_PIN9_UART2_TX     3
#define PORTC_PIN9_TIMR0_IN     4
#define PORTC_PIN9_TIMR0_OUT    5
#define PORTC_PIN9_DAC_12B_OUT  7

#define PORTC_PIN10_GPIO        0
#define PORTC_PIN10_MPU_D10     1
#define PORTC_PIN10_SPI0_SCLK   2
#define PORTC_PIN10_UART4_RX    3
#define PORTC_PIN10_PWM0AN      4
#define PORTC_PIN10_TIMR2_IN    5
#define PORTC_PIN10_TIMR2_OUT   6
#define PORTC_PIN10_ADC1_TRIG1  7
#define PORTC_PIN10_OPA0_INN    15

#define PORTC_PIN11_GPIO        0
#define PORTC_PIN11_MPU_D11     1
#define PORTC_PIN11_UART4_TX    2
#define PORTC_PIN11_PWM0BN      3
#define PORTC_PIN11_ADC0_TRIG1  4
#define PORTC_PIN11_OPA0_INP    7

#define PORTC_PIN12_GPIO        0
#define PORTC_PIN12_MPU_D12     1
#define PORTC_PIN12_INDEX_IN    2
#define PORTC_PIN12_I2C4_SCL    3
#define PORTC_PIN12_SPI1_SCLK   4
#define PORTC_PIN12_PWM3B       5
#define PORTC_PIN12_TIMR2_IN    6
#define PORTC_PIN12_TIMR2_OUT   7
#define PORTC_PIN12_ADC1_CH7	15
#define PORTC_PIN12_OPA0_OUT    15

#define PORTC_PIN13_GPIO        0
#define PORTC_PIN13_MPU_D13     1
#define PORTC_PIN13_QEB_IN      2
#define PORTC_PIN13_I2C4_SDA    3
#define PORTC_PIN13_SPI1_MOSI   4
#define PORTC_PIN13_UART0_TX    5
#define PORTC_PIN13_PWM_CLK0    6
#define PORTC_PIN13_HALL_IN0    7
#define PORTC_PIN13_TIMR0_IN    8
#define PORTC_PIN13_TIMR0_OUT   9
#define PORTC_PIN13_OPA1_INN    15

#define PORTC_PIN14_GPIO        0
#define PORTC_PIN14_MPU_D14     1
#define PORTC_PIN14_QEA_IN      2
#define PORTC_PIN14_SPI1_MISO   3
#define PORTC_PIN14_UART0_RX    4
#define PORTC_PIN14_PWM3A       5
#define PORTC_PIN14_TIMR1_IN    6
#define PORTC_PIN14_TIMR1_OUT   7
#define PORTC_PIN14_OPA1_INP    9

#define PORTC_PIN15_GPIO        0
#define PORTC_PIN15_OPA1_OUT    1

#define PORTD_PIN0_GPIO         0
#define PORTD_PIN0_UPDN_OUT     1
#define PORTD_PIN0_UART1_CTS    2
#define PORTD_PIN0_PWM2BN       3
#define PORTD_PIN0_BTIMR2_OUT   4

#define PORTD_PIN1_GPIO         0
#define PORTD_PIN1_INDEX_IN     1
#define PORTD_PIN1_UART1_RTS    2
#define PORTD_PIN1_PWM2AN       3
#define PORTD_PIN1_BTIMR1_OUT   4

#define PORTD_PIN2_GPIO         0
#define PORTD_PIN2_QEB_IN       1
#define PORTD_PIN2_UART2_CTS    2
#define PORTD_PIN2_PWM4BN       3
#define PORTD_PIN2_BTIMR0_OUT   4

#define PORTD_PIN3_GPIO         0
#define PORTD_PIN3_QEA_IN       1
#define PORTD_PIN3_UART2_RTS    2
#define PORTD_PIN3_PWM4AN       3
#define PORTD_PIN3_TIMR3_IN     4
#define PORTD_PIN3_TIMR3_OUT    5

#define PORTD_PIN4_GPIO         0
#define PORTD_PIN4_UART0_TX     1
#define PORTD_PIN4_TIMR3_IN     2
#define PORTD_PIN4_TIMR3_OUT    3

#define PORTD_PIN5_GPIO         0
#define PORTD_PIN5_UART0_RX     1
#define PORTD_PIN5_PWM4B        2

#define PORTD_PIN6_GPIO         0
#define PORTD_PIN6_SPI1_DAT3    1
#define PORTD_PIN6_UART0_CTS    2
#define PORTD_PIN6_PWM0A        3
#define PORTD_PIN6_TIMR3_IN     4
#define PORTD_PIN6_TIMR3_OUT    5

#define PORTD_PIN7_GPIO         0
#define PORTD_PIN7_UART0_RTS    1
#define PORTD_PIN7_PWM0B        2


#endif //__SWM261_PORT_H__
