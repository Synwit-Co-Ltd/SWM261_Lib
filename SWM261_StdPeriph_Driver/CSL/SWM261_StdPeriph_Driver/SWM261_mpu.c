/****************************************************************************************************************************************** 
* 文件名称: SWM261_mpu.c
* 功能说明:	SWM261单片机的MPU屏控制器功能驱动库
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项: 
* 版本日期:	V1.0.0		2016年1月30日
* 升级记录:  
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
#include "SWM261_mpu.h"


/****************************************************************************************************************************************** 
* 函数名称:	MPU_Init()
* 功能说明:	MPU LCD初始化
* 输    入: MPU_TypeDef * MPUx	指定要被设置的MPU，有效值包括MPU
*			MPU_InitStructure * initStruct    包含MPU LCD相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void MPU_Init(MPU_TypeDef * MPUx, MPU_InitStructure * initStruct)
{
	switch((uint32_t)MPUx)
	{
	case ((uint32_t)MPU):
		SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_MPU_Pos);
		__NOP();__NOP();__NOP();
		break;
	}
	
	MPUx->SR = initStruct->ByteOrder << MPU_SR_ENDIAN_Pos;
	
	MPUx->CR = ((initStruct->RDHoldTime    - 1) << MPU_CR_RDHOLD_Pos) |
			   ((initStruct->WRHoldTime    - 1) << MPU_CR_WRHOLD_Pos) |
			   ((initStruct->CSFall_WRFall - 1) << MPU_CR_CS0WR0_Pos) |
			   ((initStruct->WRRise_CSRise - 1) << MPU_CR_WR1CS1_Pos) |
			   ((initStruct->RDCSRise_Fall - 1) << MPU_CR_RCS1_0_Pos) |
			   ((initStruct->WRCSRise_Fall - 1) << MPU_CR_WCS1_0_Pos);
}


static uint32_t MPU_IsBusy(MPU_TypeDef * MPUx)
{
	return (MPUx->SR & MPU_SR_BUSY_Msk);
}


void MPU_WR_REG8(MPU_TypeDef * MPUx, uint8_t reg)
{
	MPUx->IRB = reg;
	__NOP(); __NOP(); __NOP();
	while(MPU_IsBusy(MPUx)) __NOP();
}

void MPU_WR_DATA8(MPU_TypeDef * MPUx, uint8_t val)
{
	MPUx->DRB = val;
	__NOP(); __NOP(); __NOP();
	while(MPU_IsBusy(MPUx)) __NOP();
}

void MPU_WR_DATA16(MPU_TypeDef * MPUx, uint16_t val)
{
	MPUx->DRH = val;
	__NOP(); __NOP(); __NOP();
	while(MPU_IsBusy(MPUx)) __NOP();
}

void MPU_WriteReg(MPU_TypeDef * MPUx, uint8_t reg, uint8_t val)
{
	MPU_WR_REG8(MPUx, reg);
	
	MPU_WR_DATA8(MPUx, val);
}

uint8_t MPU_ReadReg(MPU_TypeDef * MPUx, uint8_t reg)
{
	MPU_WR_REG8(MPUx, reg);
	
	return MPUx->DRB;
}
