
#include "upload.h"
#include "data.h"
#include "delay.h"
#include "24cxx.h"
#include "string.h"
#include "usart.h"
#include "tim.h"

Compensate_t compensate = {0};
u8 rx4_tx_buf[255] ={0};
u8 rx4_tx_len = 0;

static u8 comm_checksum(u8 *pdata, u8 len)
{
	u8 i=0,cs=0;
	
	for(i=0; i<len+2; i++)
	{
		cs +=  *(pdata+i);
	}
	return (u8)(cs + *(pdata+i));
}

static void comm_ack(void)
{
	rx4_tx_buf[0] = 0xA5;
	rx4_tx_buf[1] = 0xA5;
	rx4_tx_len = 2;
}

static void comm_nack(void)
{
	rx4_tx_buf[0] = 0x96;
	rx4_tx_buf[1] = 0x96;
	rx4_tx_len = 2;
}

void comm_send(void)
{
	u8 i=0,checksum=0;
	if(rx4_tx_len > 2)
	{
		for(i=0; i<rx4_tx_len-1; i++ )
		{
			checksum -= rx4_tx_buf[i];
		}
	}
	uart_puts(UART4,rx4_tx_buf,rx4_tx_len);
}

void comm_user(u8 *data)
{
	u8 cmd = *(data+2);
	switch(cmd)
	{
		case USER_QUERY_FLAG:
			if(test_result.complete_flag)
			{
				rx4_tx_buf[0] = USER_HEAD;
				rx4_tx_buf[1] = 1;
				rx4_tx_buf[2] = USER_QUERY_FLAG;
				rx4_tx_buf[3] = 1;
				rx4_tx_len = 5;
			}
			break;

		case USER_RD_RESULT:
			
			break;

		case USER_WR_OFFSET:
            comm_ack();
			break;

		default:
			break;
	}
}

void comm_process(void)
{
	u8 pos=0,len=0,rx_buf[40] = {0};
	if(rx4_rec_OK)
	{
		len = rx4_data.length(&rx4_data);
		if(len)
		{
			rx4_data.read(&rx4_data,rx_buf,len);
			while( pos < len)
			{
				if( rx_buf[pos] == USER_HEAD ) break;
				pos++;
			}
			if(comm_checksum(rx_buf+pos,rx_buf[pos+1]))
			{
				comm_user(rx_buf+pos);				
			}
			else
			{
				comm_nack();
			}
			comm_send();
		}
		rx4_rec_OK = 0;
	}
}

void read_param(void)
{
	u8 temp;
    u16 i;
	temp=AT24CXX_ReadOneByte(EE_FLAG_ADDR);			   
	if(temp != EE_FLAG)
	{
		AT24CXX_WriteOneByte(EE_FLAG_ADDR,EE_FLAG);
        for(i=0;i<COMPENSATE_NUM+2;i++)
        {
            AT24CXX_WriteOneByte(EE_OS_ADDR+i,0);
        } 
	}
	else
	{
		AT24CXX_Read(EE_OS_ADDR,(u8*)&compensate.open_offset,COMPENSATE_NUM*2); 
        AT24CXX_Read(EE_OS_ADDR+84,(u8*)&compensate.short_offset,2); 
	}
}
