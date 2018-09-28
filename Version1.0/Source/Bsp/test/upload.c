
#include "upload.h"
#include "data.h"
#include "delay.h"
#include "24cxx.h"
#include "string.h"
#include "usart.h"

#define HEAD_STR        0xAA

u8 uart_tx_buf[255] ={0};

void send_result(void)
{
    u8 i=0;
    /* head */
    uart_tx_buf[0] = HEAD_STR;
    uart_tx_buf[1] = 0x55;
  
    /* send total result */
    if(test_all_result)
    {
        memcpy(&uart_tx_buf[2],FAIL_STR,4);
    }
    else
    {
        memcpy(&uart_tx_buf[2],PASS_STR,4);
    }
    
//    /* send panel result */
//    for(i=0; i<2; i++)
//    {
//        memcpy(&uart_tx_buf[6+6*i],panelresult[i].type,4);
//        memcpy(&uart_tx_buf[10+6*i],(u8*)&panelresult[i].data,2);
//    }
//    
//    /* send os result */
//    if(oserror_times == 0)
//    {
//        memcpy(&uart_tx_buf[18],PASS_STR,4);
//    }
//    else
//    {
//        memcpy(&uart_tx_buf[18],FAIL_STR,4);
//        for(i=0; i<oserror_times; i++)
//        {
//            memcpy(&uart_tx_buf[22+6*i],(u8*)&oserror[i].tp1,2);
//            memcpy(&uart_tx_buf[28+6*i],(u8*)&oserror[i].tp2,2);
//            memcpy(&uart_tx_buf[30+6*i],(u8*)&oserror[i].data,2);
//        }
//    }
    
    /* send end */
    uart_tx_buf[i] = 0xAA;
    uart_tx_buf[i+1] = 0x55;
}

#define EEPROM_FLAG_ADDR		(4095)
#define EEPROM_FLAG				(0x55)
#define EEPROM_OS_ADDR			(0)
#define EEPROM_PANEL_ADDR		(OS_COMPENSATE_NUMBER*5)
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
