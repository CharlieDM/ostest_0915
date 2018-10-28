#include "sys.h"
#include "io.h"
#include "74HC595.h"
#include "delay.h"

#define HC595_TIME      (40)

#define A595_DAT		A595_DAT_PORT, A595_DAT_PIN
#define A595_SRCLK		A595_SRCLK_PORT, A595_SRCLK_PIN
#define A595_RCLK		A595_RCLK_PORT, A595_RCLK_PIN

#define B595_DAT		B595_DAT_PORT, B595_DAT_PIN
#define B595_SRCLK		B595_SRCLK_PORT, B595_SRCLK_PIN
#define B595_RCLK		B595_RCLK_PORT, B595_RCLK_PIN

#define C595_DAT		C595_DAT_PORT, C595_DAT_PIN
#define C595_SRCLK		C595_SRCLK_PORT, C595_SRCLK_PIN
#define C595_RCLK		C595_RCLK_PORT, C595_RCLK_PIN

#define D595_DAT		D595_DAT_PORT, D595_DAT_PIN
#define D595_SRCLK		D595_SRCLK_PORT, D595_SRCLK_PIN
#define D595_RCLK		D595_RCLK_PORT, D595_RCLK_PIN

#define E595_DAT		E595_DAT_PORT, E595_DAT_PIN
#define	E595_SRCLK		E595_SRCLK_PORT, E595_SRCLK_PIN
#define E595_RCLK		E595_RCLK_PORT, E595_RCLK_PIN

#define F595_DAT		F595_DAT_PORT, F595_DAT_PIN
#define F595_SRCLK		F595_SRCLK_PORT, F595_SRCLK_PIN
#define F595_RCLK		F595_RCLK_PORT, F595_RCLK_PIN

#define G595_DAT		G595_DAT_PORT, G595_DAT_PIN
#define G595_SRCLK		G595_SRCLK_PORT, G595_SRCLK_PIN
#define G595_RCLK		G595_RCLK_PORT, G595_RCLK_PIN

#define H595_DAT		H595_DAT_PORT, H595_DAT_PIN
#define H595_SRCLK		H595_SRCLK_PORT, H595_SRCLK_PIN
#define H595_RCLK		H595_RCLK_PORT, H595_RCLK_PIN

#define PWR595_DAT		PWR595_DAT_PORT, PWR595_DAT_PIN
#define PWR595_SRCLK	PWR595_SRCLK_PORT, PWR595_SRCLK_PIN
#define PWR595_RCLK		PWR595_RCLK_PORT, PWR595_RCLK_PIN

#define T595_DAT		T595_DAT_PORT, T595_DAT_PIN
#define T595_SRCLK		T595_SRCLK_PORT, T595_SRCLK_PIN
#define T595_RCLK		T595_RCLK_PORT, T595_RCLK_PIN

//HC595数据发送
void HC595SendData(HC595_TYPE type, uint16_t data)
{
	uint8_t i;
	if(type == SW1_A)
	{
        data = 32 - data;
		for(i=0; i<32; i++)
		{	            
			//Step 1: 将数据传送到DAT脚
			if(i == data)
				GPIO_ResetBits(A595_DAT);
			else
				GPIO_SetBits(A595_DAT);				
			//Step 2: SCLK发生一次上升沿，从DAT引脚取出数据
			GPIO_ResetBits(A595_SRCLK);
			delay_us(HC595_TIME);
			GPIO_SetBits(A595_SRCLK);
		}
		//Step 3：RCLK发生一次上升沿，把数据发出去
		GPIO_ResetBits(A595_RCLK);	
		delay_us(HC595_TIME);
		GPIO_SetBits(A595_RCLK);			
	}
	else if(type == SW1_B)
	{
        data = 32 - data;
		for(i=0; i<32; i++)
		{	
			//Step 1: 将数据传送到DAT脚
			if(i == data)
				GPIO_ResetBits(B595_DAT);
			else					
                GPIO_SetBits(B595_DAT);
			//Step 2: SCLK发生一次上升沿，从DAT引脚取出数据
			GPIO_ResetBits(B595_SRCLK);
			delay_us(HC595_TIME);
			GPIO_SetBits(B595_SRCLK);
		}
		//Step 3：RCLK发生一次上升沿，把数据发出去
		GPIO_ResetBits(B595_RCLK);	
		delay_us(HC595_TIME);
		GPIO_SetBits(B595_RCLK);			
	}
	else if(type == SW2_A)
	{
        data = 32 - data;
		for(i=0; i<32; i++)
		{	
			//Step 1: 将数据传送到DAT脚
			if(i == data)
				GPIO_ResetBits(C595_DAT);
			else
				GPIO_SetBits(C595_DAT);				
			//Step 2: SCLK发生一次上升沿，从DAT引脚取出数据
			GPIO_ResetBits(C595_SRCLK);
			delay_us(HC595_TIME);
			GPIO_SetBits(C595_SRCLK);
		}
		//Step 3：RCLK发生一次上升沿，把数据发出去
		GPIO_ResetBits(C595_RCLK);	
		delay_us(HC595_TIME);
		GPIO_SetBits(C595_RCLK);			
	}	
	else if(type == SW2_B)
	{
        data = 32 - data;
		for(i=0; i<32; i++)
		{	
			//Step 1: 将数据传送到DAT脚
			if(i == data)
				GPIO_ResetBits(D595_DAT);
			else
				GPIO_SetBits(D595_DAT);				
			//Step 2: SCLK发生一次上升沿，从DAT引脚取出数据
			GPIO_ResetBits(D595_SRCLK);
			delay_us(HC595_TIME);
			GPIO_SetBits(D595_SRCLK);
		}
		//Step 3：RCLK发生一次上升沿，把数据发出去
		GPIO_ResetBits(D595_RCLK);	
		delay_us(HC595_TIME);
		GPIO_SetBits(D595_RCLK);			
	}	
	else if(type == SW3_A)
	{
        data = 32 - data;
		for(i=0; i<32; i++)
		{	
			//Step 1: 将数据传送到DAT脚
			if(i == data)
				GPIO_ResetBits(E595_DAT);
			else
				GPIO_SetBits(E595_DAT);				
			//Step 2: SCLK发生一次上升沿，从DAT引脚取出数据
			GPIO_ResetBits(E595_SRCLK);
			delay_us(HC595_TIME);
			GPIO_SetBits(E595_SRCLK);
		}
		//Step 3：RCLK发生一次上升沿，把数据发出去
		GPIO_ResetBits(E595_RCLK);	
		delay_us(HC595_TIME);
		GPIO_SetBits(E595_RCLK);		
	}	
	else if(type == SW3_B)
	{
        data = 32 - data;
		for(i=0; i<32; i++)
		{	
			//Step 1: 将数据传送到DAT脚
			if(i == data)
				GPIO_ResetBits(F595_DAT);
			else
				GPIO_SetBits(F595_DAT);				
			//Step 2: SCLK发生一次上升沿，从DAT引脚取出数据
			GPIO_ResetBits(F595_SRCLK);
			delay_us(HC595_TIME);
			GPIO_SetBits(F595_SRCLK);
		}
		//Step 3：RCLK发生一次上升沿，把数据发出去
		GPIO_ResetBits(F595_RCLK);	
		delay_us(HC595_TIME);
		GPIO_SetBits(F595_RCLK);			
	}	
	else if(type == SW4_A)
	{
        data = 32 - data;
		for(i=0; i<32; i++)
		{	
			//Step 1: 将数据传送到DAT脚
			if(i == data)
				GPIO_ResetBits(G595_DAT);
			else
				GPIO_SetBits(G595_DAT);				
			//Step 2: SCLK发生一次上升沿，从DAT引脚取出数据
			GPIO_ResetBits(G595_SRCLK);
			delay_us(HC595_TIME);
			GPIO_SetBits(G595_SRCLK);
		}
		//Step 3：RCLK发生一次上升沿，把数据发出去
		GPIO_ResetBits(G595_RCLK);	
		delay_us(HC595_TIME);
		GPIO_SetBits(G595_RCLK);			
	}	
	else if(type == SW4_B)
	{
        data = 32 - data;
		for(i=0; i<32; i++)
		{	
			//Step 1: 将数据传送到DAT脚
			if(i == data)
				GPIO_ResetBits(H595_DAT);
			else
				GPIO_SetBits(H595_DAT);				
			//Step 2: SCLK发生一次上升沿，从DAT引脚取出数据
			GPIO_ResetBits(H595_SRCLK);
			delay_us(HC595_TIME);
			GPIO_SetBits(H595_SRCLK);
		}
		//Step 3：RCLK发生一次上升沿，把数据发出去
		GPIO_ResetBits(H595_RCLK);	
		delay_us(HC595_TIME);
		GPIO_SetBits(H595_RCLK);				
	}	
	else if(type == PWR_OUT)
	{
		for(i=0; i<8; i++)
		{	
			//Step 1: 将数据传送到DAT脚
			if((data<<i)&0x80)
				GPIO_SetBits(PWR595_DAT);
			else
				GPIO_ResetBits(PWR595_DAT);				
			//Step 2: SCLK发生一次上升沿，从DAT引脚取出数据
			GPIO_ResetBits(PWR595_SRCLK);
			delay_us(HC595_TIME);
			GPIO_SetBits(PWR595_SRCLK);
		}
		//Step 3：RCLK发生一次上升沿，把数据发出去
		GPIO_ResetBits(PWR595_RCLK);	
		delay_us(HC595_TIME);
		GPIO_SetBits(PWR595_RCLK);			
	}	
	else if(type == SW_OTHER)
	{
		for(i=0; i<8; i++)
		{	
			//Step 1: 将数据传送到DAT脚
			if((data<<i)&0x80)
				GPIO_ResetBits(T595_DAT);
			else
				GPIO_SetBits(T595_DAT);				
			//Step 2: SCLK发生一次上升沿，从DAT引脚取出数据
			GPIO_ResetBits(T595_SRCLK);
			delay_us(HC595_TIME);
			GPIO_SetBits(T595_SRCLK);
		}
		//Step 3：RCLK发生一次上升沿，把数据发出去
		GPIO_ResetBits(T595_RCLK);	
		delay_us(HC595_TIME);
		GPIO_SetBits(T595_RCLK);		
	}	
}

//初始化的时候，全部LED灯关闭
void hc595_init(void)
{
	HC595SendData(SW1_A, PIN_ALL_OFF);
	HC595SendData(SW1_B, PIN_ALL_OFF);
	HC595SendData(SW2_A, PIN_ALL_OFF);
	HC595SendData(SW2_B, PIN_ALL_OFF);
	HC595SendData(SW3_A, PIN_ALL_OFF);
	HC595SendData(SW3_B, PIN_ALL_OFF);
	HC595SendData(SW4_A, PIN_ALL_OFF);
	HC595SendData(SW4_B, PIN_ALL_OFF);
}
