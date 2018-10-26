#include "spi.h"
#include "tm7705.h"

#define TM7705_CS_0			TM7705_NSS0_PIN,TM7705_NSS0_PORT
#define TM7705_DRDY_0		TM7705_DRDY0_PIN,TM7705_DRDY0_PORT

#define TM7705_CS_1			TM7705_NSS1_PIN,TM7705_NSS1_PORT
#define TM7705_DRDY_1		TM7705_DRDY1_PIN,TM7705_DRDY1_PORT

void tm7705_io_config(void)
{
	GPIO_SetBits(TM7705_CS_0);
	GPIO_SetBits(TM7705_CS_1);	
}

void tm7705_init(u8 chip)
{
	u8 i = 0;
	
	/* set CS = 0 */
	if(chip == TM7705_CHIP0)
		GPIO_ResetBits(TM7705_CS_0);
	else
		GPIO_ResetBits(TM7705_CS_1);
		
	/* above 32 CLK sign to reset tm7705 */
	for(i=0; i<40; i++)
	{
		spi3_write_byte(0xFF);
	}

	spi3_write_byte(0x20);//ͨ��1��2����(0 0 1 0 0 0 0 0),дͨѶ�Ĵ�����һ��дʱ�ӼĴ���
	spi3_write_byte(0x02);//100HZ(0 0 0 0 0 0 1 0)	 ������Ϊ2.4576MHZ������CLKDIV=0,CLK=1
	spi3_write_byte(0x10);//ͨ��1��0 0 0 1 0 0 0 0����дͨѶ�Ĵ�����һ��д���üĴ���
	spi3_write_byte(0x58);//д���üĴ��� ,���ó�˫���ԡ��޻��塢����Ϊ0���˲�����������У׼
	spi3_write_byte(0x11);//ͨ��1��0 0 0 1 0 0 0 0����дͨѶ�Ĵ�����һ��д���üĴ���
	spi3_write_byte(0x58);//д���üĴ��� ,���ó�˫���ԡ��޻��塢����Ϊ0���˲�����������У׼
	
	/* set CS = 1 */
	if(chip == TM7705_CHIP0)
		GPIO_SetBits(TM7705_CS_0);
	else
		GPIO_SetBits(TM7705_CS_1);

}

u16 tm7705_read_data(u8 chip, u8 channel)
{
	u16 data = 0;	

	/* set CS = 0 */
	if(chip == TM7705_CHIP0)
		GPIO_ResetBits(TM7705_CS_0);
	else
		GPIO_ResetBits(TM7705_CS_1);

	/* select channel */
	if(channel == TM7705_CHANNEL0)
		spi3_write_byte(0x38);
	else 
		spi3_write_byte(0x39);

	/* wait for tm7705 finish data convert */
	while(GPIO_ReadInputDataBit(TM7705_DRDY_0));
	
	data |= spi3_read_byte();
	data = data<<8;
	data |= spi3_read_byte();

	/* set CS = 1 */
	if(chip == TM7705_CHIP0)
		GPIO_SetBits(TM7705_CS_0);
	else
		GPIO_SetBits(TM7705_CS_1);
	
	return data;

}

