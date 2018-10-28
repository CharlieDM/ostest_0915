#include "adc.h"
#include "delay.h"
	   															   
void adc_init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1, ENABLE );	 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  	 
                      
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;						
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  													//复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;								//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);									//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器  

	ADC_Cmd(ADC1, ENABLE);						//使能指定的ADC1 	
	ADC_ResetCalibration(ADC1);					//使能复位校准 	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束 	
	ADC_StartCalibration(ADC1);	 				//开启AD校准  
	while(ADC_GetCalibrationStatus(ADC1));		//等待校准结束
}
				  
u16 get_adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );			     
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);					 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));	
	return ADC_GetConversionValue(ADC1);
}

u16 get_adc_avg(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=get_adc(ch);
		delay_ms(1);
	}
	return temp_val/times;
} 	
