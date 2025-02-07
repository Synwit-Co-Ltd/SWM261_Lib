#include "SWM261.h"

#include "ST7789.h"


/****************************************************************************************************************************************** 
* ��������:	ST7789_Init()
* ����˵��: TFTҺ������ʼ����TFTʹ��ST7789�������ֱ���320*240��ʹ�� ZJY320P1600TG11 ����
* ��    ��: ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ST7789_Init(void)
{
	MPU_InitStructure MPU_initStruct;
	
	PORT_Init(PORTA, PIN8,  PORTA_PIN8_MPU_D0,  1);
	PORT_Init(PORTA, PIN9,  PORTA_PIN9_MPU_D1,  1);
	PORT_Init(PORTA, PIN10, PORTA_PIN10_MPU_D2, 1);
	PORT_Init(PORTA, PIN11, PORTA_PIN11_MPU_D3, 1);
	PORT_Init(PORTA, PIN12, PORTA_PIN12_MPU_D4, 1);
	PORT_Init(PORTA, PIN13, PORTA_PIN13_MPU_D5, 1);
	PORT_Init(PORTA, PIN14, PORTA_PIN14_MPU_D6, 1);
	PORT_Init(PORTA, PIN0,  PORTA_PIN0_MPU_D7,  1);
	
	PORT_Init(PORTB, PIN4,  PORTB_PIN4_MPU_CS,  0);
	PORT_Init(PORTB, PIN5,  PORTB_PIN5_MPU_RS,  0);
	PORT_Init(PORTB, PIN6,  PORTB_PIN6_MPU_WR,  0);
	PORT_Init(PORTB, PIN9,  PORTB_PIN9_MPU_RD,  0);
	
	MPU_initStruct.ByteOrder = MPU_BIG_ENDIAN;
	MPU_initStruct.RDHoldTime = 2;
	MPU_initStruct.WRHoldTime = 2;
	MPU_initStruct.CSFall_WRFall = 1;
	MPU_initStruct.WRRise_CSRise = 1;
	MPU_initStruct.RDCSRise_Fall = 2;
	MPU_initStruct.WRCSRise_Fall = 2;
	MPU_Init(MPU, &MPU_initStruct);
	
	GPIO_Init(GPIOB, PIN2, 1, 0, 0, 0);		//��Ļ����
	GPIO_SetBit(GPIOB, PIN2);
	GPIO_Init(GPIOB, PIN3, 1, 0, 0, 0);		//��Ļ��λ
	GPIO_ClrBit(GPIOB, PIN3);
	for(int i = 0; i < 1000000; i++) __NOP();
	GPIO_SetBit(GPIOB, PIN3);
	for(int i = 0; i < 1000000; i++) __NOP();
	
	
	uint32_t id = MPU_ReadReg(MPU, 0x04);	// dummy read
	id  = MPU->DRB << 16;
	id |= MPU->DRB <<  8;
	id |= MPU->DRB <<  0;
	if(id != 0x858552)
	{
		printf("ID = %06X, not ST7789V\n", id);
	}
	
	
	MPU_WR_REG8(MPU, 0x11);		// Sleep out
	
	MPU_WR_REG8(MPU, 0x36);		// Memory Access Control
	MPU_WR_DATA8(MPU, 0x00);
	
	MPU_WR_REG8(MPU, 0x3A);		// Interface pixel format
	MPU_WR_DATA8(MPU, 0x05);
	
	//--------------------------------ST7789S Frame rate setting-------------------------
	MPU_WR_REG8(MPU, 0xb2);
	MPU_WR_DATA8(MPU, 0x0c);
	MPU_WR_DATA8(MPU, 0x0c);
	MPU_WR_DATA8(MPU, 0x00);
	MPU_WR_DATA8(MPU, 0x33);
	MPU_WR_DATA8(MPU, 0x33);
	
	MPU_WR_REG8(MPU, 0xb7);
	MPU_WR_DATA8(MPU, 0x35);
	
	//---------------------------------ST7789S Power setting-----------------------------
	MPU_WR_REG8(MPU, 0xbb);
	MPU_WR_DATA8(MPU, 0x20);
	
	MPU_WR_REG8(MPU, 0xc0);
	MPU_WR_DATA8(MPU, 0x2c);
	
	MPU_WR_REG8(MPU,0xc2);
	MPU_WR_DATA8(MPU, 0x01);
	
	MPU_WR_REG8(MPU, 0xc3);
	MPU_WR_DATA8(MPU, 0x0b);
	
	MPU_WR_REG8(MPU, 0xc4);
	MPU_WR_DATA8(MPU, 0x20);
	
	MPU_WR_REG8(MPU, 0xc6);
	MPU_WR_DATA8(MPU, 0x0f);
	
	MPU_WR_REG8(MPU, 0xd0);
	MPU_WR_DATA8(MPU, 0xa4);
	MPU_WR_DATA8(MPU, 0xa1);

	//--------------------------------ST7789S Gamma setting------------------------------
	MPU_WR_REG8(MPU, 0xe0);
	MPU_WR_DATA8(MPU, 0xd0);
	MPU_WR_DATA8(MPU, 0x03);
	MPU_WR_DATA8(MPU, 0x09);
	MPU_WR_DATA8(MPU, 0x0e);
	MPU_WR_DATA8(MPU, 0x11);
	MPU_WR_DATA8(MPU, 0x3d);
	MPU_WR_DATA8(MPU, 0x47);
	MPU_WR_DATA8(MPU, 0x55);
	MPU_WR_DATA8(MPU, 0x53);
	MPU_WR_DATA8(MPU, 0X1A);
	MPU_WR_DATA8(MPU, 0x16);
	MPU_WR_DATA8(MPU, 0x14);
	MPU_WR_DATA8(MPU, 0x1F);
	MPU_WR_DATA8(MPU, 0x22);
	
	MPU_WR_REG8(MPU, 0xe1);
	MPU_WR_DATA8(MPU, 0xd0);
	MPU_WR_DATA8(MPU, 0x02);
	MPU_WR_DATA8(MPU, 0x08);
	MPU_WR_DATA8(MPU, 0x0D);
	MPU_WR_DATA8(MPU, 0x12);
	MPU_WR_DATA8(MPU, 0x2c);
	MPU_WR_DATA8(MPU, 0x43);
	MPU_WR_DATA8(MPU, 0x55);
	MPU_WR_DATA8(MPU, 0x53);
	MPU_WR_DATA8(MPU, 0x1E);
	MPU_WR_DATA8(MPU, 0x1B);
	MPU_WR_DATA8(MPU, 0x19);
	MPU_WR_DATA8(MPU, 0x20);
	MPU_WR_DATA8(MPU, 0x22);
	
	MPU_WR_REG8(MPU, 0x29);
}


/****************************************************************************************************************************************** 
* ��������: ST7789_SetCursor()
* ����˵��: 
* ��    ��: 
* ��    ��: 
* ע������: 
******************************************************************************************************************************************/
void ST7789_SetCursor(uint16_t x, uint16_t y)
{
	MPU_WR_REG8(MPU, 0x2A);
	MPU_WR_DATA16(MPU, x);
	
	MPU_WR_REG8(MPU, 0x2B);
	MPU_WR_DATA16(MPU, y);
}

/****************************************************************************************************************************************** 
* ��������: ST7789_DrawPoint()
* ����˵��: 
* ��    ��: 
* ��    ��: 
* ע������: 
******************************************************************************************************************************************/
void ST7789_DrawPoint(uint16_t x, uint16_t y, uint16_t rgb)
{
	ST7789_SetCursor(x, y);
	
	MPU_WR_REG8(MPU, 0x2C);
	MPU_WR_DATA16(MPU, rgb);
}

/****************************************************************************************************************************************** 
* ��������: ST7789_Clear()
* ����˵��: 
* ��    ��: 
* ��    ��: 
* ע������: 
******************************************************************************************************************************************/
void ST7789_Clear(uint16_t rgb)
{
	uint32_t i, j;
	
	ST7789_SetCursor(0, 0);
	
	MPU_WR_REG8(MPU, 0x2C);
	
	for(i = 0; i < LCD_VPIX; i++)
	{
		for(j = 0; j < LCD_HPIX; j++)
		{
			MPU_WR_DATA16(MPU, rgb);
		}
	}
}

static uint32_t MPUDMA_Color;
/****************************************************************************************************************************************** 
* ��������: ST7789_DMAClear()
* ����˵��: ������ x, y ����ʼ������ɫ rgb ��� n_rgb �����ص�
* ��    ��: 
* ��    ��: 
* ע������: ���� DMA ������ 65535 �����ݣ��޷�һ�����������Ļ��ֻ��һ�顢һ������
******************************************************************************************************************************************/
void ST7789_DMAClear(uint16_t x, uint16_t y, uint16_t rgb, uint16_t n_rgb)
{
	DMA_InitStructure DMA_initStruct;
	
	MPUDMA_Color = rgb;
	
	ST7789_SetCursor(x, y);
	
	DMA_initStruct.Mode = DMA_MODE_SINGLE;
	DMA_initStruct.Unit = DMA_UNIT_HALFWORD;
	DMA_initStruct.Count = n_rgb;
	DMA_initStruct.MemoryAddr = (uint32_t)&MPUDMA_Color;
	DMA_initStruct.MemoryAddrInc = 0;
	DMA_initStruct.PeripheralAddr = (uint32_t)&MPU->DRH;
	DMA_initStruct.PeripheralAddrInc = 0;
	DMA_initStruct.Handshake = DMA_CH1_MPUTX;
	DMA_initStruct.Priority = DMA_PRI_LOW;
	DMA_initStruct.INTEn = 0;
	DMA_CH_Init(DMA_CH1, &DMA_initStruct);
	DMA_CH_Open(DMA_CH1);
	
	MPU->SR |= MPU_SR_DMAEN_Msk;
	
	MPU->IRB = 0x2C;
}


uint32_t ST7789_DMADone(void)
{
	if(DMA_CH_INTStat(DMA_CH1, DMA_IT_DONE))
	{
		DMA_CH_INTClr(DMA_CH1, DMA_IT_DONE);
		
		MPU->SR &= ~MPU_SR_DMAEN_Msk;
		
		return 1;
	}
	else
	{
		return 0;
	}
}
