
#include "upload.h"
#include "data.h"
#include "delay.h"
#include "24cxx.h"
#include "string.h"
#include "usart.h"
#include "tim.h"
#include "ostest.h"

Compensate_t compensate = {0};
u8 rx4_tx_buf[255] ={0};
u8 rx4_tx_len = 0;

static u8 comm_checksum(u8 *pdata, u16 len)
{
	u8 i=0,cs=0;
	
	for(i=0; i<len+6; i++)
	{
		cs +=  *(pdata+i);
	}
	return cs;
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
        rx4_tx_buf[i] = checksum;
	}
	uart_puts(UART4,rx4_tx_buf,rx4_tx_len);
    rx4_tx_len = 0;
}

void comm_user(u8 *data)
{
    u8 i,offset=0;
	u8 cmd = *(data+2);
    u16 value = 0;
	switch(cmd)
	{
		case USER_QUERY_FLAG:
			if(test_result.complete_flag)
			{
				rx4_tx_buf[0] = USER_HEAD;
				rx4_tx_buf[1] = 0;
                rx4_tx_buf[2] = USER_QUERY_FLAG;
                rx4_tx_buf[3] = 00;
                rx4_tx_buf[4] = 1;
				rx4_tx_buf[5] = 1;
				rx4_tx_len = 7;
			}
            else
            {
                rx4_tx_buf[0] = USER_HEAD;
				rx4_tx_buf[1] = 0;
                rx4_tx_buf[2] = USER_QUERY_FLAG;
                rx4_tx_buf[3] = 00;
                rx4_tx_buf[4] = 1;
				rx4_tx_buf[5] = 0;
				rx4_tx_len = 7;
            }
			break;

		case USER_RD_RESULT:
            rx4_tx_buf[0] = USER_HEAD;
            rx4_tx_buf[1] = 0;
            rx4_tx_buf[2] = USER_RD_RESULT;
            rx4_tx_buf[3] = 00;
            rx4_tx_buf[4] = 1+test_result.times*3;
            /* all test result */
            if(test_result.all_result)
            {
                rx4_tx_buf[5] = 0;
            }
            else
            {
                rx4_tx_buf[5] = 1;
            }
            /* test resut */
            for(i=0; i<test_result.times; i++)
            {
                rx4_tx_buf[6+3*i] = upload_result[i].tp1;
                rx4_tx_buf[6+3*i+1] = upload_result[i].tp2;
                rx4_tx_buf[6+3*i+2] = upload_result[i].data;
            }
            rx4_tx_len = 7+test_result.times*3;
			break;

		case USER_WR_OFFSET:
            offset = *(data+5);
            if(offset <= COMPENSATE_NUM + 1 && offset > 0)
            {
                AT24CXX_WriteOneByte(EE_OS_ADDR+(offset-1)*2,*(data+6));
                AT24CXX_WriteOneByte(EE_OS_ADDR+(offset-1)*2,*(data+7));
                if(offset<=COMPENSATE_NUM)
                    compensate.open_offset[i] = *(data+6)*256+*(data+7);
                else
                    compensate.short_offset = *(data+6)*256+*(data+7);
                comm_ack();
            }
            else
            {
                comm_nack();
            }
			break;
            
        case USER_RD_OFFSET: 
            offset = *(data+5);
            if(offset <= COMPENSATE_NUM + 1)
            {
                AT24CXX_Read(EE_OS_ADDR+(offset-1)*2,(u8*)&value,2); 
                rx4_tx_buf[0] = USER_HEAD;
				rx4_tx_buf[1] = 0;
                rx4_tx_buf[2] = USER_RD_OFFSET;
                rx4_tx_buf[3] = 00;
                rx4_tx_buf[4] = 1;
				rx4_tx_buf[5] = (u8)(value>>8);
                rx4_tx_buf[6] = (u8)value;
				rx4_tx_len = 8;
            }
            else
            {
                comm_nack();
            }
			break;
            
        case USER_CLEAR_OFFSET:
            for(i=0;i<COMPENSATE_NUM*2+2;i++)
            {
                AT24CXX_WriteOneByte(EE_OS_ADDR+i,0);
                compensate.open_offset[i] = 0;
            } 
            compensate.short_offset = 0;
            comm_ack();
            break;
            
        case USER_READ_POINT:
            printf("Panel_01: (%02d,%02d) - %d\n",painchain[0].point[0],painchain[0].point[1],compensate.open_offset[0]);
            printf("Panel_02: (%02d,%02d) - %d\n",painchain[1].point[0],painchain[1].point[1],compensate.open_offset[1]);
            for(i=0; i<CHAIN_50_LEN; i++)
            {         
                printf("Panel_%02d: (%02d,%02d) - %d\n",i+3,open_40_chain[i].point[0],open_40_chain[i].point[1],compensate.open_offset[i+2]);
            }
            break;
        
		default:
            comm_nack();
			break;
	}
}

void comm_process(void)
{
	u8 pos=0,rx_buf[40] = {0};
    u16 len=0,frame_len=0;
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
            frame_len |= rx_buf[pos+3];
            frame_len = (frame_len<<8) | rx_buf[pos+4];
			if(!comm_checksum(rx_buf+pos,frame_len))
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
        for(i=0;i<COMPENSATE_NUM*2+2;i++)
        {
            AT24CXX_WriteOneByte(EE_OS_ADDR+i,0);
        } 
	}
	else
	{
		AT24CXX_Read(EE_OS_ADDR,(u8*)&compensate.open_offset,COMPENSATE_NUM*2); 
        AT24CXX_Read(EE_OS_ADDR+COMPENSATE_NUM*2+2,(u8*)&compensate.short_offset,2); 
	}
}
