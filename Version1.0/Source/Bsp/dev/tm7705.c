#include "spi.h"
#include "tm7705.h"
#include "io.h"
#include "delay.h"

#define TM7705_CS_0			TM7705_NSS0_PORT,TM7705_NSS0_PIN
#define TM7705_DRDY_0		TM7705_DRDY0_PORT,TM7705_DRDY0_PIN

#define TM7705_CS_1			TM7705_NSS1_PORT,TM7705_NSS1_PIN
#define TM7705_DRDY_1		TM7705_DRDY1_PORT,TM7705_DRDY1_PIN

void tm7705_io_config(void)
{
	GPIO_SetBits(TM7705_CS_0);
	GPIO_SetBits(TM7705_CS_1);	
}

void tm7705_init(TM7705_CHIP chip)
{
	u8 i = 0;
			
    /* set CS = 0 */
	if(chip == CHIP0)
		GPIO_ResetBits(TM7705_CS_0);
	else
		GPIO_ResetBits(TM7705_CS_1);
    delay_ms(1);
    
    /* above 32 CLK sign to reset tm7705 */
	for(i=0; i<100; i++)
	{
		spi3_readwrite_byte(0xFF);
        delay_us(100);
	}
    delay_ms(1); 

	spi3_readwrite_byte(0x20); delay_us(300); /* 写通讯寄存器,选中c时钟寄存器*/
	spi3_readwrite_byte(0x0C); delay_us(300); /* 4.9152时钟，100Hz数据更新速率 */  
	spi3_readwrite_byte(0x10); delay_us(300); /*选择设置寄存器,使用channel 1*/ 
	spi3_readwrite_byte(0x40); delay_us(300); /*写设置寄存器 ,设置成单极性、无缓冲、增益为1、滤波器工作、自校准*/
        
	spi3_readwrite_byte(0x21); delay_us(300); /* 写通讯寄存器,选中c时钟寄存器*/
	spi3_readwrite_byte(0x0C); delay_us(300); /* 4.9152时钟，20Hz数据更新速率 */  
	spi3_readwrite_byte(0x11); delay_us(300); /*选择设置寄存器,使用channel 2*/ 
	spi3_readwrite_byte(0x40); delay_us(300); /*写设置寄存器 ,设置成单极性、无缓冲、增益为1、滤波器工作、自校准*/
	
	/* set CS = 1 */
	if(chip == CHIP0)
		GPIO_SetBits(TM7705_CS_0);
	else
		GPIO_SetBits(TM7705_CS_1);

}

u16 tm7705_read_data(TM7705_CHIP chip, TM7705_CHAMNEL channel)
{
	u16 data = 0;	

	/* wait for tm7705 finish data convert */
	while(GPIO_ReadInputDataBit(TM7705_DRDY_0));    
    delay_ms(1);
    
    /* set CS = 0 */
	if(chip == CHIP0)
		GPIO_ResetBits(TM7705_CS_0);
	else
		GPIO_ResetBits(TM7705_CS_1);
    delay_ms(1);
    
    /* select channel */
	if(channel == CHANNEL0)
		spi3_readwrite_byte(0x38);
	else 
		spi3_readwrite_byte(0x39);
	delay_ms(100);    
    
	data |= spi3_readwrite_byte(0xFF);
	data = data<<8;
	data |= spi3_readwrite_byte(0xFF);

	/* set CS = 1 */
	if(chip == CHIP0)
		GPIO_SetBits(TM7705_CS_0);
	else
		GPIO_SetBits(TM7705_CS_1);
	
	return data;
}

