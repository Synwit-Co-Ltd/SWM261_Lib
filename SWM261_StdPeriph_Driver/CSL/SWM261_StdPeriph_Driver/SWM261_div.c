/****************************************************************************************************************************************** 
* �ļ�����: SWM261_div.c
* ����˵��:	SWM261��Ƭ����DIVӲ����������������
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����:	V1.0.0		2016��1��30��
* ������¼:  
*
*
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
#include "SWM261_div.h"


/****************************************************************************************************************************************** 
* ��������:	DIV_Init()
* ����˵��:	Ӳ����������ʼ��
* ��    ��: DIV_TypeDef * DIVx	ָ��Ҫ�����õ�Ӳ������������Чֵ����DIV0��DIV1
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void DIV_Init(DIV_TypeDef * DIVx)
{
	switch((uint32_t)DIVx)
	{
	case ((uint32_t)DIV0):
//		SYS->CLKEN0 |= (0x01u<< SYS_CLKEN0_DIV0_Pos);
		break;
	
	case ((uint32_t)DIV1):
//		SYS->CLKEN0 |= (0x01u<< SYS_CLKEN0_DIV0_Pos);
		break;
	}
}