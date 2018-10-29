
#include "upload.h"
#include "data.h"
#include "delay.h"
#include "24cxx.h"
#include "string.h"
#include "usart.h"

Compensate_t compensate = {0};

u8 uart_tx_buf[255] ={0};
void send_result(void)
{
	
}

void comm_process(void)
{
	
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
		AT24CXX_Read(EE_OS_ADDR,compensate.open_offset,COMPENSATE_NUM); 
        AT24CXX_Read(EE_OS_ADDR+2,(u8*)&compensate.short_offset,2); 
	}

}
