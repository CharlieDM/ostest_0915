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

	ADC_DeInit(ADC1);  													//��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;								//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);									//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���  

	ADC_Cmd(ADC1, ENABLE);						//ʹ��ָ����ADC1 	
	ADC_ResetCalibration(ADC1);					//ʹ�ܸ�λУ׼ 	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼���� 	
	ADC_StartCalibration(ADC1);	 				//����ADУ׼  
	while(ADC_GetCalibrationStatus(ADC1));		//�ȴ�У׼����
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
