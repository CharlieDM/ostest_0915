
#include "upload.h"
#include "data.h"
#include "delay.h"
#include "24cxx.h"
#include "string.h"
#include "usart.h"

u8 uart_tx_buf[255] ={0};
void send_result(void)
{
	
}

void comm_process(void)
{
	
}

void read_param(void)
{
	u8 temp,i;
	temp=AT24CXX_ReadOneByte(EEPROM_FLAG_ADDR);			   
	if(temp != EEPROM_FLAG)
	{
		for(i=0; i<EEPROM_FLAG_ADDR-1; i++)
		{
			AT24CXX_WriteOneByte(i,0);
		}
		AT24CXX_WriteOneByte(EEPROM_FLAG_ADDR,EEPROM_FLAG);
	}
	else
	{
//		AT24CXX_Read(EEPROM_OS_ADDR,(u8*)(&oscompensate.no),OS_COMPENSATE_NUMBER*5);
//		AT24CXX_Read(EEPROM_PANEL_ADDR,(u8*)(&panelcompensate.no),10);
	}

}
