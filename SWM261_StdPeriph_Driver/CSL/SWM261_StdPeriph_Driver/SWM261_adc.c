/****************************************************************************************************************************************** 
* �ļ�����:	SWM200_adc.c
* ����˵��:	SWM200��Ƭ����ADC��ģת��������������
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����: V1.0.0		2016��1��30��
* ������¼: 
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION 
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE 
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT 
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology  
*******************************************************************************************************************************************/
#include "SWM261.h"
#include "SWM261_adc.h"


/****************************************************************************************************************************************** 
* ��������: ADC_Init()
* ����˵��:	ADCģ��ת������ʼ��
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			ADC_InitStructure * initStruct		����ADC����ض�ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ADC_Init(ADC_TypeDef * ADCx, ADC_InitStructure * initStruct)
{	
	uint32_t i;
	
	switch((uint32_t)ADCx)
	{
	case ((uint32_t)ADC0):
		SYS->CLKSEL &= ~SYS_CLKSEL_ADC_Msk;
		SYS->CLKSEL |= ((initStruct->clk_src & 0xF) << SYS_CLKSEL_ADC_Pos);
		
		SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_ADC0_Pos);
		break;
	}
	
	ADC_Close(ADCx);		//һЩ�ؼ��Ĵ���ֻ����ADC�ر�ʱ����
	
	ADCx->CR |= (1 <<ADC_GO_RESET_Pos);
	for(i = 0; i < 120*20; i++) __NOP();	//����2������ʱ������
	ADCx->CR &= ~(1 << ADC_GO_RESET_Pos);
	
	ADCx->CR |= (0xF << ADC_CR_FFCLR_Pos);
	ADCx->CR &= ~(0xF << ADC_CR_FFCLR_Pos);
	
	ADCx->CR &= ~ADC_CR_AVG_Msk;
	ADCx->CR |= (initStruct->samplAvg << ADC_CR_AVG_Pos);
	
	ADCx->IE = 0;
	ADCx->IF = 0x3F3F3F3F;	//����жϱ�־
	
	ADCx->IE |= (((initStruct->EOC_IEn & ADC_SEQ0) ? 1 : 0) << ADC_IE_SEQ0EOC_Pos) |
				(((initStruct->EOC_IEn & ADC_SEQ1) ? 1 : 0) << ADC_IE_SEQ1EOC_Pos) |
				(((initStruct->EOC_IEn & ADC_SEQ2) ? 1 : 0) << ADC_IE_SEQ2EOC_Pos);
	
	ADCx->IE |= (((initStruct->HalfIEn & ADC_SEQ0) ? 1 : 0) << ADC_IE_SEQ0HALF_Pos) |
				(((initStruct->HalfIEn & ADC_SEQ1) ? 1 : 0) << ADC_IE_SEQ1HALF_Pos) |
				(((initStruct->HalfIEn & ADC_SEQ2) ? 1 : 0) << ADC_IE_SEQ2HALF_Pos);
	
	switch((uint32_t)ADCx)
	{
	case ((uint32_t)ADC0):
		if(initStruct->EOC_IEn | initStruct->HalfIEn) NVIC_EnableIRQ(ADC0_IRQn);
		break;
	}
}

static uint32_t ADC_seq2pos(uint32_t seq)
{
	uint32_t pos = 0;
	
	switch(seq)
	{
	case ADC_SEQ0: pos = 0;  break;
	case ADC_SEQ1: pos = 8;  break;
	case ADC_SEQ2: pos = 16; break;
	case ADC_SEQ3: pos = 24; break;
	}
	
	return pos;
}

/****************************************************************************************************************************************** 
* ��������: ADC_SEQ_Init()
* ����˵��:	ADC���г�ʼ��
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			uint32_t seq 			ָ��Ҫ���õ����У���Чֵ����ADC_SEQ0��ADC_SEQ1��ADC_SEQ2��ADC_SEQ3
*			ADC_SEQ_InitStructure * initStruct		����ADC�����趨��ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ADC_SEQ_Init(ADC_TypeDef * ADCx, uint32_t seq, ADC_SEQ_InitStructure * initStruct)
{
	uint32_t pos = ADC_seq2pos(seq);
	
	ADCx->SEQCHN &= ~(0xFFu << pos);
	ADCx->SEQCHN |= (initStruct->channels << pos);
	
	ADCx->SEQTRG &= ~(0xFFu << pos);
	ADCx->SEQTRG |= (initStruct->trig_src << pos);
	
	ADCx->SEQCOV &= ~(0xFFu << pos);
	ADCx->SEQCOV |= ((initStruct->conv_cnt ? initStruct->conv_cnt - 1 : 0) << pos);
	
	ADCx->SEQSMP &= ~(0xFFu << pos);
	ADCx->SEQSMP |= (initStruct->samp_tim << pos);
}

/****************************************************************************************************************************************** 
* ��������: ADC_CMP_Init()
* ����˵��:	ADC�ȽϹ��ܳ�ʼ��
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			uint32_t seq 			ָ��Ҫ���õ����У���Чֵ����ADC_SEQ0��ADC_SEQ1��ADC_SEQ2��ADC_SEQ3
*			ADC_CMP_InitStructure * initStruct		����ADC�ȽϹ����趨��ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ADC_CMP_Init(ADC_TypeDef * ADCx, uint32_t seq, ADC_CMP_InitStructure * initStruct)
{
	uint32_t idx;
	uint32_t pos = ADC_seq2pos(seq);
	
	idx = pos / 8;
	ADCx->SEQ[idx].CMP = (initStruct->UpperLimit << ADC_CMP_MAX_Pos) |
						 (initStruct->LowerLimit << ADC_CMP_MIN_Pos);
	
	if(initStruct->UpperLimitIEn) ADCx->IE |= (1 << (pos + 4));
	else                          ADCx->IE &= ~(1 << (pos + 4));
	
	if(initStruct->LowerLimitIEn) ADCx->IE |= (1 << (pos + 5));
	else                          ADCx->IE &= ~(1 << (pos + 5));
	
	if(initStruct->UpperLimitIEn || initStruct->LowerLimitIEn)
	{
		switch((uint32_t)ADCx)
		{
		case ((uint32_t)ADC0): NVIC_EnableIRQ(ADC0_IRQn); break;
		}
	}
}

/****************************************************************************************************************************************** 
* ��������:	ADC_Open()
* ����˵��:	ADC����������������������Ӳ������ADCת��
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ADC_Open(ADC_TypeDef * ADCx)
{	
	ADCx->CR |= (0x01 << ADC_CR_EN_Pos);
}


/****************************************************************************************************************************************** 
* ��������:	ADC_Close()
* ����˵��:	ADC�رգ��޷�������������Ӳ������ADCת��
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ADC_Close(ADC_TypeDef * ADCx)
{
	ADCx->CR &= ~(0x01 << ADC_CR_EN_Pos);
}

/****************************************************************************************************************************************** 
* ��������:	ADC_Start()
* ����˵��:	��������ģʽ������ADCת��
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			uint32_t seq			ָ��Ҫ���õ�ADC���У���ЧֵΪADC_SEQ0��ADC_SEQ1��ADC_SEQ2��ADC_SEQ3������ϣ�������λ�����㣩
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ADC_Start(ADC_TypeDef * ADCx, uint32_t seq)
{
	if(ADCx == ADC0)
		ADCx->GO |= (seq << ADC_GO_ADC0SEQ0_Pos);
	else
		ADCx->GO |= (seq << ADC_GO_ADC1SEQ0_Pos);
}

/****************************************************************************************************************************************** 
* ��������:	ADC_Stop()
* ����˵��:	��������ģʽ��ֹͣADCת��
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			uint32_t seq			ָ��Ҫ���õ�ADC���У���ЧֵΪADC_SEQ0��ADC_SEQ1��ADC_SEQ2��ADC_SEQ3������ϣ�������λ�����㣩
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ADC_Stop(ADC_TypeDef * ADCx, uint32_t seq)
{									 
	if(ADCx == ADC0)
		ADCx->GO &= ~(seq << ADC_GO_ADC0SEQ0_Pos);
	else
		ADCx->GO &= ~(seq << ADC_GO_ADC1SEQ0_Pos);
}

/****************************************************************************************************************************************** 
* ��������:	ADC_Read()
* ����˵��:	��ָ�����ж�ȡת�����
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			uint32_t seq			ָ��Ҫ���õ�ADC���У���ЧֵΪADC_SEQ0��ADC_SEQ1��ADC_SEQ2��ADC_SEQ3
*			uint32_t *chn			ת����������ĸ�ͨ����ADC_CH0��ADC_CH1��... ...��ADC_CH14��ADC_CH15
* ��    ��: uint32_t				��ȡ����ת�����
* ע������: ��
******************************************************************************************************************************************/
uint32_t ADC_Read(ADC_TypeDef * ADCx, uint32_t seq, uint32_t *chn)
{
	uint32_t idx = ADC_seq2pos(seq) / 8;
	
	uint32_t reg = ADCx->SEQ[idx].DR;
	
	*chn = 1 << ((reg & ADC_DR_CHNUM_Msk) >> ADC_DR_CHNUM_Pos);
	
	return reg & ADC_DR_VALUE_Msk;
}

/****************************************************************************************************************************************** 
* ��������:	ADC_DataAvailable()
* ����˵��:	ָ�������Ƿ������ݿɶ�ȡ
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			uint32_t seq			ָ��Ҫ���õ�ADC���У���ЧֵΪADC_SEQ0��ADC_SEQ1��ADC_SEQ2��ADC_SEQ3
* ��    ��: uint32_t				1 �����ݿɶ�ȡ    0 ������
* ע������: ��
******************************************************************************************************************************************/
uint32_t ADC_DataAvailable(ADC_TypeDef * ADCx, uint32_t seq)
{
	uint32_t idx = ADC_seq2pos(seq) / 8;
	
	return (ADCx->SEQ[idx].SR & ADC_SR_EMPTY_Msk) ? 0 : 1;
}


/****************************************************************************************************************************************** 
* ��������:	ADC_INTEn()
* ����˵��:	�ж�ʹ��
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			uint32_t seq			ָ��Ҫ���õ�ADC���У���ЧֵΪADC_SEQ0��ADC_SEQ1��ADC_SEQ2��ADC_SEQ3
* 			uint32_t it				interrupt type����Чֵ����ADC_IT_EOC��ADC_IT_FIFO_OVF��ADC_IT_FIFO_HALF��ADC_IT_FIFO_FULL��
*											ADC_IT_CMP_MAX��ADC_IT_CMP_MIN ���䡰��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ADC_INTEn(ADC_TypeDef * ADCx, uint32_t seq, uint32_t it)
{
	uint32_t pos = ADC_seq2pos(seq);
	
	ADCx->IE |= (it << pos);
}

/****************************************************************************************************************************************** 
* ��������:	ADC_INTDis()
* ����˵��:	�жϽ�ֹ
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			uint32_t seq			ָ��Ҫ���õ�ADC���У���ЧֵΪADC_SEQ0��ADC_SEQ1��ADC_SEQ2��ADC_SEQ3
* 			uint32_t it				interrupt type����Чֵ����ADC_IT_EOC��ADC_IT_FIFO_OVF��ADC_IT_FIFO_HALF��ADC_IT_FIFO_FULL��
*											ADC_IT_CMP_MAX��ADC_IT_CMP_MIN ���䡰��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ADC_INTDis(ADC_TypeDef * ADCx, uint32_t seq, uint32_t it)
{
	uint32_t pos = ADC_seq2pos(seq);
	
	ADCx->IE &= ~(it << pos);
}

/****************************************************************************************************************************************** 
* ��������:	ADC_INTClr()
* ����˵��:	�жϱ�־���
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			uint32_t seq			ָ��Ҫ���õ�ADC���У���ЧֵΪADC_SEQ0��ADC_SEQ1��ADC_SEQ2��ADC_SEQ3
* 			uint32_t it				interrupt type����Чֵ����ADC_IT_EOC��ADC_IT_FIFO_OVF��ADC_IT_FIFO_HALF��ADC_IT_FIFO_FULL��
*											ADC_IT_CMP_MAX��ADC_IT_CMP_MIN ���䡰��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void ADC_INTClr(ADC_TypeDef * ADCx, uint32_t seq, uint32_t it)
{
	uint32_t pos = ADC_seq2pos(seq);
	
	ADCx->IF = (it << pos);
}

/****************************************************************************************************************************************** 
* ��������:	ADC_INTStat()
* ����˵��:	�ж�״̬��ѯ
* ��    ��: ADC_TypeDef * ADCx		ָ��Ҫ���õ�ADC����Чֵ����ADC0
*			uint32_t seq			ָ��Ҫ��ѯ��ADC���У���ЧֵΪADC_SEQ0��ADC_SEQ1��ADC_SEQ2��ADC_SEQ3
* 			uint32_t it				interrupt type����Чֵ����ADC_IT_EOC��ADC_IT_FIFO_OVF��ADC_IT_FIFO_HALF��ADC_IT_FIFO_FULL��
*											ADC_IT_CMP_MAX��ADC_IT_CMP_MIN ���䡰��
* ��    ��: uint32_t					1 �жϷ���    0 �ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint32_t ADC_INTStat(ADC_TypeDef * ADCx, uint32_t seq, uint32_t it)
{
	uint32_t pos = ADC_seq2pos(seq);
	
	return (ADCx->IF & (it << pos)) ? 1 : 0;
}