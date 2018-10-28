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

	spi3_readwrite_byte(0x20); delay_us(300); /* дͨѶ�Ĵ���,ѡ��cʱ�ӼĴ���*/
	spi3_readwrite_byte(0x0C); delay_us(300); /* 4.9152ʱ�ӣ�100Hz���ݸ������� */  
	spi3_readwrite_byte(0x10); delay_us(300); /*ѡ�����üĴ���,ʹ��channel 1*/ 
	spi3_readwrite_byte(0x40); delay_us(300); /*д���üĴ��� ,���óɵ����ԡ��޻��塢����Ϊ1���˲�����������У׼*/
        
	spi3_readwrite_byte(0x21); delay_us(300); /* дͨѶ�Ĵ���,ѡ��cʱ�ӼĴ���*/
	spi3_readwrite_byte(0x0C); delay_us(300); /* 4.9152ʱ�ӣ�20Hz���ݸ������� */  
	spi3_readwrite_byte(0x11); delay_us(300); /*ѡ�����üĴ���,ʹ��channel 2*/ 
	spi3_readwrite_byte(0x40); delay_us(300); /*д���üĴ��� ,���óɵ����ԡ��޻��塢����Ϊ1���˲�����������У׼*/
	
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

